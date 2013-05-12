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
	button.setPosition(200.f, 100.f);
	button.setSize(200.f, 50.f);

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
			}
		}

		gui.Draw();

		window.display();
	}

	return 0;
}