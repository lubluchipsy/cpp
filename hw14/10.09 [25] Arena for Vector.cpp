#include <bit>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

#include <boost/noncopyable.hpp>

class Arena : private boost::noncopyable // note: no deallocations for blocks of different sizes
{
public:

	explicit Arena(std::size_t size) : m_size(size)
	{
		m_begin = ::operator new(m_size, default_alignment);
	}

	~Arena() noexcept
	{
		::operator delete(m_begin, default_alignment);
	}

	[[nodiscard]] void * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t))
	{
		void * first = get_byte(m_begin) + m_offset;

		auto space = m_size - m_offset;

		if (first = std::align(alignment, size, first, space); first) // note: modifies first and space
		{
			m_offset = m_size - space + size;                         
			
			return first; // note: aligned pointer
		}
		else return nullptr;
	}

    void deallocate(void * ptr, std::size_t size) const noexcept 
    {
		
    }

	void print() const
	{
		std::cout << m_begin << ": ";

		std::cout << std::setw(4) << std::right << std::setfill('0') << m_offset;

		std::cout << " / " << m_size << std::endl;
	}

private:

	std::byte * get_byte(void * ptr) const noexcept
	{
		return std::bit_cast < std::byte * > (ptr);
	}

public:

	static inline const std::align_val_t default_alignment { alignof(std::max_align_t) };

private:
	
	std::size_t m_size   = 0;
	std::size_t m_offset = 0;

	void * m_begin = nullptr;

}; // class Arena_Allocator : private boost::noncopyable


template < typename T > class Allocator
{
public:

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;

public:
    
    Allocator(Arena * arena): m_arena(arena){};

    pointer allocate(std::size_t size, size_type alignment = alignof(std::max_align_t)) const noexcept
    {
        return static_cast < pointer > (m_arena -> allocate(size * sizeof(T)));
    }

    void deallocate(pointer ptr, size_type size) const noexcept
    {
        m_arena -> deallocate(ptr, size * sizeof(T));
    }

private:

    Arena * m_arena = nullptr;

}; // template < typename T > class Allocator

int main()
{
	Arena arena(1024);

    Allocator < int > allocator(& arena);

    arena.print(); // note: 0 bytes used

    std::vector < int, Allocator < int > > vector(10, 42, allocator);

    arena.print(); // note: 40 bytes used

    vector.push_back(42);

    arena.print(); // note: 128 bytes used

	std::cout << alignof(int) << std::endl;

	return 0;
}