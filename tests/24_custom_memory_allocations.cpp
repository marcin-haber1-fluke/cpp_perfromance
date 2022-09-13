//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>
#include <memory_resource>

/*
 * Two kinds of allocators can be used with standard container:
 * - custom memory allocator (it is part of container type)
 * - polymorphic memory allocators (this can be change, and it is not a part of container type). In order to use polymorphic allocators we need
 * to use containers from namespace std::pmr::memory_resource to use custom memory allocator without
 */

////////////////////////////////////////////////////////////
// Very simple and easy allocator based on malloc and free
template<class T>
struct Mallocator
{
	using value_type = T;

	Mallocator() = default;

	template<class U>
	Mallocator( const Mallocator<U>& ) noexcept
	{};

	template<class U>
	auto operator==( const Mallocator<U>& ) noexcept
	{ return true; }; // Returns true for allocator of the same type (stateless allocator)

	template<class U>
	auto operator!=( const Mallocator<U>& ) noexcept
	{ return false; };

	auto allocate( size_t n ) const -> T*
	{
		if ( n == 0 )
		{
			return nullptr;
		}

		if ( n > std::numeric_limits<size_t>::max() / sizeof( T ) )
		{
			throw std::bad_array_new_length{};
		}

		void* const pv = malloc( n * sizeof( T ) );
		if ( pv == nullptr )
		{
			throw std::bad_alloc{};
		}

		std::cout << "Allocate: " << n * sizeof( T ) << " bytes of data" << std::endl;
		return static_cast<T*>( pv );
	}

	auto deallocate( T* p, size_t n ) const noexcept -> void
	{
		std::cout << "Deallocate: " << n * sizeof( T ) << " bytes of data" << std::endl;
		free(p);
	}
};

TEST( Algorithms, CustomMemoryAllocation )
{
	// Create vector with 10 elements: 10 * 4 bytes = 40 bytes
	std::vector<float, Mallocator<float>> vec( 10 );
}
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
class PrintingResource : public std::pmr::memory_resource
{
public:
	PrintingResource()
	: m_res{ std::pmr::get_default_resource() }
	{}

	void* do_allocate( std::size_t bytes, std::size_t alignment ) override
	{
		std::cout << "Allocate: " << bytes << " bytes of data, alignment: " << alignment << std::endl;
		return m_res->allocate( bytes, alignment );
	}

	void do_deallocate( void* p, std::size_t bytes, std::size_t alignment) override
	{
		std::cout << "Deallocate: " << bytes << " bytes of data, alignment: " << alignment << std::endl;
		m_res->deallocate( p, bytes, alignment );
	}

	bool do_is_equal( const std::pmr::memory_resource& other ) const noexcept override
	{
		return ( this == &other );
	}

private:
	std::pmr::memory_resource* m_res;
};

TEST( Algorithms, PolymorphicMemoryAllocation )
{
	PrintingResource p;
	// Create vector with 10 elements: 10 * 4 bytes = 40 bytes
	std::pmr::vector<float> vec( 10, &p );
}
////////////////////////////////////////////////////////////