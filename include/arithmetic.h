// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once
#include<sstream>
#include"stack.h"
#include <iostream>
class Parser
{


private:
    std::string expr;
    TStack<std::string> resultParse;
    TStack<std::string> PolishStack;

    bool IsContainVariables = false;


    void ExamOnInCorrect() {

        int count = 0;
        for (int i = 0; i < expr.size(); i++) {
            if (expr[i] == '(') count++;
            if (expr[i] == ')') count--;
        }
        if (count != 0)
            throw std::invalid_argument("num_of_closing_and_opening_brackets_not_equal");

        for (int i = 0; i < expr.size(); i++)
        {
            if (i == 0) {
                if (IsOperation(expr[i]) && expr[i] != '=' && expr[i] != '-') {
                    std::cout << "binar_operation_cannot_be_first_symbol_of_equation";
                    throw std::invalid_argument("binar_operation_cannot_be_first_symbol_of_equation");
                }
                else if (expr[i] == ')') { std::cout << "closed_bracket_cannot_start_the_expression "; throw std::invalid_argument("close_bracket_cannot_start_the_expression "); }
                else if (expr[i] == '.') { std::cout << "dot_cannot_start_the_expression"; throw std::invalid_argument("dot_cannot_start_the_expression "); }
                else if (expr[i] == '(' && IsOperation(expr[i + 1]) && expr[i + 1] != '-') {
                    std::cout << "binar_operator_after_opening_bracket";
                    throw std::invalid_argument("binar_operator_after_opening_bracket");
                }
            }
            else {
                if (IsOperation(expr[i - 1]) && IsOperation(expr[i]) && expr[i] != '-') {
                    std::cout << "two binar operations cannot be one after another";
                    throw std::invalid_argument("two binar operations cannot be one after another");
                }
                else if (expr[i] == ')' && IsOperation(expr[i - 1])) {

                    std::cout << "operator_before_closing_bracket";

                    throw std::invalid_argument("operator_before_closing_bracket");

                }
                else if (expr[i] == ')' && (IsAlpha(expr[i + 1]) || IsSymbol(expr[i + 1]))) {
                    std::cout << "symbol_or_alpha_after_closing_bracket";
                    throw std::invalid_argument("symbol_or_alpha_after_closing_bracket");
                }
                else if (expr[i] == '(' && IsOperation(expr[i + 1]) && expr[i + 1] != '-') {
                    std::cout << "binar_operator_after_opening_bracket";
                    throw std::invalid_argument("binar_operator_after_opening_bracket");
                }
                else if (expr[i] == '(' && (IsAlpha(expr[i - 1]) || IsSymbol(expr[i - 1]))) {
                    std::cout << "symbol_or_alpha_before_opening_bracket";
                    throw std::invalid_argument("symbol_or_alpha_before_opening_bracket");
                }
                else if (expr[i] != ')' && expr[i] != '(' && !IsSymbol(expr[i]) && !IsAlpha(expr[i]) && !IsOperation(expr[i]) && expr[i] != '.') {
                    std::cout << "unknown symbol";
                    throw std::invalid_argument("unknown_symbol");
                }
                else if (expr[i] != ')' && expr[i] != '(' && !IsSymbol(expr[i]) && !IsAlpha(expr[i]) && !IsOperation(expr[i]) && expr[i] != '.') {
                    std::cout << "unknown symbol";
                    throw std::invalid_argument("unknown_symbol");
                }
                else if ((expr[i] == '.' && !IsAlpha(expr[i - 1]) && !IsAlpha(expr[i + 1])) || (expr[i] == '.' && IsAlpha(expr[i - 1]) && !IsAlpha(expr[i + 1])) || (expr[i] == '.' && !IsAlpha(expr[i - 1]) && IsAlpha(expr[i + 1]))) { std::cout << "dot_without_numbers"; throw std::invalid_argument("dot_without_numbers"); }
            }
        }


        if (expr[expr.size() - 1] != '=') {
            std::cout << "equal_not_last_symbol_of_equation";
            throw std::invalid_argument("equal_not_last_symbol_of_equation");
        }

    }


    void ExamOnContainVariables() {
        for (int i = 0; i < expr.size(); i++) {
            if (IsSymbol(expr[i])) {
                IsContainVariables = true;
                break;
            }
        }
    }


    int GetOperationPrt(std::string op) {
        int Prt;
        char t = op.c_str()[0];
        switch (t) {
        case '@': Prt = 4; break;
        case '*': Prt = 3; break;
        case '/': Prt = 3; break;
        case '+': Prt = 2; break;
        case '-': Prt = 2; break;
        case '(': Prt = 1; break;
        case '=': Prt = 0; break;
        default: Prt = -1; break;
        }

        return Prt;
    }


