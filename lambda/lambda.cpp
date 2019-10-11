// lambda.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <memory>

int main()
{
	std::cout << " 1  2     3       4      5     6\n";
	std::cout << " |  |     |       |      |     |\n";
	std::cout << "[=]( ) mutable throw() -> int { }\n";
	std::cout << "\n";
	std::cout << "1) capture clause (lambda-introducer)\n";
	std::cout << "2) parameter list (lambda declarator)\n";
	std::cout << "3) mutable specification (optional)\n";
	std::cout << "4) exception specification (optional)\n";
	std::cout << "5) trailing-return-type (optional)\n";
	std::cout << "6) lambda body\n";
	std::cout << "\n";

	std::string str = "capture", str_return = "";
	auto breturn = [&str]() mutable -> bool
	{
		str = "captured";
		return true;
	} ();
	std::cout << "A) modify capture...............: " << str << std::endl;

	auto pstr = std::make_unique<std::string>(str);
	auto breturn_ = [ptr = std::move(pstr)](std::string& str_return) -> bool
	{
		str_return = *ptr;
		return true;
	} (str_return);
	std::cout << "B) bring capture to parameter...: " << str_return << std::endl;

	auto lambda = [](std::string str_return)
	{
		std::cout << "C) using function pointer.......: " << str_return << std::endl;
	};
	void (*pfunc)(std::string) = lambda;
	pfunc(str_return);

	std::cout << "\n";
	std::cout << "Hit any key ...";
	int i = _getch();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
