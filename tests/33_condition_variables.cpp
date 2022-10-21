//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <queue>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

using namespace std::chrono_literals;

/*
 * Condition variables makes it possible to wait until some specific condition has been met
 *
 * Some comments:
 * - use wait with predicate to avoid spurious wake-ups (or while loop)
 * - spurious wake-up can occur sometime even there is no trigger: example cv.wait() can exit sometimes without notification
 * - inside wait() mutex is unlocked to have possibility to modify objects
 * - std::promise is additional mechanism to do the same as with std::future. Promise is used with std::thread
 * - package_task is another wrapper to be used with threads. This time promise can be skipped - is hidden inside
 * - recommended way is to use async, because it can check if creating new thread is efficient
 */

std::queue<int> queue;
std::mutex dataMutex;
int lastValue = 10;
std::condition_variable cv;

void IntProducer()
{
	for ( int i = 0 ; i < lastValue ; ++i )
	{
		std::this_thread::sleep_for( 1s );

		{
			std::scoped_lock l( dataMutex );
			queue.push( i );
		}

		cv.notify_one();
	}
}

void IntConsumer()
{
	int i = 0;
	while( i != lastValue - 1 )
	{
		std::unique_lock l( dataMutex );
		cv.wait( l, []()
		{
			return !queue.empty();
		} );

		++i;
		std::cout << "Consumer: value: " << queue.front() << std::endl;
		queue.pop();
	}
}

TEST( ConditionVariables, ConsumerProducerIdiom )
{
	/*
	 * Differences between std::thread and std::jthread
	 * - [std::jthread] support stopping thread using stop token
	 * - [std::jthread] call wait in destructor
	 */
	std::jthread producer = std::jthread( IntProducer );
	std::jthread consumer = std::jthread( IntConsumer );
}