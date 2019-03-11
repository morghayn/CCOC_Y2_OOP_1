#include <iostream>
#include <conio.h>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include "ticketcreate.h"
#include "progfunc.h"

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_ENTER 13

using namespace std;

TicketCreate::TicketCreate(string title, int time[]) {
    tikName = title,
    flCost = "Cost:EUR0000.00",
    flDur = "EXPECTED FLIGHT TIME: 0Hours 0Minutes",
    depCode = ariCode = "???",
    depDate = ariDate = "00.00.0000",
    depTime = ariTime = "00:00";

    for (int i = 0; i < 5; i++)
        depChk[i] = time[i];
    for (int i = 0; i < 7; i++)
        fCheck[i] = 0;

    fCheck[7] = 1, quitProgram = 0, backBool = 0;
    Print(); Print(1); ticketControl = 0; Control();
}

void TicketCreate::SummaryIntro(string name, string depAirport, string arrAirport) {
    bool summaryBreak = 0;
    while(summaryBreak == 0){
        bool summaryBreakConfirm = 0;
        system("CLS"); Draw(2,24,6,71,17);
        gotoXY(48,9,"[Journey Summary]",0);
        gotoXY(28,13,("Dear " + name + ","),0);
        gotoXY(28,15,"Please find enclosed your boarding passes for your flight",0);
        gotoXY(28,16,("from " + depAirport + " to " + arrAirport + "."),0);
        gotoXY(28,18,"Press any key to view your journey summary....",0);
        cin.get(); system("CLS"); int c = 0; int s = 0; int h;
        Draw(2,24,6,71,17);
            while(summaryBreakConfirm == 0) {
                c = 0;
                gotoXY(39,11,"[Are you sure you want to continue?]",0);
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
                    case KEY_ENTER: if (s==1) {summaryBreak = 1; summaryBreakConfirm = 1;} if (s==0) {summaryBreak = 0; summaryBreakConfirm = 1;} break;
                    default: break;
                }
        }
    }
}
TicketCreate::TicketCreate(string name, float TotalCost, char **first, char **second, int fTime[], int sTime[]) {
    float rev = (TotalCost / 10);
    stringstream ss; ss << std::fixed << std::setprecision(2) << (rev); string revenue = ss.str();
    float temprevten = (rev*10);
    stringstream sf; sf << std::fixed << std::setprecision(2) << (temprevten); string moneytot = sf.str();

    for (int i = 0; i < 7; i++)
        fCheck[i] = true;
    fCheck[7] = 0;

    char **f = first, **s = second;
    SummaryIntro(name,f[0],s[3]);

    CheckDateAndTime(fTime,sTime,1);
    tikName = "[Summary Ticket]", flCost = "COST:EUR" + moneytot;
    depCode = f[0], depDate = f[1], depTime = f[2],
    ariCode = s[3], ariDate = s[4], ariTime = s[5];
    quitProgram = 0, backBool = 0;

    Print(); Print(9); ticketControl = 1; Control();

    // -> Writing Data to CSV.
    PrintFileSpalsh();
    SYSTEMTIME localTime; GetLocalTime(&localTime);
    int myYear = localTime.wYear, myMonth = localTime.wMonth, myDay = localTime.wDay;
	ofstream myFile; myFile.open("FlightLog.csv", ios_base::app);
    myFile << revenue << "," << myYear << "," << myMonth << "," <<  myDay << "," <<  name << "," <<  moneytot;
    myFile << "," <<  f[0] << "," <<  f[1] << "," <<  depTime << "," <<  s[3] << "," <<  s[4] << "," <<  ariTime << "," <<  flDur << "," <<  endl;
	myFile.close();
}
void TicketCreate::PrintFileSpalsh() {
    bool quit = 0; system("CLS");
    Draw(2,24,6,71,17);
    gotoXY(48,9,"[Ticket Print]",0);
    gotoXY(28,13,"Please note,",0);
    gotoXY(28,15,"We are going to print your ticket to file,",0);
    gotoXY(28,16,"This will store your ticket safely on file.",0);
    gotoXY(28,18,"Press any key to continue....",0);
    cin.get(); Sleep(1000);
}

