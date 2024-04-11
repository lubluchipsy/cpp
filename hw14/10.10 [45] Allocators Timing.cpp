#include <bit>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <cmath>
#include <fstream>

#include <boost/noncopyable.hpp>

class Timer
{
public:

	using clock_t = std::chrono::steady_clock;

	explicit Timer() : m_is_running(false){}

	void start()
	{
		if (m_is_running != false)
		{
			throw std::logic_error("Timer is already running.");
		}

		m_begin = clock_t::now();
		m_is_running = true;
	}

	void stop()
	{
		if (m_is_running != true)
		{
			throw std::logic_error("Timer is not running.");
		}

		m_is_running = false;
		m_series.push_back(std::chrono::duration_cast<std::chrono::microseconds>(clock_t::now() - m_begin).count());
	}

	auto result()
	{
		if (m_series.empty())
		{
			return 0.0;
		}

		auto sum = 0.0;
		for (auto time : m_series)
		{
			sum += time;
		}

		return sum / m_series.size() / 1'000'000.0;
	}

	std::vector<long long> m_series;

private:

	clock_t::time_point m_begin;

	bool m_is_running;

}; // class Timer

class Arena_Allocator : private boost::noncopyable // note: no deallocations for blocks of different sizes
{
public:

	explicit Arena_Allocator(std::size_t size) : m_size(size)
	{
		m_begin = ::operator new(m_size, default_alignment);
	}

	~Arena_Allocator() noexcept
	{
		::operator delete(m_begin, default_alignment);
	}

	[[nodiscard]] void * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) noexcept
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


class Stack_Allocator : private boost::noncopyable // note: deallocations at end for blocks of different sizes
{
private:

	using Header = std::uint8_t;

public:

	explicit Stack_Allocator(std::size_t size) : m_size(size)
	{
		m_begin = ::operator new(m_size, default_alignment);
	}

	~Stack_Allocator() noexcept
	{
		::operator delete(m_begin, default_alignment);
	}

	[[nodiscard]] void * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) noexcept
	{
		void * first = get_byte(m_begin) + m_offset;

		void * block = get_byte(first) + sizeof(Header); // note: first byte for data after header

		auto space = m_size - m_offset - sizeof(Header);

		if (block = std::align(alignment, size, block, space); block) // note: modifies block and space
		{
			auto header = get_header(get_byte(block) - sizeof(Header));

			*header = static_cast < Header > (std::distance(get_byte(first), get_byte(block)));

			m_offset = get_byte(block) - get_byte(m_begin) + size;

			return block; // note: aligned pointer
		}
		else return nullptr;
	}

	void deallocate(void * ptr) noexcept
	{
		auto header = get_header(get_byte(ptr) - sizeof(Header));

		m_offset = get_byte(ptr) - get_byte(m_begin) - *header;
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

	Header * get_header(void * ptr) const noexcept
	{
		return std::bit_cast < Header * > (ptr);
	}

public:

	static inline const std::align_val_t default_alignment { alignof(std::max_align_t) };

private:

	std::size_t m_size   = 0;
	std::size_t m_offset = 0;

	void * m_begin = nullptr;

}; // class Stack_Allocator : private boost::noncopyable

class Chain_Allocator : private boost::noncopyable // note: deallocations at any position for blocks of fixed sizes
{
private:

	struct Block { Block * next = nullptr; };
	
public:

	explicit Chain_Allocator(std::size_t size, std::size_t size_block) : m_size(size)
	{
		m_size_block = std::max(size_block, sizeof(Block));

		if (m_size % m_size_block != 0)
		{
			throw std::runtime_error("invalid size");
		}

		make_chain(); m_begin = m_head;
	}

	~Chain_Allocator() noexcept
	{
		for (std::size_t i = 0; i < std::size(m_chains); ++i)
		{
			::operator delete(m_chains[i], default_alignment);
		}
	}

