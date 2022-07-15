//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>

// This section tries to show how auto works with references. If we use auto&, it could be bound to const or mutable reference.
// Const references extends temporary object lifetimes, so they will exist until const reference exists.
//
// Forwarding reference extends also temporary objects lifetimes, but additionally allows to modify such objects

TEST( AutoReference, ConstReferenceExtendLifetimeOfTemporaryObject )
{
	auto value1 = 10;
	auto value2 = 20;

	const auto& sum = value1 + value2; // ( value1 + value2 ) is a temporary object, but it can be assigned to const ref, because it's lifetime is extended
	// auto& sum = value1 + value2; This will not compile, because sum of value1 and value2 is a temporary object
}

TEST( AutoReference, ConstReferenceDeduction )
{
	int value1 = 10;
	const int& valueRef = value1;

	// auto autoValueRef = valueRef; Compile, because copy is done here

	// Const reference is deduced
	auto& autoValueRef = valueRef;
	// autoValueRef = 10; Cannot change const reference
}

// auto&&, T&&, where T is a template argument
// extends temporary object lifetime
// temporary object can be modified
// Main use case is when forwarding arguments from one function to another, when we do not care about the type
TEST( AutoReference, ForwardingReference_UniversalReference )
{
	auto value1 = 10;
	auto value2 = 20;

	auto&& sum = value1 + value2; // No copy here
	std::cout << "Sum: " << sum << std::endl;

	sum += 10;

	std::cout << "Sum after modification: " << sum << std::endl;
}