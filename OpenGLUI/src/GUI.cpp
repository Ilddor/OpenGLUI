#include "Gui.h"
#include "..\stdafx.h"

#include <iostream>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#define NL "\n"

void glui::GUI::_ClearFocus()
{
	if(m_ControlWithFocus != nullptr)
		m_ControlWithFocus->setFocus(false);
	m_ControlWithFocus = nullptr;
}

void glui::GUI::Draw()
{
	glUseProgram(m_Program);
	for(auto it: m_Controls)
	{
		it->Draw();
	}
}

void glui::GUI::AddControl(Control* control)
{
	m_Controls.insert(control);
}

void glui::GUI::setProjectionMatrix(glm::mat4 projection)
{
	m_Projection = projection;
}

void glui::GUI::setViewMatrix(glm::mat4 view)
{
	m_View = view;
}

glui::GUI::GUI()
{
	glewInit();

	std::string vert = 
    "#version 330 core"
    NL "precision mediump float;"
    NL "layout(location = 0) in vec2 in_position;"
	NL "layout(location = 1) in vec3 in_color;"
	NL "uniform mat4 Projection, View;"
	NL "out vec3 Color;"
    NL "void main() {"
    NL "    gl_Position = Projection * View * vec4(in_position, 0.0, 1.0);"
	NL "	Color = in_color;"
    NL "}" NL;

    std::string frag = 
    "#version 330 core"
    NL "precision mediump float;"
	NL "in vec3 Color;"
    NL "out vec4 out_Color;"
    NL "void main() {"
    NL "    out_Color = vec4(Color, 1.0);"
    NL "}" NL;

	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertptr = vert.c_str();
	glShaderSource(m_VertexShader, 1, &vertptr, 0);
	glCompileShader(m_VertexShader);

	GLint info;
	glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &info);
	if(info != GL_TRUE)
	{
		GLsizei slen = 0;
		glGetShaderiv(m_VertexShader, GL_INFO_LOG_LENGTH, &info);
		char* compiler_log = new char[info];
		glGetInfoLogARB(m_VertexShader, info, &slen, compiler_log);
		std::cerr << "Vertex Shader compilation error: " << compiler_log << std::endl;
		delete[] compiler_log;
	}

	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragptr = frag.c_str();
	glShaderSource(m_FragmentShader, 1, &fragptr, 0);
	glCompileShader(m_FragmentShader);

	glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &info);
	if(info != GL_TRUE)
	{
		GLsizei slen = 0;
		glGetShaderiv(m_FragmentShader, GL_INFO_LOG_LENGTH, &info);
		char* compiler_log = new char[info];
		glGetInfoLogARB(m_FragmentShader, info, &slen, compiler_log);
		std::cerr << "Fragment Shader compilation error: " << compiler_log << std::endl;
		delete[] compiler_log;
	}

	m_Program = glCreateProgram();
	glAttachShader(m_Program, m_VertexShader);
	glAttachShader(m_Program, m_FragmentShader);

	glLinkProgram(m_Program);

	glGetProgramiv(m_Program, GL_LINK_STATUS, &info);
	if(info != GL_TRUE)
	{
		GLsizei slen = 0;
		glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &info);
		char* linker_log = new char[info];
		glGetInfoLogARB(m_Program, info, &slen, linker_log);
		std::cerr << "Program linking error: " << linker_log << std::endl;
		delete[] linker_log;
	}

	proj = glGetUniformLocation(m_Program, "Projection");
	glUseProgram(m_Program);
	glUniformMatrix4fv(proj, 1, GL_FALSE, glm::value_ptr(m_Projection));

	view = glGetUniformLocation(m_Program, "View");
	glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(m_View));
}


glui::GUI::~GUI()
{
}
