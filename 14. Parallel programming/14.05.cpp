#include <future>
#include <thread>
#include <chrono>
#include <iostream>
#include <cassert>

int main()
{
    using namespace std::chrono_literals;

    std::promise <int> p;
    std::shared_future <int> sf_A = p.get_future(); // cell A

    std::future <int> f_B = std::async(std::launch::async, [&sf_A](){std::this_thread::sleep_for(1s); return sf_A.get()*2;}); //cell B with formula using A

    p.set_value(42); // setting A value

    std::future <int> f_C = std::async(std::launch::async, [&sf_A](){std::this_thread::sleep_for(1s); return sf_A.get()/2;}); //cell C with formula using A

    assert(sf_A.get() == 42 && f_B.get() == 84 && f_C.get() == 21);

}