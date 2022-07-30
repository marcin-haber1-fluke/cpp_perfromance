//
// Created by it on 7/8/22.
//

#include <benchmark/benchmark.h>
#include <unordered_map>

/*
 * Goal:
 * string_view as a potential performance win:
 * - passing to methods
 * - substr
 */

#include <iostream>
#include <algorithm>
#include <queue>

void DoSomethingWithString( const std::string& a_str )
{

};

void DoSomethingWithStringView( std::string_view a_str )
{

};

void DoSomethingWithStringPassByStringLiteral( benchmark::State& state )
{
	for ( auto _ : state )
	{
		DoSomethingWithString( "Random string" );
	}
};

void DoSomethingWithStringPassByString( benchmark::State& state )
{
	std::string str{ "Random string" };

	for ( auto _ : state )
	{
		DoSomethingWithString( str );
	}
};

// String need to be created from string literal
BENCHMARK( DoSomethingWithStringPassByStringLiteral );

// String is created before benchmark
BENCHMARK( DoSomethingWithStringPassByString );

void DoSomethingWithStringViewPassByStringLiteral( benchmark::State& state )
{
	for ( auto _ : state )
	{
		DoSomethingWithStringView( "Random string" );
	}
};

void DoSomethingWithStringViewPassByString( benchmark::State& state )
{
	std::string str{ "Random string" };

	for ( auto _ : state )
	{
		DoSomethingWithStringView( str );
	}
};

// It's slower than pass by reference, when string is created before, but still fast and flexible, because
// can get string literals and strings
BENCHMARK( DoSomethingWithStringViewPassByStringLiteral );
BENCHMARK( DoSomethingWithStringViewPassByString );

void SubstrString( benchmark::State& state )
{
	std::string str{ "Some random text used in performance check" };

	for ( auto _ : state )
	{
		auto randomWordString = str.substr( 5, 6 ); // Takes 'random'
	}
};

void SubstrStringView( benchmark::State& state )
{
	std::string_view str( "Some random text used in performance check" );

	for ( auto _ : state )
	{
		auto randomWordString = str.substr( 5, 6 ); // Takes 'random'
	}
};

// String view version of substr, returns also string_view, so no copy is needed, string object do not need to be created
BENCHMARK( SubstrStringView );
BENCHMARK( SubstrString );

BENCHMARK_MAIN();