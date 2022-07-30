//
// Created by it on 7/8/22.
//

#include <benchmark/benchmark.h>
#include <numeric>
#include <memory>
#include <iostream>

/*
 * CPU cache information can be checked with the following command:
 * lscpu
 *
 * Example of output:
 *	Architecture:                    x86_64
 *	CPU op-mode(s):                  32-bit, 64-bit
 *	Byte Order:                      Little Endian
 *	Address sizes:                   39 bits physical, 48 bits virtual
 *	CPU(s):                          12
 *	On-line CPU(s) list:             0-11
 *	Thread(s) per core:              2
 *	Core(s) per socket:              6
 *	Socket(s):                       1
 *	NUMA node(s):                    1
 *	Vendor ID:                       GenuineIntel
 *	CPU family:                      6
 *	Model:                           158
 *	Model name:                      Intel(R) Core(TM) i7-8700 CPU @ 3.20GHz
 *	Stepping:                        10
 *	CPU MHz:                         3200.000
 *	CPU max MHz:                     4600.0000
 *	CPU min MHz:                     800.0000
 *	BogoMIPS:                        6399.96
 *	Virtualization:                  VT-x
 *	L1d cache:                       192 KiB
 *	L1i cache:                       192 KiB
 *	L2 cache:                        1.5 MiB
 *	L3 cache:                        12 MiB
 *
 *	L1d - cache for data
 *	L1i - cache for instructions
 *
 *	------------------- Main memory -------------------
 *	--------- CPU -----------
 *	--------- L3 ------------
 *	-----L2 ------- L2 ------
 *	-- L1d/L1i -- L1d/L1i ---
 *	-------- Core 0 ---------
 *
 *	Temporal locality - using data that already are in cache
 *	Spatial locality - using data that located near some other data, increase likelihood that that are in cache
 *	Cache trashing - constantly wiping out from cache
 */

constexpr auto l1CacheCapacity = 196608;
constexpr auto l1IntsInCache = l1CacheCapacity / sizeof( int );

using Matrix = std::array<std::array<int, l1IntsInCache>, l1IntsInCache>;
auto m = std::make_unique<Matrix>();

void IterateOverRows( benchmark::State& state )
{
	for ( auto _ : state )
	{
		int counter = 0;
		for ( int column = 0 ; column < l1IntsInCache ; ++column )
		{
			for ( int row = 0 ; row < l1IntsInCache ; ++row )
			{
				(*m)[column][row] = counter++;
			}
		}
	}
}

void IterateOverColumns( benchmark::State& state )
{
	for ( auto _ : state )
	{
		int counter = 0;
		for ( int row = 0 ; row < l1IntsInCache ; ++row )
		{
			for ( int column = 0 ; column < l1IntsInCache ; ++column )
			{
				(*m)[column][row] = counter++;
			}
		}
	}
}

BENCHMARK( IterateOverRows );
BENCHMARK( IterateOverColumns );

BENCHMARK_MAIN();