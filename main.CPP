#include <iostream>

#include "ticketcreate.h"
#include "ticketcreate.cpp"
#include "report.cpp"
#include "summary.cpp"
#include "progfunc.h"
#include "progfunc.cpp"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

using namespace std;

class MainMenu {
    public:
        // Main menu functionality
        MainMenu(); void Print(int s); void Execute(int s); void SetMenu(int s);

        // Selections
        void TicketProcess();
        void DailyReport() {Report Load; Print(2); Sleep(500);}
        void Help();

        // Functions which perform calculations
        string CalJourney(int first[], int second[]);
        string ConvertTime(int hours, string minutes);
    private:
        bool quitProgram;
};
int main() {MainMenu Load; return 0;}
MainMenu::MainMenu() {
    ShowConsoleCursor(0); int s = 1, c = 0; quitProgram = 0; SetMenu(s);
    while(quitProgram == 0) {
        c = 0;
        switch(c=getch()) {
        case KEY_UP: if (s == 1) s = 5; else s -= 1; break;
        case KEY_DOWN: if (s == 5) s = 1; else s += 1; break;
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

    // Converting time to 12-hour clock and calculating total cost
    string fMin = itoa(fTime[9],buffer,10), sMin = itoa(sTime[4],buffer,10);
    if(fTime[9]<10) fMin = ("0" + fMin); if(sTime[4] < 10) sMin = ("0" + sMin);
    string timeOne = ConvertTime(fTime[8],fMin), timeTwo = ConvertTime(sTime[3],sMin);
    float totalCost = First.getCost()+Second.getCost();

    // Loading summary view of ticket
    TicketCreate View(Load.getName(), totalCost, fData, sData, CalJourney(fTime,sTime), timeOne, timeTwo);
    SetMenu(1); Sleep(500);
}

void MainMenu::Help() {
        system("CLS"); int c = 0; int s = 0; int h; bool errorBreak = 0;
        //string FillOne(71,'\xDB'); string FillTwo(67,' ');
        //for (int i = 0; i < 17; i++) gotoXY(22,6+i,FillOne,0);
       // for (int i = 0; i < 15; i++) gotoXY(24,7+i,FillTwo,0);
       Draw(2,24,6,71,17);
            while(errorBreak == 0) {
                c = 0;
                gotoXY(39,9,"[Use arrow keys and enter key for input]",0);
                gotoXY(52,13,"(Confirm?)",0);
                for(int i = 0; i < 2; i++){
                        if (i == s) h = 1; else h = 0;
                        switch(i){
                        case 0: gotoXY(40,16,"No",h);
                        case 1: gotoXY(70,16,"Yes",h);
                        default: break;
                    }
                }
                switch(c=getch()) {
                    case KEY_LEFT:  if (s==1) s=0; else s=1; break;
                    case KEY_RIGHT: if (s==1) s=0; else s=1; break;
                    case KEY_ENTER: if (s==1) {errorBreak = 1;} if (s==0) {errorBreak = 0;} break;
                    default: break;
                }
        } SetMenu(4); Sleep(500);
}


string MainMenu::ConvertTime(int hours, string minutes) {
        char buffer[35]; string time = "";
        if (hours < 13) time = itoa(hours,buffer,10); else time = itoa((hours-12),buffer,10);
        if (hours == 0) time = "12";
        if (hours<12) time = time + ":" + minutes + "AM";
        if (hours>11) time = time + ":" + minutes + "PM";
        return time;
}
string MainMenu::CalJourney(int first[], int second[]) {
    // Calculates difference between first ticket departure and second ticket arrival
    // Then it converts difference to hours and minutes
    // If over 365 days, an error string is returned.

    string jTime, hour, minute; char buffer[35];
    int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31}, h, m, i, yearDif, monthDif, daytotal = 0;

    yearDif = second[0] - first[5]; daytotal -= first[7]; daytotal += second[2];
    if (yearDif == 0) monthDif = second[1] - first[6];
    else monthDif = (12 - first[6]) + second[1] + (12*(yearDif-1));

    if (yearDif>1) {
        for (i=(first[6]-1);i<12;i++) daytotal+=months[i];
        for (i=0;i<12;i++) daytotal += months[i]*(yearDif-1);
        for (i=0;i<(second[1]-1);i++) daytotal+=months[i];
    }   //PRINT ERROR HERE

    if (yearDif<2) {
        for (i=(first[6]-1);i<12;i++) daytotal+=months[i];
        for (i=0;i<(second[1]-1);i++) daytotal+=months[i];
    } if (yearDif==0) daytotal -= 365;

    if (first[7]==second[2]&&first[6]==second[1]&&first[5]==second[0]) {
        if (first[9] == second[4]) {m = 0; h = (first[8]-second[3])*-1;}
        if (second[4] > first[9]) {m = second[4] - first[9]; h = second[3]-first[8];}
        if (second[4] < first[9]) {m = (60 - first[9])+second[4]; h = (second[3]-first[8])-1;}
    }

    if (!(first[7]==second[2]&&first[6]==second[1]&&first[5]==second[0])) {
        if (first[9] == second[4]) {m = 0; h = (24-first[8])+second[3];}
        if (second[4] > first[9]) {m = second[4]-first[9]; h = (24-first[8])+second[3];}
        if (second[4] < first[9]) {m = (60-first[9])+second[4]; h = ((24-first[8])+second[3])-1;}
    } if(daytotal > 1) h += (daytotal - 1) * 24;

    if (h==0) hour = "0"; else hour = itoa(h,buffer,10); if (m==0) minute = "0"; else minute = itoa(m,buffer,10);
    jTime = "TOTAL TIME: "+hour+"Hours "+minute+"Minutes"; return jTime;
}
