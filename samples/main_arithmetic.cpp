// реализация пользовательского приложения
#include <iostream>
#include <string>
#include <arithmetic.h>
int main()
{
	int n;
	std::cout << "1.parse expression\n";
	std::cout << "2.exit\n";
	std::cout << ">>"; std::cin >> n;
	while (n != 2) {
		std::string input = "";


		std::cout << "input expression. input '.', not ','. expression must end on'=':\n";

		std::cin.clear();
		std::cin.clear();
		std::cin.ignore();
		getline(std::cin, input);

		//std::cout << input;

		Parser b(input);
		b.ParseToPolish();
		float result = b.CountPolish();
		std::cout << "result: " << result;

		std::cout << "\n1.parse expression\n";
		std::cout << "2.exit\n";
		std::cout << ">>"; std::cin >> n;


	}


	

  return 0;
}
