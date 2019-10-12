// lambda.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <memory>
#include <functional>

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
	} (); // call the lambda immediately
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
	std::cout << "D) lambda as function parameter\n";

	std::cout << "E) constexpr\n";
	// a constexpr is a expression that can be evaluated at compile time
	// it has an advantage in performance over am expression that is evaluated at
	// run time
	int const x = 10, y = 20;
	constexpr int z = x * y;
	std::cout << "   z...: " << z << std::endl;
	// can't make a lambda explicitly a constexpr, 
	// this has to do with the conformance mode of the compiler (/std:c++17)
	// the following lambda is a implicitly constexpr lambda
	// the compiler marks the lambda with a comment:
	// a lambda expression is not allowed in a constant expression
	// (so there will be undefined behaviour, i assume)
	constexpr auto a = [x, y]() { return x * y; };
	std::cout << "   a...: " << z << std::endl;

	std::cout << "EXAMPLE 1\n";
	std::cout << "assign the lambda expression that adds two numbers to an auto variable\n";
	auto f1 = [](int x, int y) { return x + y; };
	std::cout << "1 + 2 = " << f1(1, 2) << std::endl;
	std::cout << "assign the same lambda expression to a function object\n";
	std::function<int(int, int)> f2 = [](int x, int y) { return x + y; };
	std::cout << "2 + 3 = " << f2(2, 3) << std::endl;

	std::cout << "EXAMPLE 2\n";
	std::cout << "the following lambda expression captures 'a_' by value and 'b_' by reference\n";
	int a_ = 1;
	int b_ = 2;
	std::function<int()> f = [a_, &b_]() { return a_ + b_; };
	// change the values of 'a_' and 'b_'
	a_ = 2;
	b_ = 3;
	std::cout << "a_ + b_ = " << f() << std::endl;

	std::cout << "EXAMPLE 3\n";
	// use a lambda expression as a paramter in a function
	// TODO

	// spaceship comparison <=>, only in C++20

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
