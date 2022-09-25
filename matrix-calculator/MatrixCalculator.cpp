
#include "MatrixCalculator.h"

void MatrixCalculator::InitWindow()
{
    m_Window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Path Finding", sf::Style::Close);
    m_Window->setFramerateLimit(120);
}

void MatrixCalculator::InitBackground()
{
	m_BackgroundTexture.loadFromFile("Images/bg.png");
	m_Background.setSize(sf::Vector2f(m_Window->getSize().x, m_Window->getSize().y));
	m_BackgroundTexture.loadFromFile("Images/bg.png");
	m_Background.setTexture(&m_BackgroundTexture);
}

void MatrixCalculator::InitGui()
{
	//m_Textbox = new gui::TextBox(15, sf::Color::Black, {300, 100}, {70, 25});
	for (int i = 1; i < 3; i++)
	{
		for (int j = 1; j < 3; j++)
			m_Matrix.push_back(new gui::TextBox(15, sf::Color::Black, { i * 150.f, j * 100.f }, { 70, 25 }));
	}
}

MatrixCalculator::MatrixCalculator()
	: m_ActiveFlag(false), m_ActiveTextbox(nullptr)
{
    std::cout << "Starting Matrix Calculator!\n";
    InitWindow();
	InitBackground();
	InitGui();
}

MatrixCalculator::~MatrixCalculator()
{
    delete m_Window;
	for (auto& e : m_Matrix)
	{
		delete e;
	}

    std::cout << "Ending Matrix Calculator!\n";
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
				for (auto e : m_Matrix)
				{
					if (e->Contains(m_MousePos))
					{
						if (m_ActiveTextbox)
							m_ActiveTextbox->Select(false);
						m_ActiveTextbox = e;
						m_ActiveTextbox->Select(true);
					}
					if (m_ActiveTextbox)
					{
						if (!m_ActiveTextbox->Contains(m_MousePos))
						{
							m_ActiveTextbox->Select(false);
						}
					}
				}
			}
			break;

		case sf::Event::TextEntered:
			if (m_ActiveTextbox)
				m_ActiveTextbox->Type(m_Event);
			break;
		}
	}
}

void MatrixCalculator::UpdateGui()
{
	for (auto e : m_Matrix)
		e->Update();
}

void MatrixCalculator::UpdateMousePosition()
{
	m_MousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_Window));;
}

void MatrixCalculator::Update()
{
	UpdateMousePosition();
	UpdateSFMLEvents();
	UpdateGui();
}

void MatrixCalculator::Render()
{
    m_Window->clear();

	m_Window->draw(m_Background);

	for (auto e : m_Matrix)
		e->Render(m_Window);

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
