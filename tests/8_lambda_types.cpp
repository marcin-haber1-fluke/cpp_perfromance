//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>

// Lambda's have same types (assignable, default constructible) only when capture list is empty.

TEST( LambdaTypes, EmptyCaptureList )
{
	auto lambda = []( int a_value )
	{
		std::cout << "Value: " << a_value << std::endl;
	};

	auto lambdaCopy = lambda;
	decltype(lambda) anotherLambda;

	lambda( 10 );
	lambdaCopy( 10 );
	anotherLambda( 10 );

	bool isSame = std::is_same_v<decltype(lambda), decltype(lambdaCopy)>;
	ASSERT_TRUE( isSame );

	isSame = std::is_same_v<decltype(lambda), decltype(anotherLambda)>;
	ASSERT_TRUE( isSame );
}

// Lambda's with capture list has unique type and cannot be assigned! Even when capture list is totally same
TEST( LambdaTypes, SameCaptureList )
{
	auto lambda = [x = 10]( int a_value )
	{
		std::cout << "Value: " << a_value << std::endl;
	};

	auto lambda1 = [x = 10]( int a_value )
	{
		std::cout << "Value: " << a_value << std::endl;
	};

	bool isSame = std::is_same_v<decltype(lambda), decltype(lambda1)>;
	ASSERT_FALSE( isSame );
}

// Capture list does not affect its signature, so it is possible to use one std::function (with the same signature) to keep
// lambdas with different capture lists
TEST( LambdaTypes, StdFunction )
{
	auto lambda = [x = 10]( int a_value )
	{
		std::cout << "Lambda, value x: " << x << ", argument value: " << a_value << std::endl;
	};

	auto lambda1 = [x = 30, y = 10]( int a_value )
	{
		std::cout << "Lambda 1, value x: " << x << ", value y: " << y << ", argument value: " << a_value << std::endl;
	};

	std::function<void(int)> fun;
	fun = lambda;
	fun( 21 );

	fun = lambda1;
	fun( 22 );
}