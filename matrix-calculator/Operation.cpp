#include "Operation.h"

auto lambda = [](const auto& kv)
{
	return std::any_of(kv.second.begin(), kv.second.end(), [](const auto& x)
		{
			return x->GetWrongValueFlag() || (x->GetText() == "");
		});
};

auto lambda2 = [](const auto& z)
{
	return z->GetWrongValueFlag() || (z->GetText() == "");
};

op::Operation::Operation()
{
	TextFont.loadFromFile("Fonts/font1_bold.ttf");

}

double op::Operation::det(const std::vector<double>& matrix)
{
	int rows = sqrt(matrix.size());
	int columns = sqrt(matrix.size());
	int result = 0;
	for (int k = 0; k < columns; ++k)
	{
		std::vector<double> matrix2;
		for (int y = 1; y < rows; ++y)
		{
			for (int x = 0; x < columns; ++x)
			{
				if (x != k)
					matrix2.push_back(matrix[y * columns + x]);
			}
		}
		if (matrix2.size() == 1)
			result += matrix[k] * pow(-1, 1 + (k + 1)) * matrix2[0];
		else
			result += matrix[k] * pow(-1, 1 + (k + 1)) * det(matrix2);
	}
	return result;
}

void op::Operation::transpose(std::vector<double>& matrix)
{
	std::vector<double> result{};
	int columns = sqrt(matrix.size());
	int rows = sqrt(matrix.size());


	for (int x = 0; x < rows; ++x)
	{
		for (int y = 0; y < columns; ++y)
		{
			result.push_back(matrix[y * columns + x]);
		}
	}
	matrix.clear();
	std::copy(result.begin(), result.end(), std::back_inserter(matrix));
}

