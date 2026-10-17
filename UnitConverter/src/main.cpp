#include <iostream>
#include "unitlib.h"

using namespace std;

void showMenu() {
    cout << "========== 单位转换器 ==========\n";
    cout << "1. 摄氏度 (C) 转 华氏度 (F)\n";
    cout << "2. 华氏度 (F) 转 摄氏度 (C)\n";
    cout << "3. 米 (m) 转 英尺 (ft)\n";
    cout << "4. 英尺 (ft) 转 米 (m)\n";
    cout << "5. 磅 (lb) 转 千克 (kg)\n";
    cout << "6. 千克 (kg) 转 磅 (lb)\n";
    cout << "0. 退出程序\n";
    cout << "================================\n";
    cout << "请选择转换类型 (0-6): ";
}

int main() {
    int choice;
    double inputVal, result;

    while (true) {
        showMenu();
        cin >> choice;

        // 处理无效输入
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "输入无效，请输入数字！\n\n";
            continue;
        }

        if (choice == 0) {
            cout << "感谢使用，再见！\n";
            break;
        }

        cout << "请输入要转换的数值: ";
        cin >> inputVal;

        switch (choice) {
            case 1:
                result = celsiusToFahrenheit(inputVal);
                cout << inputVal << " 摄氏度 = " << result << " 华氏度\n\n";
                break;
            case 2:
                result = fahrenheitToCelsius(inputVal);
                cout << inputVal << " 华氏度 = " << result << " 摄氏度\n\n";
                break;
            case 3:
                result = metersToFeet(inputVal);
                cout << inputVal << " 米 = " << result << " 英尺\n\n";
                break;
            case 4:
                result = feetToMeters(inputVal);
                cout << inputVal << " 英尺 = " << result << " 米\n\n";
                break;
            case 5:
                result = poundsToKilograms(inputVal);
                cout << inputVal << " 磅 = " << result << " 千克\n\n";
                break;
            case 6:
                result = kilogramsToPounds(inputVal);
                cout << inputVal << " 千克 = " << result << " 磅\n\n";
                break;
            default:
                cout << "无效的选择，请重新输入！\n\n";
                break;
        }
    }
    return 0;
}