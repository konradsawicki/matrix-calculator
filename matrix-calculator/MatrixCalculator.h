#pragma once
#include "Operation.h"

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
	std::unordered_map<std::string, sf::Vector2f> m_MatrixPositions;
	std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>> m_Lines;

	std::unordered_map<std::string, gui::TextBox*> m_RowTextboxes;
	std::unordered_map<std::string, gui::TextBox*> m_ColumnTextboxes;

	sf::Font m_TextFont;
	std::unordered_map<std::string, sf::Text> m_TextsCharX;
	std::unordered_map<std::string, sf::Text> m_MatrixNames;

	gui::RadioButton* m_ActiveRadioButton;
	std::vector<gui::RadioButton*> m_RadioButtons;
	std::vector<std::string> m_OperationsNames;

	gui::Button* m_CalculateButton;

	std::unordered_map<std::string, op::Operation*> m_Operations;

	bool m_ActiveFlag;
	bool m_MouseTextMatrixAFlag;
	bool m_MouseTextMatrixBFlag;
	bool m_MouseTextDimensionsFlag;
	bool m_MouseHandFlag;
	bool m_DimensionsChangeFlag;

	// Initializer functions
	void InitWindow();
	void InitBackground();
	void InitGui();
	void InitMatrix(const std::string&, const sf::Vector2f&);


public:
	MatrixCalculator();
	virtual ~MatrixCalculator();

	void UpdateSFMLEvents();
	void UpdateGui();
	void UpdateMousePosition();
	void UpdateMouseLook();
	void UpdateTextbox(gui::TextBox*);
	void UpdateDimensionTextbox(gui::TextBox*, const std::string&);
	void UpdateTextboxesAfterMouseRelease();
	void UpdateTextboxesAfterKeyRelease();
	void UpdateRadioButton(gui::RadioButton*);
	void UpdateLines(const std::string&, const int&, const int&);



	void RenderGui();

	void Update();
	void Render();

	void Run();
};