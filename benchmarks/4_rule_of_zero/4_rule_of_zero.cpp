//
// Created by it on 7/8/22.
//

#include <benchmark/benchmark.h>

// Rule of zero:
// Class should take care about their resources, so it's a good practice to have all 5 methods implemented:
// - Copy Constructor
// - Destructor
// - Assignment Operator
// - Move Constructor
// - Move Assignment Operator
// Rule of zero says, that when class need to have self written one of above functions, then probably code can be written
// differently. Writing one of these, could prevent compiler to generate the rest that could decrease code performance.

class TestClassDefineOnlyDestructor
{
public:
	~TestClassDefineOnlyDestructor() {};
};

class TestClassTrivial
{
};

void CopyClassWithEmptyDestructor( benchmark::State& state )
{
	for ( auto _ : state )
	{
		std::vector<TestClassDefineOnlyDestructor> vec( 100000 );
		std::vector<TestClassDefineOnlyDestructor> vecCopy;
		std::copy( std::cbegin( vec ), std::cend( vec ), std::back_inserter( vecCopy ) );
	}
}

void CopyClassTrivial( benchmark::State& state )
{
	for ( auto _ : state )
	{
		std::vector<TestClassTrivial> vec( 100000 );
		std::vector<TestClassTrivial> vecCopy;
		std::copy( std::cbegin( vec ), std::cend( vec ), std::back_inserter( vecCopy ) );
	}

}

// std::copy() can be optimized, when move constructor is available. Because destructor was defined, compiler cannot generate move
// constructor, so copying is slower.
BENCHMARK( CopyClassWithEmptyDestructor );
BENCHMARK( CopyClassTrivial );
BENCHMARK_MAIN();