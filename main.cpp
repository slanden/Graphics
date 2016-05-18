#define GLEW_STATIC
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>
//// TinyOBJloader
//#define TINYOBJLOADER_IMPLEMENTATION
//#include "tiny_obj_loader.h"

#include <iostream>
#include "Window.h"
#include "Shader.h"
#include "Perlin.h"
#include "ObjModel.h"
#include <vector>

//called when a key is pressed
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	// When a user presses the escape key, we set the WindowShouldClose property to true, 
//	// closing the application
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//}


int main()
{
	Window window;
	window.Init();

	///shader setup
	//create shader
	Shader shader("./shaders/simpleShader.vert", "./shaders/simpleShader.frag");
	Shader perlinShader("./shaders/PerlinNoise.vert", "./shaders/PerlinNoise.frag");


	///drawing
	//mesh
	GLfloat verts[] = {
		0.5f,  0.5f, 0.0f,   // Top Right
		0.5f, -0.5f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};
	GLuint indices[] = {
		0, 1, 3,		  // First Triangle
		1, 2, 3			  // Second Triangle
	};

	std::vector<Vertex> verties;
	std::vector<GLuint> indies;

	int rows, cols;
	rows = cols = 64;
	GenGrid(rows, cols, verties, indies);

	//needs 1 element for every vertex in grid, in this case it will be an octave of 32
	int dims = 64;
	float *pData = new float[dims * dims];
	float scale = (1.0 / dims) * 3;
	int octaves = 6;

	for (int x = 0; x < dims; ++x)
	{
		for (int y = 0; y < dims; ++y)
		{
			float amplitude = 1.0f;
			float persistence = 0.3f;

			pData[y * dims + x] = 0;
			for (int o = 0; o < octaves; ++o)
			{
				float freq = powf(2, (float)o);
				float perlin_sample = glm::perlin(vec2((float)x, (float)y) * scale * freq) * 0.5f + 0.5f;
				pData[y * dims + x] += perlin_sample * amplitude;
				amplitude *= persistence;
			}
			
		}
	}
	
	std::cout << "Vertices: " << verties.size() << std::endl;
	std::cout << "Indicies: " << indies.size() << std::endl;
	

#pragma region tinyobj
	////load obj
	//std::vector<tinyobj::shape_t> shapes;
	//std::vector<tinyobj::material_t> materials;

	//std::string err;
	//bool ret = tinyobj::LoadObj(shapes, materials, err, "./models/bunny.obj");

	////create buffers for obj
	//void createOpenGLBuffers(std::vector<tinyobj::shape_t>&shapes);


	////store info for obj
	//struct ModelInfo
	//{
	//	unsigned int VAO;
	//	unsigned int VBO;
	//	unsigned int IBO;
	//	unsigned int indexCount;
	//};

	////vector of obj infos
	//std::vector<ModelInfo> modelInfo;

	/*modelInfo.resize(shapes.size());*/

	//for (unsigned int i = 0; i < shapes.size(); ++i)
	//{
	//	glGenVertexArrays(1, &modelInfo[i].VAO);
	//	glGenBuffers(1, &modelInfo[i].VBO);
	//	glGenBuffers(1, &modelInfo[i].IBO);
	//	glBindVertexArray(modelInfo[i].VAO);

	//	unsigned int count = shapes[i].mesh.positions.size();
	//	count += shapes[i].mesh.normals.size();
	//	count += shapes[i].mesh.texcoords.size();

	//	std::vector<GLfloat> vertexData;
	//	vertexData.reserve(count);

	//	vertexData.insert(vertexData.end(), shapes[i].mesh.positions.begin(), shapes[i].mesh.positions.end());
	//	vertexData.insert(vertexData.end(), shapes[i].mesh.normals.begin(), shapes[i].mesh.normals.end());

	//	modelInfo[i].indexCount = shapes[i].mesh.indices.size();

	//	glBindBuffer(GL_ARRAY_BUFFER, modelInfo[i].VBO);
	//	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);

	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelInfo[i].IBO);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapes[i].mesh.indices.size() * sizeof(GLuint), shapes[i].mesh.indices.data(), GL_STATIC_DRAW);

	//	glEnableVertexAttribArray(0);	//position
	//	glEnableVertexAttribArray(1);	//normals

	//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, (GLvoid*)(sizeof(GLfloat)*shapes[i].mesh.positions.size()));

	//	glBindVertexArray(0);
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//}
#pragma endregion


