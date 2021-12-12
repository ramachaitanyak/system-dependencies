#include "install_remove.h"

bool
InstallRemove::check_redundant_install(std::string install_sw) {
    // Make sure the software being installed is not alread installed

    for (int i=0; i<installed_sw.size(); i++) {
        if (sw.compare(installed_sw[i]) == 0) {
            // This is already installed, print message and return
            std::cout<<sw<<" is already installed."<<std::endl;
            return true;
        }
    }

    return false;
}

void
InstallRemove::install_sw(std::string sw, std::vector<std::string> dependency_list) {

    if (check_redundant_install(sw)) {
        return;
    }

    // If not already installed continue with installation
    // Install all pre-requisites if not already installed
    for (int j=0; j<dependency_list.size(); j++) {

        //CXX! NB: Here the problem does not describe about the dependencies that not explicit
        for (int i=0; i<dependency_list.size(); i++) {
            if (check_redundant_install(dependency_list[i])) {
                continue;
            } else {
                // Install this dependency
                std::cout<<"Installing "<<dependency_list[i]<<std::endl;
                // Add to install list
                installed_sw.push_back(dependency_list[i]);
            }
        }
    }

    return;
}

void
InstallRemove::remove_all_occurences(std::string sw, std::map<std::string, std::vector<std::string>>& used_by_map) {
    for (auto it = used_by_map.begin(); it != used_by_map.end(); it++) {
        auto it1 = it->second.find(sw);
        it->second.erase(it1);
    }
}

void
InstallRemove::remove_sw(std::string sw, std::map<std::string, std::vector<std::string>> used_by_map) {
    // Check if installed first
    if (check_redundant_install(sw)) {
        // if there is no sw using this remove it and remove all occurences from used by
        auto it = used_by_map.find(sw);
        if (it != used_by_map.end()) {
            // Can not remove as it is used by another application
            std::cout<<sw<<" is still needed."<<std::endl;
        } else {
            // Remove all occuerences from map
            remove_all_occurences(std::string sw)
            // Remove from the installed sw
            auto it = installed_sw.find(sw);
            installed_sw.erase(it);
        }

    } else {
        // Print not installed
        std::cout<<sw<<" is not installed."<<std::endl;
    }
}

void
InstallRemove::list() {
    for (int i=0; i<installed_sw.size(); i++) {
        std::cout<<installed_sw[i]<<std::endl;
    }
}
