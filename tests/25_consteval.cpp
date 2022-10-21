//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>

consteval auto sum( int a, int b )
{
	return a + b;
}

// Consteval functions are also called immediate functions
TEST( Templates, Consteval )
{
	auto x = sum( 10, 11 );
	std::cout << "Sum: " << x << std::endl;

// This code will not compile, consteval can be used only in compile time, so all parameters should be known
// during compilation
//	auto a = 10;
//	x = sum( a, 11 );
}