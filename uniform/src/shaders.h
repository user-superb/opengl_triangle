#ifndef SHADERS_H
#define SHADERS_H
const char* vertexShaderSource = 	"#version 330 core\n"
									"layout (location = 0) in vec3 aPos;\n"
									"void main()\n"
									"{\n"
									"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
									"}\0";
const char* fragmentShaderOrangeSource = 	"#version 330 core\n"
											"out vec4 FragColor;\n"
											"void main()\n"
											"{\n"
											"   FragColor = ourColor;\n"
											"}\n\0";
const char* fragmentShaderYellowSource = 	"#version 330 core\n"
											"out vec4 FragColor;\n"
											"void main()\n"
											"{\n"
											"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
											"}\n\0";

#endif