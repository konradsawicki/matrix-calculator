
#include "MatrixCalculator.h"


void MatrixCalculator::InitWindow()
{
    m_Window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Path Finding", sf::Style::Close);
    m_Window->setFramerateLimit(120);
}

void MatrixCalculator::InitBackground()
{

}

void MatrixCalculator::InitGui()
{

}

MatrixCalculator::MatrixCalculator()
{
    std::cout << "Starting App!\n";
    InitWindow();
}

MatrixCalculator::~MatrixCalculator()
{
    delete m_Window;

    std::cout << "Ending App!\n";
}

void MatrixCalculator::UpdateSFMLEvents()
{
	while (m_Window->pollEvent(m_Event))
	{
		switch (m_Event.type)
		{
		case sf::Event::Closed:
			m_Window->close();
			break;

		case sf::Event::MouseButtonReleased:
			if (m_Event.mouseButton.button == sf::Mouse::Left)
			{

			}
			break;
		}
	}
}

void MatrixCalculator::Update()
{
	UpdateSFMLEvents();
}

void MatrixCalculator::Render()
{
    m_Window->clear();

    m_Window->display();
}

void MatrixCalculator::Run()
{
    while (m_Window->isOpen())
    {
        Update();
        Render();
    }
}
