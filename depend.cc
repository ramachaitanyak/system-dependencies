#include <iostream>
#include <map>
#include <string>
#include "depend.h"

using namespace std;




// populate maps by parsing
//

// COMMAND -> NAMES, .... (Add only for DEPEND)
//
//

void
Depend::update_used_by(std::string item1, std::string used_by) {
    auto it = used_by_map.find(item1);
    if (it != used_by_map.end()) {
        it->second.push_back(used_by);
    } else {
        std::vector<std::string> used_by_vec;
        used_by_vec.push_back(used_by);
        used_by_map.insert(std::make_pair(item1, used_by_vec));
    }
}


bool
Depend::check_dependent_present(std::string dependent, std::vector<std::string> curr_dependents) {
    for (int i=0; i<curr_dependents.size(); i++) {
        if (dependent.compare(curr_dependents[i]) == 0) {
            return true;
        }
    }

    return false;
}

bool
Depend::check_transitive_dependency(std::string item1, std::string item2) {
    // Check if item2 is already used by item1
    // Check if item2 is already present in used_by_map;
    auto it = used_by_map.find(item2);
    if (it != used_by_map.end()) {
        // It is currently in use
        // Make sure it is not already used by item1
        std::vector<string> curr_users = it->second;
        for (int i =0; i<curr_users.size(); i++) {
            if (item1.compare(curr_users[i])== 0) {
                return false;
            }
        }
    }

    return true;
}

void
Depend::build_dependency(std::string item, std::vector<string> dependents) {
    // Find if the item is already present in the depends_on_map
    auto it = depends_on_map.find(item);
    if (it != depends_on_map.end()) {
        // Found the item, check dependency if dependent not present
        for (int i=0; i<dependents.size(); i++) {
            // Proceed evaluating only if the dependents are not already added
            if (!check_dependent_present(dependents[i], it->second)) {
                // Before adding to the depends_on_map make sure that transitive dependency
                // in used_by_map is addressed

                // Check there is no transitive dependency between dependents[i] and it->first
                if (check_transitive_dependency(it->first, dependents[i])) {
                    // Add to dependency map
                    //
                    it->second.push_back(dependents[i]);
                    update_used_by(dependents[i], it->first);
                }

            }

        } // End
        
    }  else {  // End not found in map

        // Add to the depends_on_map with the same checks
        std::vector<std::string> append_vector;
        for (int i=0; i<dependents.size(); i++) {
            // Proceed evaluating only if the dependents are not already added
            if (!check_dependent_present(dependents[i], it->second)) {
                // Before adding to the depends_on_map make sure that transitive dependency
                // in used_by_map is addressed

                // Check there is no transitive dependency between dependents[i] and it->first
                if (check_transitive_dependency(it->first, dependents[i])) {
                    // Add to dependency map
                    //
                    append_vector.push_back(dependents[i]);
                    update_used_by(dependents[i], item);
                }

            }

        } // End
        depends_on_map.insert(std::make_pair(item, append_vector));

    }
}


