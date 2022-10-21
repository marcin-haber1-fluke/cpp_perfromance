//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>

// Why it can be useful:
// 1. Template are too generic, this help us add limitation on the type
// 2. Normally error is found when C++ code is generated, with constraints it can be found in instantiation phase
// 3. Template programming is hard to maintain in big projects, constraints make them more clean
// 4. if constexpr are hard to read when grow up, so it's better sometimes to use constraints
//
// Template handling:
// Templates -> Instantiate (errors occurs here when using constraints and concepts) -> Function/Classes -> Compilation -> Machine code -> Execution -> Machine

template<typename T>
struct Point2DNoConstraint
{
	Point2DNoConstraint( T a_x, T a_y )
	: m_x( a_x )
	, m_y( a_y )
	{}

	T m_x;
	T m_y;
};

class A
{};

TEST( ConstraintsAndConcepts, Point2DNoConstraint )
{
	// In version without constraint we can use whatever we want, and it will compile even it is has no sens
	Point2DNoConstraint( A(), A() );
}

// New concept
template<typename T>
concept FloatingPoint = std::is_floating_point_v<T>; // we use type traits here

// Using two concepts with or operator
template<typename T>
concept Number = FloatingPoint<T> || std::is_integral_v<T>; // we use type traits here

template<typename T>
requires Number<T> // Here we use constraints
struct Point2D
{
	Point2D( T a_x, T a_y )
			: m_x( a_x )
			  , m_y( a_y )
	{}

	T m_x;
	T m_y;
};

// requires keyboard can be also used with return type or inside template declaration:
// Number<T> auto sum();
//
// template<Number T>
// int sum();

TEST( ConstraintsAndConcepts, Point2D )
{
	// Will not compile, do not meet requirements
	//	Point2D( A(), A() );

	// Ok, we put integers
	Point2D( 10, 11 );
}

// Re

struct B
{
	void fun() {};
};

struct C
{
	void fun1() {};
};

template<typename T>
concept FunFunction = requires( T& )
{
	std::declval<T>().fun();
};

template<typename T>
requires FunFunction<T>
class TemplateWithFunFunction
{};

TEST( ConstraintsAndConcepts, RequiresToCheckIfMethodExist )
{
	TemplateWithFunFunction<B> b;

	// Not compile, there is no method fun() in 'C' class
//	TemplateWithFunFunction<C> c;
}