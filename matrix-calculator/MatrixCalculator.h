#pragma once
#include "Gui.h"

class MatrixCalculator
{
private:
	// Variables
	sf::RenderWindow* m_Window;
	sf::Event m_Event;
	sf::Vector2f m_MousePos;
	sf::Cursor m_Cursor;

	sf::Texture m_BackgroundTexture;
	sf::RectangleShape m_Background;
	sf::Font m_TitleFont;
	sf::Text m_TitleText;

	gui::TextBox* m_ActiveTextbox;
	gui::TextBox* m_MouseTextbox;
	std::vector<gui::TextBox*> m_Matrix;

	gui::RadioButton* m_ActiveRadioButton;
	std::vector<gui::RadioButton*> m_RadioButtons;
	std::vector<std::string> m_Operations;


	bool m_ActiveFlag;
	bool m_MouseTextFlag;
	bool m_MouseHandFlag;

	// Initializer functions
	void InitWindow();
	void InitBackground();
	void InitGui();

public:
	MatrixCalculator();
	virtual ~MatrixCalculator();

	void UpdateSFMLEvents();
	void UpdateGui();
	void UpdateMousePosition();
	void UpdateMouseLook();

	void RenderGui();

	void Update();
	void Render();

	void Run();
};