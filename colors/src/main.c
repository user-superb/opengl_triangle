#include <stdio.h>
#include <math.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "shaders.h"

#define SRC_WIDTH 1280
#define SRC_HEIGHT 720

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {
	// glfw: init and configuration
	// ----------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw: window creation
	// ---------------------
	GLFWwindow *window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "Title", NULL, NULL);
	if (!window) {
		printf("Failed to init the window.\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all opengl functions
	// -------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to init GLAD.\n");
		return -1;
	}

	// gl: init
	// --------
	glViewport(0, 0, SRC_WIDTH, SRC_HEIGHT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	GLint success = 1;
	char infoLog[512];

	// gl: vertexShader
	// ----------------
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// vertexShader: compilation error checking
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, 0, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION. \n%s\n", infoLog);
	}

	// gl: fragmentShader
	// ------------------
	GLuint fragmentShader;
	// gl: fragmentShader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// fragmentShader: compilation error checking
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, 0, infoLog);
		printf("ERROR::SHADER::FRAGMENT::FRAGMENTSHADER_ORANGE::COMPILATION. \n%s\n", infoLog);
	}
	
	// gl: shaderProgram
	// -----------------
	GLuint shaderProgram;
	// shaderProgram
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// shaderProgram: linking error checking
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, 0, infoLog);
		printf("ERROR::SHADERPROGRAM::SHADERPROGRAM_ORANGE::LINKING. \n%s\n", infoLog);
	}

	// shaderProgram: cleanup
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// gl: Vertex Array Object
	// -----------------------
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	// Bind VAO first, and then VBO later
	glBindVertexArray(VAO);

	// gl: Vertex Buffer Object
	// ------------------------
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	GLfloat vertices[] = {
		// Coordinates		// Colors
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f
	};
	GLuint indices[] = {
		0, 1, 2,
	};
	// gl: Element Buffer Object
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// GLfloat array[] = {X, Y, Z, R, G, B, ...};

	// render_loop
	// -----------
	float 	time,
			color_value;
	// Updating an uniform variable requieres to the program that is linked to be used first
	while (!glfwWindowShouldClose(window)) {
		// gl: render
		glClear(GL_COLOR_BUFFER_BIT); // cleans the screen with the color defined with glClearColor();

		// gl: draw
		glUseProgram(shaderProgram);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, NULL);

		// glfw: swap buffers and polls IO events (windows events or keys pressed)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: cleanup
	glfwTerminate();
	return 0;
}
