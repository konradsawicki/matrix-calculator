#pragma once
#include "Gui.h"

class MatrixCalculator
{
private:
	// Variables
	sf::RenderWindow* m_Window;
	sf::Event m_Event;
	sf::Vector2f m_MousePos;

	sf::Texture m_BackgroundTexture;
	sf::RectangleShape m_Background;
	gui::TextBox* m_ActiveTextbox;
	std::vector<gui::TextBox*> m_Matrix;
	bool m_ActiveFlag;

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

	void Update();
	void Render();

	void Run();
};