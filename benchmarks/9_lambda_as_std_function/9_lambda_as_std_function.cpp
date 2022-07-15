//
// Created by it on 7/8/22.
//

#include <benchmark/benchmark.h>
#include <numeric>
#include <memory>

// std::function add some additional overhead to when call method. Also, it is hard to optimized calls by compiler.
// Using directly lambdas can be significant faster, specially when lambda is very trivial.

auto lambda = []( int v )
{
	return v * 3;
};

std::function<void(int)> stdFunction = lambda;

void UseLambda( benchmark::State& state )
{
	using T = decltype(lambda);
	std::vector<T> functions( 10'000'000, lambda );
	int i = 10;
	for ( auto _ : state )
	{
		for ( const auto& fun : functions )
		{
			fun( i );
		}
	}
}

void UseStdFunction( benchmark::State& state )
{
	using T = decltype(stdFunction);
	std::vector<T> functions( 10'000'000, stdFunction );
	int i = 10;
	for ( auto _ : state )
	{
		for ( const auto& fun : functions )
		{
			fun( i );
		}
	}
}

BENCHMARK( UseLambda );
BENCHMARK( UseStdFunction );

BENCHMARK_MAIN();