#pragma region triangles
	////buffer objects
	//GLuint VBO, VAO, EBO;
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	//glGenVertexArrays(1, &VAO);

	////1. bind vertex array object
	//glBindVertexArray(VAO);
	////2. copy verts into bufffer
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	////3. copy index array in element buffer
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	////4. set vertex attribute pointers
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	////5. unbind VAO.  Don't unbind EBO before unbinding VAO
	//glBindVertexArray(0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#pragma endregion

#pragma region perlin
	//buffer objects
	GLuint VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	//1. bind vertex array object
	glBindVertexArray(VAO);
	//2. copy verts into bufffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verties.size(), verties.data(), GL_STATIC_DRAW);
	//3. copy index array in element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indies.size(), indies.data(), GL_STATIC_DRAW);
	//4. set vertex attribute pointers
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);
	// texcoords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(vec4));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//5. unbind VAO.  Don't unbind EBO before unbinding VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#pragma endregion

	///texture
	GLuint perlinTexture;
	glGenTextures(1, &perlinTexture);
	glBindTexture(GL_TEXTURE_2D, perlinTexture);
	//bind data as float for single channel
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, cols, rows, 0, GL_RED, GL_FLOAT, pData/*verties.data()*/);

	// enable blending else samples must be "exact" centre of texels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// set wrap to stop errors at edge of noise sampling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);



 
	//projection = glm::ortho(0.0f, (GLfloat)WINDOW_WIDTH, 0.0f, (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
	glm::mat4 modelMat, viewMat, projMat;
	//projMat = glm::perspective(glm::pi<float>()*0.25f, 16 / 9.f, 0.1f, 1000.f);
	projMat = glm::perspective(glm::radians(45.0f), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 1000.0f);	
	//viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -25.0f));
	viewMat = glm::lookAt(glm::vec3(2.0, 45.0, 100.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	//projMat = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

	perlinShader.Use();
	GLuint projID = glGetUniformLocation(perlinShader.Program, "Projection");
	GLuint viewID = glGetUniformLocation(perlinShader.Program, "View");
	glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(projID, 1, GL_FALSE, glm::value_ptr(projMat));

	int texUniform = glGetUniformLocation(perlinShader.Program, "noiseTex");
	glUniform1i(texUniform, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, perlinTexture);

	//modelMat = glm::scale(modelMat, glm::vec3(5.0, 5.0, 5.0));
	//modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//game loop
	while (!glfwWindowShouldClose(window.getHandle()))
	{
		glClearColor(0.25f, 0.25f, 0.25f, 1);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		///enable this to draw in wireframe mode. 
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		///enable this to return to fill mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		///draw triangles
		//shader.Use();

		//get uniforms for shader	
		GLuint modelID = glGetUniformLocation(perlinShader.Program, "Model");
		//pass uniforms to shaders
		glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(modelMat));

		//modelMat = glm::rotate(modelMat, glm::radians(-55.0f) * .06f, glm::vec3(0.0f, 1.0f, 0.0f));
		

		//draw
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indies.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		////tinyobj
		//for (unsigned int i = 0; i < modelInfo.size(); ++i)
		//{
		//	glBindVertexArray(modelInfo[i].VAO);
		//	glDrawElements(GL_TRIANGLES, modelInfo[i].indexCount, GL_UNSIGNED_INT, 0);
		//	glBindVertexArray(0);
		//}
		

		glfwSwapBuffers(window.getHandle());
		glfwPollEvents();
	}
	///de-allocate resources

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//tinyobj
	//for (unsigned int i = 0; i < modelInfo.size(); ++i)
	//{
	//	glDeleteVertexArrays(1, &modelInfo[i].VAO);
	//	glDeleteBuffers(1, &modelInfo[i].VBO);
	//	glDeleteBuffers(1, &modelInfo[i].IBO);
	//	//glBindVertexArray(0);
	//}

	delete[] pData;

	glfwTerminate();
	return 0;
}