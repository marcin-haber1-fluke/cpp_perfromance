//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>

/* Variadic templates allow to create a template with any number of parameters
 *
 * Example:
 * template<typename... Ts>
 * void Get( const Ts& ... args ) Compiler will create a coma separated list of parameters
 * {
 *
 * }
 *
 */

template<typename... Ts>
void WorkWithParameters( const Ts& ... a_args )
{
	// One of the idea is to use std::tie() to create tuple out of given parameters and the work with them
	auto t = std::tie( a_args... );
	std::cout << "Value of int: " << std::get<0>( t ) << std::endl;
	std::cout << "Value of bool: " << std::get<1>( t ) << std::endl;
	std::cout << "Value of string: " << std::get<2>( t ) << std::endl;
}

TEST( VariadicTemplate, UsingParameters )
{
	WorkWithParameters( 10, true, "string" );
}


void Print()
{
	std::cout << "End of recursion" << std::endl;
}

template<typename Head, typename... Ts>
void Print( const Head& head, const Ts& ... tail )
{
	std::cout << "Head: " << head << std::endl;
	Print( tail... );
}

TEST( VariadicTemplate, HeadTailIdiom )
{
	Print( 10, true, "string" );
}