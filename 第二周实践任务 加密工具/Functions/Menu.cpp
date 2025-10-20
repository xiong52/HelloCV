#include "../include/Menu.h"
#include "../include/Crypto.h"
#include "../include/FileHandler.h"
#include <iostream>

using namespace std;

void Menu::showMainMenu() {
    cout << "\n=== 文件加密解密工具 ===\n";
    cout << "1. 文本加密\n";
    cout << "2. 文本解密\n";
    cout << "3. 文件加密（文件名+内容加密）\n";
    cout << "4. 文件解密（文件名+内容解密）\n";
    cout << "0. 退出\n";
    cout << "请选择功能: ";
}

int Menu::showAlgorithmMenu() {
    cout << "\n选择加密算法:\n";
    cout << "1. Caesar Cipher\n";
    cout << "2. XOR 加密\n";
    cout << "请选择算法: ";
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    if (choice < 1 || choice > 2) {
        cout << "无效选择，使用默认算法 (Caesar Cipher)\n";
        return 1;
    }
    
    return choice;
}

string Menu::getInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int Menu::getIntInput(const string& prompt) {
    int input;
    cout << prompt;
    cin >> input;
    cin.ignore();
    return input;
}

bool Menu::confirmAction(const string& message) {
    string answer;
    cout << message << " (y/n): ";
    getline(cin, answer);
    return answer == "y" || answer == "Y";
}

void Menu::handleTextEncryption() {
    string text = getInput("请输入要加密的文本: ");
    int key = getIntInput("请输入密钥: ");
    int algorithm = showAlgorithmMenu();
    
    string encrypted = Crypto::encrypt(text, key, algorithm);
    cout << "加密结果: " << encrypted << endl;
}

void Menu::handleTextDecryption() {
    string text = getInput("请输入要解密的文本: ");
    int key = getIntInput("请输入密钥: ");
    int algorithm = showAlgorithmMenu();
    
    string decrypted = Crypto::decrypt(text, key, algorithm);
    cout << "解密结果: " << decrypted << endl;
}

void Menu::handleFileEncryption() {
    string inputFile = getInput("请输入要加密的文件路径: ");
    
    if (!FileHandler::fileExists(inputFile)) {
        cout << "文件不存在!" << endl;
        return;
    }
    
    int key = getIntInput("请输入密钥: ");
    int algorithm = showAlgorithmMenu();
    
    // 使用相同的密钥加密文件名和文件内容
    string outputFile = FileHandler::generateEncryptedPath(inputFile, key);
    
    cout << "加密文件将保存到: " << outputFile << endl;
    
    if (!confirmAction("确认开始加密？")) {
        cout << "操作已取消。" << endl;
        return;
    }
    
    try {
        string content = FileHandler::readFile(inputFile);
        string encrypted = Crypto::encrypt(content, key, algorithm);
        
        if (FileHandler::writeFile(outputFile, encrypted)) {
            cout << "? 加密成功！" << endl;
            cout << "原文件: " << inputFile << endl;
            cout << "加密文件: " << outputFile << endl;
            cout << "使用的密钥: " << key << " (请妥善保存)" << endl;
        } else {
            cout << "? 保存文件失败!" << endl;
        }
    } catch (const exception& e) {
        cout << "错误: " << e.what() << endl;
    }
}

void Menu::handleFileDecryption() {
    string inputFile = getInput("请输入要解密的文件路径: ");
    
    if (!FileHandler::fileExists(inputFile)) {
        cout << "文件不存在!" << endl;
        return;
    }
    
    int key = getIntInput("请输入密钥: ");
    int algorithm = showAlgorithmMenu();
    
    // 使用相同的密钥解密文件名和文件内容
    string outputFile = FileHandler::generateDecryptedPath(inputFile, key);
    
    cout << "解密文件将保存到: " << outputFile << endl;
    
    if (!confirmAction("确认开始解密？")) {
        cout << "操作已取消。" << endl;
        return;
    }
    
    try {
        string content = FileHandler::readFile(inputFile);
        string decrypted = Crypto::decrypt(content, key, algorithm);
        
        if (FileHandler::writeFile(outputFile, decrypted)) {
            cout << "? 解密成功！" << endl;
            cout << "加密文件: " << inputFile << endl;
            cout << "解密文件: " << outputFile << endl;
        } else {
            cout << "? 保存文件失败!" << endl;
        }
    } catch (const exception& e) {
        cout << "错误: " << e.what() << endl;
    }
}

void Menu::run() {
    int choice;
    
    do {
        showMainMenu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                handleTextEncryption();
                break;
            case 2:
                handleTextDecryption();
                break;
            case 3:
                handleFileEncryption();
                break;
            case 4:
                handleFileDecryption();
                break;
            case 0:
                cout << "感谢使用，再见!" << endl;
                break;
            default:
                cout << "无效选择，请重新输入!" << endl;
                break;
        }
    } while (choice != 0);
}
