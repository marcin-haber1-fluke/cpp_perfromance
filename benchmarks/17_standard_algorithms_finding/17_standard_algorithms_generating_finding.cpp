//
// Created by it on 7/8/22.
//

#include <benchmark/benchmark.h>
#include <unordered_map>

/*
 * Goal:
 * Be familiar with most important standard algorithms.
 *
 * Check also different optimization levels in CMakeLists.txt
 */

#include <iostream>
#include <algorithm>
#include <numeric>

class Algorithms : public benchmark::Fixture
{
public:
	Algorithms()
	{
		Init( 10'000'000 );
	}

	void Init( int a_size )
	{
		m_data.resize( a_size );
		std::iota( m_data.begin(), m_data.end(), 0 );
	}

	void SetUp(const ::benchmark::State& state)
	{}

	void TearDown(const ::benchmark::State& state)
	{}

	void Find();
	void BinarySearch(); // Need to have sorted data

	std::vector<int> m_data;
	const int m_elementToFind = 5'000'000;
};

void Algorithms::Find()
{
	std::ranges::find( m_data, m_elementToFind );
};

BENCHMARK_F(Algorithms, Find)(benchmark::State& st)
{
	for ( auto _: st )
	{
		Find();
	}
}

void Algorithms::BinarySearch()
{
	std::ranges::binary_search( m_data, m_elementToFind );
};

BENCHMARK_F(Algorithms, BinarySearch)(benchmark::State& st)
{
	for ( auto _: st )
	{
		BinarySearch();
	}
}

//////////////////////////////
//////////////////////////////

BENCHMARK_MAIN();