#include <Gui.h>
#include <Button.h>
#include <SFML\Window.hpp>
#include <gtc\matrix_transform.hpp>

#include <iostream>

int main()
{
	sf::Window window(sf::VideoMode(800, 600), "OpenGLUI sample", sf::Style::Default, sf::ContextSettings(24, 0, 0, 3, 3));

	glui::GUI gui;

	glm::mat4 projection = glm::mat4(1.f);
	glm::mat4 view = glm::mat4(1.f);

	projection *= glm::ortho(0.f, 800.f, 600.f, 0.f);
	gui.setProjectionMatrix(projection);
	gui.setViewMatrix(view);

	glui::Button button;
	button.setPosition(100.f, 50.f);
	button.setSize(600.f, 500.f);
	button.setFunction([&](){
		button.setPosition(10.f, 10.f);
	});

	gui.AddControl(&button);

	sf::Event event;
	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed :
				window.close();
				break;
			case sf::Event::Resized :
				break;
			case sf::Event::MouseButtonPressed :
				gui.MousePress(event.mouseButton.x, event.mouseButton.y);
				break;
			}
		}
		glClearColor(0.f,0.f,0.f,1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER);

		/*glBegin(GL_QUADS);
			glColor3f(1.f,1.f,1.f);
			glVertex3f(1.f,1.f,0.f);
			glVertex3f(1.f,-1.f,0.f);
			glVertex3f(-1.f,-1.f,0.f);
			glVertex3f(-1.f,1.f,0.f);
		glEnd();*/

		glFlush();

		gui.Draw();

		window.display();
	}

	return 0;
}