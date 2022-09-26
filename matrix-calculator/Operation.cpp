#include "Operation.h"

auto lambda = [](const auto& kv)
{
	return std::any_of(kv.second.begin(), kv.second.end(), [](const auto& x)
		{
			return x->GetWrongValueFlag() || (x->GetText() == "");
		});
};

op::Operation::Operation()
{

}

op::Operation::~Operation()
{

}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

op::Addition::Addition()
{

}

void op::Addition::Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>& Matrices,
	const std::unordered_map<std::string, gui::TextBox*>& RowTextboxes,
		const std::unordered_map<std::string, gui::TextBox*>& ColumnTextboxes)
{	
	if (!Matrices["Result"].empty())
	{
		for (gui::TextBox* e : Matrices["Result"])
			delete e;
		Matrices["Result"].clear();
	}
	if (RowTextboxes.at("Matrix A")->GetText() == RowTextboxes.at("Matrix B")->GetText() &&
		ColumnTextboxes.at("Matrix A")->GetText() == ColumnTextboxes.at("Matrix B")->GetText() &&
		std::none_of(Matrices.begin(), Matrices.end(), lambda))
	{

		std::cout << "Addition!\n";

		sf::Vector2f Position = { 1600 - 335.f, 380.f };
		int b = ((ColumnTextboxes.at("Matrix A")->GetValue()) * 60 + (ColumnTextboxes.at("Matrix A")->GetValue() - 1) * 10) / 2;

		sf::Vector2f TempPos;
		for (int y = 0; y < static_cast<int>(RowTextboxes.at("Matrix A")->GetValue()); ++y)
		{
			for (int x = 0; x < static_cast<int>(ColumnTextboxes.at("Matrix A")->GetValue()); ++x)
			{
				if (Matrices["Result"].empty())
				{
					Matrices["Result"].push_back(new gui::TextBox(15, sf::Color::Black, { Position.x - b, Position.y }, { 60, 25 }));
					TempPos = Matrices["Result"].back()->GetPosition();
				}
				else
					Matrices["Result"].push_back(new gui::TextBox(15, sf::Color::Black, { TempPos.x + x * 70, TempPos.y + y * 35.f }, { 60, 25 }));
			}
		}

		for (int i = 0; i < Matrices["Matrix A"].size(); ++i)
			Matrices["Result"][i]->SetText(Matrices["Matrix A"][i]->GetValue() + Matrices["Matrix B"][i]->GetValue());
	}
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

op::Substraction::Substraction()
{

}

void op::Substraction::Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>& Matrices,
	const std::unordered_map<std::string, gui::TextBox*>& RowTextboxes,
	const std::unordered_map<std::string, gui::TextBox*>& ColumnTextboxes)
{
	if (!Matrices["Result"].empty())
	{
		for (gui::TextBox* e : Matrices["Result"])
			delete e;
		Matrices["Result"].clear();
	}
	if (RowTextboxes.at("Matrix A")->GetText() == RowTextboxes.at("Matrix B")->GetText() &&
		ColumnTextboxes.at("Matrix A")->GetText() == ColumnTextboxes.at("Matrix B")->GetText() &&
		std::none_of(Matrices.begin(), Matrices.end(), lambda))
	{
		std::cout << "Substraction!\n";

		sf::Vector2f Position = { 1600 - 335.f, 380.f };
		int b = ((ColumnTextboxes.at("Matrix A")->GetValue()) * 60 + (ColumnTextboxes.at("Matrix A")->GetValue() - 1) * 10) / 2;

		sf::Vector2f TempPos;
		for (int y = 0; y < static_cast<int>(RowTextboxes.at("Matrix A")->GetValue()); ++y)
		{
			for (int x = 0; x < static_cast<int>(ColumnTextboxes.at("Matrix A")->GetValue()); ++x)
			{
				if (Matrices["Result"].empty())
				{
					Matrices["Result"].push_back(new gui::TextBox(15, sf::Color::Black, { Position.x - b, Position.y }, { 60, 25 }));
					TempPos = Matrices["Result"].back()->GetPosition();
				}
				else
					Matrices["Result"].push_back(new gui::TextBox(15, sf::Color::Black, { TempPos.x + x * 70, TempPos.y + y * 35.f }, { 60, 25 }));
			}
		}

		for (int i = 0; i < Matrices["Matrix A"].size(); ++i)
			Matrices["Result"][i]->SetText(Matrices["Matrix A"][i]->GetValue() - Matrices["Matrix B"][i]->GetValue());
	}
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

op::Multiplication::Multiplication()
{

}

void op::Multiplication::Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>& Matrices,
	const std::unordered_map<std::string, gui::TextBox*>& RowTextboxes,
	const std::unordered_map<std::string, gui::TextBox*>& ColumnTextboxes)
{
	if (!Matrices["Result"].empty())
	{
		for (gui::TextBox* e : Matrices["Result"])
			delete e;
		Matrices["Result"].clear();
	}
	if (ColumnTextboxes.at("Matrix A")->GetText() == RowTextboxes.at("Matrix B")->GetText() &&
		std::none_of(Matrices.begin(), Matrices.end(), lambda))
		std::cout << "Multiplication!\n";
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

op::Transposition::Transposition()
{

}


void op::Transposition::Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>& Matrices,
	const std::unordered_map<std::string, gui::TextBox*>& RowTextboxes,
	const std::unordered_map<std::string, gui::TextBox*>& ColumnTextboxes)
{
	if(std::none_of(Matrices.begin(), Matrices.end(), lambda))
		std::cout << "Transposition!\n";
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

op::Determinant::Determinant()
{

}

void op::Determinant::Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>& Matrices,
	const std::unordered_map<std::string, gui::TextBox*>& RowTextboxes,
	const std::unordered_map<std::string, gui::TextBox*>& ColumnTextboxes)
{
	if(RowTextboxes.at("Matrix A")->GetText() == ColumnTextboxes.at("Matrix A")->GetText() &&
		std::none_of(Matrices.begin(), Matrices.end(), lambda))
		std::cout << "Determinant!\n";
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

op::Inversion::Inversion()
{

}

void op::Inversion::Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>& Matrices,
	const std::unordered_map<std::string, gui::TextBox*>& RowTextboxes,
	const std::unordered_map<std::string, gui::TextBox*>& ColumnTextboxes)
{
	if (RowTextboxes.at("Matrix A")->GetText() == ColumnTextboxes.at("Matrix A")->GetText() &&
		std::none_of(Matrices.begin(), Matrices.end(), lambda))
		std::cout << "Inversion!\n";
}
