
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
		m_Window->getSize().y / 2.f - 380.f)
	);
}

void MatrixCalculator::InitGui()
{
	int i_max = 3;
	int j_max = 3;

	int a = ((i_max) * 25 + (i_max - 1) * 10);
	int b = ((j_max) * 60 + (j_max - 1) * 10) / 2;

	sf::Vector2f TempPos;
	for (int i = 0; i < i_max; i++)
	{
		for (int j = 0; j < j_max; j++)
		{
			if (m_Matrices["MATRIX_A"].empty())
			{
				m_Matrices["MATRIX_A"].push_back(new gui::TextBox(15, sf::Color::Black, { m_DimensionXMatrixTextbox - b, m_DimensionYMatrixTextbox }, { 60, 25 }));
				TempPos = m_Matrices["MATRIX_A"].back()->GetPosition();
			}
			else
				m_Matrices["MATRIX_A"].push_back(new gui::TextBox(15, sf::Color::Black, { TempPos.x + j * 70, TempPos.y + i * 35.f }, { 60, 25 }));
			//m_Matrix.back()->SetLimit(true, 6);
		}
	}

	float m_DimensionX_TextboxesPos = m_DimensionXMatrixTextbox - 30.f;
	float m_DimensionY_TextboxesPos = m_DimensionYMatrixTextbox - 40.f;
	m_DimensionX_Textboxes["MATRIX_A"] = new gui::TextBox(15, sf::Color::Black, {m_DimensionX_TextboxesPos - 40, m_DimensionY_TextboxesPos}, {60, 25});
	m_DimensionX_Textboxes["MATRIX_A"]->SetText(j_max);
	m_DimensionY_Textboxes["MATRIX_A"] = new gui::TextBox(15, sf::Color::Black, { m_DimensionX_TextboxesPos + 40, m_DimensionY_TextboxesPos }, { 60, 25 });
	m_DimensionY_Textboxes["MATRIX_A"]->SetText(i_max);
	m_TextFont.loadFromFile("Fonts/font1_bold.ttf");
	m_TextsCharX["MATRIX_A"].setFont(m_TextFont);
	m_TextsCharX["MATRIX_A"].setCharacterSize(15);
	m_TextsCharX["MATRIX_A"].setString("X");
	m_TextsCharX["MATRIX_A"].setPosition({ m_DimensionX_TextboxesPos + 25, m_DimensionY_TextboxesPos + 3 });

	m_MatrixNames["MATRIX_A"].setFont(m_TextFont);
	m_MatrixNames["MATRIX_A"].setCharacterSize(20);
	m_MatrixNames["MATRIX_A"].setString("Matrix A");
	m_MatrixNames["MATRIX_A"].setPosition({ m_DimensionX_TextboxesPos - 10, m_DimensionY_TextboxesPos - 30});

	m_Lines["MATRIX_A"].first = sf::RectangleShape(sf::Vector2f(3, a + 10));
	m_Lines["MATRIX_A"].first.setPosition({ m_Matrices["MATRIX_A"].front()->GetPosition().x - 10, m_Matrices["MATRIX_A"].front()->GetPosition().y - 5});
	m_Lines["MATRIX_A"].second = sf::RectangleShape(sf::Vector2f(3, a + 10));
	m_Lines["MATRIX_A"].second.setPosition({ m_Matrices["MATRIX_A"].front()->GetPosition().x + 2*b + 7, m_Matrices["MATRIX_A"].front()->GetPosition().y - 5 });



	for (int k = 0, i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (m_RadioButtons.empty())
			{
				m_RadioButtons.push_back(new gui::RadioButton(10, { m_Window->getSize().x / 2.f - 180.f, 130}, m_Operations[k]));
				TempPos = m_RadioButtons.back()->GetPosition();
			}
			else
				m_RadioButtons.push_back(new gui::RadioButton(10, { TempPos.x + j * 150, TempPos.y + i * 50 }, m_Operations[k]));
			k++;
		}
	}
}

MatrixCalculator::MatrixCalculator()
	: m_ActiveFlag(false), m_ActiveTextbox(nullptr), m_MouseTextMatrixAFlag(false), m_MouseTextMatrixBFlag(false), m_MouseTextDimensionsFlag(false),
	m_MouseHandFlag(false), m_Operations({ "Add", "Substract", "Multiply", "Transpose", "Determinant", "Inverse" }), m_DimensionXMatrixTextbox(250.f),
	m_DimensionYMatrixTextbox(350.f)
{
    std::cout << "Starting Matrix Calculator!\n";
    InitWindow();
	InitBackground();
	InitGui();
	//std::thread Thread(&MatrixCalculator::UpdateMouseText, std::ref(*this));
	//Thread.detach();
}

