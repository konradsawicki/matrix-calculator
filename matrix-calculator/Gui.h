#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <functional>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

enum class BUTTON_STATES
{
	BTN_IDLE, BTN_HOVER, BTN_ACTIVE
};


namespace gui
{

	class Button
	{
	private:
		BUTTON_STATES m_ButtonState;

		sf::RectangleShape m_Button;
		sf::Text m_Text;
		sf::Font m_Font;

		sf::Color m_IdleColor;
		sf::Color m_HoverColor;
		sf::Color m_ActiveColor;

	public:
		Button(float, float, float, float, std::string,
			sf::Color, sf::Color, sf::Color, const int&);
		~Button();

		bool Contains(const sf::Vector2f&) const;
		std::string GetText() const;

		void SetText(const sf::String& Text);
		void setOutlineThickness(int);

		void Update(const sf::Vector2f&);
		void Render(sf::RenderTarget*);
	};

	class TextBox
	{
	private:
		sf::Font m_Font;
		sf::Text m_Textbox;
		std::ostringstream m_Text;
		bool m_IsSelected;
		bool m_HasLimit = false;
		int m_Limit;

		bool m_WrongValueFlag = false;

		sf::RectangleShape m_TextboxBackground;

		void InputLogic(const int&);
		void DeleteLastChar();
		void UpdateTextPosition();
		void UpdateOutline();

	public:
		TextBox() = default;
		TextBox(const int&, sf::Color, const sf::Vector2f&, const sf::Vector2f&);

		void SetLimit(const bool&);
		void SetLimit(const bool&, const int&);

		bool IsSelected();
		void Select(const bool&);
		bool Contains(const sf::Vector2f&);
		
		bool GetWrongValueFlag() const;
		sf::Vector2f GetPosition();
		std::string GetText() const;
		double GetValue() const;

		void SetText(double);

		void Type(sf::Event);
		void CheckText();

		void Update();
		void Render(sf::RenderWindow*);
	};

	class RadioButton
	{
	private:
		sf::RectangleShape m_ButtonBackground;
		sf::CircleShape m_OuterCircle;
		sf::CircleShape m_InnerCircle;
		sf::Font m_FontLight;
		sf::Font m_FontBold;
		sf::Text m_Text;

		sf::Color m_InactiveColor;
		sf::Color m_ActiveColor;

		bool m_ActiveFlag;

	public:
		RadioButton(const float&, const sf::Vector2f&, const std::string&);
		bool Contains(const sf::Vector2f&);

		void SetActive();
		void SetInactive();

		std::string GetText() const;

		bool IsActive();
		sf::Vector2f GetPosition();

		void Update();
		void Render(sf::RenderWindow*);
	};
}


