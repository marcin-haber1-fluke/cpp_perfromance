//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>

// Rule of five:
// Class should take care about their resources, so it's a good practice to have all 5 methods implemented:
// - Copy Constructor
// - Destructor
// - Assignment Operator
// - Move Constructor
// - Move Assignment Operator

// It is important to remember, that move constructor and move assignment operators, should be declared as noexcept. If not
// standard containers and algorithms could copy objects in certain condition. Of course noexpect can be use only when
// move assigment operator and move constructor does not throw exceptions.

class ClassWithoutNoexpect
{
public:
	ClassWithoutNoexpect()
	{
		std::cout << "Default Constructor" << std::endl;
	}
	ClassWithoutNoexpect( const ClassWithoutNoexpect& )
	{
		std::cout << "Copy Constructor" << std::endl;
	}
	~ClassWithoutNoexpect()
	{
		std::cout << "Destructor" << std::endl;
	}
	ClassWithoutNoexpect( ClassWithoutNoexpect&& )
	{
		std::cout << "Move Constructor" << std::endl;
	}
	auto& operator=( const ClassWithoutNoexpect& )
	{
		std::cout << "Assignment operator" << std::endl;
		return *this;
	}
	auto& operator=( ClassWithoutNoexpect&& )
	{
		std::cout << "Move Assignment operator" << std::endl;
		return *this;
	}
};

class ClassWithNoexpect
{
public:
	ClassWithNoexpect()
	{
		std::cout << "Default Constructor" << std::endl;
	}
	ClassWithNoexpect( const ClassWithNoexpect& )
	{
		std::cout << "Copy Constructor" << std::endl;
	}
	~ClassWithNoexpect()
	{
		std::cout << "Destructor" << std::endl;
	}
	ClassWithNoexpect( ClassWithNoexpect&& ) noexcept
	{
		std::cout << "Move Constructor" << std::endl;
	}
	auto& operator=( const ClassWithNoexpect& )
	{
		std::cout << "Assignment operator" << std::endl;
		return *this;
	}
	auto& operator=( ClassWithNoexpect&& ) noexcept
	{
		std::cout << "Move Assignment operator" << std::endl;
		return *this;
	}
};

TEST( RuleOfFive, CopyInContainerInsteadOfMove )
{
	{
		std::cout << "#########################" << std::endl;
		std::cout << "# Class without noexpect" << std::endl;
		std::cout << "#########################" << std::endl;
		std::vector<ClassWithoutNoexpect> vec;
		vec.reserve( 2 );
		std::cout << "--Emplace back" << std::endl;
		vec.emplace_back( ClassWithoutNoexpect() );
		vec.emplace_back( ClassWithoutNoexpect() );
		std::cout << "--Resize from 2 to 5" << std::endl;

		// Resize - creates 3 additional default constructed objects, also copy old to new space
		vec.resize( 5 );

		std::cout << "--End of test" << std::endl;
	}

	{
		std::cout << "#########################" << std::endl;
		std::cout << "# Class with noexpect" << std::endl;
		std::cout << "#########################" << std::endl;
		std::vector<ClassWithNoexpect> vec;
		vec.reserve( 2 );
		std::cout << "--Emplace back" << std::endl;
		vec.emplace_back( ClassWithNoexpect() );
		vec.emplace_back( ClassWithNoexpect() );
		std::cout << "--Resize from 2 to 5" << std::endl;

		// Resize - creates 3 additional default constructed objects, also move old to new space
		vec.resize( 5 );

		std::cout << "--End of test" << std::endl;
	}
}