MatrixCalculator::~MatrixCalculator()
{
    delete m_Window;
	for (auto& kv : m_Matrices)
	{
		for (auto& e : kv.second)
			delete e;
	}

	for (auto& kv : m_DimensionX_Textboxes)
	{
		delete kv.second;
	}

	for (auto& kv : m_DimensionY_Textboxes)
	{
		delete kv.second;
	}

	for (auto e : m_RadioButtons)
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
				gui::TextBox* Temp;
				auto it = std::find_if(m_Matrices.begin(), m_Matrices.end(), [&](const auto& kv)
						{
							return std::any_of(kv.second.begin(), kv.second.end(), [&](const auto& x)
								{
									if (x->Contains(m_MousePos))
									{
										Temp = x;
										return true;
									}
									else
										return false;
								});
						});
				if (it != m_Matrices.end())
				{
					std::cout << "1\n";
					UpdateTextbox(Temp);
				}
					
				/*else if (m_DimensionX_Textboxes["MATRIX_A"]->Contains(m_MousePos))*/
				else if (std::find_if(m_DimensionX_Textboxes.begin(), m_DimensionX_Textboxes.end(), [&](const auto& kv)
					{
						if (kv.second->Contains(m_MousePos))
						{
							Temp = kv.second;
							return true;
						}
						else
							return false;
					}) != m_DimensionX_Textboxes.end())
				{
					std::cout << "2\n";
					UpdateTextbox(Temp);
				}

				else if (std::find_if(m_DimensionY_Textboxes.begin(), m_DimensionY_Textboxes.end(), [&](const auto& kv)
					{
						if (kv.second->Contains(m_MousePos))
						{
							Temp = kv.second;
							return true;
						}
						else
							return false;
					}) != m_DimensionY_Textboxes.end())
				{
					std::cout << "3\n";
					UpdateTextbox(Temp);
				}
				else
				{
					if (m_ActiveTextbox)
					{
						std::cout << "razdwa\n";
						m_ActiveTextbox->Select(false);
						m_ActiveTextbox->Update();
						m_TempDimensionTextbox = m_ActiveTextbox;
						m_ActiveTextbox = nullptr;
					}
				}


				auto it2 = std::find_if(m_RadioButtons.begin(), m_RadioButtons.end(), [&](const auto& x) { return x->Contains(m_MousePos); });
				if (it2 != m_RadioButtons.end())
					UpdateRadioButton(*it2);

			}
			break;
		case sf::Event::TextEntered:
			if (m_ActiveTextbox)
				m_ActiveTextbox->Type(m_Event);
			break;

		case sf::Event::KeyReleased:
			if (m_Event.key.code == sf::Keyboard::Tab || m_Event.key.code == sf::Keyboard::Enter)
			{
				if (m_ActiveTextbox)
				{
					auto it = std::find(m_Matrices["MATRIX_A"].begin(), m_Matrices["MATRIX_A"].end(), m_ActiveTextbox);
					if (it != m_Matrices["MATRIX_A"].end())
					{
						if (it + 1 != m_Matrices["MATRIX_A"].end())
						{
							m_ActiveTextbox->Select(false);
							m_ActiveTextbox->Update();
							m_ActiveTextbox = *(it + 1);
							m_ActiveTextbox->Select(true);
						}
						else
						{
							m_ActiveTextbox->Select(false);
							m_ActiveTextbox->Update();
							m_ActiveTextbox = *m_Matrices["MATRIX_A"].begin();
							m_ActiveTextbox->Select(true);
						}
					}
					else if (m_ActiveTextbox == m_DimensionX_Textboxes["MATRIX_A"])
					{
						m_ActiveTextbox->Select(false);
						m_ActiveTextbox->Update();
						UpdateDimensionTextbox(m_ActiveTextbox);
						m_ActiveTextbox = m_DimensionY_Textboxes["MATRIX_A"];
						m_ActiveTextbox->Select(true);
					}
					else if (m_ActiveTextbox == m_DimensionY_Textboxes["MATRIX_A"])
					{
						m_ActiveTextbox->Select(false);
						m_ActiveTextbox->Update();
						UpdateDimensionTextbox(m_ActiveTextbox);
						m_ActiveTextbox = m_Matrices["MATRIX_A"][0];
						m_ActiveTextbox->Select(true);
					}
				}
			}
			break;
		}
	}
}

void MatrixCalculator::UpdateGui()
{
	if (m_ActiveTextbox)
	{
		m_ActiveTextbox->Update();
	}
	if (m_TempDimensionTextbox == m_DimensionX_Textboxes["MATRIX_A"])
		UpdateDimensionTextbox(m_DimensionX_Textboxes["MATRIX_A"]);
	else if (m_TempDimensionTextbox == m_DimensionY_Textboxes["MATRIX_A"])
		UpdateDimensionTextbox(m_DimensionY_Textboxes["MATRIX_A"]);
}


