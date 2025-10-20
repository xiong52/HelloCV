#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include <vector>

class Crypto {
public:
    // Caesar Cipher 加密
    static std::string caesarEncrypt(const std::string& text, int key);
    
    // Caesar Cipher 解密
    static std::string caesarDecrypt(const std::string& text, int key);
    
    // XOR 加密/解密
    static std::string xorEncryptDecrypt(const std::string& text, int key);
    
    // 文件名加密
    static std::string encryptFilename(const std::string& filename, int key);
    
    // 文件名解密
    static std::string decryptFilename(const std::string& filename, int key);
    
    // 选择算法加密
    static std::string encrypt(const std::string& text, int key, int algorithm);
    
    // 选择算法解密
    static std::string decrypt(const std::string& text, int key, int algorithm);
    
    // 生成安全随机数
    static int generateRandomKey();
};

#endif
