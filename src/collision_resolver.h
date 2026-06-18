#ifndef COLLISION_RESOLVER_H
#define COLLISION_RESOLVER_H
#include <string>
#include <unordered_set>
#include <filesystem>

namespace SorterLogics { 
    std::filesystem::path resolve_name_collision(const std::filesystem::path& desired_path, 
    std::unordered_set<std::string>& booked_paths
    );
}

#endif