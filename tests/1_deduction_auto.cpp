//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <typeinfo>

int& return_int( int& a_value )
{
	return a_value;
};

// Auto can be used with and without trailing return type, but there are some cases where trailing type is needed:
// - virtual methods
// - method declaration, when definition is in .cpp file

// These tests show that when exact type is needed, then decltype(auto) can be used. It could for example detect
// reference type, when normal auto will deduce not reference type.

// Auto deduce int& as int
TEST( DeductionAuto, ReturnTypeDeducedByAuto )
{
	std::cout << std::endl << std::endl << ::testing::UnitTest::GetInstance()->current_test_info()->name() << std::endl;

	// Method with return value of type int:
	int input_value = 10;

	// Deduces int, so when we change output value, input value will be the same
	auto output_value = return_int( input_value );

	std::cout << "input_value: " << input_value << std::endl;
	std::cout << "output_value: " << output_value << std::endl;

	// Changing output value
	output_value = 20;

	std::cout << "after changing input_value: " << input_value << std::endl;
	std::cout << "after changing output_value: " << output_value << std::endl;
}

// decltype(auto) deduce int& as int&
TEST( DeductionAuto, ReturnTypeDeducedByDecltypeAuto )
{
	std::cout << std::endl << std::endl << ::testing::UnitTest::GetInstance()->current_test_info()->name() << std::endl;

	// Method with return value of type int:
	int input_value = 10;

	// Deduces int, so when we change output value, input value will be the same
	decltype(auto) output_value = return_int( input_value );

	std::cout << "input_value: " << input_value << std::endl;
	std::cout << "output_value: " << output_value << std::endl;

	// Changing output value
	output_value = 20;

	std::cout << "after changing input_value: " << input_value << std::endl;
	std::cout << "after changing output_value: " << output_value << std::endl;
}

// Auto can be used when we want to implement wrapper for method, but we are not sure what is the return type
const int& GetValue( const int& a_value )
{
	return a_value;
}

decltype(auto) GetValueWrapperDecltype()
{
	return GetValue( 10 );
}

auto GetValueWrapper()
{
	return GetValue( 10 );
}

TEST( DeductionAuto, WrapperOfMethod )
{
	decltype(auto) value = GetValue( 10 );
	decltype(auto) wrappedValue = GetValueWrapper();
	decltype(auto) wrappedValueDecltype = GetValueWrapperDecltype();

	// Not compile, because value and wrappedValueDecltype are const references
	// value = 2;
	// wrappedValueDecltype = 2;

	// Normal auto is used and type is different
	wrappedValue = 2;
}