#include <iostream>
#include <fstream>

#include "ticketcreate.h"
#include "progfunc.h"

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

using namespace std;

Report::Report() {
    CalculateReport(); bool quit = 0; system("CLS"); Draw(2,20,8,79,15);
    gotoXY(48,11,"[Daily Report]",0);
    gotoXY(28,14,("\tTotal commision today: EUR"+totalCommission),0);
    gotoXY(28,16,("\tTotal cost of all flights today: EUR"+totalFlightCost),0);
    gotoXY(28,18,"\tTotal flights today: " + flightAmount + " Flights",0);
    cin.get();
}

void Report::CalculateReport() {
    string s, localYear, localMonth, localDay; int sTotal = 0, x = 0, yCounter = 0; float totalCost = 0, totalFlights = 0, calcCost = 0;
    char **arr=new char*[13]; char buffer[35]; SYSTEMTIME localTime; GetLocalTime(&localTime);
    localYear = itoa(localTime.wYear,buffer,10);
    localMonth = itoa(localTime.wMonth,buffer,10);
    localDay = itoa(localTime.wDay,buffer,10);

    ifstream myFile; myFile.open("FlightLog.csv");
    while(myFile.good()) {getline(myFile, s); sTotal++;}
    myFile.close(); if (sTotal < 1) sTotal = 1;

    ifstream myCSV; myCSV.open("FlightLog.csv");
    while(yCounter < sTotal-1) {
        calcCost = 0; x = 0; string temp;
        while (x < 13) {
            string line;
            getline(myCSV, line, ',');
            arr[x] = new char[line.length()];
            for (int i=0; i<line.length()+1; i++) {arr[x][i] = line[i];}
            x++;
        } char **myData = arr; temp = myData[5]; float multiplier = 10, tempCalc, tempfloat[temp.length()];

        for (int i = 0; i < (temp.length()-5); i++) {multiplier += (9 * multiplier);}
        for (int i = 0; i < (temp.length()); i++) {if(i != temp.length()-3) tempfloat[i] += (float(temp[i]) - 48);}
        for (int i = 0; i < (temp.length()); i++) {
            if(i != temp.length()-3) calcCost += (tempfloat[i] * multiplier);
            if(i != temp.length()-3) multiplier = multiplier / 10;
        } yCounter++;
        if (myData[1] == localYear && myData[2] == localMonth && myData[3] == localDay) {totalFlights += 1; totalCost += calcCost;}
	} myCSV.close();

    float tempFloaty = (totalCost); stringstream fs; fs << std::fixed << std::setprecision(2) << (tempFloaty); totalFlightCost = fs.str();
    tempFloaty = (totalCost/10); stringstream ss; ss << std::fixed << std::setprecision(2) << (tempFloaty); totalCommission = ss.str();
    int tempInty = (totalFlights); stringstream ts; ts << (tempInty); flightAmount = ts.str();
}
