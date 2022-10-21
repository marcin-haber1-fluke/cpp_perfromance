//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>
#include <thread>
#include <chrono>
#include <latch>

using namespace std::chrono_literals;

/*
 * Latch can be considered as counter, that can be decremented. In this way it is possible to create a sync point between threads.
 * Most common use case it when we want to do some initialization before main work.
 */

/*
 * Assume that we have 2 threads, all have to do some work before then can continue their work.
 */

void DoInitialization( std::chrono::duration<float> a_initTime )
{
	std::cout << "Thread init: " << std::this_thread::get_id << " - start" << std::endl;
	std::this_thread::sleep_for( a_initTime );
	std::cout << "Thread init: " << std::this_thread::get_id << " - end" << std::endl;
}

std::latch latch( 2 );

void Thread1Work()
{
	DoInitialization( 2s );
	latch.arrive_and_wait();
	std::cout << "Thread work: " << std::this_thread::get_id << " - Done" << std::endl;
}

void Thread2Work()
{
	DoInitialization( 4s );
	latch.arrive_and_wait();
	std::cout << "Thread work: " << std::this_thread::get_id << " - Done" << std::endl;
}

TEST( Latch, InitializationBeforeWork )
{
	std::jthread thread1 = std::jthread( Thread1Work );
	std::jthread thread2 = std::jthread( Thread2Work );
}