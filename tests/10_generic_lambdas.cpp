//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>

// Generic lambda allows using auto as an arguments type. That means, function operator will be a member template function.

// The following lambda
// auto lambda = []( auto a_value )
// {
//
// }
//
// corresponds to the following implementation:
//
// class Lambda
//{
//	template<typename T>
//	auto operator()( T a_value ) const
//	{
//
//	}
//}
//

// If argument type need to be accessed in body on lamda, another style can be used
// The following lambdas are the same:
// auto lambda = []( auto x ){};
// auto lambda1 = []<typename T>( T x ){};
TEST( GenericLambda, UsingTypeNameInLambda )
{
	auto lambda = []( auto x )
	{
		std::cout << "Standard style lambda" << std::endl;
	};

 	auto lambda1 = []<typename T>( T x )
	{
		std::cout << "Template style lambda" << std::endl;
		T anotherValue = 10;
		return anotherValue + x;
	};

	lambda( 10 );
	lambda1( 10 );

	// Types are not the same, but have the same meaning
	bool isSame = std::is_same_v<decltype(lambda), decltype(lambda1)>;
	ASSERT_FALSE( isSame );
}