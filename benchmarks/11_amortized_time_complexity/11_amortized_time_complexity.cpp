//
// Created by it on 7/8/22.
//

#include <benchmark/benchmark.h>
#include <numeric>
#include <memory>

/*
 * Complexity - big O notation:
 * Formal definition:
 * If f(n) is a function that specifies the running time of an algorithm with input size 'n', we say that f(n) is O(g(n)) if there is a constant
 * k such that f(n) < k * g(n)
 *
 * Examples:
 * O(1) - constant time, running time does not depend on input size
 * O(logn) - logarithmic
 * O(n) - linear
 * O(nlogn) - n logn
 * O(n^2) - quadratic
 * O(2^n) - exponential
 *
 * Normally complexity is calculated for the worst case. In standard library amortized complexity is used. Amortized complexity is defined
 * as running algorith many times, sum execution time and finally divide by number of runs.
 *
 * To show how it works we can discuss push_back from vector, that in documentation is described as O(1). That is a little confusing,
 * because vector, when exceed its capacity need to allocated new memory and then copy all elements into new location. So for n-elements
 * we need to do n copies. So why it is only O(1) instead of O(n)?
 *
 * First example to show how amortized complexity can be calculated for algorithm that has constant execution time T:
 * When calling it n-times, total time is n*T. Finally, to calculate amortized complexity we need to divide that by number of calls:
 * n*T/ n = T, where T is constant. Ok, so it is O(1) complexity.
 *
 * What about push_back()? To show how it works, lets assume that when we call push_back() and vector need to be resized, we create new
 * vector with double size. So for m elements, we need to resize vector log2(m) times, each time copy 2^i elements to new allocated space.
 * So when we sum all calls weh have:
 * Total = 2^1 + 2^2 + ... + 2^log2(m) = from sum on geometric series = 2m - 2
 * Now to finish calculation total time need to be diveded by number of calls:
 * Amortized complexity = T/m = (2m-2)/m=2-2/m = O(1)
 *
 * So for very big number of operations amortized complexity is O(1). But it is different for different number of elements, as can be checked
 * with google benchmark
 *
 * With google benchmark it is possible to check algorithm complexity
 */

void PushBackInternal( int max )
{
	std::vector<int> data;
	for ( int i = 0 ; i < max ; ++i )
	{
		data.push_back( i );
	}
}

void PushBack( benchmark::State& state )
{
	auto n = state.range( 0 );

	for ( auto _ : state )
	{
		PushBackInternal( n );
	}
	state.SetComplexityN(n);
}

BENCHMARK( PushBack )->RangeMultiplier(2)->Range(1, 100000000)->Complexity(); // Start from 1, increase by multiplication by 2, up to 1000

BENCHMARK_MAIN();