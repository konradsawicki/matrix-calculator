
#include "MatrixCalculator.h"

void MatrixCalculator::InitWindow()
{
    m_Window = new sf::RenderWindow(sf::VideoMode(1280+300, 720+100), "Matrix Calculator", sf::Style::Close);
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

void MatrixCalculator::InitMatrix(const std::string& MatrixName, const sf::Vector2f& Position)
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
			if (m_Matrices[MatrixName].empty())
			{
				m_Matrices[MatrixName].push_back(new gui::TextBox(15, sf::Color::Black, { Position.x - b, Position.y }, { 60, 25 }));
				TempPos = m_Matrices[MatrixName].back()->GetPosition();
			}
			else
				m_Matrices[MatrixName].push_back(new gui::TextBox(15, sf::Color::Black, { TempPos.x + j * 70, TempPos.y + i * 35.f }, { 60, 25 }));
		}
	}

	float m_DimensionX_TextboxesPos = Position.x - 30.f;
	float m_DimensionY_TextboxesPos = Position.y - 40.f;
	m_DimensionX_Textboxes[MatrixName] = new gui::TextBox(15, sf::Color::Black, { m_DimensionX_TextboxesPos - 40, m_DimensionY_TextboxesPos }, { 60, 25 });
	m_DimensionX_Textboxes[MatrixName]->SetText(j_max);
	m_DimensionY_Textboxes[MatrixName] = new gui::TextBox(15, sf::Color::Black, { m_DimensionX_TextboxesPos + 40, m_DimensionY_TextboxesPos }, { 60, 25 });
	m_DimensionY_Textboxes[MatrixName]->SetText(i_max);
	m_TextFont.loadFromFile("Fonts/font1_bold.ttf");
	m_TextsCharX[MatrixName].setFont(m_TextFont);
	m_TextsCharX[MatrixName].setCharacterSize(15);
	m_TextsCharX[MatrixName].setString("X");
	m_TextsCharX[MatrixName].setPosition({ m_DimensionX_TextboxesPos + 25, m_DimensionY_TextboxesPos + 3 });

	m_MatrixNames[MatrixName].setFont(m_TextFont);
	m_MatrixNames[MatrixName].setCharacterSize(20);
	m_MatrixNames[MatrixName].setString(MatrixName);
	m_MatrixNames[MatrixName].setPosition({ m_DimensionX_TextboxesPos - 10, m_DimensionY_TextboxesPos - 30 });

	m_Lines[MatrixName].first = sf::RectangleShape(sf::Vector2f(3, a + 10));
	m_Lines[MatrixName].first.setPosition({ m_Matrices[MatrixName].front()->GetPosition().x - 10, m_Matrices[MatrixName].front()->GetPosition().y - 5 });
	m_Lines[MatrixName].second = sf::RectangleShape(sf::Vector2f(3, a + 10));
	m_Lines[MatrixName].second.setPosition({ m_Matrices[MatrixName].front()->GetPosition().x + 2 * b + 7, m_Matrices[MatrixName].front()->GetPosition().y - 5 });
}

