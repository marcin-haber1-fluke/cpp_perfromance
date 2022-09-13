//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>

void Print( const std::vector<float>& a_data, std::string_view a_title )
{
	std::cout << a_title << std::endl;
	for( const auto& value : a_data )
	{
		std::cout << value << std::endl;
	}
	std::cout << std::endl;
}

void Print( auto a_iterBegin, auto a_iterEnd, std::string_view a_title )
{
	std::cout << a_title << std::endl;
	for( auto iter = a_iterBegin ; iter != a_iterEnd ; ++iter )
	{
		std::cout << *iter << std::endl;
	}
	std::cout << std::endl;
}

TEST( Algorithms, Sort )
{
	std::vector<float> data( 10 );
	std::ranges::generate( data, []()
	{
		return std::rand() % 10;
	} );

	std::ranges::sort( data );
	Print( data, "Sort" );
}

TEST( Algorithms, EqualRange )
{
	int i = 0;
	std::vector<float> data( 10 );
	std::ranges::generate( data, [i]() mutable
	{
		return ++i % 3;
	} );

	std::ranges::sort( data );
	auto range = std::ranges::equal_range( data, 1 );

	Print( data, "EqualRange" );
	std::cout << "Begin: " << std::distance( data.begin(), range.begin() ) << std::endl;
	std::cout << "End: " << std::distance( data.begin(), range.end() ) << std::endl;

}