	[[nodiscard]] void * allocate()
	{
		if (m_head == nullptr) // note: current chain has ended
		{
			if (m_offset == std::size(m_chains))
			{
				make_chain();
			}
			else m_head = get_block(m_chains[++m_offset - 1]); // note: switch to next chain
		}

		auto block = m_head;

		if (!block->next) // note: try switch to next block in current chain
		{
			if (auto next  = get_byte(  block               ) + m_size_block; 
				     next != get_byte(m_chains[m_offset - 1]) + m_size)
			{
				m_head = get_block(next); m_head->next = nullptr;
			}
			else m_head = m_head->next; // note: current chain has ended
		}
		else m_head = m_head->next; // note: next after deallocation

		return block;
	}

	void deallocate(void * ptr) noexcept
	{
		auto block = get_block(ptr); 
		
		block->next = m_head; m_head = block; // note: link freed block to previous head
	}

	void print() const
	{
		std::cout << m_head << std::endl;
	}

private:

	std::byte * get_byte(void * ptr) const noexcept
	{
		return std::bit_cast < std::byte * > (ptr);
	}

	Block * get_block(void * ptr) const noexcept
	{ 
		return std::bit_cast < Block * > (ptr); 
	}

	Block * allocate_blocks() const
	{
		auto block = get_block(::operator new(m_size, default_alignment));
		
		block->next = nullptr; return block;
	}

	void make_chain()
	{
		m_head = allocate_blocks(); ++m_offset; m_chains.push_back(m_head);
	}

public:

	static inline const std::align_val_t default_alignment { alignof(std::max_align_t) };

private:

	std::size_t m_size       = 0;
	std::size_t m_size_block = 0;
		
	Block * m_head = nullptr;

	std::size_t m_offset = 0;

	std::vector < void * > m_chains;

	void * m_begin = nullptr;

}; // class Chain_Allocator : private boost::noncopyable

void test_arena(Timer & timer)
{
	constexpr std::size_t kb = 1024, mb = kb * kb, gb = kb * kb * kb;

	timer.start();
	{
		Arena_Allocator allocator(gb); 

		for (std::size_t i = 0; i < kb; ++i)
		{
			auto ptr = allocator.allocate(mb);
		}
	}
	timer.stop();
}

void test_stack(Timer & timer)
{
	constexpr std::size_t kb = 1024, mb = kb * kb, gb = kb * kb * kb;

	timer.start();
	{
		Stack_Allocator allocator(gb); 

		for (std::size_t i = 0; i < kb; ++i)
		{
			auto ptr = allocator.allocate(mb);
			allocator.deallocate(ptr);
		}
	}
	timer.stop();
}

void test_chain(Timer & timer)
{
	constexpr std::size_t kb = 1024, mb = kb * kb, gb = kb * kb * kb;

	timer.start();
	{
		Chain_Allocator allocator(gb, mb); 

		for (std::size_t i = 0; i < kb; ++i)
		{
			auto ptr = allocator.allocate();
			allocator.deallocate(ptr);
		}

	}
	timer.stop();
}

void test_new(Timer & timer)
{
	constexpr std::size_t kb = 1024, mb = kb * kb;

	std::vector < void * > pointers(kb, nullptr);

	timer.start();
	{
		for (std::size_t i = 0; i < kb; ++i) pointers[i] = ::operator    new(             mb);
		for (std::size_t i = 0; i < kb; ++i)               ::operator delete(pointers[i], mb);
	}
	timer.stop();
}



int main()
{
	Timer arena;
	Timer stack;
	Timer chain;
	Timer t_new;

	for (auto i = 0; i < 10; i++)
	{
		test_arena(arena);
		test_stack(stack);
		test_chain(chain);
		test_new(t_new);
	}

	std::ofstream out;          // поток для записи
    out.open("allocators_comparison.txt");      // открываем файл для записи
    if (out.is_open())
	{
		out << "Average time of allocating 1048576 bytes with          Arena: " << arena.result() << " seconds" << std::endl;
		out << "Average time of allocating 1048576 bytes with          Stack: " << stack.result() << " seconds"  << std::endl;
		out << "Average time of allocating 1048576 bytes with          Chain: " << chain.result() << " seconds" << std::endl;
		out << "Average time of allocating 1048576 bytes with ::operator new: " << t_new.result() << " seconds"  << std::endl;
	}

	// results in allocators_comparison.txt

	return 0;
}