#include "Game.h"

RenderWindow window(VideoMode(800, 600), "Sudoku", sf::Style::Titlebar | sf::Style::Close);

Game::Game()
{
	state = END;

	if (!font.loadFromFile("Sud0ku\\Fonts\\sfns-display-bold"))
		return;

	state = MENU;
}
void Game::run()
{
	while (state != END)
	{
		switch (state)
		{
		case GameState::MENU:
			menu();
			break;
		case GameState::GAME:
			levels();
			break;
		}
	}
}
void Game::menu()
{
	Text title("Sudoku", font, 80);
	title.setStyle(Text::Bold);

	title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 60);

	const int x = 3;

	Text text[x];

	string str[] = { "Play","Exit" };
	for (int i = 0; i < x; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(65);

		text[i].setString(str[i]);
		text[i].setPosition(800 / 2 - text[i].getGlobalBounds().width / 2, 200 + i * 120);
	}

	while (state == MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;

		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;
                                       
			else if (text[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GAME;
			}

			else if (text[2].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = END;
			}
		}
		for (int i = 0; i < x; i++)
			if (text[i].getGlobalBounds().contains(mouse))
				text[i].setColor(Color::Red);
			else text[i].setColor(Color::White);

		window.clear();

		window.draw(title);
		for (int i = 0; i < x; i++)
			window.draw(text[i]);

		window.display();
	}
}
void Game::levels()
{
	sf::Text title("Levels", font, 90);
	title.setStyle(sf::Text::Bold);

	title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 30);
	title.setStyle(sf::Text::Bold);

	string easy, medium, hard;
	const int x = 4;

	sf::Text text[x];

	std::string levels[] = { "Easy","Medium","Hard", "back" };
	for (int i = 0; i < x; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(65);
		text[i].setString(levels[i]);
		text[i].setPosition(800 / 2 - text[i].getGlobalBounds().width / 2, 150 + i * 120);
	}


	while (state == GAME && window.isOpen())
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;
		Sudoku sudoku;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (text[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if (sudoku.run(window, 0))
					state = GAME;
				else
					state = MENU;
			}

			else if (text[1].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				if (sudoku.run(window, 1))
					state = GAME;
				else
					state = MENU;
			}

			else if (text[2].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				if (sudoku.run(window, 2))
					state = GAME;
				else
					state = MENU;
			}

			else if (text[3].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				state = MENU;
			}
		}

		for (int i = 0; i < x; i++)
			if (text[i].getGlobalBounds().contains(mouse))
				text[i].setColor(Color::Red);
			else text[i].setColor(Color::White);


		window.clear();
		window.draw(title);
		for (int i = 0; i < x; i++)
			window.draw(text[i]);
		window.display();
	}

}
