#include <iostream>

#include "ticketcreate.h"
#include "ticketcreate.cpp"
#include "report.cpp"
#include "summary.cpp"
#include "progfunc.h"
#include "progfunc.cpp"

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_ENTER 13

using namespace std;

class MainMenu {
    public:
        // Main menu functionality
        MainMenu(); void Print(int s); void Execute(int s); void SetMenu(int s);

        // Selections
        void TicketProcess();
        void DailyReport() {Report Load; SetMenu(2); Sleep(200);}
        void Help();

        // Functions which perform calculations
        string ConvertTime(int hours, string minutes);

        // Back Button
        void setGoBack(bool x) {goBack = x;};
    private:
        bool quitProgram, goBack;
};
int main() {ShowConsoleCursor(0); MainMenu Load; return 0;}
MainMenu::MainMenu() {
    ShowConsoleCursor(0); int s = 1, c = 0; quitProgram = 0; SetMenu(s);
    while(quitProgram == 0) {
        c = 0;
        switch(c=getch()) {
        case KEY_UP: if(s==4) s = 1; else if(s==5) s = 3; break;
        case KEY_LEFT: --s; if(s == 0) s = 1; else if(s == 3) s = 4; break;
        case KEY_RIGHT: ++s; if(s == 4) s = 3; else if(s == 6) s = 5; break;
        case KEY_DOWN: if(s==1) s = 4; else if(s==3) s = 5; break;
        case KEY_ENTER: Execute(s); break;
        default: break;
        } Print(s); Sleep(10);
    }
}
void MainMenu::SetMenu(int s) {system("CLS"); gotoXY(45,11,"[Long Distance Flight Travel]",0); Draw(2,20,8,79,15); Print(s);}
void MainMenu::Print(int s) {
    int i = 0, h, l = 15;
    while(i < 7) {
        if (i == s) h = 1; else h = 0;
        switch(i) {
        case 1: gotoXY(38,l,"Create",h); break;
        case 2: gotoXY(53,l,"Daily Report",h); break;
        case 3: gotoXY(73,l,"Database",h); break;
        case 4: gotoXY(46,l+3,"Help",h); break;
        case 5: gotoXY(68,l+3,"Quit",h); break;
        case 6: gotoXY(0,0); break;
        default: break;
        } i++;
    }
}
void MainMenu::Execute(int s) {
    switch(s) {
    case 1: TicketProcess(); break;
    case 2: DailyReport(); break;
    case 3: break;
    case 4: Help(); break;
    case 5: quitProgram = 1; break;
    default: break;
    }
}

void MainMenu::TicketProcess() {
    // Loading TicketOne then TicketTwo
    int fCheck[] = {2019,1,1,0,0}; TicketCreate First("[Ticket - One]",fCheck);
    int * sCheck = First.TicketTime(); TicketCreate Second("[Ticket - Two]",sCheck);

    // Creating arrays from data arrays in ticket objects
    int * fTime = First.TicketTime(), * sTime = Second.TicketTime();
    char **fData = First.TicketData(), **sData = Second.TicketData(),buffer[35];

    // Loading input for summary
    Summary Load(fData, sData);


    /* Excluding conversion for this commit, will get back to it and add it to the ticketcreate.cpp when I clear some junk */
    /*
    // Converting time to 12-hour clock and calculating total cost
    string fMin = itoa(fTime[9],buffer,10), sMin = itoa(sTime[4],buffer,10);
    if(fTime[9]<10) fMin = ("0" + fMin); if(sTime[4] < 10) sMin = ("0" + sMin);
    string timeOne = ConvertTime(fTime[8],fMin), timeTwo = ConvertTime(sTime[3],sMin);
        */
    float totalCost = First.getCost()+Second.getCost();

    // Loading summary view of ticket
    TicketCreate View(Load.getName(), totalCost, fData, sData, fTime, sTime);
    SetMenu(1); Sleep(500);
}

void MainMenu::Help() {
    system("CLS"); bool errorBreak = 0; int c = 0, s = 0, h; Draw(2,20,8,79,15);
    while(errorBreak == 0) {
        c = 0;
        gotoXY(39,11,"[Use arrow keys and enter key for input]",0); gotoXY(52,14,"(Confirm?)",0);
        if (s == 0) h = 1; else h = 0; gotoXY(40,18,"No",h);
        if (s == 1) h = 1; else h = 0; gotoXY(70,18,"Yes",h);
        switch(c=getch()) {
            case KEY_LEFT:  if (s==1) s=0; else s=1; break;
            case KEY_RIGHT: if (s==1) s=0; else s=1; break;
            case KEY_ENTER: if (s==1) {errorBreak = 1;} if (s==0) {errorBreak = 0;} break;
            default: break;
        }
    } SetMenu(4); Sleep(500);
}

/*
string MainMenu::ConvertTime(int hours, string minutes) {
    char buffer[35]; string time = "";
    if (hours < 13) time = itoa(hours,buffer,10); else time = itoa((hours-12),buffer,10);
    if (hours == 0) time = "12";
    if (hours<12) time = time + ":" + minutes + "AM";
    if (hours>11) time = time + ":" + minutes + "PM";
    return time;
}
*/
