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

	public:
		virtual void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
		const std::unordered_map<std::string, gui::TextBox*>&,
		const std::unordered_map<std::string, gui::TextBox*>&) = 0;
	};



	class Addition : public Operation
	{
	private:


	public:
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&) override;
	};



	class Substraction : public Operation
	{
	private:


	public:
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&) override;
	};



	class Multiplication : public Operation
	{
	private:


	public:
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&) override;
	};



	class Transposition : public Operation
	{
	private:


	public:
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&) override;
	};



	class Determinant : public Operation
	{
	private:

	public:
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&) override;
	};


	class Inversion : public Operation
	{
	private:


	public:
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&) override;
	};
}

