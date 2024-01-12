#include "Constants.h"

namespace constants{
    const std::string gResPath = [] {
        
        std::filesystem::path exePath = std::filesystem::current_path();

        exePath /= "resources/";

        return exePath.string();
    }();
}