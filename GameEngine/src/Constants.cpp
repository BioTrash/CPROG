#include "Constants.h"
#include <iostream>

namespace constants{
    const std::string gResPath = [] {
        
        std::filesystem::path exePath = std::filesystem::current_path();

        exePath /= "resources/";

        std::cout << "gResPath: " << exePath.string() << std::endl;

        return exePath.string();
    }();
}