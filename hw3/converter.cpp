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

    double get_dzh()
    {
        switch(m_unit)
        {
            case 'd':
                return m_value;
            case 'e':
                return m_value * 1.6 * pow(10, 19);
            case 'c':
                return m_value * 4.184;
        }
        return 0;
    }

    double get_cal()
    {
        switch(m_unit)
        {
            case 'd':
                return m_value / 4.184;
            case 'e':
                return m_value * 3.83 * pow(10, 20);
            case 'c':
                return m_value;
        }
        return 0;
    }

    double get_ev()
    {
        switch(m_unit)
        {
            case 'd':
                return m_value * 6,24 * pow(10, 18);
            case 'e':
                return m_value;
            case 'c':
                return m_value * 2.61 * pow(10, 19);
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