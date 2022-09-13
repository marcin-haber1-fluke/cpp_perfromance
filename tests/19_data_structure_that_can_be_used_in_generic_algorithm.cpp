//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>
#include <ranges>

struct Grid
{
	Grid( int a_width, int a_height )
	: m_width( a_width )
	, m_height( a_height )
	{
		m_data.resize( a_width * a_height );
	}

	auto GetRowPair( int a_row )
	{
		auto left = m_data.begin() + m_width * a_row;
		auto right = left + m_width;
		return std::make_pair( left, right );
	}

	auto GetRowSubranges( int a_row )
	{
		auto left = m_data.begin() + m_width * a_row;
		auto right = left + m_width;

		// creates range contained two iterators
		return std::ranges::subrange{ left, right };
	}

	auto GetRowCountedView( int a_row )
	{
		auto left = m_data.begin() + m_width * a_row;
		// creates range based on first iterator and number of elements
		return std::views::counted( left, m_width );
	}

	void Print()
	{
		int index = 0;
		for ( const auto& value : m_data )
		{
			if ( index % m_width == 0 )
			{
				std::cout << std::endl;
			}

			std::cout << value << " ";
			++index;
		}
	}

	std::vector<int> m_data;
	const int m_width;
	const int m_height;
};

// A little inconvenient because we need to use iterators directly
TEST( DataStructureWithGenericAlgorithms, UsingPair )
{
	Grid grid( 3, 3 );
	grid.Print();

	auto row = grid.GetRowPair( 1 );
	for ( auto iter = row.first ; iter != row.second ; ++iter )
	{
		*iter = 2;
	}

	std::cout << "After row modification" << std::endl;
	grid.Print();
}

// Now its better we can use for loop like always
TEST( DataStructureWithGenericAlgorithms, UsingSubranges )
{
	Grid grid( 3, 3 );
	grid.Print();

	auto row = grid.GetRowSubranges( 1 );
	for ( auto& value : row )
	{
		value = 2;
	}

	std::cout << std::endl << std::endl << "After row modification" << std::endl;
	grid.Print();
}

TEST( DataStructureWithGenericAlgorithms, UsingCountedView )
{
	Grid grid( 3, 3 );
	grid.Print();

	auto row = grid.GetRowCountedView( 1 );
	for ( auto& value : row )
	{
		value = 2;
	}

	std::cout << std::endl << std::endl << "After row modification" << std::endl;
	grid.Print();
}