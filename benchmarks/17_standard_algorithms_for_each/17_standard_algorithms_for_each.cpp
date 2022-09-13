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
		std::ranges::generate( m_data, std::rand );
	}

	void SetUp(const ::benchmark::State& state)
	{}

	void TearDown(const ::benchmark::State& state)
	{}

	// For loops
	void ForEachRanges();
	void ForEachStandard();
	void ForRangeBased();
	void ForIterators();
	void StandardFor();

	std::vector<int> m_data;
};

//////////////////////////////
// For loops
//////////////////////////////

void Algorithms::ForEachRanges()
{
	std::ranges::for_each( m_data, []( auto&& a_value )
	{
		a_value += 1;
	} );
};

BENCHMARK_F(Algorithms, ForEachRanges)(benchmark::State& st)
{
	for ( auto _: st )
	{
		ForEachRanges();
	}
}

void Algorithms::ForEachStandard()
{
	std::for_each( m_data.begin(), m_data.end(), []( auto&& a_value )
	{
		a_value += 1;
	} );
};

BENCHMARK_F(Algorithms, ForEachStandard)(benchmark::State& st)
{
	for ( auto _: st )
	{
		ForEachStandard();
	}
}

void Algorithms::ForRangeBased()
{
	for( auto&& a_value : m_data )
	{
		a_value += 1;
	}
};

BENCHMARK_F(Algorithms, ForRangeBased)(benchmark::State& st)
{
	for ( auto _: st )
	{
		ForRangeBased();
	}
}

void Algorithms::StandardFor()
{
	for( size_t i = 0 ; i < m_data.size() ; ++i )
	{
		m_data.at( i ) += 1;
	}
};

BENCHMARK_F(Algorithms, StandardFor)(benchmark::State& st)
{
	for ( auto _: st )
	{
		StandardFor();
	}
}

void Algorithms::ForIterators()
{
	for( auto iter = m_data.begin() ; iter != m_data.end() ; ++iter )
	{
		*iter += 1;
	}
};

BENCHMARK_F(Algorithms, ForIterators)(benchmark::State& st)
{
	for ( auto _: st )
	{
		ForIterators();
	}
}

//////////////////////////////
//////////////////////////////

BENCHMARK_MAIN();