	//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <random>
#include <thread>
#include <barrier>

/*
 * Barriers are very similar to Latches, but they can be reused. When counter decrease to zero, given method is called. After calling method
 * count is reset to initial state.
 */

/*
 * Dice game:
 * - each roll can be done in separate thread
 * - we want to check how many times we need to roll the dice to have all 6
 */

auto generator = std::default_random_engine{ std::random_device{}() };
auto distribution = std::uniform_real_distribution<>{ 1, 6 }; // Number from 1 to 6

std::array<int, 5> values;
bool done = false;
int turns = 0;

std::barrier barrier{ 5, []()
{
	++turns;
	 for( const auto& val : values )
	 {
		 if ( val != 1 )
		 {
			 done = false;
			 return;
		 }
	 }
	 done = true;
} };

void RollDice( int a_index )
{
	values[a_index] = distribution( generator );
	barrier.arrive_and_wait();
}

TEST( Barriers, DiceGame )
{
	std::vector<std::thread> threads;
	for ( int i = 0 ; i < 5 ; ++i )
	{
		threads.emplace_back( [i]()
		{
			while( !done )
			{
				RollDice( i );
			}
		} );
	}

	for( auto&&  t : threads)
	{
		t.join();
	}

	std::cout << "Turns: " << turns << std::endl;
}