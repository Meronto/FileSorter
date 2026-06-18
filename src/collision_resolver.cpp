#include "collision_resolver.h"
using namespace std;
namespace fs = std::filesystem;

namespace SorterLogics{ fs::path resolve_name_collision(const fs::path& desired_path, 
    unordered_set<std::string>& booked_paths
    ) {
        fs::path final_path = desired_path;
        string filename_stem = final_path.stem().string();
        string file_ext = final_path.extension().string();

        int counter = 1;
        while (fs::exists(final_path) || booked_paths.count(final_path.string()) > 0) {
            string new_filename = filename_stem + "_" + to_string(counter) + file_ext;
            final_path = desired_path.parent_path() / new_filename;
            counter++;
        }
        booked_paths.insert(final_path.string());
        return final_path;
  }
}
