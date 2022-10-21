//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>
#include <optional>

// Optional is stack-allocated container with max size 1. There is no dynamic allocation. Object
// need to be stored inside optional object

auto allocated = size_t{ 0 };

void* operator new( size_t a_size )
{
	void* p = std::malloc( a_size );
	allocated += a_size;
	return p;
}

void operator delete( void* p ) noexcept
{
	return std::free( p );
}

namespace Optional
{

class A
{
public:
	A()
	{
		std::cout << "A ctor" << std::endl;
	}
	~A()
	{
		std::cout << "A dtor" << std::endl;
	}

	int m_value;
	int m_value1;
};

TEST( Optional, CheckOptionalSize )
{
	std::cout << "Size of A: " << sizeof( A ) << std::endl;

	std::optional<A> optA;
	std::cout << "Size of optional<A>: " << sizeof( optA ) << std::endl;

	std::cout << "Comment: until now A object is not created, but space for A object was allocated" << std::endl;

	// Constructor is invoked now, but memory allocation was done before
	optA = A();
}

TEST( Optional, NoDynamicAllocation )
{
	auto allocatedByGoogleTest = allocated;
	std::optional<A> optA = A();
	std::cout << "Dynamically allocated memory: " << allocatedByGoogleTest - allocated << std::endl;
}

}