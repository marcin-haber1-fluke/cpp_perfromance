//
// Created by it on 7/8/22.
//

#include <benchmark/benchmark.h>
#include <unordered_map>

/*
 * Unordered sets and maps based on hash tables. For each element hash is generated. If hash
 * has the same value for two elements, they are kept in one bucket. Then when finding such elements
 * whole bucket need to be checked with O(n) complexity. So it is very important to have good has method.
 *
 * Possible implementation (buckets can have 0 or more elements):
 * Buckets:
 * 0: element1, element2, element3
 * 1:
 * 2: element 6
 * 3:
 * 4:
 * 5: element4, element5, element6
 *
 * Elements need to have equal operator implemented to be able to find element in the bucket.
 *
 * Hash value need to be computed in constant time and need respect container size. It is important to create
 * same hash for same objects. It is allowed to have the same hash for different objects. Then elements just
 * go to one bucket related to the calculated hash. (one bucket - one hash value).
 *
 * Good hash table should meet the following requirements:
 * - fast to compute
 * - distribute hash over container to avoid many elements in on bucket
 *
 * Goal:
 * Create unordered map with pure hashing object and with default hashing object. Check performance of finding objects
 * in both maps. Key type need to define comparison operator to be able to find correct value in bucket.
 */

#include <iostream>

void CreatingMapWithBiggerNumberOfBuckets( benchmark::State& state )
{
	for ( auto _ : state )
	{
		//	template <class Key,
		//		class T,
		//		class Hash = std::hash<Key>,
		//		class Pred = std::equal_to<Key>>
		using Map = std::unordered_map<int, int>;
		Map map;

		for ( int i = 0 ; i < 1000 ; ++i )
		{
			map.insert_or_assign( i, i * 2 );
		}
	}
}

// Need to rehash map, when there is too much elements per buckets
void CreatingMapWithDefaultNumberOfBuckets( benchmark::State& state )
{
	for ( auto _ : state )
	{
		for ( auto _ : state )
		{
			//	template <class Key,
			//		class T,
			//		class Hash = std::hash<Key>,
			//		class Pred = std::equal_to<Key>>
			using Map = std::unordered_map<int, int>;
			Map map{ 100 };

			for ( int i = 0 ; i < 1000 ; ++i )
			{
				map.insert_or_assign( i, i * 2 );
			}
		}
	}
}

BENCHMARK( CreatingMapWithBiggerNumberOfBuckets );
BENCHMARK( CreatingMapWithDefaultNumberOfBuckets );

/////////////////////////////////////////
/////////////////////////////////////////

struct Person
{

};

auto hash = []( int a_Key )
{
	return 10;
};

class UnorderedMapWithSameHashForAllObjectsFixture : public benchmark::Fixture
{
public:
	UnorderedMapWithSameHashForAllObjectsFixture()
	{
		if ( !done )
		{
			done = true;

			std::cout << "-- UnorderedMapWithSameHashForAllObjectsFixture --" << std::endl;
			std::cout << "Buckets count: " << map.bucket_count() << std::endl;
			std::cout << "Average number of elements per bucket: " << map.load_factor() << std::endl;

			// When this is exceeded, then number of buckets is increased and rehashing need to be done (because hashing function depends on number of buckets)
			std::cout << "Max average number of elements per bucket: " << map.max_load_factor() << std::endl; // Upper limit of load factor

			for ( int i = 0 ; i < 1000 ; ++i )
			{
				map.insert_or_assign( i, Person{} );
			}

			std::cout << "After adding 1000 elements, bucket size: " << map.bucket_size( 10 ) << std::endl; // Print bucket size for 10, all elements in the same bucket, find is slow
			std::cout << "After adding 1000 elements, buckets count: " << map.bucket_count() << std::endl;
			std::cout << "After adding 1000 elements, average elements per bucket: " << map.load_factor() << std::endl;
			std::cout << "After adding 1000 elements, max average elements per bucket: " << map.max_load_factor() << std::endl;
		}
	}

	void SetUp(const ::benchmark::State& state)
	{
	}

	void TearDown(const ::benchmark::State& state)
	{
	}

	void Test()
	{
		auto iter = map.find( 950 );
	}

	//	template <class Key,
	//		class T,
	//		class Hash = std::hash<Key>,
	//		class Pred = std::equal_to<Key>>
	using Map = std::unordered_map<int, Person, decltype( hash )>;
	inline static Map map;
	inline static bool done = false;
};

/*
* Buckets:
* 10: element1, element2, element3, ..., element1000 - find is very slow, because we need to check all elements to find expected one
*/
BENCHMARK_F(UnorderedMapWithSameHashForAllObjectsFixture, Test)(benchmark::State& st)
{
	for ( auto _: st )
	{
		Test();
	}
}

/////////////////////////////////////////
/////////////////////////////////////////

/*
* Buckets:
* 1: element1, element200, element3, ...
* 2: element101, element223, element5, ...
* ...
* 1230: element345, element2, ...
*
* First we found bucket by hash, that should be fast O(1), then find element in bucket, normally number of elements in buckets should be 1, so also fast
*/
class UnorderedMapWithDefaultHashForAllObjectsFixture : public benchmark::Fixture
{
public:
	UnorderedMapWithDefaultHashForAllObjectsFixture()
	{
		if ( !done )
		{
			done = true;

			std::cout << "-- UnorderedMapWithDefaultHashForAllObjectsFixture --" << std::endl;
			std::cout << "Buckets count: " << map.bucket_count() << std::endl;
			std::cout << "Average number of elements per bucket: " << map.load_factor() << std::endl;

			// When this is exceeded, then number of buckets is increased and rehashing need to be done (because hashing function depends on number of buckets)
			std::cout << "Max average number of elements per bucket: " << map.max_load_factor() << std::endl; // Upper limit of load factor

			for ( int i = 0 ; i < 1000 ; ++i )
			{
				map.insert_or_assign( i, Person{} );
			}

			std::cout << "After adding 1000 elements, buckets count: " << map.bucket_count() << std::endl;
			std::cout << "After adding 1000 elements, average elements per bucket: " << map.load_factor() << std::endl;
			std::cout << "After adding 1000 elements, max average elements per bucket: " << map.max_load_factor() << std::endl;
		}
	}

	void SetUp(const ::benchmark::State& state)
	{
	}

	void TearDown(const ::benchmark::State& state)
	{
	}

	void Test()
	{
		auto iter = map.find( 950 );
	}

	//	template <class Key,
	//		class T,
	//		class Hash = std::hash<Key>,
	//		class Pred = std::equal_to<Key>>
	using Map = std::unordered_map<int, Person>;
	inline static Map map;
	inline static bool done = false;
};

BENCHMARK_F(UnorderedMapWithDefaultHashForAllObjectsFixture, Test)(benchmark::State& st)
{
	for ( auto _: st )
	{
		Test();
	}
}

BENCHMARK_MAIN();