void MatrixCalculator::InitGui()
{

	sf::Vector2f TempPos;
	m_MatrixPositions["Matrix A"] = sf::Vector2f(m_DimensionXMatrixTextbox, m_DimensionYMatrixTextbox);
	InitMatrix("Matrix A", m_MatrixPositions["Matrix A"]);
	
	m_MatrixPositions["Matrix B"] = sf::Vector2f(750.f, 350.f);
	InitMatrix("Matrix B", m_MatrixPositions["Matrix B"]);

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
					UpdateTextbox(Temp);
				}
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
					UpdateTextbox(Temp);
				}
				else
				{
					if (m_ActiveTextbox)
					{
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
					std::vector<gui::TextBox*>::const_iterator TempTextboxIter;
					std::vector<gui::TextBox*>::const_iterator TempKVsecondEnd;
					std::vector<gui::TextBox*>::const_iterator TempKVsecondBegin;
					std::string TempMatrixName;
					auto it = std::find_if(m_Matrices.begin(), m_Matrices.end(), [&](const auto& kv)
						{
							return std::any_of(kv.second.begin(), kv.second.end(), [&](const auto& x)
								{
									if (x == m_ActiveTextbox)
									{
										TempKVsecondEnd = kv.second.cend();
										TempKVsecondBegin = kv.second.cbegin();
										TempTextboxIter = std::find(kv.second.begin(), kv.second.end(), m_ActiveTextbox);
										return true;
									}
									else
										return false;
								});
						});
					if (it != m_Matrices.end())
					{
						if (TempTextboxIter + 1 != TempKVsecondEnd)
						{
							m_ActiveTextbox->Select(false);
							m_ActiveTextbox->Update();
							m_ActiveTextbox = *(TempTextboxIter + 1);
							m_ActiveTextbox->Select(true);
						}
						else
						{
							m_ActiveTextbox->Select(false);
							m_ActiveTextbox->Update();
							m_ActiveTextbox = *TempKVsecondBegin;
							m_ActiveTextbox->Select(true);
						}
					}
					else if (std::any_of(m_DimensionX_Textboxes.begin(), m_DimensionX_Textboxes.end(), [&](const auto& kv)
						{
							if (m_ActiveTextbox == kv.second)
							{
								TempMatrixName = kv.first;
								return true;
							}
							else 
								return false;
						})
					)
					{
						m_ActiveTextbox->Select(false);
						m_ActiveTextbox->Update();
						UpdateDimensionTextbox(m_ActiveTextbox, TempMatrixName);
						m_ActiveTextbox = m_DimensionY_Textboxes[TempMatrixName];
						m_ActiveTextbox->Select(true);
					}
					else if (std::any_of(m_DimensionY_Textboxes.begin(), m_DimensionY_Textboxes.end(), [&](const auto& kv)
						{
							if (m_ActiveTextbox == kv.second)
							{
								TempMatrixName = kv.first;
								return true;
							}
							else
								return false;
						})
					)
					{
						m_ActiveTextbox->Select(false);
						m_ActiveTextbox->Update();
						UpdateDimensionTextbox(m_ActiveTextbox, TempMatrixName);
						m_ActiveTextbox = m_Matrices[TempMatrixName][0];
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
	std::string TempMatrixName;
	if (std::any_of(m_DimensionX_Textboxes.begin(), m_DimensionX_Textboxes.end(), [&](const auto& kv)
		{
			if (m_TempDimensionTextbox == kv.second)
			{
				TempMatrixName = kv.first;
				return true;
			}
			else
				return false;
		})
	)
	{
		UpdateDimensionTextbox(m_DimensionX_Textboxes[TempMatrixName], TempMatrixName);
	}	
	else if (std::any_of(m_DimensionY_Textboxes.begin(), m_DimensionY_Textboxes.end(), [&](const auto& kv)
		{
			if (m_TempDimensionTextbox == kv.second)
			{
				TempMatrixName = kv.first;
				return true;
			}
			else
				return false;
		})
	)
	{
		UpdateDimensionTextbox(m_DimensionY_Textboxes[TempMatrixName], TempMatrixName);
	}
		
}

void MatrixCalculator::UpdateMousePosition()
{
	m_MousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_Window));;
	//std::cout << m_MousePos.x << " " << m_MousePos.y;
	//system("cls");
}

void MatrixCalculator::UpdateMouseLook()
{
	if (std::any_of(m_Matrices.begin(), m_Matrices.end(), [&](const auto& kv)
		{
			return std::any_of(kv.second.begin(), kv.second.end(), [&](const auto& x)
				{
					if (x->Contains(m_MousePos))
					{
						return true;
					}
					else
						return false;
				});
		}))
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

	if (std::any_of(m_DimensionX_Textboxes.begin(), m_DimensionX_Textboxes.end(), [&](const auto& kv)
		{
			if (kv.second->Contains(m_MousePos))
			{
				return true;
			}
			else
				return false;

		}) || 

		std::any_of(m_DimensionY_Textboxes.begin(), m_DimensionY_Textboxes.end(), [&](const auto& kv)
		{
			if (kv.second->Contains(m_MousePos))
			{
				return true;
			}
			else
				return false;
		})
	)
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
		m_TempDimensionTextbox = m_ActiveTextbox;
		m_ActiveTextbox = Textbox;
		m_ActiveTextbox->Select(true);
	}
	else if (m_ActiveTextbox)
	{
		if (!m_ActiveTextbox->Contains(m_MousePos) && !Textbox->Contains(m_MousePos))
		{
			m_ActiveTextbox->Select(false);
			m_ActiveTextbox->Update();
			m_TempDimensionTextbox = m_ActiveTextbox;
			m_ActiveTextbox = nullptr;
		}
	}
}

