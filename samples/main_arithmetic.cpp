// реализация пользовательского приложения
#include <iostream>
#include <string>
#include <arithmetic.h>
void input_string() {
	int flag = 0;
		do {
			try {
				
				std::cout << "\ninput expression. input '.', not ','. expression must end on'=':\n";
				std::string input = "";
		
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());


				getline(std::cin, input);
				flag = 0;
				Parser b(input);
				b.ParseToPolish();
				if (b.GetIsContainVariables()) {
					
					b.inputVariables();
					float result = b.CountPolish();
					std::cout << "result: " << result;
					int n;
					std::cout << "\n1.to menu\n";
					std::cout << "2.input_new_variables\n";
					std::cout << ">>"; std::cin >> n;
					while (n != 1) {
						b.inputVariables();
						float result = b.CountPolish();
					    std::cout << "result: " << result;
						std::cout << "\n1.to menu\n";
						std::cout << "2.input_new_variables\n";
						std::cout << ">>"; std::cin >> n;
					}
				}
				else {
					b.inputVariables();
					float result = b.CountPolish();
					std::cout << "result: " << result;
				}
			}
			catch (std::invalid_argument err) {
				
				flag = 1;
			}
		} while (flag == 1);
}
int main()
{
	int n;
	std::cout << "1.parse expression\n";
	std::cout << "2.exit\n";
	std::cout << ">>"; std::cin >> n;
	while (n != 2) {

		input_string();

		std::cout << "\n1.parse expression\n";
		std::cout << "2.exit\n";
		std::cout << ">>"; std::cin >> n;
	}

  return 0;
}
