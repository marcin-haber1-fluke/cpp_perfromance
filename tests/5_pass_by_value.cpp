//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>

// Passing by value is a recommended method for most of the cases. It is not the most efficient, but statistically enough efficient.
// More performant is to write separate methods to handle rvalues and lvalues, but this extends code base and in standard cases
// differences are not so big

int numberOfDefaultConstructorCalls = 0;
int numberOfCopyConstructorCalls = 0;
int numberOfMoveConstructorCalls = 0;
int numberOfCopyAssignmentOperatorCalls = 0;
int numberOfMoveAssignmentOperatorCalls = 0;

class A
{
public:
	A()
	{
		numberOfDefaultConstructorCalls++;
//		std::cout << "Default Constructor" << std::endl;
	}
	A( const A& )
	{
		numberOfCopyConstructorCalls++;
//		std::cout << "Copy Constructor" << std::endl;
	}
	~A()
	{
//		std::cout << "Destructor" << std::endl;
	}
	A( A&& ) noexcept
	{
		numberOfMoveConstructorCalls++;
//		std::cout << "Move Constructor" << std::endl;
	}
	auto& operator=( const A& )
	{
		numberOfCopyAssignmentOperatorCalls++;
//		std::cout << "Assignment operator" << std::endl;
		return *this;
	}
	auto& operator=( A&& ) noexcept
	{
		numberOfMoveAssignmentOperatorCalls++;
//		std::cout << "Move Assignment operator" << std::endl;
		return *this;
	}
};

class BConstRef_Copy
{
public:
	BConstRef_Copy( const A& a_a )
			: m_a( a_a )
	{}

	A m_a;
};

class BCopy_Move
{
public:
	BCopy_Move( A a_a )
			: m_a( std::move( a_a ) )
	{}

	A m_a;
};

class BMixed
{
public:
	BMixed( const A& a_a )
			: m_a( a_a )
	{}
	BMixed( A&& a_a )
			: m_a( std::move( a_a ) )
	{}

	A m_a;
};

// Input: rvalue, Argument type: const ref
TEST( PassingByValue, InputRValue_ArgumentTypeConstReference )
{
	numberOfDefaultConstructorCalls = 0;
	numberOfCopyConstructorCalls = 0;
	numberOfMoveConstructorCalls = 0;
	numberOfCopyAssignmentOperatorCalls = 0;
	numberOfMoveAssignmentOperatorCalls = 0;

	BConstRef_Copy b{ A() };
	b.m_a;

	std::cout << "###########################################" << std::endl;
	std::cout << "# Input: rvalue, Argument type: const ref" << std::endl;
	std::cout << "###########################################" << std::endl;
	std::cout << "Default constructor calls: " << numberOfDefaultConstructorCalls << std::endl;
	std::cout << "Copy constructor calls: " << numberOfCopyConstructorCalls << std::endl;
	std::cout << "Move constructor calls: " << numberOfMoveConstructorCalls << std::endl;
	std::cout << "Copy assignment operator calls: " << numberOfCopyAssignmentOperatorCalls << std::endl;
	std::cout << "Move assignment operator calls: " << numberOfMoveAssignmentOperatorCalls << std::endl;
}

// Input: lvalue, Argument type: const ref
TEST( PassingByValue, InputLValue_ArgumentTypeConstReference )
{
	numberOfDefaultConstructorCalls = 0;
	numberOfCopyConstructorCalls = 0;
	numberOfMoveConstructorCalls = 0;
	numberOfCopyAssignmentOperatorCalls = 0;
	numberOfMoveAssignmentOperatorCalls = 0;

	auto a = A();
	BConstRef_Copy b{ a };
	b.m_a;

	std::cout << "###########################################" << std::endl;
	std::cout << "# Input: lvalue, Argument type: const ref" << std::endl;
	std::cout << "###########################################" << std::endl;
	std::cout << "Default constructor calls: " << numberOfDefaultConstructorCalls << std::endl;
	std::cout << "Copy constructor calls: " << numberOfCopyConstructorCalls << std::endl;
	std::cout << "Move constructor calls: " << numberOfMoveConstructorCalls << std::endl;
	std::cout << "Copy assignment operator calls: " << numberOfCopyAssignmentOperatorCalls << std::endl;
	std::cout << "Move assignment operator calls: " << numberOfMoveAssignmentOperatorCalls << std::endl;
}

