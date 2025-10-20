#include "../include/FileHandler.h"
#include "../include/Crypto.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#define MKDIR(path) mkdir(path, 0755)
#endif

std::string FileHandler::readFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("无法打开文件: " + filePath);
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    return content;
}

bool FileHandler::writeFile(const std::string& filePath, const std::string& content) {
    // 确保目录存在
    std::string dir = getDirectory(filePath);
    if (!dir.empty() && !createDirectoryIfNotExists(dir)) {
        return false;
    }
    
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    file << content;
    file.close();
    return true;
}

bool FileHandler::fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}

std::string FileHandler::getFilename(const std::string& filePath) {
    size_t lastSlash = filePath.find_last_of("/\\");
    if (lastSlash != std::string::npos) {
        return filePath.substr(lastSlash + 1);
    }
    return filePath;
}

std::string FileHandler::getDirectory(const std::string& filePath) {
    size_t lastSlash = filePath.find_last_of("/\\");
    if (lastSlash != std::string::npos) {
        return filePath.substr(0, lastSlash + 1);
    }
    return "";
}

std::string FileHandler::generateEncryptedPath(const std::string& originalPath, int key) {
    std::string dir = getDirectory(originalPath);
    std::string filename = getFilename(originalPath);
    
    // 加密文件名
    std::string encryptedFilename = Crypto::encryptFilename(filename, key);
    
    // 在加密目录中保存
    return dir + "encrypted/" + encryptedFilename;
}

std::string FileHandler::generateDecryptedPath(const std::string& encryptedPath, int key) {
    std::string dir = getDirectory(encryptedPath);
    std::string filename = getFilename(encryptedPath);
    
    // 解密文件名
    std::string decryptedFilename = Crypto::decryptFilename(filename, key);
    
    // 在解密目录中保存
    return dir + "../decrypted/" + decryptedFilename;
}

bool FileHandler::createDirectoryIfNotExists(const std::string& dirPath) {
    if (dirPath.empty()) {
        return true;
    }
    
    struct stat info;
    if (stat(dirPath.c_str(), &info) != 0) {
        // 目录不存在，创建它
        return MKDIR(dirPath.c_str()) == 0;
    } else if (info.st_mode & S_IFDIR) {
        // 目录已存在
        return true;
    } else {
        // 存在但不是目录
        return false;
    }
}
