#ifndef SHADERS_H
#define SHADERS_H
const char* vertexShaderSource = 	"#version 330 core\n"
									"layout (location = 0) in vec3 aPos;\n"
									"layout (location = 1) in vec3 aColor;\n"
									"out vec3 ourColor;\n"
									"void main()\n"
									"{\n"
									"   gl_Position = vec4(aPos, 1.0);\n"
									"	ourColor	= aColor;\n"
									"}\0";

const char* fragmentShaderSource = 	"#version 330 core\n"
									"out vec4 FragColor;\n"
									"in vec3 ourColor;\n"
									"void main()\n"
									"{\n"
									"   FragColor = vec4(ourColor, 1.0);\n"
									"}\n\0";
											
#endif