#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string>

#include "ticketcreate.h"
#include "progfunc.h"

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_ENTER 13

using namespace std;

Summary::Summary(char **first, char **second) {
    char **f = first; char **s = second;
    quitProgram = false;
    summaryTitle = "[Summary Input]";
    CustomerName = "<CustomerName>";
    AddressLineOne = "<Address Line 1>";
    AddressLineTwo = "<Address Line 2>";
    AddressLineThree = "<Address Line 3>";
    REF = ""; REF = REF + f[0] + "/" + s[3] + "/" + s[4];
    Control();
}

void Summary::Print(int x) {
    system("CLS"); int i = 0; int h;
    while(i < 13) {
        if (i == x) h = 1; else h = 0;
        switch(i) {
        case 0: Draw(1,24,7,71,13); break; // Drawing Frame
        case 1: gotoXY(58,9,CustomerName,h);           break;
        case 2: gotoXY(58,11,AddressLineOne,h);        break;
        case 3: gotoXY(58,12,AddressLineTwo,h);        break;
        case 4: gotoXY(58,13,AddressLineThree,h);      break;
        case 5: gotoXY(27,22,"Back",h);                 break;
        case 6: gotoXY(84,22,"Continue",h);             break;
        case 7: gotoXY(58,16,REF,h);                   break;
        // 46 + 47 = size of console
        case 8: gotoXY(44,9,"Name:",h);                break;
        case 9: gotoXY(44,11,"Address:",h);            break;
        case 10: gotoXY(44,16,"REF:",h);                break;
        case 11: gotoXY(51,5,summaryTitle,h);          break;
        case 12: gotoXY(0,0); break;
        default: break;
        } i++;
    }
}

void Summary::Control(){
    int c = 0; int s = 1; Print(s);
    while(quitProgram == false) {
        c = 0;
        switch(c=getch()) {
        case KEY_UP: s--; if (s==0) s=6; break;
        case KEY_LEFT: if(s!=5) s=5; else s=6; break;
        case KEY_RIGHT: if(s!=6) s=6; else s=5; break;
        case KEY_DOWN: s++; if (s==7) s=1; break;
        case KEY_ENTER: Execute(s); break;
        default: break;
        } Print(s); Sleep(10);
    }
}

void Summary::Execute(int s) {
    switch(s) {
    case 1: setName(); break;
    case 2: setAddressOne(); break;
    case 3: setAddressTwo(); break;
    case 4: setAddressThree(); break;
    case 6: backBool = 1; quitProgram = 1; break;
    case 7: quitProgram = 1; break;
    default:break;
    }
}
void Summary::setName() {
    gotoXY(37,22,"Input Name: ",0);
    cin.getline(limitChar, 25);
    CustomerName = limitChar;
    if (CustomerName == "") CustomerName = "<CustomerName>";
    Print(1); gotoXY(0,0);
}
void Summary::setAddressOne() {
    gotoXY(37,22,"Input First Line: ",0);
    cin.getline(limitChar, 25);
    AddressLineOne = limitChar;
    if (AddressLineOne == "") AddressLineOne = "<Address Line 1>";
    Print(2); gotoXY(0,0);
}
void Summary::setAddressTwo() {
    gotoXY(37,22,"Input Second Line: ",0);
    cin.getline(limitChar, 25);
    AddressLineTwo = limitChar;
    if (AddressLineTwo == "") AddressLineTwo = "<Address Line 2>";
    Print(3); gotoXY(0,0);
}
void Summary::setAddressThree() {
    gotoXY(37,22,"Input Third Line: ",0);
    cin.getline(limitChar, 25);
    AddressLineThree = limitChar;
    if (AddressLineThree == "") AddressLineThree = "<Address Line 3>";
    Print(4); gotoXY(0,0);
}

string Summary::getName() {
    string newname = ""; bool breakName = 0;
    int x = CustomerName.length();
    for (int i = 0; i < x; i++) {
        if(CustomerName[i] == ' ') break;newname += CustomerName[i];
    }
    return newname;
}