void TicketCreate::Control(){
    int s = 1; int c = 0;
    while(quitProgram == 0 && ticketControl == 0) {
        c = 0;
        switch(c=getch()) {
        case KEY_UP: if (s==1) s=9; else if (s==2) s=8; else if (s==3) s=6; else if (s==9) s=7; else s-=3; break;
        case KEY_LEFT: if (s==1) s=9; else s-=1; break;
        case KEY_RIGHT: if (s==9) s=1; else s+=1; break;
        case KEY_DOWN: if (s==6) s=3; else if (s==7) s=9; else if (s==8) s=2; else if (s==9) s=1; else s+=3; break;
        case KEY_ENTER: ExecuteSetter(s); break;
        default: break;
        } Print(s); Sleep(20);
    } s = 9;
    while(quitProgram == 0 && ticketControl == 1) {
        c = 0;
        switch(c=getch()) {
        case KEY_LEFT: s = (s == 9) ? 8 : 9; break;
        case KEY_RIGHT: s = (s == 9) ? 8 : 9; break;
        case KEY_ENTER: ExecuteSetter(s); break;
        default: break;
        } Print(s); Sleep(20);
    }
}
void TicketCreate::Print() {
    system("CLS"); Draw(1,24,7,71,13);
    gotoXY(51,5,tikName,0);
    gotoXY(27,9,"Boarding Pass",0);
    gotoXY(51,9,"CLASS: ECONOMY",0);
    gotoXY(27,11,"FROM",0);
    gotoXY(51,11,"DATE",0);
    gotoXY(76,11,"TIME",0);
    gotoXY(27,14,"To",0);
}
void TicketCreate::Print(int x) {
    int i = 0; int h; string wipeEditor(120,' ');
    while(i < 12) {
        if (i == x) h = 1; else h = 0;
        switch(i) {
            case 0: gotoXY(0,22,wipeEditor,0); break;
            case 1: gotoXY(76,9,flCost,h); break;
            case 2: gotoXY(27,12,depCode,h); break;
            case 3: gotoXY(51,12,depDate,h); break;
            case 4: gotoXY(76,12,depTime,h); break;
            case 5: gotoXY(27,15,ariCode,h); break;
            case 6: gotoXY(51,15,ariDate,h); break;
            case 7: gotoXY(76,15,ariTime,h); break;
            case 8: gotoXY(27,22,"Back",h); break;
            case 9: gotoXY(84,22,"Continue",h); break;
            case 10: gotoXY(27,17,flDur, h); break;
            case 11: gotoXY(0,0); break;
        default: break;
        } i++;
        if (fCheck[2] == true && fCheck[3] == true && fCheck[7] == true) DepartureCheck();
        if (fCheck[2] == true && fCheck[3] == true && fCheck[5] == true && fCheck[6] == true && fCheck[7] == true) CheckDateAndTime(TicketTime(),TicketTime(),0);
    }
}



