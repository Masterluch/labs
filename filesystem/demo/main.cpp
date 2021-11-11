#include <iostream>
#include <boost/filesystem.hpp>
#include <Broker.hpp>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>

namespace fs = boost::filesystem;

//std::vector parse_information()

std::string get_dicertoria_name(const fs::path& path)
{
    std::string string_path = path.string();
    std::string dicertoria_name = "";
    std::reverse(string_path.begin(), string_path.end());
    for (auto simb : string_path)
    {
        if (simb != '/') { dicertoria_name += simb; }
        else { break; }
    }
    std::reverse(dicertoria_name.begin(), dicertoria_name.end());
    
    return dicertoria_name;
}

void scan_path(const std::regex& regex_setting, const fs::path& path, std::vector<Broker>& brokers, const std::string& dicertoria_name = "")
{
    for (const fs::directory_entry& x : fs::directory_iterator{path})
        {
            bool is_found = false;
            if (fs::is_directory(x.path()))
            {
                const fs::path new_path = x.path();
                std::string new_dicertoria_name = get_dicertoria_name(new_path);
                scan_path(regex_setting, new_path, brokers, new_dicertoria_name);
            }
            else if (fs::is_symlink(x.path()))
            {
                const fs::path new_path = fs::read_symlink(x.path());
                std::string new_dicertoria_name = get_dicertoria_name(new_path);
                scan_path(regex_setting, new_path, brokers, new_dicertoria_name);
            }
            else if (std::regex_match(x.path().filename().string(), regex_setting))
            {
                std::cout << dicertoria_name << " " << x.path().filename().string() << std::endl;
                for (auto& broker : brokers)
                {
                    if (broker._name == dicertoria_name)
                    {
                        is_found = true;
                        std::string string_account = x.path().stem().string();
                        broker.check_account(string_account);
                    }
                }
                if (!is_found)
                {
                    brokers.push_back(Broker(dicertoria_name));
                }
            }
        }
}

int main(int argc, char *argv[]) {

    if (argc < 2){ return 1; }
    const fs::path path_to_ftp(argv[1]);
    if (!fs::exists(path_to_ftp)){ return 1; }

    std::vector<Broker> brokers;
    std::regex regex_setting("balance_\\d{8}_\\d{8}\\.txt");
    scan_path(regex_setting, path_to_ftp, brokers);

    std::cout << std::endl;
    for (auto& broker : brokers)
    {
        broker.print_account_data();
    }
}