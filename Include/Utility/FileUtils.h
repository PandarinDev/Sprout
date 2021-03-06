#pragma once

#include <string>

namespace sprout {

    class FileUtils final {

    public:

		static std::string getParent(const std::string& filePath);
        static std::string readFileContents(const std::string& filePath);

    private:

        FileUtils() = default;

    };

}