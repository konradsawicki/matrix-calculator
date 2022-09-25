#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height, std::string Text,
	sf::Color IdleColor, sf::Color HoverColor, sf::Color ActiveColor, const int& Size)
{
	m_ButtonState = BUTTON_STATES::BTN_IDLE;

	m_Button.setPosition(sf::Vector2f(x, y));
	m_Button.setSize(sf::Vector2f(width, height));
	m_Button.setOutlineColor(sf::Color::Black);
	m_Button.setOutlineThickness(1);

	m_Font.loadFromFile("Fonts/font1.ttf");
	m_Text.setFont(m_Font);
	m_Text.setString(Text);
	m_Text.setFillColor(sf::Color::White);
	m_Text.setCharacterSize(Size); // 25
	m_Text.setPosition(
		m_Button.getPosition().x + (width / 2.f) - m_Text.getGlobalBounds().width / 2.f,
		m_Button.getPosition().y + (height / 2.f) - m_Text.getGlobalBounds().height / 1.3f /*2.f*/
	);

	m_IdleColor = IdleColor;
	m_HoverColor = HoverColor;
	m_ActiveColor = ActiveColor;

	m_Button.setFillColor(m_IdleColor);
}

gui::Button::~Button()
{

}

bool gui::Button::Contains(const sf::Vector2f& Something) const
{
	return m_Button.getGlobalBounds().contains(Something);
}


std::string gui::Button::GetText() const
{

	return m_Text.getString();
}

void gui::Button::SetText(const sf::String& Text)
{
	m_Text.setString(Text);
	m_Text.setPosition(
		m_Button.getPosition().x + (m_Button.getSize().x / 2.f) - m_Text.getGlobalBounds().width / 2.f,
		m_Button.getPosition().y + (m_Button.getSize().y / 2.f) - m_Text.getGlobalBounds().height / 1.3f /*2.f*/
	);
}

void gui::Button::setOutlineThickness(int thick)
{
	m_Button.setOutlineThickness(thick);
}

void gui::Button::Update(const sf::Vector2f& MousePos)
{
	m_ButtonState = BUTTON_STATES::BTN_IDLE;

	if (m_Button.getGlobalBounds().contains(MousePos))
	{
		m_ButtonState = BUTTON_STATES::BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_ButtonState = BUTTON_STATES::BTN_ACTIVE;
		}
	}


	switch (m_ButtonState)
	{
	case BUTTON_STATES::BTN_IDLE:
		m_Button.setFillColor(m_IdleColor);
		break;
	case BUTTON_STATES::BTN_HOVER:
		m_Button.setFillColor(m_HoverColor);
		break;
	case BUTTON_STATES::BTN_ACTIVE:
		m_Button.setFillColor(m_ActiveColor);
		break;
	default:
		m_Button.setFillColor(sf::Color::Red);
		break;
	}
}

void gui::Button::Render(sf::RenderTarget* Target)
{
	Target->draw(m_Button);
	Target->draw(m_Text);
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

gui::DropDownList::DropDownList(float x, float y, float width, float height,
	std::vector<std::string> List, unsigned NrOfElements, unsigned default_index)
	: m_ShowList(false)
{
	m_ActiveElement = new gui::Button(x, y, width, height, List[0],
		sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), 25);

	for (int i = 0; i < NrOfElements; ++i)
	{
		m_List.push_back(new gui::Button(x, y + ((i + 1) * height), width, height, List[i],
			sf::Color(100, 100, 100, 100), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), 25));
	}

	// Triangle on the Drop Down List
	m_Triangle.setRadius(10.f);
	m_Triangle.setPointCount(3);
	m_Triangle.setFillColor(sf::Color::White);
	m_Triangle.setPosition(560, 360);
	m_Triangle.setOrigin(10, 6.67);
	m_Triangle.rotate(180);
}

gui::DropDownList::~DropDownList()
{
	delete m_ActiveElement;
	for (auto& e : m_List)
	{
		delete e;
	}
}

std::string gui::DropDownList::GetActiveElementText() const
{
	return m_ActiveElement->GetText();
}

void gui::DropDownList::UpdateButtonState(const sf::Vector2f& MousePos)
{
	m_ActiveElement->Update(MousePos);
	for (auto& e : m_List)
	{
		e->Update(MousePos);
	}
}

void gui::DropDownList::Update(const sf::Vector2f& MousePos)
{
	if (m_ActiveElement->Contains(MousePos))
	{
		if (m_ShowList)
		{
			m_ActiveElement->setOutlineThickness(1);
			m_Triangle.rotate(180);
			m_ShowList = false;
		}
		else
		{
			m_ActiveElement->setOutlineThickness(-3);
			m_Triangle.rotate(180);
			m_ShowList = true;
		}
	}

	if (m_ShowList)
	{
		for (auto& i : m_List)
		{
			if (i->Contains(MousePos))
			{
				m_ActiveElement->setOutlineThickness(1);
				m_Triangle.rotate(180);
				m_ShowList = false;
				m_ActiveElement->SetText(i->GetText());
			}
		}
	}
}

