#pragma once
#include "Gui.h"

namespace op
{
	class Operation
	{
	protected:

		
	public:
		Operation();
		virtual ~Operation();

		virtual void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
		const std::unordered_map<std::string, gui::TextBox*>&,
		const std::unordered_map<std::string, gui::TextBox*>&) = 0;
	};



	class Addition : public Operation
	{
	private:


	public:
		Addition();
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&) override;
	};



	class Substraction : public Operation
	{
	private:


	public:
		Substraction();
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&) override;
	};



	class Multiplication : public Operation
	{
	private:


	public:
		Multiplication();
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&) override;
	};



	class Transposition : public Operation
	{
	private:


	public:
		Transposition();
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&) override;
	};



	class Determinant : public Operation
	{
	private:


	public:
		Determinant();
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&) override;
	};


	class Inversion : public Operation
	{
	private:


	public:
		Inversion();
		void Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>&,
			const std::unordered_map<std::string, gui::TextBox*>&,
			const std::unordered_map<std::string, gui::TextBox*>&) override;
	};
}

