#include <iostream>
#include <filesystem>
#include <string>

std::string filename_to_upper(std::string filename)
{
    std::size_t name_end = filename.find_last_of(".");
    if (name_end = std::string::npos)
    {
        std::transform(filename.begin(), filename.end(), filename.begin(), [](unsigned char c){return std::toupper(c);});
        return filename;
    }
    else
    {
        std::string name = filename.substr(0, name_end);
        std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c){return std::toupper(c);});
        return name + filename.substr(name_end, filename.size());
    }
}

void filenames_to_upper(const std::filesystem::path & dir)
{
    if (std::filesystem::exists(dir))
    {
        for (const auto & entry : std::filesystem::directory_iterator(dir))
		{
            if (entry.is_regular_file()) 
            {
                std::filesystem::path old_path = entry.path();
                std::filesystem::path new_path = entry.path();
                std::string new_name = filename_to_upper(old_path.filename().string());
                new_path.replace_filename(new_name);
                std::filesystem::rename(old_path, new_path);
            }
        }
    } 
}

int main()
{
    std::filesystem::path path {"./direct"};

    filenames_to_upper(path);
}