void MatrixCalculator::UpdateMousePosition()
{
	m_MousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_Window));;
	//std::cout << m_MousePos.x << " " << m_MousePos.y;
	//system("cls");
}

void MatrixCalculator::UpdateMouseLook()
{
	if (std::any_of(m_Matrices["MATRIX_A"].begin(), m_Matrices["MATRIX_A"].end(), [&](const auto& x) { return x->Contains(m_MousePos); }))
	{
		if (m_Cursor.loadFromSystem(sf::Cursor::Text) && !m_MouseTextMatrixAFlag)
		{
				m_Window->setMouseCursor(m_Cursor);
				m_MouseTextMatrixAFlag = true;
		}
	}
	else
	{
		if (m_Cursor.loadFromSystem(sf::Cursor::Arrow) && m_MouseTextMatrixAFlag)
		{
			m_MouseTextMatrixAFlag = false;
			m_Window->setMouseCursor(m_Cursor);
		}
	}

	if (m_DimensionX_Textboxes["MATRIX_A"]->Contains(m_MousePos) || m_DimensionY_Textboxes["MATRIX_A"]->Contains(m_MousePos))
	{
		if (m_Cursor.loadFromSystem(sf::Cursor::Text) && !m_MouseTextDimensionsFlag)
		{
			m_Window->setMouseCursor(m_Cursor);
			m_MouseTextDimensionsFlag = true;
		}
	}
	else
	{
		if (m_Cursor.loadFromSystem(sf::Cursor::Arrow) && m_MouseTextDimensionsFlag)
		{
			m_MouseTextDimensionsFlag = false;
			m_Window->setMouseCursor(m_Cursor);
		}
	}


	if (std::any_of(m_RadioButtons.begin(), m_RadioButtons.end(), [&](const auto& x) { return x->Contains(m_MousePos); }))
	{
		if (m_Cursor.loadFromSystem(sf::Cursor::Hand) && !m_MouseHandFlag)
		{
			m_Window->setMouseCursor(m_Cursor);
			m_MouseHandFlag = true;
		}
	}
	else
	{
		if (m_Cursor.loadFromSystem(sf::Cursor::Arrow) && m_MouseHandFlag)
		{
			m_MouseHandFlag = false;
			m_Window->setMouseCursor(m_Cursor);
		}
	}
}

void MatrixCalculator::UpdateTextbox(gui::TextBox* Textbox)
{
	if (Textbox->Contains(m_MousePos) && Textbox != m_ActiveTextbox)
	{
		if (m_ActiveTextbox)
		{
			m_ActiveTextbox->Select(false);
			m_ActiveTextbox->Update();
		}
		std::cout << "Elo1\n";
		m_TempDimensionTextbox = m_ActiveTextbox;
		m_ActiveTextbox = Textbox;
		m_ActiveTextbox->Select(true);
	}
	else if (m_ActiveTextbox)
	{
		if (!m_ActiveTextbox->Contains(m_MousePos) && !Textbox->Contains(m_MousePos))
		{
			std::cout << "Elo2\n";
			m_ActiveTextbox->Select(false);
			m_ActiveTextbox->Update();
			m_TempDimensionTextbox = m_ActiveTextbox;
			m_ActiveTextbox = nullptr;
			std::cout << "Elo3\n";
		}
	}
}

