#include <Gui.h>
#include <Button.h>
#include <SFML\Window.hpp>
//#include <gl\glew.h>

#include <iostream>

int main()
{
	sf::Window window(sf::VideoMode(800, 600), "OpenGLUI sample", sf::Style::Default, sf::ContextSettings(24, 0, 0, 3, 3));

	//glewInit();

	glui::GUI gui;

	glViewport(0,0,800,600);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glui::Button button;
	button.setPosition(0.f, 0.f);
	button.setSize(0.5f, 0.5f);

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
				glViewport(0,0,event.size.width,event.size.height);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(0, 800, 600, 0, -100, 100);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				break;
			}
		}

		gui.Draw();

		window.display();
	}

	return 0;
}