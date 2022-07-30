//
// Created by it on 7/8/22.
//

#include <benchmark/benchmark.h>
#include <unordered_map>

/*
 * Goal:
 * Optimization by reducing object size, when frequently iteration is needed.
 *
 * We have huge list of players and we need to know how many of them has age below 18
 *
 * Drawbacks:
 * - code readability is poor for parallel arrays
 * - we need to keep synchronisation between arrays
 * - if we want to use more than one parameter, then sometimes is better to use bigger objects
 */

#include <iostream>
#include <memory>

struct Player
{
	std::string name = ""; 	// 32 bytes for pointer
	int age = 29; 			// 4 bytes
	int score = 234;		// 4 bytes
	bool isVip = false;		// 1 byte, alignment to 4 bytes
	// Total 48 bytes
};

/*
 * Iterating over collection with big objects to check only one parameter is very slow. Data need to be put into
 * cache all time we want to check one parameter in object
 */
void IterateOverBigObjectCollection( benchmark::State& state )
{
	std::vector<Player> players;
	for ( int i = 0 ; i < 10000000 ; ++i )
	{
		players.push_back( Player{ std::string( "Player: " ) + std::to_string( i ),  i % 60, i, static_cast<bool>( i ) } );
	}

	for ( auto _ : state )
	{
		std::count_if( players.begin(), players.end(), []( const auto& a_player )
		{
			return a_player.age < 18;
		} );
	}
};

struct Player1RareData
{
	std::string name = ""; 	// 32 bytes for pointer
	int score = 234;		// 4 bytes
	bool isVip = false;		// 1 byte, alignment to 4 bytes
	// Total 40 bytes
};

struct Player1
{
	int age = 29; 								// 4 bytes
	std::unique_ptr<Player1RareData> data;		// 4 bytes
	// Total 16 bytes
};

void IterateOverObjectWithPointerCollection( benchmark::State& state )
{
	std::vector<Player1> players;
	for ( int i = 0 ; i < 10000000 ; ++i )
	{
		players.push_back( Player1{ i % 60, std::make_unique<Player1RareData>( Player1RareData{ std::string( "Player: " ) + std::to_string( i ), i, static_cast<bool>( i ) } ) } );
	}

	for ( auto _ : state )
	{
		std::count_if( players.begin(), players.end(), []( const auto& a_player )
		{
			return a_player.age < 18;
		} );
	}
};

struct Player2RareData
{
	std::string name = ""; 	// 32 bytes for pointer
	int score = 234;		// 4 bytes
	bool isVip = false;		// 1 byte, alignment to 4 bytes
	// Total 40 bytes
};

struct Player2
{
	int age = 29; 								// 4 bytes
	// Total 4
};

void IterateSmallOverObjectCollection( benchmark::State& state )
{
	std::vector<Player2> players;
	std::vector<Player2RareData> playersRareData;
	for ( int i = 0 ; i < 10000000 ; ++i )
	{
		players.push_back( Player2{ i % 60 } );
		playersRareData.push_back( Player2RareData{ std::string( "Player: " ) + std::to_string( i ), i, static_cast<bool>( i ) } );
	}

	for ( auto _ : state )
	{
		std::count_if( players.begin(), players.end(), []( const auto& a_player )
		{
			return a_player.age < 18;
		} );
	}
};

BENCHMARK( IterateOverBigObjectCollection );
BENCHMARK( IterateOverObjectWithPointerCollection );
BENCHMARK( IterateSmallOverObjectCollection );

BENCHMARK_MAIN();