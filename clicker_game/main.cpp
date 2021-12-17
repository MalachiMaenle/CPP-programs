#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
#include <fstream>
#include "../libraries/json.hpp"

using namespace std;
using json = nlohmann::json;

class shopItem {
    public:
        long long numItems;
        long long basePrice;
        long double itemValue;
        long long currentPrice() const;
        long double totalValue() const;
        void purchaseItem();
        void purchaseItem(int);
        shopItem(long double, long double);
};

string name = "";
bool space = false;
bool click = false;
bool key1 = false;
bool key2 = false;
bool key3 = false;
bool key4 = false;
bool key5 = false;
bool key6 = false;
long long numClicks = 0;
long double clickValue = 1;
long double money = 0;
long double moneySpent = 0;
shopItem cursor(0.1, 15);
shopItem grandma(1, 100);
shopItem farm(8, 1100);
shopItem mine(47, 12000);
shopItem factory(260, 130000);
shopItem bank(1400, 1400000);
string filePath = getenv ("appdata");
json j;

void readSave();
void writeSave();
void print();
void updateMoney();
long double getMoneyPerSecond();
void setCursorPos(int x, int y);
void firstPrint();
void showCursor(bool visible);


int main() {
    filePath += "/save.json";
    cout << fixed << showpoint << setprecision(2);
    readSave();
    showCursor(false);
    firstPrint();

    while(true) {
        if (GetAsyncKeyState('Q')) {
            return 1;
        }

        if (GetAsyncKeyState(' ')) {
            if(space == false) {
                money += clickValue;
                numClicks++;
            }
            space = true;
        } else {
            space = false;
        }

        if (GetAsyncKeyState(VK_LBUTTON)) {
            if(click == false) {
                money += clickValue;
                numClicks++;
            }
            click = true;
        } else {
            click = false;
        }

        if (GetAsyncKeyState('1')) {
            if(key1 == false) {
                cursor.purchaseItem();
            }
            key1 = true;
        } else {
            key1 = false;
        }

        if (GetAsyncKeyState('2')) {
            if(key2 == false) {
                grandma.purchaseItem();
            }
            key2 = true;
        } else {
            key2 = false;
        }

        if (GetAsyncKeyState('3')) {
            if(key3 == false) {
                farm.purchaseItem();
            }
            key3 = true;
        } else {
            key3 = false;
        }

        if (GetAsyncKeyState('4')) {
            if(key1 == false) {
                mine.purchaseItem();
            }
            key4 = true;
        } else {
            key4 = false;
        }

        if (GetAsyncKeyState('5')) {
            if(key5 == false) {
                factory.purchaseItem();
            }
            key5 = true;
        } else {
            key5 = false;
        }

        if (GetAsyncKeyState('6')) {
            if(key6 == false) {
                bank.purchaseItem();
            }
            key6 = true;
        } else {
            key6 = false;
        }

        Sleep(1);
        updateMoney();
        writeSave();
        print();
    }

    return 0;
}

void firstPrint() {
    system("cls");
    cout << "Name: " << name << endl;
    cout << "Money: " << money << endl;
    cout << "Money spent: " << moneySpent << endl;
    cout << "Clicks: " << numClicks << endl << endl;
    
    cout << "1 - cursor:  " << "0" << "                        Price: " << "0" << endl;
    cout << "2 - grandma: " << "0" << "                        Price: " << "0" << endl;
    cout << "3 - farm:    " << "0" << "                        Price: " << "0" << endl;
    cout << "4 - mine:    " << "0" << "                        Price: " << "0" << endl;
    cout << "5 - factory: " << "0" << "                        Price: " << "0" << endl;
    cout << "6 - bank:    " << "0" << "                        Price: " << "0" << endl;
    cout << setw(0);
}

void print() {
    setCursorPos(7, 1);
    cout << money << "          ";
    setCursorPos(13, 2);
    cout << moneySpent << "          ";
    setCursorPos(8, 3);
    cout << numClicks << "          ";

    setCursorPos(13, 5);
    cout << cursor.numItems;
    setCursorPos(45, 5);
    cout << cursor.currentPrice();

    setCursorPos(13, 6);
    cout << grandma.numItems;
    setCursorPos(45, 6);
    cout << grandma.currentPrice();

    setCursorPos(13, 7);
    cout << farm.numItems;
    setCursorPos(45, 7);
    cout << farm.currentPrice();

    setCursorPos(13, 8);
    cout << mine.numItems;
    setCursorPos(45, 8);
    cout << mine.currentPrice();

    setCursorPos(13, 9);
    cout << factory.numItems;
    setCursorPos(45, 9);
    cout << factory.currentPrice();

    setCursorPos(13, 10);
    cout << bank.numItems;
    setCursorPos(45, 10);
    cout << bank.currentPrice();

    cout << setw(0);
}

void setCursorPos(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void showCursor(bool visible) {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void updateMoney() {
    money = money + getMoneyPerSecond() / 50;
}

long double getMoneyPerSecond() {
    return cursor.totalValue() + grandma.totalValue() + farm.totalValue() + mine.totalValue() + factory.totalValue() + bank.totalValue();
}

void readSave() {
    std::ifstream ifs(filePath);

    if(!ifs) {
        ofstream saveFile(filePath);
        cout << "Enter New Shop name: ";
        getline(cin, name);
        saveFile << "{\n    \"name\": \"" << name << "\",\n    \"money\": 0,\n    \"moneySpent\": 0,\n    \"numClicks\": 0,\n    \"cursor\": 0,\n    \"grandma\": 0,\n    \"farm\": 0,\n    \"mine\": 0,\n    \"factory\": 0,\n    \"bank\": 0\n,\n    \"saveTime\": 0\n}";
        saveFile.close();
        std::ifstream ifs(filePath);
    }

    j = json::parse(ifs);

    name = j["name"];
    money = j["money"];
    moneySpent = j["moneySpent"];
    numClicks = j["numClicks"];
    cursor.numItems = j["cursor"];
    grandma.numItems = j["grandma"];
    farm.numItems = j["farm"];
    mine.numItems = j["mine"];
    factory.numItems = j["factory"];
    bank.numItems = j["bank"];

    ifs.close();
}

void writeSave() {
    std::ofstream ifs(filePath);

    j["name"] = name;
    j["money"] = money;
    j["moneySpent"] = moneySpent;
    j["numClicks"] = numClicks;
    j["cursor"] = cursor.numItems;
    j["grandma"] = grandma.numItems;
    j["farm"] = farm.numItems;
    j["mine"] = mine.numItems;
    j["factory"] = factory.numItems;
    j["bank"] = bank.numItems;

    ifs << setw(4) << j << endl;
    ifs.close();
}


long long shopItem::currentPrice() const {
    return ceil(basePrice * pow(1.15, numItems));
}

long double shopItem::totalValue() const {
    return numItems * itemValue;
}

void shopItem::purchaseItem() {
    if(money >= currentPrice()) {
        money -= currentPrice();
        moneySpent += currentPrice();
        numItems++;
    }
}
/*
void shopItem::purchaseItem(int num) {
    numItems = numItems + num;
}
*/
shopItem::shopItem(long double value, long double cost) {
    numItems = 0;
    itemValue = value;
    basePrice = cost;
}