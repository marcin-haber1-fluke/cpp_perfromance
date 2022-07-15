//
// Created by it on 7/8/22.
//

#include <benchmark/benchmark.h>
#include <numeric>
#include <memory>

// Lambda - comparison to function objects:

////////////////////////////////////
// Capture list by value
////////////////////////////////////

// Lambda with capture by value
void LambdaCaptureByValue( benchmark::State& state )
{
	int x = 10;
	auto isBigger = [x]( int y )
	{
		return y > x;
	};

	std::vector<int> data( 1000 );
	std::iota( std::begin( data ), std::end( data ), 1 );

	for ( auto _ : state )
	{
		for ( const auto& v : data )
		{
			isBigger( v );
		}
	}
}

// Function object corresponds to lambda capture by value
// - capture list -> arguments in constructor, same types as a members
// - calling -> const function operator with lambda arguments - cannot change members
class IsBiggerByValue
{
public:
	IsBiggerByValue( int a_x )
			: m_x{ a_x }
	{}

	auto operator()( int a_y ) const
	{
		return a_y > m_x;
	}

	int m_x;
};

void FunctionObjectCorrespondingToLambdaCaptureByValue( benchmark::State& state )
{
	int x = 10;
	IsBiggerByValue isBigger( x );

	std::vector<int> data( 1000 );
	std::iota( std::begin( data ), std::end( data ), 1 );

	for ( auto _ : state )
	{
		for ( const auto& v : data )
		{
			isBigger( v );
		}
	}
}

////////////////////////////////////
// Capture list by reference
////////////////////////////////////

// Lambda with capture by reference
void LambdaCaptureByReference( benchmark::State& state )
{
	int x = 10;
	auto isBigger = [&x]( int y )
	{
		return y > x;
	};

	std::vector<int> data( 1000 );
	std::iota( std::begin( data ), std::end( data ), 1 );

	for ( auto _ : state )
	{
		for ( const auto& v : data )
		{
			isBigger( v );
		}
	}
}

// Function object corresponds to lambda capture by value
// - capture list -> arguments in constructor, same types as a members
// - calling -> const function operator with lambda arguments - cannot change members
class IsBiggerByReference
{
public:
	IsBiggerByReference( int& a_x )
			: m_x{ a_x }
	{}

	auto operator()( int a_y ) const
	{
		return a_y > m_x;
	}

	int& m_x;
};

void FunctionObjectCorrespondingToLambdaCaptureByReference( benchmark::State& state )
{
	int x = 10;
	IsBiggerByValue isBigger( x );

	std::vector<int> data( 1000 );
	std::iota( std::begin( data ), std::end( data ), 1 );

	for ( auto _ : state )
	{
		for ( const auto& v : data )
		{
			isBigger( v );
		}
	}
}

////////////////////////////////////
// Mutable lambda
////////////////////////////////////

// Lambda with capture by value mutable
void LambdaCaptureByValueMutable( benchmark::State& state )
{
	int x = 10;
	auto getSum = [x]( int y ) mutable
	{
		return x = y + y;
	};

	std::vector<int> data( 1000 );
	std::iota( std::begin( data ), std::end( data ), 1 );

	for ( auto _ : state )
	{
		for ( const auto& v : data )
		{
			getSum( v );
		}
	}
}

// Function object corresponds to lambda capture by value
// - capture list -> arguments in constructor, same types as a members
// - calling -> function operator with lambda arguments - can change members
class GetSumMutable
{
public:
	GetSumMutable( int a_x )
			: m_x{ a_x }
	{}

	auto operator()( int a_y )
	{
		return m_x = a_y + a_y;
	}

	int m_x;
};

void FunctionObjectCorrespondingToLambdaCaptureByValueMutable( benchmark::State& state )
{
	int x = 10;
	GetSumMutable getSum( x );

	std::vector<int> data( 1000 );
	std::iota( std::begin( data ), std::end( data ), 1 );

	for ( auto _ : state )
	{
		for ( const auto& v : data )
		{
			getSum( v );
		}
	}
}

////////////////////////////////////
// Lambda with member initialization
////////////////////////////////////

// Lambda with member initialization
// - std::move() can be used
// - different name for lambda argument can be used
void LambdaWithMemberInitialization( benchmark::State& state )
{
	auto get = [x = 20]()
	{
		return x;
	};

	// This lambda corresponds to the following function object
	//	class Get
	//	{
	//	public:
	//		Get()
	//				: m_x{ 20 }
	//		{}
	//
	//		auto operator()()
	//		{
	//			return m_x;
	//		}
	//
	//		std::unique_ptr<int> m_x;
	//	};

	std::vector<int> data( 1000 );
	std::iota( std::begin( data ), std::end( data ), 1 );

	for ( auto _ : state )
	{
		for ( const auto& v : data )
		{
			get();
		}
	}
}

// Some examples of captures:
// int a, b, c
// auto func = [=]{}; Capture a, b, c by value

// int a, b, c
// auto func = [&]{}; Capture a, b, c by reference

// int a, b, c
// auto func = [=, &c]{}; Capture a, b by value, c by reference

// int a, b, c
// auto func = [&, c]{}; Capture a, b by reference, c by value

// Be careful when using reference in capture list - object have to exist, when lambda is called

BENCHMARK( LambdaCaptureByValue );
BENCHMARK( FunctionObjectCorrespondingToLambdaCaptureByValue );

BENCHMARK( LambdaCaptureByReference );
BENCHMARK( FunctionObjectCorrespondingToLambdaCaptureByReference );

BENCHMARK( LambdaCaptureByValueMutable );
BENCHMARK( FunctionObjectCorrespondingToLambdaCaptureByValueMutable );

BENCHMARK( LambdaWithMemberInitialization );

BENCHMARK_MAIN();