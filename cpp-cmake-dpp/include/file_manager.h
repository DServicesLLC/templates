#pragma once

#include <fstream>
#include <filesystem>
#include <string>
#include <print>

class FileManager {
private:
    static constexpr const char* BASE_DIR = "data/";

public:
    static void save(const std::string& guild_id, const std::string& filename, const std::string& data) {
        std::filesystem::path guild_folder = std::format("{}/{}", BASE_DIR, guild_id);
        std::filesystem::path file_path = std::format("{}/{}.txt", guild_folder.string(), filename);
        
        std::filesystem::create_directories(guild_folder);
        
        std::ofstream file(file_path);
        file << data;
        
        std::println("[INFO] Saved file: {}", file_path.string());
    }

    static std::string load(const std::string& guild_id, const std::string& filename) {
        std::filesystem::path file_path = std::format("{}/{}/{}.txt", BASE_DIR, guild_id, filename);

        if (!std::filesystem::exists(file_path)) {
            std::println("[ERROR] File not found: {}", file_path.string());
            return "";
        }
        
        std::ifstream file(file_path);
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        std::println("[INFO] Loaded file: {}", file_path.string());
        return content;
    }

    static bool exists(const std::string& guild_id, const std::string& filename) {
        std::filesystem::path file_path = std::format("{}/{}/{}.txt", BASE_DIR, guild_id, filename);
        return std::filesystem::exists(file_path);
    }
};
