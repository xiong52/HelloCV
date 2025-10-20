#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

class FileHandler {
public:
    // 读取文件内容
    static std::string readFile(const std::string& filePath);
    
    // 写入文件内容
    static bool writeFile(const std::string& filePath, const std::string& content);
    
    // 检查文件是否存在
    static bool fileExists(const std::string& filePath);
    
    // 获取文件名（不含路径）
    static std::string getFilename(const std::string& filePath);
    
    // 获取目录路径
    static std::string getDirectory(const std::string& filePath);
    
    // 生成加密文件路径
    static std::string generateEncryptedPath(const std::string& originalPath, int key);
    
    // 生成解密文件路径
    static std::string generateDecryptedPath(const std::string& encryptedPath, int key);
    
    // 创建目录（如果不存在）
    static bool createDirectoryIfNotExists(const std::string& dirPath);
};

#endif
