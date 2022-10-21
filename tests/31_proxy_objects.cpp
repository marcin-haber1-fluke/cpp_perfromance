//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <math.h>

/*
 * Proxy objects:
 * - goal is to keep same interface with postpone some operation (do some optimization)
 * - should not be visible by the user of library
 */

/*
 * For vector (x, y) the length is defined as sqrt(x^2 + y^2), when comparing lengths
 * we can skip sqrt and compare only inner part. That will save some calculations
 */
class LengthProxyObject
{
public:
	LengthProxyObject(float x, float y)
			: m_square( x * x + y * y )
	{}

	bool operator==( const LengthProxyObject& other ) const = default;
	auto operator<=>( const LengthProxyObject& other ) const = default;

	friend auto operator<=>( const LengthProxyObject& other, float len )
	{
		std::cout << "Operator <=>" << std::endl;
		return other.m_square <=> len * len;
	}

	operator float() const && // Can be called only on rvalues to prevent to many calls of std::sqrt
	{
		std::cout << "Operator float" << std::endl;
		return std::sqrt( m_square );
	}

private:
	float m_square;
};

class Vector2D
{
public:
	Vector2D(float x, float y)
			: m_x( x )
			  , m_y( y )
	{}

	auto length() const
	{
		return LengthProxyObject( m_x, m_y ); // Return proxy object
	}

private:
	float m_x;
	float m_y;
};

TEST( ProxyObject, VectorLength )
{
	Vector2D vec( 10, 11 );
	float len = vec.length();
	std::cout << "Len: " << len << std::endl;

	 auto len1 = vec.length();
	//	float len1Float = len1; // Not compile, len is a lvalue, float operator can be used only on rvalues

	Vector2D vec2( 10, 11 );

	EXPECT_TRUE( vec.length() == vec2.length() );
}