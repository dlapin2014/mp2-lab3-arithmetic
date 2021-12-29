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
public:


    Parser(std::string Expr) : expr(Expr) {

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





    void ExamOnInCorrect() {
        for (int i = 0; i < expr.size(); i++)
        {
            if (i == 0) {
                if (IsOperation(expr[i]) && expr[i] != '=' && expr[i] != '-') {
                    std::cout << "binar_operation_cannot_be_first_symbol_of_equation";
                    throw std::invalid_argument("binar_operation_cannot_be_first_symbol_of_equation");
                }
                else if (expr[i] == ')') { std::cout << "closed_bracket_cannot_start_the_expression "; throw std::invalid_argument("open_bracket_cannot_start_the_expression "); }
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
                else if (expr[i]!=')' && expr[i]!='(' && !IsSymbol(expr[i]) && !IsAlpha(expr[i]) && !IsOperation(expr[i]) && expr[i]!='.') {
                    std::cout << "unknown symbol";
                    throw std::invalid_argument("unknown_symbol");
                }
            }
        }
    }


    void ParseToPolish() {
        expr.erase(remove_if(expr.begin(), expr.end(), isspace), expr.end());
        ExamOnInCorrect();
        


        //std::stringstream temp;
        int count = 0;
        std::stringstream is(expr);
        char ch; char prev; std::string x; std::string t;
        TStack <std::string> PolishStack, OperationStack;
        ch = '+';
        do {

            prev = ch;
            ch = is.peek();
            x = std::string(1, ch);




            if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z')) {
                std::string t = "";
                do {

                    t += ch;
                    is.ignore();
                    ch = is.peek();
                } while (IsSymbol(ch));

                PolishStack.push(t);


            }
            else if (('0' <= ch && ch <= '9') || ch == '.') {
                std::string t = "";
                int count = 0;
                do {

                    t += ch;
                    is.ignore();
                    ch = is.peek();
                    if (ch == '.') count += 1;
                } while (('0' <= ch && ch <= '9') || ch == '.');

                if (count > 1) { std::cout << "incorrect_input_of_float_numbers"; throw std::invalid_argument("incorrect_input_of_float_numbers"); }

                PolishStack.push(t);


            }



            /*if ('0' <= ch && ch <= '9') {
                float sh;
                is >> sh;
                PolishStack.push(std::to_string(sh));
            }*/



            else if (x == "(") {
                OperationStack.push(x); is.ignore();
            }
            else if (x == ")") {
                /*if (IsOperation(prev)) throw std::invalid_argument("operator_before_closing_bracket");*/
                is.ignore();
                while (1) {
                    std::string t = OperationStack.top();
                    OperationStack.pop();
                    if (t == "(") break;
                    PolishStack.push(t);
                }
            }
            /*else if (ch == '-' && IsOperation(prev)) {
                is.ignore();
                ch = '@';
                x = "@";


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


            }*/
            else if (IsOperation(ch)) {

                


                is.ignore();
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
            else { throw std::invalid_argument("user input unknown symbol"); }
        } while (x != "=");


        while (!PolishStack.empty()) {
            std::string lem = PolishStack.top();
            if (IsSymbol(lem[0])) {
                std::cout << "input " << lem << ":";
                std::cin >> lem;
            }
            resultParse.push(lem);

            PolishStack.pop();
        }



        /*std::string result = "";
        while (!resultParse.empty()) {
            result += resultParse.top();
            result += " ";
            resultParse.pop();
        }

        std::cout << result;*/



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


    float CountPolish() {
        /*std::string result = "";
        while (!resultParse.empty()) {
            result += resultParse.top();
            result += " ";
            resultParse.pop();
        }*/

        //std::cout << result;

        float t=0;
        TStack<std::string> count;

        while (!resultParse.empty()) {
            std::string temp = resultParse.top();
            resultParse.pop();
            if ('0' <= temp[0] && temp[0] <= '9')
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

        
        
        //std::cout << "\n\n     " << count.top() << " ";
        return std::stof(count.top());
    }









};