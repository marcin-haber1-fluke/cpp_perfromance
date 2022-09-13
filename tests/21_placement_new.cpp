//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>

/*
 * It shows that allocating memory and creating objects are separate in C++
 */

class SomeClass
{
	int value;
};

TEST( AllocatingMemory, PlacementNew )
{
	// Use malloc to allocate memory
	auto* memory = malloc( sizeof( SomeClass ) );
	auto* user = ::new ( memory ) SomeClass;

	// Deleting - no placement destructor, so it needs to be called manually, then memory need to be freed
	user->~SomeClass();
	free( memory );

	// The same we can do with support of c++20 standard
	memory = malloc( sizeof( SomeClass ) );
	user = reinterpret_cast<SomeClass*>( memory );

	std::construct_at( user, SomeClass() );
	std::destroy_at( user );
	free( memory );
}