void MatrixCalculator::UpdateDimensionTextbox(gui::TextBox* DimensionTextbox)
{
	std::cout << "Halo\n";
	std::string TextX = m_DimensionX_Textboxes["MATRIX_A"]->GetText();
	std::string TextY = m_DimensionY_Textboxes["MATRIX_A"]->GetText();
	if (TextX == "")
	{
		TextX = "1";
		if (DimensionTextbox == m_DimensionX_Textboxes["MATRIX_A"])
			m_DimensionX_Textboxes["MATRIX_A"]->SetText(1);
	}

	if (TextY == "")
	{
		TextY = "1";
		if (DimensionTextbox == m_DimensionY_Textboxes["MATRIX_A"])
			m_DimensionY_Textboxes["MATRIX_A"]->SetText(1);
	}

	int rows = std::stoi(TextX);
	int columns = std::stoi(TextY);

	if (rows <= 0)
	{
		rows = 1;
		if (DimensionTextbox == m_DimensionX_Textboxes["MATRIX_A"])
			m_DimensionX_Textboxes["MATRIX_A"]->SetText(1);
	}
	else if (rows > 6)
	{
		rows = 6;
		if (DimensionTextbox == m_DimensionX_Textboxes["MATRIX_A"])
			m_DimensionX_Textboxes["MATRIX_A"]->SetText(6);
	}

	if (columns <= 0)
	{
		columns = 1;
		if (DimensionTextbox == m_DimensionY_Textboxes["MATRIX_A"])
			m_DimensionY_Textboxes["MATRIX_A"]->SetText(1);
	}
	else if (columns > 6)
	{
		columns = 6;
		if (DimensionTextbox == m_DimensionY_Textboxes["MATRIX_A"])
			m_DimensionY_Textboxes["MATRIX_A"]->SetText(6);
	}

	if (m_Matrices["MATRIX_A"].size() / rows != columns)
	{
		std::cout << "Halo1\n";
		m_ActiveTextbox = nullptr;
		for (auto e : m_Matrices["MATRIX_A"])
			delete e;
		m_Matrices["MATRIX_A"].clear();
		int b = ((columns) * 60 + (columns - 1) * 10) / 2;
		sf::Vector2f TempPos;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (m_Matrices["MATRIX_A"].empty())
				{
					m_Matrices["MATRIX_A"].push_back(new gui::TextBox(15, sf::Color::Black, { m_DimensionXMatrixTextbox - b, m_DimensionYMatrixTextbox }, { 60, 25 }));
					TempPos = m_Matrices["MATRIX_A"].back()->GetPosition();
				}
				else
					m_Matrices["MATRIX_A"].push_back(new gui::TextBox(15, sf::Color::Black, { TempPos.x + j * 70, TempPos.y + i * 35.f }, { 60, 25 }));
				//m_Matrix.back()->SetLimit(true, 6);
			}
		}
		//UpdateMousePosition();
		auto it = std::find_if(m_Matrices["MATRIX_A"].begin(), m_Matrices["MATRIX_A"].end(), [&](const auto& x) { return x->Contains(m_MousePos); });
		if (it != m_Matrices["MATRIX_A"].end())
		{
			m_ActiveTextbox = *it;
			m_ActiveTextbox->Select(true);
		}
		else if (m_DimensionX_Textboxes["MATRIX_A"]->Contains(m_MousePos))
		{
			m_ActiveTextbox = m_DimensionX_Textboxes["MATRIX_A"];
			m_ActiveTextbox->Select(true);
		}
		else if (m_DimensionY_Textboxes["MATRIX_A"]->Contains(m_MousePos))
		{
			m_ActiveTextbox = m_DimensionY_Textboxes["MATRIX_A"];
			m_ActiveTextbox->Select(true);
		}

	}
	m_TempDimensionTextbox = nullptr;
}

void MatrixCalculator::UpdateRadioButton(gui::RadioButton* RadioButton)
{
	if (RadioButton->Contains(m_MousePos) && RadioButton != m_ActiveRadioButton)
	{
		if (m_ActiveRadioButton)
		{
			m_ActiveRadioButton->SetInactive();
		}
		m_ActiveRadioButton = RadioButton;
		m_ActiveRadioButton->SetActive();
	}
}

void MatrixCalculator::UpdateLines()
{


	//int a = ((rows) * 25 + (rows - 1) * 10);
	//int b = ((columns) * 60 + (columns - 1) * 10) / 2;

	//m_Lines["MATRIX_A"].first = sf::RectangleShape(sf::Vector2f(3, a + 10));
	//m_Lines["MATRIX_A"].first.setPosition({ m_Matrix.front()->GetPosition().x - 10, m_Matrix.front()->GetPosition().y - 5 });
	//m_Lines["MATRIX_A"].second = sf::RectangleShape(sf::Vector2f(3, a + 10));
	//m_Lines["MATRIX_A"].second.setPosition({ m_Matrix.front()->GetPosition().x + 2 * b + 7, m_Matrix.front()->GetPosition().y - 5 });
}

void MatrixCalculator::Update()
{
	UpdateMouseLook();
	UpdateMousePosition();
	UpdateSFMLEvents();
	UpdateGui();

}

void MatrixCalculator::RenderGui()
{
	for (auto e : m_Matrices["MATRIX_A"])
		e->Render(m_Window);

	m_DimensionX_Textboxes["MATRIX_A"]->Render(m_Window);
	m_DimensionY_Textboxes["MATRIX_A"]->Render(m_Window);
	for (auto& kv : m_TextsCharX)
		m_Window->draw(kv.second);

	for (auto& kv : m_MatrixNames)
		m_Window->draw(kv.second);

	for (auto& kv : m_Lines)
	{
		m_Window->draw(kv.second.first);
		m_Window->draw(kv.second.second);
	}
		

	for (auto e : m_RadioButtons)
		e->Render(m_Window);
}

void MatrixCalculator::Render()
{
    m_Window->clear();

	m_Window->draw(m_Background);
	m_Window->draw(m_TitleText);

	RenderGui();

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
