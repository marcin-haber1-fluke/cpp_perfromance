//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>
#include <cstddef>

/*
 * An alignment is and implementation-defined integer value representing the number of bytes between successive addresses at which a given object can be allocated
 */

TEST( Alignment, CheckingAlignmentForType )
{
	std::cout << "Alignment for char: " << alignof( char ) << std::endl;
	std::cout << "Alignment for int: " << alignof( int ) << std::endl;
	std::cout << "Alignment for float: " << alignof( float ) << std::endl;
	std::cout << std::endl;
}

TEST( Alignment, SetCustomAlignment )
{
	alignas( 4 ) char a;
	std::cout << "Alignment for char: " << alignof( char ) << std::endl;
	std::cout << "Alignment for custom aligned char: " << alignof( a ) << std::endl;

	struct alignas( 4 ) CustomClass
	{
		std::byte m_data[ 5 ];
	};

	std::cout << "Alignment for custom aligned class: " << alignof( CustomClass ) << std::endl;

	CustomClass object1;
	CustomClass object2;

	// We define 4 bytes, but alignment is 8, because size od m_data is 5. If we change size to 4, the alignment will be 4 as expected
	std::cout << "Alignment of CustomClass objects: " << (long long)( &object2 ) - (long long)( &object1 ) << std::endl;

	std::cout << std::endl;
}

TEST( Alignment, ChackingMaxAlignment )
{
	std::cout << "Maximum alignment: " << alignof( std::max_align_t ) << std::endl;
	std::cout << std::endl;
}

/*
 * Compiler is force to put variables in order that they are defined inside a class. To ensure that whole class alignment is valid
 * some additional bytes are added. Whole class has alignment as the biggest alignment it's members.
 */
TEST( Alignment, Padding )
{
	struct Document
	{
		bool a;
		double b;
		int c;
	};

	std::cout << "Alignment of bool: " << alignof( bool ) << std::endl;
	std::cout << "Alignment of double: " << alignof( double ) << std::endl;
	std::cout << "Alignment of int: " << alignof( int ) << std::endl;
	std::cout << "Alignment of Document: " << alignof( Document ) << std::endl;

	std::cout << "Size of document: " << sizeof( Document ) << std::endl;

	// Double type has the biggest alignment: 8, so all members are aligned with 8 bytes. Document class is then created like this
	//	struct Document
	//	{
	//		bool a;
	//		std::bytes [7]
	//		double b;
	//		int c;
	//		std::bytes [4]
	//	};
	// This is why size of the Document is 24 bytes

	// It is possible to change order in Document class to reduce it's size
	struct Document1
	{
		bool a;
		// std::bytes[3]
		int c;
		// Together bool and int are located on 8 bytes
		double b;
	};
	std::cout << "Size of document1: " << sizeof( Document1 ) << std::endl;

	std::cout << std::endl;
}