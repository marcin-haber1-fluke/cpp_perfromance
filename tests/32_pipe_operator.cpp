//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>


/*
 * Goal is to achieve the following:
 * auto numbers = std::vector{ 1, 2, 3, 4, 5 , 6, 7, 8, 9 };
 * auto seven = 7;
 * bool hasSeven = numbers | contains(seven);
 */

template<typename T>
struct ContainsProxy
{
	const T& m_value;
};

// Pipe operator, we need proxy object to distinguish second argument
template<typename Range, typename T>
auto operator|(const Range& r, const ContainsProxy<T>& proxy)
{
	const auto& value = proxy.m_value;
	return std::find( r.begin(), r.end(), value ) != r.end();
}

// Just return proxy object
template<typename T>
auto contains( const T& v )
{
	return ContainsProxy<T>{ v };
}

TEST( PipeOperator, Contains )
{
	auto numbers = std::vector{ 1, 2, 3, 4, 5 , 6, 7, 8, 9 };

	{
		auto value = 7;
		bool hasValue = numbers | contains(value);
		EXPECT_TRUE( hasValue );
	}

	{
		auto value = 10;
		bool hasValue = numbers | contains(value);
		EXPECT_FALSE( hasValue );
	}
}