void TicketCreate::Continue() {
    bool dontContinue = false;
    for (int i = 0; i < 7; i++) if(fCheck[i] == false) dontContinue = true;

    if (dontContinue == false) {backBool = true; quitProgram = true;}

    if (dontContinue == true) {
            string cantContinue = "Error: All fields must be set once.";
            gotoXY(40,13,cantContinue, 1); Sleep(2000);
    }
}
void TicketCreate::ExecuteSetter(int s) {
    switch(s) {
    case 1: SetValue(7,1,7); JourneyCost = jCost;
           for (int i = 0; i < 7; i++) {
                if (char(priceString[i-1]) == 32 && i < 3) {if (char(priceString[i]) == 48) priceString[i] = char(' ');}
                if (i == 0) {if (char(priceString[i]) == 48) priceString[i] = char(' ');}
            } flCost = "Cost:EUR" + priceString; fCheck[0] = true; break;
    case 2: SetValue(3,2,3); depCode = iataString; fCheck[1] = true; break;
    case 3: SetValue(3,3,10); depDate = dateString; depDay = dayInt; depMonth = monthInt; depYear = yearInt; fCheck[2] = true; break;
    case 4: SetValue(2,4,5); depTime = timeString; depHour = hourInt; depMinute = minuteInt;  fCheck[3] = true; break;
    case 5: SetValue(3,2,3); ariCode = iataString; fCheck[4] = true; break;
    case 6: SetValue(3,3,10); ariDate = dateString; ariDay = dayInt; ariMonth = monthInt; ariYear = yearInt; fCheck[5] = true; break;
    case 7: SetValue(2,4,5); ariTime = timeString; ariHour = hourInt; ariMinute = minuteInt; fCheck[6] = true; break;
    case 8: Continue(); break;
    case 9: Continue(); break;
    default: break;
    }
}
void TicketCreate::SetValue(int sMax, int wSet, int wLoop) {
    priceString = "0000.00"; iataString = "???"; dateString = "01.01.2019"; timeString = "00:00";
    jCost = 0;  dayInt = monthInt = 1; yearInt = 2019; hourInt = 0; minuteInt = 0;
    int c = 0; int s = 1; bool quit = false; Print(48,22,s,wSet,wLoop);
    while(quit == false) {
        c = 0;
        switch(c=getch()){
        case KEY_UP: Update(wSet,s,1); break;
        case KEY_DOWN: Update(wSet,s,2); break;
        case KEY_LEFT: s--; if (s < 1) s = sMax; if (s == 5) s = 4; break;
        case KEY_RIGHT: s++; if (sMax < s) s = 1; if (s == 5) s = 6; break;
        case KEY_ENTER: s++; if (sMax < s) quit = 1; if (s == 5) s = 6; break;
        default: break;
        } Print(48,22,s,wSet,wLoop); Sleep(10);
    }
}
void TicketCreate::Update(int wSet, int s, int x) {
    switch(wSet) {
    case 1: UpdateCost(x,s); break;
    case 2: UpdateChar(x,s); break;
    case 3: UpdateDate(x,s); break;
    case 4: UpdateTime(x,s); break;
    default: break;
    }
}
void TicketCreate::UpdateCost(int crease, int s) {
    // String Cost -> Float Cost && Update Cost -> String Cost
    char buffer [33]; string coststring[7]; float costfloat[7]; jCost = 0;
    for (int i = 0; i < 7; i++) {if(i != 4) costfloat[i] = float(priceString[i]) - 48;}
    if (crease == 1) costfloat[s-1]++; else costfloat[s-1]--; float multiplier = 1000; priceString = "";
    for (int i = 0; i < 7; i++) {
        if (i != 4) {
            if (i+1 == s) {if (costfloat[i] > 9) costfloat[i] = 0; else if (costfloat[i] < 0) costfloat[i] = 9;}
            coststring[i] = itoa(costfloat[i],buffer,10);
            jCost += costfloat[i] * multiplier; multiplier /= 10;
            priceString += coststring[i];
        } else priceString += ".";
    }
}
void TicketCreate::UpdateChar(int crease, int s) {
    // String -> Int -> Increment / Decrement -> String
    int asc = int(iataString[s - 1]); if (asc == 63) asc = 64;
    if (crease == 1) ++asc; else --asc;
    if(asc < 65) asc = 90; else if(asc > 90) asc = 65;
    iataString[s - 1] = char(asc);
}
void TicketCreate::UpdateDate(int crease, int s) {
    int d = dayInt, m = monthInt, y = yearInt;

    // String to Int
    int e, f, g, h; string i, j, k; char buffer [33];
    e = (int(dateString[0]) - 48) * 10;   f = int(dateString[1]) - 48; d = e + f;
    e = (int(dateString[3]) - 48) * 10;   f = int(dateString[4]) - 48; m = e + f;
    e = (int(dateString[6]) - 48) * 1000; f = (int(dateString[7]) - 48) * 100;
    g = (int(dateString[8]) - 48) * 10;   h = int(dateString[9]) - 48; y = e + f + g + h;

    // Increment / Decrement
    if (crease == 1) {if (s == 1) d++; if (s == 2) m++; if (s == 3) y++;}
    if (crease == 2) {if (s == 1) d--; if (s == 2) m--; if (s == 3) y--;}
    if (m > 12) m = 1; else if (m < 1) m = 12; if (y < 2019) y = 2019;

    // If dayInt is greater than the monthInt's max dayInt...
    int monthInts[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if ((s == 1 || s == 2) && (d < 1)) d = monthInts[m-1]; else if((s == 1 || s == 2) && (d > monthInts[m-1])) d = 1;

    // Int to String
    i = itoa (d,buffer,10); j = itoa (m,buffer,10); k = itoa (y,buffer,10);
    if (d < 10) dateString = "0" + i; else dateString = i;
    if (m < 10) dateString += ".0" + j; else dateString += "." + j;
    dateString += "." + k; dayInt = d, monthInt = m, yearInt = y;
}
void TicketCreate::UpdateTime(int crease, int s) {

    // String to Int
    char buffer [33]; int a, b; string c, d;
    a = (int(timeString[0]) - 48) * 10; b = int(timeString[1]) - 48; hourInt = a + b;
    a = (int(timeString[3]) - 48) * 10; b = int(timeString[4]) - 48; minuteInt = a + b;

    // Increment / Decrement
    if (s == 1 && crease == 1) hourInt++; else if(s == 2 && crease == 1) minuteInt++;
    if (s == 1 && crease == 2) hourInt--; else if(s == 2 && crease == 2) minuteInt--;
    if (hourInt > 23) hourInt = 0; else if (minuteInt > 59) minuteInt = 0;
    if (hourInt < 0) hourInt = 23; else if (minuteInt < 0) minuteInt = 59;

    // Int to String
    c = itoa(hourInt,buffer,10); d = itoa(minuteInt,buffer,10); timeString = "";
    if (hourInt < 10) timeString += "0" + c; else timeString += c;
    if (minuteInt < 10) timeString += ":0" + d; else timeString += ":" +d;
}
void TicketCreate::Print(int x, int y, int s, int wSet, int wLoop) {
    int h = 0; string text, wChar, wOut; gotoXY(x,y);
	if (wSet == 1) {wOut = "Set Flight Cost: "; wChar = priceString;}
	if (wSet == 2) {wOut = "Set IATA Code: "; wChar = iataString;}
	if (wSet == 3) {wOut = "Set The Date: "; wChar = dateString;}
	if (wSet == 4) {wOut = "Set The Time: "; wChar = timeString;}
    cout << wOut;
    for (int i = 0; i < wLoop; i++) {
        text = wChar[i];
		if(wSet==1 || wSet == 2) { if(i+1==s) h = 1; else h = 0; }
		if(wSet==3) {if(s == 1 && i < 2) h=1; else if(s == 2 && i > 2 && i < 5) h = 1; else if(s == 3 && i > 5) h = 1; else h = 0;}
		if(wSet==4) {if(((i+1) < 3) && s == 1) h = 1; else if(((i+1) > 3) && s == 2) h = 1; else h = 0; }
        gotoXY(((48+wOut.length())+i),22,text,h); // 48
		if ((i==1||i==4)&&wSet==3) {cout << "."; i++;}
    } gotoXY(0,0);
}



char **TicketCreate::TicketData() {
    string transfer; int x = 0; char **arr=new char*[6];
    while(x < 6) {
        switch(x) {
        case 0: transfer = depCode; break;
        case 1: transfer = depDate; break;
        case 2: transfer = depTime; break;
        case 3: transfer = ariCode; break;
        case 4: transfer = ariDate; break;
        case 5: transfer = ariTime; break;
        default: break;
        } arr[x] = new char[transfer.length()];
        for (int i=0; i<transfer.length()+1; i++) {arr[x][i] = transfer[i];}
        x++;
    } return arr;
}
int* TicketCreate::TicketTime() {
    int* arr = new int[10];
        arr[0] = ariYear; arr[1] = ariMonth; arr[2] = ariDay; arr[3] = ariHour; arr[4] = ariMinute;
        arr[5] = depYear; arr[6] = depMonth; arr[7] = depDay; arr[8] = depHour; arr[9] = depMinute;
    return arr;
}
void TicketCreate::CheckDateAndTime(int first[], int second[], bool func) {
    int tolDays = 0, hours = 0, minutes = 0; string hour, minute; char buffer[33];
    for (int i = first[5]; i <= second[0]; i++) {
        int mList[12] = {31,28,31,30,31,30,31,31,30,31,30,31}, startMonth = 1, endMonth = 12;
        if (i == second[0]) endMonth = second[1], mList[endMonth - 1] = (second[2]);
        if (i == first[5]) startMonth = first[6], mList[startMonth - 1] -= (first[7]);
        if (((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0)) mList[1] = 29;
        for (int x = startMonth; x <= endMonth; x++) {tolDays += mList[x - 1];}
    }
    hours = (tolDays * 24) + (second[3] - first[8]), minutes = second[4] - first[9];
    if (minutes < 0) {hours -= 1; minutes += 60;}
    hour = itoa(hours,buffer,10), minute = itoa(minutes,buffer,10);
    if ((func == 0) && ((hours < 0) || (hours > 24) || (hours == 24 && minutes > 0))) {
        hour = "0", minute = "0", fCheck[5] = 0, fCheck[6] = 0,
        ariDate = "00.00.0000", ariTime = "00:00"; ErrorPrompt("Error");
    } flDur = "EXPECTED FLIGHT TIME: " + hour + "Hours " + minute + "Minutes";
}



void TicketCreate::DepartureCheck() {
    for (int i=0;i<5;i++) DateCheck[i] = true;
    DateCheck[0] = (depChk[0] > depYear) ? false : true;
    DateCheck[1] = (depChk[0] == depYear && depChk[1] > depMonth) ? false : true;
    DateCheck[2] = (depChk[0] == depYear && depChk[1] == depMonth && depChk[2] > depDay) ? false : true;
    DateCheck[3] = (depChk[0] == depYear && depChk[1] == depMonth && depChk[2] == depDay && depChk[3] > depHour) ? false : true;
    DateCheck[4] = (depChk[0] == depYear && depChk[1] == depMonth && depChk[2] == depDay && depChk[3] == depHour && depChk[4] > depMinute) ? false : true;
    string errFlightStart = "Departure must be after first arrival";

    for (int i=0;i<5;i++) {
        if (DateCheck[i] == false && fCheck[2] == true) {
            fCheck[2] = false; fCheck[3] = false;
            depDate = "00.00.0000"; depTime = "00:00";
            ErrorPrompt(errFlightStart); Print();
        }
    }
}
void TicketCreate::ErrorPrompt(string errString) {
    system("CLS"); int c = 0; int s = 0; int h; bool errorBreak = 0;
    Draw(2,24,6,71,17);
            while(errorBreak == 0) {
                c = 0;
                gotoXY(39,9,"["+errString+"]",0);
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
        } Print();
}
