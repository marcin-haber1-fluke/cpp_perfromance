//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>

// Lambda can be used with C libraries, cause can be cast to normal function pointer, when the following condition are met:
// - no capture list
// - plus used in lambda definition

void Caller( void (*callback)(int) )
{
	callback( 10 );
}

void CCallback( int a_value )
{
	std::cout << "C style callback, value: " << a_value << std::endl;
}

TEST( LambdaAsFunctionPointer, PassingLambdaAsFunctionPointer )
{
	Caller( CCallback ); // Just pass pointer to function

	auto LambdaCallback = +[]( int a_value )
	{
		std::cout << "Lambda callback, value: " << a_value << std::endl;
	};
	Caller( LambdaCallback );

	// Will not compile, cannot cast lambda with capture list as a c-style function pointer
	//	auto LambdaCallbackCaptureList = [x = 10]( int a_value )
	//	{
	//		std::cout << "Lambda callback, value: " << a_value << std::endl;
	//	};
	//	Caller( LambdaCallbackCaptureList );

	auto LambdaCallbackMissingPlus = []( int a_value ) // That should not compile - but probably it is compiler dependent (page 60 in C++ High Performance book)
	{
		std::cout << "Lambda (without plus) callback, value: " << a_value << std::endl;
	};
	Caller( LambdaCallbackMissingPlus );
}