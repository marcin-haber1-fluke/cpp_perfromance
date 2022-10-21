//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>
#include <coroutine>

/*
 * Subroutines (standard functions):
 * - can be called and exist until return from it
 *
 * Coroutines:
 * - function that can be suspended and resumed
 * - it's state is kept until coroutine exit
 * - two types of coroutines can be implemented: stackless and stackful
 * -- stackless: hase separate stack similar to threads
 * -- stackful: keeps coroutine frame usually on a heap
 *
 * Calling functions:
 * - creating call frame:
 * 	- parameters passed to the function
 * 	- local variable of the function
 * 	- snapshot of the registers that we need to use and therefore need to restore before returning
 * 	- return address to know when back when return
 * 	- optional frame pointer - needed for some debuggers to have stack trace
 */

class Resumable
{
	// When a coroutine function is called there are a number of steps that are performed
	// prior to executing the code in the source of the coroutine body that are a little different to regular
	// functions.
	struct Promise
	{
		// These methods need to be defined
		Resumable get_return_object()
		{
			using Handle = std::coroutine_handle<Promise>;
			return Resumable{ Handle::from_promise( *this ) };
		}
		auto initial_suspend(){ return std::suspend_always{}; };
		auto final_suspend() noexcept { return std::suspend_always{}; };
		auto return_void(){};
		auto unhandled_exception(){ std::terminate(); };
	};

	explicit Resumable( std::coroutine_handle<Promise> a_handle )
			: m_handle( a_handle )
	{}

	std::coroutine_handle<Promise> m_handle;

public:
	using promise_type = Promise;

	explicit Resumable( Resumable&& a_other )
	: m_handle( std::exchange( a_other.m_handle, {} ) )
	{}

	~Resumable()
	{
		if ( m_handle )
		{
			m_handle.destroy();
		}
	}

	bool resume()
	{
		if ( !m_handle.done() )
		{
			m_handle.resume();
		}
		return false;
	}
};

auto MyFirstCoroutine() -> Resumable
{
	std::cout << "3" << std::endl;
	co_await std::suspend_always{}; // suspend function
	std::cout << "5" << std::endl;
}

TEST( Coroutines, MinimalExample )
{
	std::cout << "1" << std::endl;
	auto resumable = MyFirstCoroutine(); // Suspend of the beginning - this behaviour can be configured
	std::cout << "2" << std::endl;
	resumable.resume();
	std::cout << "4" << std::endl;
	resumable.resume();
	std::cout << "6" << std::endl;
}