void gui::DropDownList::Render(sf::RenderTarget* Target)
{
	m_ActiveElement->Render(Target);
	Target->draw(m_Triangle);

	if (m_ShowList)
	{
		for (auto& i : m_List)
		{
			i->Render(Target);
		}
	}
}

/////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


gui::TextBox::TextBox(const int& CharSize, sf::Color Color, const sf::Vector2f& Pos, const sf::Vector2f& BackgroundSize)
	: m_IsSelected(false)
{
	m_TextboxBackground.setSize(BackgroundSize);
	m_TextboxBackground.setFillColor(sf::Color(152, 152, 156));
	m_TextboxBackground.setPosition(Pos);

	m_Font.loadFromFile("Fonts/font1.ttf");
	m_Textbox.setFont(m_Font);
	m_Textbox.setFillColor(Color);
	m_Textbox.setCharacterSize(CharSize);
	m_Textbox.setPosition(
		m_TextboxBackground.getPosition().x + m_TextboxBackground.getSize().x / 2.f - m_Textbox.getGlobalBounds().width / 2.f,
		m_TextboxBackground.getPosition().y + m_TextboxBackground.getSize().y / 2.f - 10
	);

}

void gui::TextBox::InputLogic(const int& CharTyped)
{
	if (CharTyped != DELETE_KEY && CharTyped != ENTER_KEY && CharTyped != ESCAPE_KEY)
	{
		m_Text.seekp(0, m_Text.end);
		m_Text << static_cast<char>(CharTyped);
	}
	else if (CharTyped == DELETE_KEY)
	{
		if (m_Text.str().length() > 0)
			DeleteLastChar();
	}
	m_Textbox.setString(m_Text.str() + "|");
}

void gui::TextBox::DeleteLastChar()
{
	std::string temp = m_Text.str();
	temp.pop_back();
	m_Text.str(temp);

	m_Textbox.setString(m_Text.str());
}


void gui::TextBox::SetLimit(const bool& TrueOrFalse)
{
	m_HasLimit = TrueOrFalse;
}

void gui::TextBox::SetLimit(const bool& TrueOrFalse, const int& Limit)
{
	m_HasLimit = TrueOrFalse;
	m_Limit = Limit;
}


bool gui::TextBox::IsSelected()
{
	return m_IsSelected;
}

void gui::TextBox::Select(const bool& IsSelected)
{
	m_IsSelected = IsSelected;
	if (m_IsSelected)
		m_Textbox.setString(m_Text.str() + "|");
	else
		m_Textbox.setString(m_Text.str());
}	

bool gui::TextBox::Contains(const sf::Vector2f& Something)
{
	return m_TextboxBackground.getGlobalBounds().contains(Something);
}


std::string gui::TextBox::GetText()
{
	return m_Text.str();
}

void gui::TextBox::Type(sf::Event Event)
{
	if (m_IsSelected)
	{
		int CharTyped = Event.text.unicode;
		if (CharTyped < 128)
		{
			if (m_HasLimit)
			{
				if (m_Text.str().length() <= m_Limit)
				{
					InputLogic(CharTyped);
				}
				else if (m_Text.str().length() > m_Limit && CharTyped == DELETE_KEY)
					DeleteLastChar();
			}
			else
				InputLogic(CharTyped);
		}
	}
}

void gui::TextBox::UpdateTextPosition()
{
	if (m_Text.str().empty())
	{
		m_Textbox.setPosition(
			m_TextboxBackground.getPosition().x + m_TextboxBackground.getSize().x / 2.f - m_Textbox.getGlobalBounds().width / 2.f,
			m_TextboxBackground.getPosition().y + m_TextboxBackground.getSize().y / 2.f - 10
		);
	}
	else
	{
		m_Textbox.setPosition(
			m_TextboxBackground.getPosition().x + m_TextboxBackground.getSize().x / 2.f - m_Textbox.getGlobalBounds().width / 2.f + 2,
			m_TextboxBackground.getPosition().y + m_TextboxBackground.getSize().y / 2.f - 10
		);
	}
}

void gui::TextBox::UpdateOutline()
{
	if (m_IsSelected)
	{
		m_TextboxBackground.setOutlineColor(sf::Color::Yellow);
		m_TextboxBackground.setOutlineThickness(2);
	}
	else
		m_TextboxBackground.setOutlineThickness(0);

}

void gui::TextBox::Update()
{
	UpdateTextPosition();
	UpdateOutline();
}

void gui::TextBox::Render(sf::RenderWindow* Window)
{
	Window->draw(m_TextboxBackground);
	Window->draw(m_Textbox);
}