#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include <vector>

class Crypto {
public:
    // Caesar Cipher ����
    static std::string caesarEncrypt(const std::string& text, int key);
    
    // Caesar Cipher ����
    static std::string caesarDecrypt(const std::string& text, int key);
    
    // XOR ����/����
    static std::string xorEncryptDecrypt(const std::string& text, int key);
    
    // �ļ�������
    static std::string encryptFilename(const std::string& filename, int key);
    
    // �ļ�������
    static std::string decryptFilename(const std::string& filename, int key);
    
    // ѡ���㷨����
    static std::string encrypt(const std::string& text, int key, int algorithm);
    
    // ѡ���㷨����
    static std::string decrypt(const std::string& text, int key, int algorithm);
    
    // ���ɰ�ȫ�����
    static int generateRandomKey();
};

#endif