void MatrixCalculator::UpdateDimensionTextbox(gui::TextBox* DimensionTextbox, const std::string& MatrixName)
{
	std::cout << "Halo\n";

	std::string TextX = m_DimensionX_Textboxes[MatrixName]->GetText();
	std::string TextY = m_DimensionY_Textboxes[MatrixName]->GetText();
	if (TextX == "")
	{
		TextX = "1";
		if (DimensionTextbox == m_DimensionX_Textboxes[MatrixName])
			m_DimensionX_Textboxes[MatrixName]->SetText(1);
	}

	if (TextY == "")
	{
		TextY = "1";
		if (DimensionTextbox == m_DimensionY_Textboxes[MatrixName])
			m_DimensionY_Textboxes[MatrixName]->SetText(1);
	}

	int rows = std::stoi(TextX);
	int columns = std::stoi(TextY);

	if (rows <= 0)
	{
		rows = 1;
		if (DimensionTextbox == m_DimensionX_Textboxes[MatrixName])
			m_DimensionX_Textboxes[MatrixName]->SetText(1);
	}
	else if (rows > 6)
	{
		rows = 6;
		if (DimensionTextbox == m_DimensionX_Textboxes[MatrixName])
			m_DimensionX_Textboxes[MatrixName]->SetText(6);
	}

	if (columns <= 0)
	{
		columns = 1;
		if (DimensionTextbox == m_DimensionY_Textboxes[MatrixName])
			m_DimensionY_Textboxes[MatrixName]->SetText(1);
	}
	else if (columns > 6)
	{
		columns = 6;
		if (DimensionTextbox == m_DimensionY_Textboxes[MatrixName])
			m_DimensionY_Textboxes[MatrixName]->SetText(6);
	}

	if (m_Matrices[MatrixName].size() / rows != columns)
	{
		std::cout << "Halo1\n";
		m_ActiveTextbox = nullptr;
		for (auto e : m_Matrices[MatrixName])
			delete e;
		m_Matrices[MatrixName].clear();
		int b = ((columns) * 60 + (columns - 1) * 10) / 2;
		sf::Vector2f TempPos;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (m_Matrices[MatrixName].empty())
				{
					m_Matrices[MatrixName].push_back(new gui::TextBox(15, sf::Color::Black, { m_MatrixPositions[MatrixName].x - b, m_MatrixPositions[MatrixName].y }, {60, 25}));
					TempPos = m_Matrices[MatrixName].back()->GetPosition();
				}
				else
					m_Matrices[MatrixName].push_back(new gui::TextBox(15, sf::Color::Black, { TempPos.x + j * 70, TempPos.y + i * 35.f }, { 60, 25 }));
			}
		}

		UpdateLines(MatrixName, rows, columns);

		auto it = std::find_if(m_Matrices[MatrixName].begin(), m_Matrices[MatrixName].end(), [&](const auto& x) { return x->Contains(m_MousePos); });
		if (it != m_Matrices[MatrixName].end())
		{
			m_ActiveTextbox = *it;
			m_ActiveTextbox->Select(true);
		}
		else if (m_DimensionX_Textboxes[MatrixName]->Contains(m_MousePos))
		{
			m_ActiveTextbox = m_DimensionX_Textboxes[MatrixName];
			m_ActiveTextbox->Select(true);
		}
		else if (m_DimensionY_Textboxes[MatrixName]->Contains(m_MousePos))
		{
			m_ActiveTextbox = m_DimensionY_Textboxes[MatrixName];
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

void MatrixCalculator::UpdateLines(const std::string& MatrixName, const int& rows, const int& columns)
{



	int a = ((rows) * 25 + (rows - 1) * 10);
	int b = ((columns) * 60 + (columns - 1) * 10) / 2;

	m_Lines[MatrixName].first = sf::RectangleShape(sf::Vector2f(3, a + 10));
	m_Lines[MatrixName].first.setPosition({ m_Matrices[MatrixName].front()->GetPosition().x - 10, m_Matrices[MatrixName].front()->GetPosition().y - 5});
	m_Lines[MatrixName].second = sf::RectangleShape(sf::Vector2f(3, a + 10));
	m_Lines[MatrixName].second.setPosition({ m_Matrices[MatrixName].front()->GetPosition().x + 2 * b + 7, m_Matrices[MatrixName].front()->GetPosition().y - 5 });
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
	for (auto& kv : m_Matrices)
		for (auto& e : kv.second)
			e->Render(m_Window);

	for (auto& kv : m_DimensionX_Textboxes)
		kv.second->Render(m_Window);

	for (auto& kv : m_DimensionY_Textboxes)
		kv.second->Render(m_Window);

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
