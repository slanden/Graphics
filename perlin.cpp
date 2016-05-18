////#define GLM_FORCE_PURE
//#include <vector>
////#include "stdio.h"
////#include <gl_core_4_4.h>
////#include <GLFW/glfw3.h> 
//#include <glm/fwd.hpp>
//#include <glm\glm.hpp>
//#include <glm\ext.hpp>
////#include <iostream>
////#include <fstream>
////#include <string> 
////
///////added
////#define GLEW_STATIC
////// GLM
////#include <glm/gtc/matrix_transform.hpp>
////#include <glm/gtc/type_ptr.hpp>
////
////
//using glm::vec3;
//using glm::vec4;
////using glm::mat4;
////using namespace std;
////
////
////
////
////#define BUFFER_OFFSET(i) ((char *)NULL + (i))
////
////unsigned int m_VAO, m_VBO, m_IBO;
////unsigned int m_shader;
//struct Vertex 
//{
//	vec4 position;
//};
//
////void generateGrid(unsigned int rows, unsigned int cols, std::vector<vec3> &, std::vector<int>&);
//// function to create a grid
//void GenerateGrid(unsigned int rows, unsigned int cols, std::vector<vec3> &verts, std::vector<int> &indices)
//{
//	for (unsigned int r = 0; r < rows; ++r) {
//		for (unsigned int c = 0; c < cols; ++c)
//		{
//			verts.push_back(vec3((float)c, 0, (float)r));
//		}
//	}
//
//	// defining index count based off quad count (2 triangles per quad)
//	unsigned int index = 0;
//	for (unsigned int r = 0; r < (rows - 1); ++r)
//	{
//		for (unsigned int c = 0; c < (cols - 1); ++c)
//		{
//			int p0 = r * cols + c;
//			int p1 = (r + 1) * cols + c;
//			int p2 = (r + 1) * cols + (c + 1);
//			int p3 = r * cols + c;
//			int p4 = (r + 1) * cols + (c + 1);
//			int p5 = r * cols + (c + 1);
//			indices.push_back(p0);
//			indices.push_back(p1);
//			indices.push_back(p2);
//			indices.push_back(p3);
//			indices.push_back(p4);
//			indices.push_back(p5);
//
//		}
//	}
//
//}
//
////string LoadShader(std::string file)
////{
////	string line, shader;
////	ifstream inFile(file);
////	if (inFile.is_open())
////		while (getline(inFile, line))
////		{
////			shader.append(line);
////			shader.append("\n");
////		}
////	inFile.close();
////	return shader;
////}
////
//////Setup some geometry to draw
//////MyVertex will be the storage container for our vertex information
////static const GLfloat cube_vertices[] =
////{
////	// front
////	-1.0, -1.0,  1.0,//0
////	1.0, -1.0,  1.0, //1
////	1.0,  1.0,  1.0, //2
////	-1.0,  1.0,  1.0,//3
////					 // back
////	-1.0, -1.0, -1.0,//4
////	1.0, -1.0, -1.0, //5
////	1.0,  1.0, -1.0, //6
////	-1.0,  1.0, -1.0,//7
////};
////
////// RGB color triples for every coordinate above.
////static const GLfloat cube_colors[] = {
////	// front colors
////	1.0, 0.0, 0.0,//0
////	0.0, 1.0, 0.0,//1
////	0.0, 0.0, 1.0,//2
////	1.0, 1.0, 1.0,//3
////				  // back colors
////	1.0, 0.0, 0.0,//4
////	0.0, 1.0, 0.0,//5
////	0.0, 0.0, 1.0,//6
////	1.0, 1.0, 1.0,//7
////};
////
////unsigned int cube_elements[] =
////{
////	// front
////	0, 1, 2,
////	2, 3, 0,
////	// top
////	1, 5, 6,
////	6, 2, 1,
////	// back
////	7, 6, 5,
////	5, 4, 7,
////	// bottom
////	4, 0, 3,
////	3, 7, 4,
////	// left
////	4, 5, 1,
////	1, 0, 4,
////	// right
////	3, 2, 6,
////	6, 7, 3,
////};
////
////int main()
////{
////	//Now we put it on the graphics card
////	//generate your buffer on the graphics card
////	//this contains all the vertices
////	vector<vec3> plane;
////	vector<int> indices;
////
////	generateGrid(5, 5, plane, indices);
////
////
////	int numVertices = plane.size();
////	int numColors = sizeof(cube_colors) / sizeof(GLfloat);
////	int vertOffset = plane.size() * sizeof(vec3);
////	int colorOffset = numColors * sizeof(cube_colors);
////
////	//int numIndices = sizeof(cube_elements) / sizeof(unsigned int);
////	int numIndices = indices.size();
////
////	printf("numVertices: %d \n", numVertices);
////	printf("numColors: %d \n", numColors);
////	printf("numIndices: %d \n", numIndices);
////
////
////
////	glGenBuffers(1, &m_IBO);
////	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
////	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
////		indices.size() * sizeof(int),
////		indices.data(),
////		GL_STATIC_DRAW);
////	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
////
////	glGenBuffers(1, &m_VBO);
////	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
////	glBufferData(GL_ARRAY_BUFFER,
////		vertOffset + colorOffset,
////		NULL,
////		GL_STATIC_DRAW);
////
////	glBufferSubData(GL_ARRAY_BUFFER,
////		0,
////		plane.size() * sizeof(vec3),
////		plane.data());
////	glBufferSubData(GL_ARRAY_BUFFER, vertOffset, colorOffset, &cube_colors[0]);
////
////
////
////	glGenVertexArrays(1, &m_VAO);
////	glBindVertexArray(m_VAO);
////	glEnableVertexAttribArray(0);
////	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
////
////	glEnableVertexAttribArray(1);
////	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)vertOffset);
////	//unbind now that we have generated and populated
////
////
////
////
////	glBindBuffer(GL_ARRAY_BUFFER, 0);
////	glBindVertexArray(0);
////}