#include <iostream>


double pow(double a, int b)
{
    auto res = 1.0;
    for(auto i = 0; i < b; i++)
    {
        res *= a;
    }
    return res;
}


class Energy
{
public:
    Energy(double value, char unit) : m_value(value), m_unit(unit)
    {
    }

    static inline const double q_e = 1.6 * pow(10, 19);
    static inline const double cal = 4.184;

    double get_dzh() const
    {
        switch(m_unit)
        {
            case 'd':
                return m_value;
            case 'e':
                return m_value / q_e;
            case 'c':
                return m_value * cal;
        }
        return 0;
    }

    double get_cal() const
    {
        switch(m_unit)
        {
            case 'd':
                return m_value / cal;
            case 'e':
                return m_value / q_e / cal;
            case 'c':
                return m_value;
        }
        return 0;
    }

    double get_ev() const
    {
        switch(m_unit)
        {
            case 'd':
                return m_value * q_e;
            case 'e':
                return m_value;
            case 'c':
                return m_value * cal * q_e;
        }
        return 0;
    }
    
private:
    double m_value{};
    char m_unit{};
};

int main()
{
    double value{};
    char unit{};
    std::cout << "Input the value of energy and its measurement unit(d for dzh, e for ev, c for cal): ";
    std::cin >> value >> unit;
    Energy energy(value, unit);
    std::cout << energy.get_cal() << " cal" << "\n";
    std::cout << energy.get_dzh() << " dzh" << "\n";
    std::cout << energy.get_ev() << " ev";
}