//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>

/*
 * Tuple is a fixed size array with specified types
 */

TEST( Tuple, Initialization )
{
	// Initialization by types
	auto t1 = std::tuple<int, bool, std::string>{};

	// Initialization by argument deduction in constructor
	auto t2 = std::tuple(10, true, "str");

	// Initialization by argument deduction in function - this one is superfluous, because constructor can from C++17 also deduce types
	auto t3 = std::make_tuple(10, true, "str");

	/* All above tuples will be interpreted as normal struct:
	 *
	 * struct Tuple
	 * {
	 *  	int data0_{};
	 *  	bool data1_{};
	 *  	std::string data2_{};
	 * }
	*/
}

TEST( Tuple, AccessingElements )
{
	// Accessing elements is done with free function 'get'. 'at()' cannot be used
	// because at() can be used only for one type
	auto t1 = std::tuple<int, bool, std::string>{};

	auto data0 = std::get<0>(t1);
	auto data1 = std::get<1>(t1);
	auto data2 = std::get<2>(t1);

	std::cout << "Data with index 0: " << data0 << std::endl;
	std::cout << "Data with index 1: " << data1 << std::endl;
	std::cout << "Data with index 2: " << data2 << std::endl;

	/* 'get()' can be interpreted as:
	 *
	 * template<size_t Index, typename Tuple>
	 * auto& get( const Tuple& a_tuple )
	 * {
	 * 		if constexpr( Index == 0 )
	 * 		{
	 * 			return t.data0;
	 * 		}
	 * 		if constexpr( Index == 1 )
	 * 		{
	 * 			return t.data1;
	 * 		}
	 * 		if constexpr( Index == 2 )
	 * 		{
	 * 			return t.data2;
	 * 		}
	 * }
	*/
}