#pragma once
#include "Gui.h"

class MatrixCalculator
{
private:
	// Variables
	sf::RenderWindow* m_Window;
	sf::Event m_Event;

	// Initializer functions
	void InitWindow();
	void InitBackground();
	void InitGui();

public:
	MatrixCalculator();
	virtual ~MatrixCalculator();

	void UpdateSFMLEvents();

	void Update();
	void Render();

	void Run();
};