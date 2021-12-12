#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

class InstallRemove {

public:
    InstallRemove(){}
    ~InstallRemove() = default;

    void install_sw(std::string sw, std::vector<std::string> dependency_list);
    bool check_redundant_install(std::string install_sw);
    void remove_sw(std::string sw, std::map<std::string, std::vector<std::string>>& used_by_map);
    void remove_all_occurences(std::string sw, std::map<std::string, std::vector<std::string>>& used_by_map);
    void list(); // List all currently installed sw


private:
    std::vector<string> installed_sw;
}:

