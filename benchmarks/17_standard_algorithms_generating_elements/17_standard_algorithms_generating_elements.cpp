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
	void SetUp(const ::benchmark::State& state)
	{}

	void TearDown(const ::benchmark::State& state)
	{}

	void Generate();
	void GenerateOwn(); // Do the same as iota

	void Iota();
	void IotaOwn();

	void Fill();
	void FillOwn();

};

//////////////////////////////
// For loops
//////////////////////////////

void Algorithms::Generate()
{
	std::vector<float> data( 1'000'000 );
	int i = 0;
	std::ranges::generate( data, [i]() mutable
	{
		return ++i;
	} );
};

BENCHMARK_F(Algorithms, Generate)(benchmark::State& st)
{
	for ( auto _: st )
	{
		Generate();
	}
}

void Algorithms::GenerateOwn()
{
	std::vector<float> data( 1'000'000 );
	int i = 0;

	for ( auto &value : data )
	{
		value = ++i;
	}
};

BENCHMARK_F(Algorithms, GenerateOwn)(benchmark::State& st)
{
	for ( auto _: st )
	{
		GenerateOwn();
	}
}

void Algorithms::Iota()
{
	std::vector<float> data( 1'000'000 );
	std::iota( data.begin(), data.end(), 0 );
};

BENCHMARK_F(Algorithms, Iota)(benchmark::State& st)
{
	for ( auto _: st )
	{
		Iota();
	}
}

void Algorithms::IotaOwn()
{
	GenerateOwn(); // It do the same as iota
};

BENCHMARK_F(Algorithms, IotaOwn)(benchmark::State& st)
{
	for ( auto _: st )
	{
		IotaOwn();
	}
}

void Algorithms::Fill()
{
	std::vector<float> data( 1'000'000 );
	int i = 0;

	std::ranges::fill( data, 1 );
};

BENCHMARK_F(Algorithms, Fill)(benchmark::State& st)
{
	for ( auto _: st )
	{
		Fill();
	}
}

void Algorithms::FillOwn()
{
	std::vector<float> data( 1'000'000 );
	int i = 0;

	for ( auto &value : data )
	{
		value = 1;
	}
};

BENCHMARK_F(Algorithms, FillOwn)(benchmark::State& st)
{
	for ( auto _: st )
	{
		FillOwn();
	}
}

//////////////////////////////
//////////////////////////////

BENCHMARK_MAIN();