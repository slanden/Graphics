#define GLEW_STATIC
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// TinyOBJloader
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <iostream>
#include "Window.h"
#include "Shader.h"

////called when a key is pressed
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
#pragma region oldInitWindowCode
	////initialize glfw
	//glfwInit();
	////set glfw options
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	////create a window object
	//GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	//if (window == nullptr)
	//{
	//	std::cout << "Failed to create GLFW window" << std::endl;
	//	glfwTerminate();
	//	return -1;
	//}
	//glfwMakeContextCurrent(window);

	////set callback functions
	//glfwSetKeyCallback(window, key_callback);

	//
	////glewExperimental ensures GLEW uses more modern techniques for managing OpenGL functionality.
	//glewExperimental = GL_TRUE;
	////initialize GLEW.
	//if (glewInit() != GLEW_OK)
	//{
	//	std::cout << "Failed to initialize GLEW" << std::endl;
	//	return -1;
	//}

	////define the viewport to transform processed coordinates from
	////the -1 to 1 range to screen coordinates
	//glViewport(0, 0, 800, 600);
#pragma endregion


	///shader setup
	//create shader
	Shader shader("./shaders/simpleShader.vert", "./shaders/simpleShader.frag");


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

#pragma region tinyobj
	//load obj
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(shapes, materials, err, "./models/bunny.obj");

	////create buffers for obj
	//void createOpenGLBuffers(std::vector<tinyobj::shape_t>&shapes);


	////store info for obj
	//struct GLInfo
	//{
	//	unsigned int VAO;
	//	unsigned int VBO;
	//	unsigned int IBO;
	//	unsigned int indexCount;
	//};

	////vector of obj infos
	//std::vector<GLInfo> glInfo;

	//glInfo.resize(shapes.size());

	//for (unsigned int i = 0; i < shapes.size(); ++i)
	//{
	//	glGenVertexArrays(1, &glInfo[i].VAO);
	//	glGenBuffers(1, &glInfo[i].VBO);
	//	glGenBuffers(1, &glInfo[i].IBO);
	//	glBindVertexArray(glInfo[i].VAO);

	//	unsigned int count = shapes[i].mesh.positions.size();
	//	count += shapes[i].mesh.normals.size();
	//	count += shapes[i].mesh.texcoords.size();

	//	std::vector<GLfloat> vertexData;
	//	vertexData.reserve(count);

	//	vertexData.insert(vertexData.end(), shapes[i].mesh.positions.begin(), shapes[i].mesh.positions.end());
	//	vertexData.insert(vertexData.end(), shapes[i].mesh.normals.begin(), shapes[i].mesh.normals.end());

	//	glInfo[i].indexCount = shapes[i].mesh.indices.size();

	//	glBindBuffer(GL_ARRAY_BUFFER, glInfo[i].VAO);
	//	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);

	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glInfo[i].IBO);
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
	//buffer objects
	GLuint VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	//1. bind vertex array object
	glBindVertexArray(VAO);
	//2. copy verts into bufffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	//3. copy index array in element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//4. set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//5. unbind VAO.  Don't unbind EBO before unbinding VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#pragma endregion

	//glEnable(GL_DEPTH_TEST);


	//projection matrix doesn't change so we don't include it in the loop

 
	//projection = glm::ortho(0.0f, (GLfloat)WINDOW_WIDTH, 0.0f, (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
	glm::mat4 modelMat, viewMat, projMat;
	projMat = glm::perspective(glm::radians(45.0f), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
	viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
	//projMat = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
	shader.Use();
	GLuint projID = glGetUniformLocation(shader.Program, "Projection");
	GLuint viewID = glGetUniformLocation(shader.Program, "View");
	glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(projID, 1, GL_FALSE, glm::value_ptr(projMat));
	//game loop
	while (!glfwWindowShouldClose(window.getHandle()))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT*/);

		///enable this to draw in wireframe mode. 
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		///enable this to return to fill mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		///draw triangles
		//shader.Use();


		//get uniforms for shader
		
		
		//pass uniforms to shaders	
	
		GLuint modelID = glGetUniformLocation(shader.Program, "Model");
		glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(modelMat));

		modelMat = glm::rotate(modelMat, glm::radians(-55.0f) * .16f, glm::vec3(1.0f, 0.0f, 0.0f));

		//draw
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//tinyobj
		/*
		for (unsigned int i = 0; i < glInfo.size(); ++i)
		{
			glBindVertexArray(glInfo[i].VAO);
			glDrawElements(GL_TRIANGLES, glInfo[i].indexCount, GL_UNSIGNED_INT, 0);
			//glBindVertexArray(0);
		}
		*/

		glfwSwapBuffers(window.getHandle());
	}
	//de-allocate resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}