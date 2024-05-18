#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>


struct Process
{
    std::string name;
    unsigned int id;
    std::string status;
    std::string user;
};

void output_processes(const std::vector<Process> & processes) 
{
    std::sort(std::begin(processes), std::end(processes), [](const Process & p1, const Process & p2){return p1.name < p2.name;});
    std::cout << std::setw(25) << std::left << "Process Name";
    std::cout << std::setw(7) << std::left << "ID";
    std::cout << std::setw(10) << std::left << "Status";
    std::cout << std::setw(20) << std::left << "User";
    std::cout << '\n';

    for (auto const & p:processes)
    {
        std::cout << std::setw(25) << std::left << p.name;
        std::cout << std::setw(6) << std::right << p.id << ' ';
        std::cout << std::setw(10) << std::left << p.status;
        std::cout << std::setw(20) << std::left << p.user;
        std::cout << std::endl;
    }
}

int main()
{
    std::vector<Process> processes {{"code", 3614, "running", "marina"}, 
                                    {"firefox", 2635, "running", "marina"}, 
                                    {"pipewire-media-session", 1258, "running", "marina"}, 
                                    {"discord", 2754, "suspended", "marina"}};
    output_processes(processes);

    return 0;
}