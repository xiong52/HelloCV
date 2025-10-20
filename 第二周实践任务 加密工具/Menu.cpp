#include "../include/Menu.h"
#include "../include/Crypto.h"
#include "../include/FileHandler.h"
#include <iostream>

using namespace std;

void Menu::showMainMenu() {
    cout << "\n=== �ļ����ܽ��ܹ��� ===\n";
    cout << "1. �ı�����\n";
    cout << "2. �ı�����\n";
    cout << "3. �ļ����ܣ��ļ���+���ݼ��ܣ�\n";
    cout << "4. �ļ����ܣ��ļ���+���ݽ��ܣ�\n";
    cout << "0. �˳�\n";
    cout << "��ѡ����: ";
}

int Menu::showAlgorithmMenu() {
    cout << "\nѡ������㷨:\n";
    cout << "1. Caesar Cipher\n";
    cout << "2. XOR ����\n";
    cout << "��ѡ���㷨: ";
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    if (choice < 1 || choice > 2) {
        cout << "��Чѡ��ʹ��Ĭ���㷨 (Caesar Cipher)\n";
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
    string text = getInput("������Ҫ���ܵ��ı�: ");
    int key = getIntInput("��������Կ: ");
    int algorithm = showAlgorithmMenu();
    
    string encrypted = Crypto::encrypt(text, key, algorithm);
    cout << "���ܽ��: " << encrypted << endl;
}

void Menu::handleTextDecryption() {
    string text = getInput("������Ҫ���ܵ��ı�: ");
    int key = getIntInput("��������Կ: ");
    int algorithm = showAlgorithmMenu();
    
    string decrypted = Crypto::decrypt(text, key, algorithm);
    cout << "���ܽ��: " << decrypted << endl;
}

void Menu::handleFileEncryption() {
    string inputFile = getInput("������Ҫ���ܵ��ļ�·��: ");
    
    if (!FileHandler::fileExists(inputFile)) {
        cout << "�ļ�������!" << endl;
        return;
    }
    
    int key = getIntInput("��������Կ: ");
    int algorithm = showAlgorithmMenu();
    
    // ʹ����ͬ����Կ�����ļ������ļ�����
    string outputFile = FileHandler::generateEncryptedPath(inputFile, key);
    
    cout << "�����ļ������浽: " << outputFile << endl;
    
    if (!confirmAction("ȷ�Ͽ�ʼ���ܣ�")) {
        cout << "������ȡ����" << endl;
        return;
    }
    
    try {
        string content = FileHandler::readFile(inputFile);
        string encrypted = Crypto::encrypt(content, key, algorithm);
        
        if (FileHandler::writeFile(outputFile, encrypted)) {
            cout << "? ���ܳɹ���" << endl;
            cout << "ԭ�ļ�: " << inputFile << endl;
            cout << "�����ļ�: " << outputFile << endl;
            cout << "ʹ�õ���Կ: " << key << " (�����Ʊ���)" << endl;
        } else {
            cout << "? �����ļ�ʧ��!" << endl;
        }
    } catch (const exception& e) {
        cout << "����: " << e.what() << endl;
    }
}

void Menu::handleFileDecryption() {
    string inputFile = getInput("������Ҫ���ܵ��ļ�·��: ");
    
    if (!FileHandler::fileExists(inputFile)) {
        cout << "�ļ�������!" << endl;
        return;
    }
    
    int key = getIntInput("��������Կ: ");
    int algorithm = showAlgorithmMenu();
    
    // ʹ����ͬ����Կ�����ļ������ļ�����
    string outputFile = FileHandler::generateDecryptedPath(inputFile, key);
    
    cout << "�����ļ������浽: " << outputFile << endl;
    
    if (!confirmAction("ȷ�Ͽ�ʼ���ܣ�")) {
        cout << "������ȡ����" << endl;
        return;
    }
    
    try {
        string content = FileHandler::readFile(inputFile);
        string decrypted = Crypto::decrypt(content, key, algorithm);
        
        if (FileHandler::writeFile(outputFile, decrypted)) {
            cout << "? ���ܳɹ���" << endl;
            cout << "�����ļ�: " << inputFile << endl;
            cout << "�����ļ�: " << outputFile << endl;
        } else {
            cout << "? �����ļ�ʧ��!" << endl;
        }
    } catch (const exception& e) {
        cout << "����: " << e.what() << endl;
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
                cout << "��лʹ�ã��ټ�!" << endl;
                break;
            default:
                cout << "��Чѡ������������!" << endl;
                break;
        }
    } while (choice != 0);
}
