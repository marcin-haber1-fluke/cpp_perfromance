//
// Created by it on 7/8/22.
//

#include <benchmark/benchmark.h>
#include <unordered_map>

/*
 * Goal:
 * List m elements from n elements collection with the highest rank
 *
 * Real example:
 * We have 1000 of books. We want to print first 10 with the highest rank
 *
 * We could do it on at least 3 ways, using:
 * std::sort
 * std::partial_sort
 * std::priority_queue
 *
 * Priority queue is an example of container adaptors. Different example of adaptors are:
 * - stack (LIFO)
 * - queue (FIFO)
 *
 * Container adaptors - representation of abstract data types with using different underlying sequence containers like vectors,
 * lists, dequeue
 */

#include <iostream>
#include <algorithm>
#include <queue>

struct Book
{
	Book( float a_rank )
	: rank( a_rank )
	{}
	float rank;
};

auto compare = []( const auto a, const auto b )
{
	return a.rank > b.rank;
};

void First10WithSort( benchmark::State& state )
{
	auto n = state.range( 0 );

	srand (time(NULL));
	std::vector<Book> ranks;
	for ( int i = 0 ; i < n ; ++i )
	{
		ranks.emplace_back( rand() % n );
	}

	for ( auto _ : state )
	{
		std::sort( std::begin( ranks ), std::end( ranks ), compare );
	}
}

void First10WithPartialSort( benchmark::State& state )
{
	auto n = state.range( 0 );

	srand (time(NULL));
	std::vector<Book> ranks;
	for ( int i = 0 ; i < n ; ++i )
	{
		ranks.emplace_back( rand() % n );
	}

	for ( auto _ : state )
	{
		std::partial_sort( std::begin( ranks ), std::begin( ranks ) + 10, std::end( ranks ), compare );
	}
}

template<typename It>
auto SortWithPriorityQueue( It a_begin, It a_end, uint a_size ) -> std::vector<Book>
{
	std::priority_queue<Book, std::vector<Book>, decltype(compare)> queue;

	auto iterator = a_begin;
	while( iterator != a_end )
	{
		if ( queue.size() < a_size )
		{
			queue.push( *iterator );
		}
		else if ( iterator->rank > queue.top().rank )
		{
			queue.pop();
			queue.push( *iterator );
		}
		++iterator;
	}

	// No create results in revers order
	std::vector<Book> result;

	while ( !queue.empty() )
	{
		result.push_back( queue.top() );
		queue.pop();
	}
	std::reverse(result.begin(), result.end());
	return result;
}

void First10WithPriorityQueue( benchmark::State& state )
{
	auto n = state.range( 0 );

	srand (time(NULL));
	std::vector<Book> ranks;
	for ( int i = 0 ; i < n ; ++i )
	{
		ranks.emplace_back( rand() % n );
	}

	for ( auto _ : state )
	{
		auto result = SortWithPriorityQueue( std::begin( ranks ), std::end( ranks ), 10u );
	}
}

BENCHMARK( First10WithSort )->RangeMultiplier( 10 )->Range( 1000, 10000000 );
BENCHMARK( First10WithPartialSort )->RangeMultiplier( 10 )->Range( 1000, 10000000 );
BENCHMARK( First10WithPriorityQueue )->RangeMultiplier( 10 )->Range( 1000, 10000000 );

BENCHMARK_MAIN();