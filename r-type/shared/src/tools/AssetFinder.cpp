#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <unistd.h>

/*!
* @brief Get the executable path.
*
* This function retrieves the path of the currently running executable.
*
* @return std::string The path of the executable.
* @throws std::runtime_error If the executable path cannot be determined.
*/
std::string getExecutablePath() {
    char buffer[1024];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len == -1) throw std::runtime_error("Failed to get executable path.");
    buffer[len] = '\0';
    return std::string(buffer);
}

/*!
* @brief Find the root path containing a specific marker.
*
* This function searches for a directory containing a specific marker file.
*
* @param startPath The path to start the search from.
* @param marker The marker file or directory to search for.
* @return std::filesystem::path The root path containing the marker.
* @throws std::runtime_error If the root directory with the marker is not found.
*/
std::filesystem::path findRootPath(const std::filesystem::path& startPath, const std::string& marker) {
    std::filesystem::path currentPath = startPath;

    while (currentPath != currentPath.root_path()) {
        if (std::filesystem::exists(currentPath / marker)) {
            return currentPath;
        }
        currentPath = currentPath.parent_path();
    }

    throw std::runtime_error("Root directory with marker not found.");
}

/*!
* @brief Find the assets directory.
*
* This function locates the assets directory.
*
* @return std::string The path to the assets directory.
*/
std::string assetFinder() {
    try {
        std::string executablePath = getExecutablePath();
        std::filesystem::path execPath(executablePath);
        std::filesystem::path projectRoot = findRootPath(execPath.parent_path(), ".git");
        std::filesystem::path assetsRoot = projectRoot / "r-type" / "assets";

        // std::cout << "Executable Path: " << execPath << std::endl;
        // std::cout << "Project Root Path: " << projectRoot << std::endl;
        // std::cout << "Assets Root Path: " << assetsRoot << std::endl;

        if (!std::filesystem::exists(assetsRoot)) {
            std::cerr << "Folder assets not found, please make sure the assets are in the correct folder." << std::endl;
            return {};
        }

        // std::cout << "Assets found at: " << assetsRoot << std::endl;
        return assetsRoot;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return {};
    }

}