#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

class FileHandler {
public:
    // ��ȡ�ļ�����
    static std::string readFile(const std::string& filePath);
    
    // д���ļ�����
    static bool writeFile(const std::string& filePath, const std::string& content);
    
    // ����ļ��Ƿ����
    static bool fileExists(const std::string& filePath);
    
    // ��ȡ�ļ���������·����
    static std::string getFilename(const std::string& filePath);
    
    // ��ȡĿ¼·��
    static std::string getDirectory(const std::string& filePath);
    
    // ���ɼ����ļ�·��
    static std::string generateEncryptedPath(const std::string& originalPath, int key);
    
    // ���ɽ����ļ�·��
    static std::string generateDecryptedPath(const std::string& encryptedPath, int key);
    
    // ����Ŀ¼����������ڣ�
    static bool createDirectoryIfNotExists(const std::string& dirPath);
};

#endif
