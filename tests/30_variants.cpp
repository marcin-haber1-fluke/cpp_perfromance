//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <variant>

/*
 * Variant:
 * - use stack to allocate object
 * - size of variant is a size of the biggest type plus index of types
 * - is not exception save, could be in valueless state, when for example created object throws exception in constructor
 * - is implemented as a template
 * - when variant is created, object of first type is created, if it is not default constructible, then variant is also not default constructible
 * - when all types are not default constructible std::monostate object can be used as a first argument
 * - variant can keep more than one same type
 */

TEST( Variants, Size )
{
	std::variant<double, std::string, float, int> variant;

	std::cout << "Size of variant: " << sizeof( variant ) << std::endl;
	std::cout << "Size of double: " << sizeof( double ) << std::endl;
	std::cout << "Size of std::string: " << sizeof( std::string ) << std::endl;
	std::cout << "Size of float: " << sizeof( float ) << std::endl;
	std::cout << "Size of int: " << sizeof( int ) << std::endl;
	std::cout << "Size of size_t: " << sizeof( size_t ) << std::endl;

	// Variant is the sum of max sized type + size_t that is needed for indexing
}

TEST( Variants, CheckingCurrentAlternative )
{
	std::variant<double, std::string, float, int> variant;

	// Holds default constructed double object, because it is the first one
	std::cout << "Holds alternative double: " << std::holds_alternative<double>( variant ) << std::endl;
	std::cout << "Holds alternative std::string: " << std::holds_alternative<std::string>( variant ) << std::endl;
	std::cout << "Holds alternative float: " << std::holds_alternative<float>( variant ) << std::endl;
	std::cout << "Holds alternative int: " << std::holds_alternative<int>( variant ) << std::endl;

	variant = "string";
	std::cout << std::endl << "Assigning string" << std::endl;
	std::cout << "Holds alternative double: " << std::holds_alternative<double>( variant ) << std::endl;
	std::cout << "Holds alternative std::string: " << std::holds_alternative<std::string>( variant ) << std::endl;
	std::cout << "Holds alternative float: " << std::holds_alternative<float>( variant ) << std::endl;
	std::cout << "Holds alternative int: " << std::holds_alternative<int>( variant ) << std::endl;
}

TEST( Variants, Get )
{
	std::variant<double, std::string, float, int> variant = "data";

	std::cout << "Get using index: " << std::get<1>( variant ) << std::endl;
	std::cout << "Get using type: " << std::get<std::string>( variant ) << std::endl;

	try
	{
		std::cout << std::get<int>( variant ) << std::endl;
	}
	catch ( std::bad_variant_access& exc )
	{
		std::cout << "Exception: " << exc.what() << std::endl;
	}

}

/* This is ok, then we want to do the same action for all types
 * If not, then we need to create separate operator for each type.
 *
 * Visit is interpreted as if... else... and calling operator() for contained type
 *
 * For example visit could be implemented as:
 * struct GeneratedFunctorImplementation
 * {
 * 		auto operator()( int&& val ) { std::cout << val << std::endl; };
 * 		auto operator()( double&& val ) { std::cout << val << std::endl; };
 * 		auto operator()( std::string&& val ) { std::cout << val << std::endl; };
 * 		auto operator()( float&& val ) { std::cout << val << std::endl; };
 * }
 */
TEST( Variants, Visit )
{
	std::variant<double, std::string, float, int> variant( "string" );

	std::visit( []( auto&& val )
	{
		std::cout << val << std::endl;
	}, variant );
}

//Bring a specific member from the namespace into the current scope.
//Bring all members from the namespace into the current scope.
//Bring a base class method or variable into the current class’s scope.

template<typename... Lambdas>
struct Overloaded : Lambdas...
{
	using Lambdas::operator()...; // Just expands to all types separated by comas
};

// Deduction quide is needed
template<typename... Lambdas>
Overloaded(Lambdas...) -> Overloaded<Lambdas...>;

TEST( Variants, VisitMultipleLambdas )
{
	std::variant<double, std::string, float, int> variant( "string" );

	auto overloaded = Overloaded{
			[]( double val )
			{
				std::cout << "double: " << val << std::endl;
			},
			[]( std::string val )
			{
				std::cout << "std::string: " << val << std::endl;
			},
			[]( float val )
			{
				std::cout << "float: " << val << std::endl;
			},
			[]( int val )
			{
				std::cout << "int: " << val << std::endl;
			}
	};

	std::visit( overloaded, variant );
}