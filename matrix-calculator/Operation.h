#pragma once
#include "Gui.h"

namespace op
{
	class Operation
	{
	protected:
	sf::Vector2f Position = { 1600 - 335.f, 380.f };
	double det(const std::vector<double>&);
	void transpose(std::vector<double>&);
	std::vector<double> dop(const std::vector<double>&);
	float MatrixName_PosX = Position.x - 30.f;
	float MatrixName_PosY = Position.y - 60.f;
	sf::Font TextFont;

	public:
		Operation();
		virtual void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
		const std::unordered_map<std::string, gui::TextBox*>&,
		const std::unordered_map<std::string, gui::TextBox*>&,
		std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>>&,
			std::unordered_map<std::string, sf::Text>&) = 0;
	};



	class Addition : public Operation
	{
	private:


	public:
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>>&,
			std::unordered_map<std::string, sf::Text>&) override;
	};



	class Substraction : public Operation
	{
	private:


	public:
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>>&,
			std::unordered_map<std::string, sf::Text>&) override;
	};



	class Multiplication : public Operation
	{
	private:


	public:
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>>&,
			std::unordered_map<std::string, sf::Text>&) override;
	};



	class Transposition : public Operation
	{
	private:


	public:
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>>&,
			std::unordered_map<std::string, sf::Text>&) override;
	};



	class Determinant : public Operation
	{
	private:

	public:
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>>&,
			std::unordered_map<std::string, sf::Text>&) override;
	};


	class Inversion : public Operation
	{
	private:


	public:
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>>&,
			std::unordered_map<std::string, sf::Text>&) override;
	};
}

