#pragma once
#include <GL\glew.h>
// TinyOBJloader
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <vector>

class ObjModel
{
public:

	const char* name;
	//store info for obj
	struct MeshInfo
	{
		unsigned int VAO;
		unsigned int VBO;
		unsigned int IBO;
		unsigned int indexCount;
	};

private:

	std::vector<MeshInfo> LoadModel(const char* path)
	{
		//load obj
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string err;
		bool ret = tinyobj::LoadObj(shapes, materials, err, path);

		std::vector<MeshInfo> meshInfo;
		meshInfo.resize(shapes.size());

		for (unsigned int i = 0; i < shapes.size(); ++i)
		{
			glGenVertexArrays(1, &meshInfo[i].VAO);
			glGenBuffers(1, &meshInfo[i].VBO);
			glGenBuffers(1, &meshInfo[i].IBO);
			glBindVertexArray(meshInfo[i].VAO);

			unsigned int count = shapes[i].mesh.positions.size();
			count += shapes[i].mesh.normals.size();
			count += shapes[i].mesh.texcoords.size();

			std::vector<GLfloat> vertexData;
			vertexData.reserve(count);

			vertexData.insert(vertexData.end(), shapes[i].mesh.positions.begin(), shapes[i].mesh.positions.end());
			vertexData.insert(vertexData.end(), shapes[i].mesh.normals.begin(), shapes[i].mesh.normals.end());

			meshInfo[i].indexCount = shapes[i].mesh.indices.size();

			glBindBuffer(GL_ARRAY_BUFFER, meshInfo[i].VBO);
			glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo[i].IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapes[i].mesh.indices.size() * sizeof(GLuint), shapes[i].mesh.indices.data(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);	//position
			glEnableVertexAttribArray(1);	//normals

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, (GLvoid*)(sizeof(GLfloat)*shapes[i].mesh.positions.size()));

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	}

	void Draw(std::vector<MeshInfo> meshInfo)
	{
		for (unsigned int i = 0; i < meshInfo.size(); ++i)
		{
			glBindVertexArray(meshInfo[i].VAO);
			glDrawElements(GL_TRIANGLES, meshInfo[i].indexCount, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}

	void Destroy(std::vector<MeshInfo> meshInfo)
	{
		for (unsigned int i = 0; i < meshInfo.size(); ++i)
		{
			glDeleteVertexArrays(1, &meshInfo[i].VAO);
			glDeleteBuffers(1, &meshInfo[i].VBO);
			glDeleteBuffers(1, &meshInfo[i].IBO);
			//glBindVertexArray(0);
		}
	}

};