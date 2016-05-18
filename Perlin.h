#pragma once
#include <glm\glm.hpp>

#include <vector>
using glm::vec2;
using glm::vec4;

struct Vertex
{
	vec4 position;
	vec2 texCoord;
};

//void generateGrid(unsigned int rows, unsigned int cols, std::vector<vec3> &, std::vector<int>&);
// function to create a grid
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

void GenGrid(unsigned int rows, unsigned int cols, std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
{
	vertices.resize(rows * cols);
	for (unsigned int r = 0; r < rows; ++r)
	{
		for (unsigned int c = 0; c < cols; ++c)
		{
			Vertex v;
			//v.position = vec4((float)c, 0, (float)r, 1.0f);
			//vertices.push_back(v);
			vertices[r * cols + c].position = vec4(c - cols * 0.5f, 0, r - rows * 0.5f, 1);
			vertices[r * cols + c].texCoord = vec2(c * (1.f / cols), r * (1.f / rows));
			//vertices.push_back(v);
		}
	}

	// defining index count based off quad count (2 triangles per quad)
	unsigned int index = 0;
	for (unsigned int r = 0; r < (rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (cols - 1); ++c)
		{
			int p0 = r * cols + c;
			int p1 = (r + 1) * cols + c;
			int p2 = (r + 1) * cols + (c + 1);
			int p3 = r * cols + c;
			int p4 = (r + 1) * cols + (c + 1);
			int p5 = r * cols + (c + 1);
			indices.push_back(p0);
			indices.push_back(p1);
			indices.push_back(p2);
			indices.push_back(p3);
			indices.push_back(p4);
			indices.push_back(p5);
	
		}
	}
}