    bool IsOperation(char op) {
        if (op == '+' || op == '-' || op == '*' || op == '/' || op == '=' || op == '@')
            return true;
        else
            return false;
    }

    bool IsSymbol(char ch) {
        if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z'))
            return true;
        else
            return false;

    }

    bool IsAlpha(char ch) {
        if ('0' <= ch && ch <= '9')
            return true;
        else
            return false;
    }



    float doOperation(float a, float b, char op) {
        float result;

        switch (op) {
        case '*': result = a * b; break;
        case '/': result = a / b; break;
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        default: result = -1; break;
        }

        return result;

    }



public:


    Parser(std::string Expr) : expr(Expr) {

    }

    bool GetIsContainVariables() {
        return IsContainVariables;
    }

    



    


    void ParseToPolish() {
        expr.erase(remove_if(expr.begin(), expr.end(), isspace), expr.end());
        ExamOnInCorrect();
        ExamOnContainVariables();


        std::string x; std::string t;
        TStack <std::string> OperationStack;
        char ch = '+';
        int pos = 0;
        do {
            ch = expr[pos];
            x = std::string(1, ch);

            if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z')) {
                std::string t = "";
                do {

                    t += ch;
                    pos += 1;
                    ch = expr[pos];
                } while (IsSymbol(ch));

                PolishStack.push(t);


            }
            else if (('0' <= ch && ch <= '9') || ch == '.') {
                std::string t = "";
                int count = 0;
                do {

                    t += ch;
                    pos += 1;
                    ch = expr[pos];
                    if (ch == '.') count += 1;
                } while (('0' <= ch && ch <= '9') || ch == '.');

                if (count > 1) { std::cout << "incorrect_input_of_float_numbers"; throw std::invalid_argument("incorrect_input_of_float_numbers"); }

                PolishStack.push(t);


            }

            else if (x == "(") {
                OperationStack.push(x); pos += 1;
            }
            else if (x == ")") {

                pos += 1;
                while (1) {
                    std::string t = OperationStack.top();
                    OperationStack.pop();
                    if (t == "(") break;
                    PolishStack.push(t);
                }
            }
            else if ((pos == 0 && ch == '-') || (ch == '-' && IsOperation(expr[pos - 1])) || (ch == '-' && expr[pos - 1] == '(')) {
                pos += 1;
                ch = '@';
                x = "@";


                while (!OperationStack.empty()) {
                    std::string t = OperationStack.top();
                    if (GetOperationPrt(x) < GetOperationPrt(t)) {
                        OperationStack.pop();
                        PolishStack.push(t);
                    }
                    else {
                        break;
                    }
                }

                OperationStack.push(x);
            }
            else if (IsOperation(ch)) {

                pos += 1;
                while (!OperationStack.empty()) {
                    std::string t = OperationStack.top();
                    if (GetOperationPrt(x) <= GetOperationPrt(t)) {
                        OperationStack.pop();
                        PolishStack.push(t);
                    }
                    else {
                        break;
                    }
                }

                OperationStack.push(x);
            }
            else { throw std::invalid_argument("user_input_unknown_symbol"); }
        } while (x != "=");

    }


    void inputVariables() {

        TStack <std::string> temp_stack(PolishStack);

        while (!temp_stack.empty()) {
            std::string lem = temp_stack.top();
            if (IsSymbol(lem[0])) {
                std::cout << "input " << lem << ":";
                std::cin >> lem;


                for (int i = 0; i < lem.size(); i++) {
                    if (!(IsAlpha(lem[i]) || lem[i] == '.' || lem[i] == '-')) {
                        std::cout << "incorrect_input_of_variables";
                        throw std::invalid_argument("incorrect_input_of_variables");
                    }
                }
            }
            resultParse.push(lem);

            temp_stack.pop();
        }

    }










    float CountPolish() {
        TStack<std::string> count;


        while (!resultParse.empty()) {
            std::string temp = resultParse.top();
            resultParse.pop();
            if (('0' <= temp[0] && temp[0] <= '9') || (temp[0] == '-' && temp.size() > 1))
            {
                count.push(temp);
            }
            else if (temp[0] == '@') {
                std::string first = count.top();
                count.pop();
                std::string sh = std::to_string(-(std::stof(first)));
                count.push(sh);
            }
            else if (IsOperation(temp[0])) {
                std::string second = count.top();
                count.pop();
                std::string first = count.top();
                count.pop();
                std::string sh = std::to_string(doOperation(std::stof(first), std::stof(second), temp[0]));
                count.push(sh);
            }
        }


        return std::stof(count.top());
    }



};