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
	gui::TextBox* m_TempDimensionTextbox;

	std::unordered_map<std::string, std::vector<gui::TextBox*>> m_Matrices;
	std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>> m_Lines;

	std::unordered_map<std::string, gui::TextBox*> m_DimensionX_Textboxes;
	std::unordered_map<std::string, gui::TextBox*> m_DimensionY_Textboxes;

	sf::Font m_TextFont;
	std::unordered_map<std::string, sf::Text> m_TextsCharX;
	std::unordered_map<std::string, sf::Text> m_MatrixNames;

	
	float m_DimensionXMatrixTextbox;
	float m_DimensionYMatrixTextbox;

	gui::RadioButton* m_ActiveRadioButton;
	std::vector<gui::RadioButton*> m_RadioButtons;
	std::vector<std::string> m_Operations;


	bool m_ActiveFlag;
	bool m_MouseTextMatrixAFlag;
	bool m_MouseTextMatrixBFlag;
	bool m_MouseTextDimensionsFlag;
	bool m_MouseHandFlag;
	bool m_DimensionsChangeFlag;

	int id = 0;
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
	void UpdateTextbox(gui::TextBox*);
	void UpdateDimensionTextbox(gui::TextBox*);
	void UpdateRadioButton(gui::RadioButton*);
	void UpdateLines();

	void RenderGui();

	void Update();
	void Render();

	void Run();
};