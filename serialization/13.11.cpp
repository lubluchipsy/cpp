#include <iostream>
#include <fstream>
#include <unordered_map>
#include <filesystem>

namespace fs = std::filesystem;

void createSymlink(const fs::path& target, const fs::path& symlink) 
{
    fs::create_symlink(target, symlink);
}

void remove_duplicates(const fs::path & dir) 
{
    std::unordered_map <std::string, std::filesystem::path> files;
    for (const auto & entry : fs::recursive_directory_iterator(dir)) 
    {
        if (fs::is_regular_file(entry)) 
        {
            std::ifstream filein(entry.path(), std::ios::binary);
            if (filein.is_open()) 
            {
                std::string content((std::istreambuf_iterator<char>(filein)), std::istreambuf_iterator<char>());
                filein.close();

                auto same_file = files.find(content);
                if (same_file != files.end()) 
                {
                    fs::path duplicate_file = entry.path();
                    fs::remove(entry.path());
                    create_symlink(fs::absolute(same_file->second), duplicate_file);
                } 
                else 
                {
                    files[content] = entry.path();
                }
            }
            else 
            {
                std::cout << "Cannot open file: " << entry.path() << std::endl;
            }
        }
    }
}


int main() 
{
    std::filesystem::path dir = "./direct";
    remove_duplicates(dir);
}   
