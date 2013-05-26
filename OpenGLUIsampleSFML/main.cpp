#include <Gui.h>
#include <Button.h>
#include <Label.h>
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
	button.setPosition(10.f, 50.f);
	button.setSize(200.f, 50.f);
	button.setFunction([&](){
		button.setPosition(10.f, 10.f);
	});

	glui::Font font;
	font.loadFromFile("arial.ttf");

	glui::Label label;
	label.setFont(&font);
	label.setPosition(100.f, 100.f);
	label.setSize(100.f, 25.f);
	label.setText(L"Hello World");

	gui.AddDrawableObject(&button);
	gui.AddDrawableObject(&label);

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

		glBegin(GL_QUADS);
			glColor3f(0.f,0.f,0.f);
			glVertex3f(1.f,1.f,0.f);
			glVertex3f(1.f,-1.f,0.f);
			glVertex3f(-1.f,-1.f,0.f);
			glVertex3f(-1.f,1.f,0.f);
		glEnd();	//don't know why glClear doesn't work so i use this to clear buffer:P
		glFlush();

		gui.Draw();

		window.display();
	}

	return 0;
}