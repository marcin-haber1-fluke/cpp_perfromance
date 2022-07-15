//
// Created by it on 7/8/22.
//

#include <benchmark/benchmark.h>

// Usually there is a recommendation to use copy-move idiom. There some exceptions, when this is not a good idea. For example
// working with vectors. It is sometimes better to pass vector as reference and then copy, because it is possible, that we will
// use allocated earlier memory.

// In version with passing vector by const reference we can avoid additional memory allocation when copying vectors into class member if
// member vector was allocated before and if new vector size is less or equal vector inside class. There is a very small difference, between
// the cases, but still this difference can be considered if performance is a critical requirement.

class DataConstRefCopy
{
public:
	void Set( const std::vector<int>& a_data )
	{
		m_data = a_data;
	}

	std::vector<int> m_data;
};

class DataCopyMove
{
public:
	void Set( std::vector<int> a_data )
	{
		m_data = std::move( a_data );
	}

	std::vector<int> m_data;
};

void SetVectorByConstReference( benchmark::State& state )
{
	for ( auto _ : state )
	{
		std::vector<int> vec( 100000 );
		DataConstRefCopy b;
		for ( int i = 0 ; i < 100 ; ++i )
		{
			b.Set( vec );
		}
	}
}

void SetVectorByCopy( benchmark::State& state )
{
	for ( auto _ : state )
	{
		std::vector<int> vec( 100000 );
		DataCopyMove b;
		for ( int i = 0 ; i < 100 ; ++i )
		{
			b.Set( vec );
		}
	}
}

BENCHMARK( SetVectorByConstReference );
BENCHMARK( SetVectorByCopy );
BENCHMARK_MAIN();