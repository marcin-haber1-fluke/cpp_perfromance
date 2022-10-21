//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>
#include <thread>
#include <semaphore>
#include <chrono>

using namespace std::chrono_literals;


/*
 * Semaphores:
 * - allow access for being in critical sections for at most defined number of threads
 * - acquire() decrement counter and block thread when counter is 0
 * - release() increment counter and signal threads that waits for entering to critical section
 * - one thread can acquire() and different one can release()
 * - binary semaphore is a counting semaphore that has max threads set to 1. There is a guarantee that
 * it is more efficients implemented than other semaphores
 */

/*
 * In the following examples we create 10 threads that will try to enter critical section, but semaphore will
 * limit quests to only 4 in the same time
 */

auto sem = std::counting_semaphore<4>( 4 );

void DoWork( int a_id )
{
	std::cout << "Do work... Waiting for entering to critical section: " << a_id << std::endl;
	sem.acquire();
	std::cout << "I am in critical section: " << a_id << std::endl;
	std::this_thread::sleep_for( 4s );
	auto message = "Exit critical section: " + std::to_string( a_id );
	std::cout << message << std::endl;
	sem.release();
}

TEST( Semaphores, EqualRange )
{
	std::vector<std::jthread> threads;
	for ( int i = 0 ; i < 10 ; ++i )
	{
		threads.emplace_back( [i]()
		{
			DoWork( i );
		} );
	}
}