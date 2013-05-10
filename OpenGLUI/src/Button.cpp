#include "Button.h"

#include <string>
#include <iostream>

#define NL "\n"

void glui::Button::Draw()
{
	glBindVertexArray(m_VAOID);
	glEnableVertexAttribArray(m_VAOID);

	glUseProgram(progid);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

glui::Button::Button(void)
{
	m_VAOID = 0;
	m_vertices = 0;
	m_colors = 0;

	GLuint cos = 0;

	glGenVertexArrays(1, &cos);
	glBindVertexArray(m_VAOID);

	glGenBuffers(1, &m_vertices);
	glGenBuffers(1, &m_colors);

	GLfloat tmp[9] = {-1.f,0.f,0.f, 1.f,0.f,0.f, 0.f,1.f,0.f};
	GLfloat color[9] = {1.f,0.f,0.f, 0.f,0.f,1.f, 0.f,1.f,1.f};

	glBindBuffer(GL_ARRAY_BUFFER, m_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*9, tmp, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*9, color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	std::string vert = 
    "#version 330 core"
    NL "precision mediump float;"
    NL "layout(location = 0) in vec3 in_position;"
	NL "layout(location = 1) in vec3 in_color;"
	NL "out vec3 Color;"
    NL "void main() {"
    NL "    gl_Position = vec4(in_position, 1.0);"
	NL "	Color = in_color;"
    NL "}" NL;

    std::string frag = 
    "#version 330 core"
    NL "precision mediump float;"
	NL "in vec3 Color;"
    NL "out vec4 out_Color;"
    NL "void main() {"
    NL "    out_Color = vec4(1.0,1.0,1.0,1.0);//vec4(Color, 1.0);"
    NL "}" NL;

	vertid = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertptr = vert.c_str();
	glShaderSource(vertid, 1, &vertptr, NULL);
	glCompileShader(vertid);

	GLint compiled;
	glGetShaderiv(vertid, GL_COMPILE_STATUS, &compiled);
	if(compiled != GL_TRUE)
	{
		GLsizei slen = 0;
		std::cout << "Vertex Shader compilation error: ";
		glGetShaderiv(vertid, GL_INFO_LOG_LENGTH, &compiled);

		char* compiler_log = new char[compiled];
		glGetInfoLogARB(vertid, compiled, &slen, compiler_log);
		std::cout << compiler_log << std::endl;
		delete[] compiler_log;
	}

	fragid = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragptr = frag.c_str();
	glShaderSource(fragid, 1, &fragptr, NULL);
	glCompileShader(fragid);

	glGetShaderiv(fragid, GL_COMPILE_STATUS, &compiled);
	if(compiled != GL_TRUE)
	{
		GLsizei slen = 0;
		std::cout << "Fragment Shader compilation error: ";
		glGetShaderiv(fragid, GL_INFO_LOG_LENGTH, &compiled);

		char* compiler_log = new char[compiled];
		glGetInfoLogARB(fragid, compiled, &slen, compiler_log);
		std::cout << compiler_log << std::endl;
		delete[] compiler_log;
	}

	progid = glCreateProgram();
	glAttachShader(progid, vertid);
	glAttachShader(progid, fragid);

	glLinkProgram(progid);

	GLint linked;
	glGetProgramiv(progid, GL_LINK_STATUS, &linked);
	if(linked != GL_TRUE)
		std::cout << "Program link error: " << std::endl;
}


glui::Button::~Button(void)
{
	glDeleteBuffers(1, &m_vertices);
	glDeleteBuffers(1, &m_colors);
	glDeleteVertexArrays(1, &m_VAOID);

	glDeleteShader(vertid);
	glDeleteShader(fragid);
	glDeleteProgram(progid);
}
