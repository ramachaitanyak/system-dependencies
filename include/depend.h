#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>


class Depend {

public:
    Depend(){}
    ~Depend() = default;

    void build_dependency(std::string item, std::vector<string> dependents);
    bool check_transitive_dependency(std::string item1, std::string item2);
    bool check_dependent_present(std::string dependent, std::vector<std::string> curr_dependents);
    void update_used_by(std::string item1, std::string used_by);

private:
    std::map<string, vector<string>> used_by_map;
    std::map<string, vector<string>> depends_on_map;
        
};
