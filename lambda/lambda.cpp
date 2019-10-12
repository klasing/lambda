// lambda.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <conio.h>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

//****************************************************************************
//*                     func
//****************************************************************************
int func(const char& a
	, const char& b
	, int i
)
{
	std::cout << a << " + " << b << " = " << i << std::endl;
	return 0;
}
void func1(int i)
{
	std::cout << "i: " << i << std::endl;
};
//****************************************************************************
//*                     functor
//****************************************************************************
struct functor
{
	void operator()(int i)
	{
		std::cout << "i: " << i << std::endl;
	}
};
//****************************************************************************
//*                     FunctorClass
//****************************************************************************
struct FunctorClass
{
	void func(int i)
	{
		std::cout << "i: " << i << std::endl;
	}
};
//****************************************************************************
//*                     wrap
//****************************************************************************
template <typename T>
T wrap(T a, T b)
{
	auto f = [](T a, T b) -> T { return a + b; };
	return f(a, b);
}
//****************************************************************************
//*                     an_exception
//****************************************************************************
struct an_exception : public std::exception
{
	const char* what() const throw()
	{
		return "an exception is thrown";
	}
};
//****************************************************************************
//*                     main
//****************************************************************************
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
	/*constexpr*/ auto a = [x, y]() { return x * y; };
	std::cout << "   a...: " << a() << std::endl;

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
	std::cout << "3.A) use a lambda expression as a parameter in a function\n";
	auto f3 = [](int a, int b) -> int { return a + b; };
	func('a', 'b', f3(a_, b_));
	// function object points to function
	std::cout << "3.B) function object points to function\n";
	std::function<void(int)> f4 = func1;
	f4(1);
	// function object points to functor
	std::cout << "3.C) function object points to functor\n";
	f4 = functor();
	f4(2);
	// function object points to member function
	std::cout << "3.D) function object points to member function\n";
	const FunctorClass functor_object;
	using std::placeholders::_1;
	f4 = std::bind(&FunctorClass::func, functor_object, _1);
	f4(3);
	// templated lambda
	std::cout << "EXAMPLE 4\n";
	std::cout << "templated lambda\n";
	std::cout.precision(2);
	std::cout << "1.05 + 2.05 = " << std::fixed << wrap(1.05, 2.05) << std::endl;
	std::cout << "1 + 2 = " << (1, 2) << std::endl;
	// exception handling in lambda
	std::cout << "EXAMPLE 4\n";
	std::cout << "exception handling in lambda\n";
	auto f5 = []() throw()
	{
		try
		{
			throw an_exception();
		}
		catch (an_exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	};
	f5();

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
