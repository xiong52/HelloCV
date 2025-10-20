#ifndef MENU_H
#define MENU_H

#include <string>

class Menu {
public:
    static void showMainMenu();
    static int showAlgorithmMenu();
    static void handleTextEncryption();
    static void handleTextDecryption();
    static void handleFileEncryption();
    static void handleFileDecryption();
    static void run();
    
private:
    static std::string getInput(const std::string& prompt);
    static int getIntInput(const std::string& prompt);
    static bool confirmAction(const std::string& message);
};

#endif
