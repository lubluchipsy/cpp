#include <iostream>
#include <filesystem>
#include <chrono>
#include <string>

void delete_files_by_time(const std::filesystem::path & dir, const std::chrono::system_clock::time_point & time)
{
    if (std::filesystem::exists(dir) && std::filesystem::is_directory(dir))
    {
        for (const auto & entry : std::filesystem::directory_iterator(dir))
		{
            const auto ftime = std::filesystem::last_write_time(entry.path());
            const auto sys_ftime = std::chrono::file_clock::to_sys(ftime);

            if (sys_ftime < time && std::filesystem::is_regular_file(entry.path()))
            {
                std::cout << "File " << entry.path().string() << " is removed" << std::endl;
                std::filesystem::remove(entry.path());
            }
        }
    }
}

int main()
{
    std::filesystem::path d {"./direct"};
    std::chrono::system_clock::time_point time = std::chrono::system_clock::now() - std::chrono::minutes(10);
    delete_files_by_time(d, time);
}