std::vector<double> op::Operation::dop(const std::vector<double>& matrix)
{
	std::vector<double> result{};
	std::vector<std::vector<double>> matrix_dop{};
	std::vector<double> temp_det;
	int columns = sqrt(matrix.size());
	int rows = sqrt(matrix.size());

	for (int deleted_row = 0; deleted_row < rows; ++deleted_row)
	{
		for (int deleted_column = 0; deleted_column < columns; ++deleted_column)
		{
			for (int y = 0; y < rows; ++y)
			{
				for (int x = 0; x < columns; ++x)
				{
					if (y != deleted_row && x != deleted_column)
						temp_det.push_back(matrix[y * columns + x]);
				}
			}
			matrix_dop.push_back(temp_det);
			temp_det.clear();
		}
	}

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			result.push_back(det(matrix_dop[y * columns + x]));
			result.back() *= pow(-1, y + 1 + x + 1);
		}
	}
	transpose(result);
	return result;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void op::Addition::Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>& Matrices,
	const std::unordered_map<std::string, gui::TextBox*>& RowTextboxes,
		const std::unordered_map<std::string, gui::TextBox*>& ColumnTextboxes,
	std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>>& Lines,
	std::unordered_map<std::string, sf::Text>& MatrixNames)
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

		int b = ((ColumnTextboxes.at("Matrix A")->GetValue()) * 60 + (ColumnTextboxes.at("Matrix A")->GetValue() - 1) * 10) / 2;
		int rows = static_cast<int>(RowTextboxes.at("Matrix A")->GetValue());
		int columns = static_cast<int>(ColumnTextboxes.at("Matrix A")->GetValue());

		sf::Vector2f TempPos;
		for (int y = 0; y < rows; ++y)
		{
			for (int x = 0; x < columns; ++x)
			{
				if (Matrices["Result"].empty())
				{
					Matrices["Result"].push_back(new gui::TextBox(15, sf::Color::Black, { Position.x - b, Position.y }, { 60, 25 }));
					TempPos = Matrices["Result"].back()->GetPosition();
				}
				else
					Matrices["Result"].push_back(new gui::TextBox(15, sf::Color::Black, { TempPos.x + x * 70, TempPos.y + y * 35.f }, { 60, 25 }));
				Matrices["Result"][y * columns + x]->SetText(Matrices["Matrix A"][y * columns + x]->GetValue() + Matrices["Matrix B"][y * columns + x]->GetValue());
			}
		}
	}
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void op::Substraction::Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>& Matrices,
	const std::unordered_map<std::string, gui::TextBox*>& RowTextboxes,
	const std::unordered_map<std::string, gui::TextBox*>& ColumnTextboxes,
	std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>>& Lines,
	std::unordered_map<std::string, sf::Text>& MatrixNames)
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

		int b = ((ColumnTextboxes.at("Matrix A")->GetValue()) * 60 + (ColumnTextboxes.at("Matrix A")->GetValue() - 1) * 10) / 2;
		int rows = static_cast<int>(RowTextboxes.at("Matrix A")->GetValue());
		int columns = static_cast<int>(ColumnTextboxes.at("Matrix A")->GetValue());

		sf::Vector2f TempPos;
		for (int y = 0; y < rows; ++y)
		{
			for (int x = 0; x < columns; ++x)
			{
				if (Matrices["Result"].empty())
				{
					Matrices["Result"].push_back(new gui::TextBox(15, sf::Color::Black, { Position.x - b, Position.y }, { 60, 25 }));
					TempPos = Matrices["Result"].back()->GetPosition();
				}
				else
					Matrices["Result"].push_back(new gui::TextBox(15, sf::Color::Black, { TempPos.x + x * 70, TempPos.y + y * 35.f }, { 60, 25 }));
				Matrices["Result"][y * columns + x]->SetText(Matrices["Matrix A"][y * columns + x]->GetValue() - Matrices["Matrix B"][y * columns + x]->GetValue());
			}
		}	
	}
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void op::Multiplication::Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>& Matrices,
	const std::unordered_map<std::string, gui::TextBox*>& RowTextboxes,
	const std::unordered_map<std::string, gui::TextBox*>& ColumnTextboxes,
	std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>>& Lines,
	std::unordered_map<std::string, sf::Text>& MatrixNames)
{
	if (!Matrices["Result"].empty())
	{
		for (gui::TextBox* e : Matrices["Result"])
			delete e;
		Matrices["Result"].clear();
	}
	if (ColumnTextboxes.at("Matrix A")->GetText() == RowTextboxes.at("Matrix B")->GetText() &&
		std::none_of(Matrices.begin(), Matrices.end(), lambda))
	{
		std::cout << "Multiplication!\n";

		int b = ((ColumnTextboxes.at("Matrix B")->GetValue()) * 60 + (ColumnTextboxes.at("Matrix B")->GetValue() - 1) * 10) / 2;

		int rows1 = static_cast<int>(RowTextboxes.at("Matrix A")->GetValue());
		int columns1 = static_cast<int>(ColumnTextboxes.at("Matrix A")->GetValue());
		int rows2 = static_cast<int>(RowTextboxes.at("Matrix B")->GetValue());
		int columns2 = static_cast<int>(ColumnTextboxes.at("Matrix B")->GetValue());

		sf::Vector2f TempPos;
		for (int y = 0; y < rows1; ++y)
		{
			for (int x = 0; x < columns2; ++x)
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

		int index = 0;
		for (int k = 0, j = 0; j < rows1; ++j, k += columns1) //poruszam sie po wierszach w A za pomoca zmiennej k
		{
			for (int g = 0; g < columns2; ++g) //poruszam sie po elemantach kolumn w B
			{
				double temp = 0;
				for (int t = 0, i = k; i < columns1 + k; ++i, ++t) // i - poruszam sie po kolejnych elementach wiersza macierzy A // ++t - poruszam sie po kolejnych wierszach macierzy B
				{
					temp += Matrices["Matrix A"][i]->GetValue() * Matrices["Matrix B"][columns2 * t + g]->GetValue();
				}
				Matrices["Result"][index]->SetText(temp); // dodaje elementy do wektora
				++index;
			}
		}
	}
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


void op::Transposition::Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>& Matrices,
	const std::unordered_map<std::string, gui::TextBox*>& RowTextboxes,
	const std::unordered_map<std::string, gui::TextBox*>& ColumnTextboxes,
	std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>>& Lines,
	std::unordered_map<std::string, sf::Text>& MatrixNames)
{
	if (!Matrices["Result"].empty())
	{
		for (gui::TextBox* e : Matrices["Result"])
			delete e;
		Matrices["Result"].clear();
	}
	if (std::none_of(Matrices["Matrix A"].begin(), Matrices["Matrix A"].end(), lambda2))
	{
		std::cout << "Transposition!\n";

		int b = ((ColumnTextboxes.at("Matrix A")->GetValue()) * 60 + (ColumnTextboxes.at("Matrix A")->GetValue() - 1) * 10) / 2;
		int rows = static_cast<int>(RowTextboxes.at("Matrix A")->GetValue());
		int columns = static_cast<int>(ColumnTextboxes.at("Matrix A")->GetValue());
		sf::Vector2f TempPos;

		for (int index =0, x = 0; x < columns; ++x)
		{
			for (int y = 0; y < rows; ++y, ++index)
			{
				if (Matrices["Result"].empty())
				{
					Matrices["Result"].push_back(new gui::TextBox(15, sf::Color::Black, { Position.x - b, Position.y }, { 60, 25 }));
					TempPos = Matrices["Result"].back()->GetPosition();
				}
				else
				{
					Matrices["Result"].push_back(new gui::TextBox(15, sf::Color::Black, { TempPos.x + y * 70, TempPos.y + x * 35.f }, { 60, 25 }));

				}
				double c = Matrices["Matrix A"][y * columns + x]->GetValue();
				Matrices["Result"].back()->SetText(c);
				std::cout << "GetValue()=" << c << std::endl;
			}
		}	
	}

}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void op::Determinant::Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>& Matrices,
	const std::unordered_map<std::string, gui::TextBox*>& RowTextboxes,
	const std::unordered_map<std::string, gui::TextBox*>& ColumnTextboxes,
	std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>>& Lines,
	std::unordered_map<std::string, sf::Text>& MatrixNames)
{
	if (!Matrices["Result"].empty())
	{
		for (gui::TextBox* e : Matrices["Result"])
			delete e;
		Matrices["Result"].clear();
	}
	if (RowTextboxes.at("Matrix A")->GetText() == ColumnTextboxes.at("Matrix A")->GetText() &&
		std::none_of(Matrices["Matrix A"].begin(), Matrices["Matrix A"].end(), lambda2))
	{
		std::cout << "Determinant!\n";
		std::vector<double> TempMatrixA;

		for (auto& e : Matrices["Matrix A"])
		{
			TempMatrixA.push_back(e->GetValue());
		}

		double result = det(TempMatrixA);
		std::cout << "det(A) = " << result << std::endl;

	}

}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void op::Inversion::Calculate(std::unordered_map<std::string, std::vector<gui::TextBox*>>& Matrices,
	const std::unordered_map<std::string, gui::TextBox*>& RowTextboxes,
	const std::unordered_map<std::string, gui::TextBox*>& ColumnTextboxes,
	std::unordered_map<std::string, std::pair<sf::RectangleShape, sf::RectangleShape>>& Lines,
	std::unordered_map<std::string, sf::Text>& MatrixNames)
{
	if (!Matrices["Result"].empty())
	{
		for (gui::TextBox* e : Matrices["Result"])
			delete e;
		Matrices["Result"].clear();
	}
	if (RowTextboxes.at("Matrix A")->GetText() == ColumnTextboxes.at("Matrix A")->GetText() &&
		std::none_of(Matrices["Matrix A"].begin(), Matrices["Matrix A"].end(), lambda2))

	{
		std::cout << "Inversion!\n";
		std::vector<double> TempMatrixA;
		for (auto& e : Matrices["Matrix A"])
		{
			TempMatrixA.push_back(e->GetValue());
		}

		if (det(TempMatrixA) != 0)
		{
			auto result = dop(TempMatrixA);

			std::transform(result.begin(), result.end(), result.begin(), std::bind(std::multiplies<double>(), std::placeholders::_1, 1 / det(TempMatrixA)));

			int b = ((ColumnTextboxes.at("Matrix A")->GetValue()) * 60 + (ColumnTextboxes.at("Matrix A")->GetValue() - 1) * 10) / 2;
			int rows = static_cast<int>(RowTextboxes.at("Matrix A")->GetValue());
			int columns = static_cast<int>(ColumnTextboxes.at("Matrix A")->GetValue());

			sf::Vector2f TempPos;
			for (int y = 0; y < rows; ++y)
			{
				for (int x = 0; x < columns; ++x)
				{
					if (Matrices["Result"].empty())
					{
						Matrices["Result"].push_back(new gui::TextBox(15, sf::Color::Black, { Position.x - b, Position.y }, { 60, 25 }));
						TempPos = Matrices["Result"].back()->GetPosition();
					}
					else
						Matrices["Result"].push_back(new gui::TextBox(15, sf::Color::Black, { TempPos.x + x * 70, TempPos.y + y * 35.f }, { 60, 25 }));
					Matrices["Result"][y * columns + x]->SetText(result[y * columns + x]);
				}
			}
			int a = ((rows) * 25 + (rows - 1) * 10);

			Lines["Result"].first = sf::RectangleShape(sf::Vector2f(3, a + 10));
			Lines["Result"].first.setPosition({ Matrices["Result"].front()->GetPosition().x - 10, Matrices["Result"].front()->GetPosition().y - 5 });
			Lines["Result"].second = sf::RectangleShape(sf::Vector2f(3, a + 10));
			Lines["Result"].second.setPosition({ Matrices["Result"].front()->GetPosition().x + 2 * b + 7, Matrices["Result"].front()->GetPosition().y - 5 });

			MatrixNames["Result"].setFont(TextFont);
			MatrixNames["Result"].setCharacterSize(20);
			MatrixNames["Result"].setString("Result");
			MatrixNames["Result"].setPosition({ MatrixName_PosX, MatrixName_PosY - 30 });
		}
	}
}
