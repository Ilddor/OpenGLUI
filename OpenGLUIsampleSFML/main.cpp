#include <Gui.h>
#include <Button.h>
#include <SFML\Window.hpp>
//#include <gl\glew.h>

int main()
{
	sf::Window window(sf::VideoMode(800, 600), "OpenGLUI sample", sf::Style::Default, sf::ContextSettings(24, 0, 0, 3, 3));

	//glewInit();

	glui::GUI gui;

	gui.AddControl(new glui::Button());

	sf::Event event;
	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type = sf::Event::Closed)
			{
				window.close();
			}
		}

		gui.Draw();

		window.display();
	}

	return 0;
}