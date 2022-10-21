//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <any>
/* Any:
 * - implementations are encouraged to avoid dynamic allocations for small objects
 * , but such an optimization may only be applied to type for which std::is_nothrow_move_constructible returns true.
 * - dynamically allocation is needed because 'any' does not know a type
 * - it is not a template like optional and variant
 * - 'any' destroy object when lifetime ends
*/

TEST( DynamicallySizedHeterogenousCollections, Any )
{
	struct A {};

	// default initialization:
	std::any a;
	assert(!a.has_value());

	// direct initialization with object:
	std::any a2(10); // int
	std::any a3(A());

	// in_place:
	std::any a4(std::in_place_type<A>);
	std::any a5{std::in_place_type<std::string>, "Hello world"};

	// make_any
	std::any a6 = std::make_any<std::string>("Hello world");
}

TEST( DynamicallySizedHeterogenousCollections, AnyInContainer )
{
	std::vector<std::any> m = { static_cast<int>( 10 ), 43.2f, static_cast<std::string>( "string" ) };

	for (auto &val : m)
	{
		if (val.type() == typeid(int))
		{
			std::cout << "int: " << std::any_cast<int>(val) << "\n";
		}
		else if (val.type() == typeid(std::string))
		{
			std::cout << "string: " << std::any_cast<std::string>(val) << "\n";
		}
		else if (val.type() == typeid(float))
		{
			std::cout << "float: " << std::any_cast<float>(val) << "\n";
		}
		else
		{
			std::cout << "Not handled type: " << val.type().name() << "\n";
		}
	}
}