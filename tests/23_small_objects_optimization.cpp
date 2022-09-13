//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>

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

/*
 * String has two versions packed into union:
 * How it can be implemented:
 * - long version:
 * 		- capacity (8 bytes)
 * 		- size (8 bytes)
 * 		- pointer to data (8 bytes)
 * - short version
 * 		- size (1 byte)
 * 		- data (23 bytes)
 * 	But versions have 24 bytes, but for small string is more efficient to keep data on a stack instead of stack.
 * 	If string is short, then short version is used, we can use 23 of bytes, if string is longer, then we need to use
 * 	long version and then we need to allocate additional heap memory. What is important, short version use available memory
 * 	from capacity, pointer and size to keep data, so no additional buffer is needed.
 */
TEST( SmallObjectOptimization, String )
{
	{
		allocated = 0;
		std::string str = "";
		std::cout << "Stack space: " << sizeof( str ) << ", heap space: " << allocated << ", capacity: " << str.capacity() << std::endl << std::endl;
	}

	{
		allocated = 0;
		std::string str = "123456789012345";
		std::cout << "Stack space: " << sizeof( str ) << ", heap space: " << allocated << ", capacity: " << str.capacity() << std::endl << std::endl;
	}

	{
		allocated = 0;
		std::string str = "1234567890123456";
		std::cout << "Stack space: " << sizeof( str ) << ", heap space: " << allocated << ", capacity: " << str.capacity() << std::endl << std::endl;
	}

	{
		allocated = 0;
		std::string str = "12345678901234567";
		std::cout << "Stack space: " << sizeof( str ) << ", heap space: " << allocated << ", capacity: " << str.capacity() << std::endl << std::endl;
	}

	{
		allocated = 0;
		std::string str = "12345678901234567890";
		std::cout << "Stack space: " << sizeof( str ) << ", heap space: " << allocated << ", capacity: " << str.capacity() << std::endl << std::endl;
	}

	{
		allocated = 0;
		std::string str = "123456789012345678901234567890";
		std::cout << "Stack space: " << sizeof( str ) << ", heap space: " << allocated << ", capacity: " << str.capacity() << std::endl << std::endl;
	}

	{
		allocated = 0;
		std::string str = "1234567890123456789012345678901";
		std::cout << "Stack space: " << sizeof( str ) << ", heap space: " << allocated << ", capacity: " << str.capacity() << std::endl << std::endl;
	}

	{
		allocated = 0;
		std::string str = "12345678901234567890123456789012";
		std::cout << "Stack space: " << sizeof( str ) << ", heap space: " << allocated << ", capacity: " << str.capacity() << std::endl << std::endl;
	}

	{
		allocated = 0;
		std::string str = "123456789012345678901234567890123";
		std::cout << "Stack space: " << sizeof( str ) << ", heap space: " << allocated << ", capacity: " << str.capacity() << std::endl << std::endl;
	}
}