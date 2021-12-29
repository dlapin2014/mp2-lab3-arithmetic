// тесты для вычисления арифметических выражений

#include <gtest.h>
#include<arithmetic.h>
TEST(Parser, expression_started_from_closed_bracket)
{

	std::string a =  ")+25=";
	Parser h(a);
	ASSERT_ANY_THROW(h.ParseToPolish());
}

TEST(Parser, binar_operator_first)
{

	std::string a = "+25+50=";
	Parser h(a);
	ASSERT_ANY_THROW(h.ParseToPolish());
}



TEST(Parser, dot_cannot_start_the_expression)
{

	std::string a = ".5+50=";
	Parser h(a);
	ASSERT_ANY_THROW(h.ParseToPolish());
}


TEST(Parser, dot_without_numbers)
{

	std::string a = "5+50.=";
	Parser h(a);
	ASSERT_ANY_THROW(h.ParseToPolish());
}



TEST(Parser, unar_minus_operator_first)
{

	std::string a = "-25+50=";
	Parser h(a);
	ASSERT_NO_THROW(h.ParseToPolish());
}


TEST(Parser, alpha_before_open_bracket)
{

	//std::string a = "-25(50+6)=";
	//Parser h(a);
	//ASSERT_ANY_THROW(h.ParseToPolish());
}

TEST(Parser, symbol_before_open_bracket)
{

	std::string a = "-h(50+6)=";
	Parser h(a);
	ASSERT_ANY_THROW(h.ParseToPolish());
}


TEST(Parser, two_binar_operations_one_after_another)
{

	std::string a = "-/(50+6)=";
	Parser h(a);
	ASSERT_ANY_THROW(h.ParseToPolish());
}

TEST(Parser, operator_before_closing_bracket)
{

	std::string a = "(50+6+)=";
	Parser h(a);
	ASSERT_ANY_THROW(h.ParseToPolish());
}


TEST(Parser, symbol_after_closing_bracket)
{

	std::string a = "(50+6)h=";
	Parser h(a);
	ASSERT_ANY_THROW(h.ParseToPolish());
}


TEST(Parser, alpha_after_closing_bracket)
{

	std::string a = "(50+6)5=";
	Parser h(a);
	ASSERT_ANY_THROW(h.ParseToPolish());
}

TEST(Parser, binar_operator_after_opening_bracket) {
	std::string a = "(+50+6)*5=";
	Parser h(a);
	ASSERT_ANY_THROW(h.ParseToPolish());
}



TEST(Parser, unknown_symbol) {
	std::string a = "(50?6)*5=";
	Parser h(a);
	ASSERT_ANY_THROW(h.ParseToPolish());
}

TEST(Parser, incorrect_input_of_float_numbers) {
	std::string a = "(50.2.1-6)*5=";
	Parser h(a);
	ASSERT_ANY_THROW(h.ParseToPolish());
}