// Input: rvalue, Argument type: copy + move
TEST( PassingByValue, InputRValue_ArgumentTypeCopy )
{
	numberOfDefaultConstructorCalls = 0;
	numberOfCopyConstructorCalls = 0;
	numberOfMoveConstructorCalls = 0;
	numberOfCopyAssignmentOperatorCalls = 0;
	numberOfMoveAssignmentOperatorCalls = 0;

	BCopy_Move b{ A() };
	b.m_a;

	std::cout << "###########################################" << std::endl;
	std::cout << "# Input: rvalue, Argument type: copy + move" << std::endl;
	std::cout << "###########################################" << std::endl;
	std::cout << "Default constructor calls: " << numberOfDefaultConstructorCalls << std::endl;
	std::cout << "Copy constructor calls: " << numberOfCopyConstructorCalls << std::endl;
	std::cout << "Move constructor calls: " << numberOfMoveConstructorCalls << std::endl;
	std::cout << "Copy assignment operator calls: " << numberOfCopyAssignmentOperatorCalls << std::endl;
	std::cout << "Move assignment operator calls: " << numberOfMoveAssignmentOperatorCalls << std::endl;
}

// Input: lvalue, Argument type: copy + move
TEST( PassingByValue, InputLValue_ArgumentTypeCopy )
{
	numberOfDefaultConstructorCalls = 0;
	numberOfCopyConstructorCalls = 0;
	numberOfMoveConstructorCalls = 0;
	numberOfCopyAssignmentOperatorCalls = 0;
	numberOfMoveAssignmentOperatorCalls = 0;

	auto a = A();
	BCopy_Move b{ a };
	b.m_a;

	std::cout << "###########################################" << std::endl;
	std::cout << "# Input: lvalue, Argument type: copy + move" << std::endl;
	std::cout << "###########################################" << std::endl;
	std::cout << "Default constructor calls: " << numberOfDefaultConstructorCalls << std::endl;
	std::cout << "Copy constructor calls: " << numberOfCopyConstructorCalls << std::endl;
	std::cout << "Move constructor calls: " << numberOfMoveConstructorCalls << std::endl;
	std::cout << "Copy assignment operator calls: " << numberOfCopyAssignmentOperatorCalls << std::endl;
	std::cout << "Move assignment operator calls: " << numberOfMoveAssignmentOperatorCalls << std::endl;
}

// Conclusion:
// When use idom copy and move we have in the worst case one copy and one move, when move is considered as very cheap. When using reference and copy
// approach we have one copy all the time.

// The best approach, but with need of more typing is to provide two versions: one for lvalues and one for rvalues

// Input: rvalue, Argument type: mixed
TEST( PassingByValue, InputRValue_ArgumentTypeMixed )
{
	numberOfDefaultConstructorCalls = 0;
	numberOfCopyConstructorCalls = 0;
	numberOfMoveConstructorCalls = 0;
	numberOfCopyAssignmentOperatorCalls = 0;
	numberOfMoveAssignmentOperatorCalls = 0;

	BMixed b{ A() };
	b.m_a;

	std::cout << "###########################################" << std::endl;
	std::cout << "# Input: rvalue, Argument type: mixed" << std::endl;
	std::cout << "###########################################" << std::endl;
	std::cout << "Default constructor calls: " << numberOfDefaultConstructorCalls << std::endl;
	std::cout << "Copy constructor calls: " << numberOfCopyConstructorCalls << std::endl;
	std::cout << "Move constructor calls: " << numberOfMoveConstructorCalls << std::endl;
	std::cout << "Copy assignment operator calls: " << numberOfCopyAssignmentOperatorCalls << std::endl;
	std::cout << "Move assignment operator calls: " << numberOfMoveAssignmentOperatorCalls << std::endl;
}

// Input: lvalue, Argument type: mixed
TEST( PassingByValue, InputLValue_ArgumentTypeMixed )
{
	numberOfDefaultConstructorCalls = 0;
	numberOfCopyConstructorCalls = 0;
	numberOfMoveConstructorCalls = 0;
	numberOfCopyAssignmentOperatorCalls = 0;
	numberOfMoveAssignmentOperatorCalls = 0;

	auto a = A();
	BMixed b{ a };
	b.m_a;

	std::cout << "###########################################" << std::endl;
	std::cout << "# Input: lvalue, Argument type: mixed" << std::endl;
	std::cout << "###########################################" << std::endl;
	std::cout << "Default constructor calls: " << numberOfDefaultConstructorCalls << std::endl;
	std::cout << "Copy constructor calls: " << numberOfCopyConstructorCalls << std::endl;
	std::cout << "Move constructor calls: " << numberOfMoveConstructorCalls << std::endl;
	std::cout << "Copy assignment operator calls: " << numberOfCopyAssignmentOperatorCalls << std::endl;
	std::cout << "Move assignment operator calls: " << numberOfMoveAssignmentOperatorCalls << std::endl;
}

// In the mixed version in the worst case we have one copy, and in the best case one move.