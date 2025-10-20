#include "../include/Crypto.h"
#include <cctype>
#include <random>
#include <algorithm>

std::string Crypto::caesarEncrypt(const std::string& text, int key) {
    std::string result = "";

    for (char c : text) {
        if (std::isalpha(c)) {
            char base = std::islower(c) ? 'a' : 'A';
            c = (c - base + key) % 26 + base;
        }
        result += c;
    }

    return result;
}

std::string Crypto::caesarDecrypt(const std::string& text, int key) {
    return caesarEncrypt(text, 26 - (key % 26));
}

std::string Crypto::xorEncryptDecrypt(const std::string& text, int key) {
    std::string result = "";

    for (char c : text) {
        result += c ^ key;
    }

    return result;
}

std::string Crypto::encryptFilename(const std::string& filename, int key) {
    // �����ļ�������չ��
    size_t dotPos = filename.find_last_of('.');
    std::string name, ext;

    if (dotPos != std::string::npos) {
        name = filename.substr(0, dotPos);
        ext = filename.substr(dotPos);
    } else {
        name = filename;
        ext = "";
    }

    // ���ļ������ֽ��м���
    std::string encryptedName = "";
    for (char c : name) {
        if (std::isalnum(c)) {
            if (std::isalpha(c)) {
                char base = std::islower(c) ? 'a' : 'A';
                c = (c - base + key) % 26 + base;
            } else if (std::isdigit(c)) {
                c = '0' + (c - '0' + key) % 10;
            }
        }
        encryptedName += c;
    }

    // ��Ӽ��ܱ�ʶ����Կ��ϣ���򵥵�У����ƣ�
    int hash = (key * 31) % 100;
    return encryptedName + "_enc_" + std::to_string(hash) + ext;
}

std::string Crypto::decryptFilename(const std::string& filename, int key) {
    // ���Ҽ��ܱ�ʶ
    size_t encPos = filename.find("_enc_");
    if (encPos == std::string::npos) {
        return filename; // û�м��ܱ�ʶ��ֱ�ӷ���ԭ�ļ���
    }

    // ��֤��Կ��ϣ
    size_t hashPos = encPos + 5;
    size_t extPos = filename.find_last_of('.');
    std::string hashStr;

    if (extPos != std::string::npos && extPos > hashPos) {
        hashStr = filename.substr(hashPos, extPos - hashPos);
    } else {
        hashStr = filename.substr(hashPos);
    }

    int expectedHash = (key * 31) % 100;
    if (std::to_string(expectedHash) != hashStr) {
        return filename; // ��Կ��ƥ�䣬����ԭ�ļ���
    }

    // ��ȡԭʼ�ļ�������
    std::string encryptedName = filename.substr(0, encPos);
    std::string ext = (extPos != std::string::npos) ? filename.substr(extPos) : "";

    // �����ļ���
    std::string decryptedName = "";
    for (char c : encryptedName) {
        if (std::isalnum(c)) {
            if (std::isalpha(c)) {
                char base = std::islower(c) ? 'a' : 'A';
                c = (c - base + (26 - (key % 26))) % 26 + base;
            } else if (std::isdigit(c)) {
                c = '0' + (c - '0' + (10 - (key % 10))) % 10;
            }
        }
        decryptedName += c;
    }

    return decryptedName + ext;
}

std::string Crypto::encrypt(const std::string& text, int key, int algorithm) {
    switch (algorithm) {
        case 1: // Caesar Cipher
            return caesarEncrypt(text, key);
        case 2: // XOR
            return xorEncryptDecrypt(text, key);
        default:
            return text;
    }
}

std::string Crypto::decrypt(const std::string& text, int key, int algorithm) {
    switch (algorithm) {
        case 1: // Caesar Cipher
            return caesarDecrypt(text, key);
        case 2: // XOR
            return xorEncryptDecrypt(text, key);
        default:
            return text;
    }
}

int Crypto::generateRandomKey() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 25); // 1-25�������Կ
    return dis(gen);
}
