#include <iostream>
#include <numeric>

struct Error: public std::exception
{
    const char * what() const noexcept override
    {
        return "Invalid denominator";
    }

};


class Ratio
{
public:

	using int_t = int;

public:

	Ratio(int_t n = 0, int_t d = 1) : // good: no explicit constructor
		m_numerator(n), m_denominator(d) 
	{
		if (m_denominator == 0) 
		{
			throw Error();
		}

		if (m_denominator < 0) // note: numerator keeps ratio sign
		{
			m_numerator   *= -1;
			m_denominator *= -1;
		}

		reduce();
	}

	explicit operator double() const // good: explicit cast operator
	{
		return 1.0 * m_numerator / m_denominator;
	}

private:

	void reduce()
	{
		auto gcd = std::gcd(m_numerator, m_denominator);

		m_numerator   /= gcd;
		m_denominator /= gcd;
	}

public:

	auto numerator() const
	{
		return m_numerator;
	}

	auto denominator() const
	{
		return m_denominator;
	}

public:

	void print() const // note: function instead of output operator
	{
		std::cout << m_numerator << '/' << m_denominator << std::endl;
	}

public:

	auto & operator+=(Ratio other)
	{
		auto lcm = std::lcm(m_denominator, other.m_denominator);

		m_numerator = m_numerator * (lcm /       m_denominator) +
			    other.m_numerator * (lcm / other.m_denominator);

		m_denominator = lcm;

		reduce();

		return *this;
	}

	auto & operator-=(Ratio other)
	{
		return (*this += (other.m_numerator *= -1));
	}
		
	auto & operator*=(Ratio other)
	{
		m_numerator   *= other.m_numerator;
		m_denominator *= other.m_denominator;

		reduce();

		return *this;
	}
	
	auto & operator/=(Ratio other)
	{
		return (*this *= Ratio(other.m_denominator, other.m_numerator));
	}

public:

	auto & operator++()
	{
		m_numerator += m_denominator;

		return *this;
	}

	auto & operator--()
	{
		m_numerator -= m_denominator;

		return *this;
	}

	auto operator++(int)
	{
		Ratio tmp(*this);

		++(*this);

		return tmp;

	}

	auto operator--(int)
	{
		Ratio tmp(*this);

		--(*this);

		return tmp;
	}

private:

	int_t m_numerator;
	int_t m_denominator;

}; // class Ratio

auto operator+(Ratio lhs, Ratio rhs) // good: free function
{
	return (lhs += rhs);
}

auto operator-(Ratio lhs, Ratio rhs) // good: free function
{
	return (lhs -= rhs);
}

auto operator*(Ratio lhs, Ratio rhs) // good: free function
{
	return (lhs *= rhs);
}

auto operator/(Ratio lhs, Ratio rhs) // good: free function
{
	return (lhs /= rhs);
}

auto operator<(Ratio lhs, Ratio rhs)
{
	return static_cast < double > (lhs) < static_cast < double > (rhs);
}

auto operator>(Ratio lhs, Ratio rhs)
{
	return (rhs < lhs);
}

auto operator<=(Ratio lhs, Ratio rhs)
{
	return !(lhs > rhs);
}

auto operator>=(Ratio lhs, Ratio rhs)
{
	return !(lhs < rhs);
}

auto operator==(Ratio lhs, Ratio rhs)
{
	return (!(lhs < rhs) && !(rhs < lhs));
}

auto operator!=(Ratio lhs, Ratio rhs)
{
	return !(lhs == rhs);
}

int main()
{
    try
    {
        Ratio r0(2, 0);

        return EXIT_SUCCESS;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what();

        return 1;
    }

	return 0;
}