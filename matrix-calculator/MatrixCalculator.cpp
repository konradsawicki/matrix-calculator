
#include "MatrixCalculator.h"

void MatrixCalculator::InitWindow()
{
    m_Window = new sf::RenderWindow(sf::VideoMode(1280+100, 720+100), "Matrix Calculator", sf::Style::Close);
    m_Window->setFramerateLimit(120);
}

void MatrixCalculator::InitBackground()
{
	m_Background.setSize(sf::Vector2f(m_Window->getSize().x, m_Window->getSize().y));
	m_BackgroundTexture.loadFromFile("Images/bg2.png");
	m_Background.setTexture(&m_BackgroundTexture);

	m_TitleFont.loadFromFile("Fonts/font2.ttf");
	m_TitleText.setFont(m_TitleFont);
	m_TitleText.setString("MATRIX CALCULATOR");
	m_TitleText.setFillColor(sf::Color::White);
	m_TitleText.setCharacterSize(50);
	m_TitleText.setPosition(sf::Vector2f
		(m_Window->getSize().x / 2.f - m_TitleText.getGlobalBounds().width / 2.f,
		m_Window->getSize().y / 2.f - 390.f)
	);
}

void MatrixCalculator::InitGui()
{
	sf::Vector2f TempPos;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (m_Matrix.empty())
			{
				m_Matrix.push_back(new gui::TextBox(15, sf::Color::Black, { 100.f, 200.f }, { 60, 25 }));
				TempPos = m_Matrix.back()->GetPosition();
			}
			else
				m_Matrix.push_back(new gui::TextBox(15, sf::Color::Black, { TempPos.x + j * 70, TempPos.y + i * 35.f }, { 60, 25 }));
			m_Matrix.back()->SetLimit(true, 6);
		}
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
							m_ActiveTextbox->Update();
							m_ActiveTextbox = nullptr;
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
	if (m_ActiveTextbox)
		m_ActiveTextbox->Update();
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
	m_Window->draw(m_TitleText);

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
