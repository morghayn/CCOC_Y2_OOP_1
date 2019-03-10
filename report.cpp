#include <iostream>
#include <fstream>

#include "ticketcreate.h"
#include "progfunc.h"

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

using namespace std;

Report::Report() {
    CalculateReport(); bool quit = 0; system("CLS");
    Draw(2,24,6,71,17);
    gotoXY(48,9,"[Daily Report]",0);
//  gotoXY(28,13,("\t:Today's statistics..."),0);
    gotoXY(28,13,("\tTotal commision today: EUR"+totalCommission),0);
    gotoXY(28,15,("\tTotal cost of all flights today: EUR"+totalFlightCost),0);
    gotoXY(28,17,"\tTotal flights today: " + flightAmount + " Flights",0);
    cin.get(); Sleep(1000);
}

void Report::CalculateReport() {

    string s; int sTotal = 0;
    ifstream myFile; myFile.open("FlightLog.csv");
    while(myFile.good()) {getline(myFile, s); sTotal++;}
    myFile.close();

    int x = 0, yCounter = 0; float totalCost = 0; totalFlights = 0;
    char **arr=new char*[13]; char buffer[35];
    SYSTEMTIME localTime; GetLocalTime(&localTime); float calcCost = 0;
    int myYear = localTime.wYear, myMonth = localTime.wMonth, myDay = localTime.wDay;
    string localYear = itoa(myYear,buffer,10), localMonth = itoa(myMonth,buffer,10), localDay = itoa(myDay,buffer,10);
    ifstream myCSV; myCSV.open("FlightLog.csv");
    while(yCounter < sTotal-1) {
        calcCost = 0;
        x = 0; string temp;
        while (x < 13) {
            string line;
            getline(myCSV, line, ',');
            arr[x] = new char[line.length()];
            for (int i=0; i<line.length()+1; i++) {arr[x][i] = line[i];}
            x++;
        }
        char **myData = arr; temp = myData[5]; float multiplier = 10;
        float tempfloat[temp.length()]; float tempCalc;
        for (int i = 0; i < (temp.length()-5); i++) {multiplier += (9 * multiplier);}
        for (int i = 0; i < (temp.length()); i++) {if(i != temp.length()-3) tempfloat[i] += (float(temp[i]) - 48);}
        for (int i = 0; i < (temp.length()); i++) {
            if(i != temp.length()-3) calcCost += (tempfloat[i]*multiplier);
            if(i != temp.length()-3) multiplier = multiplier / 10;
        }
       // cout << calcCost << endl; cin.get();
        if (myData[1] == localYear && myData[2] == localMonth && myData[3] == localDay) {totalFlights += 1; totalCost += calcCost;}
        //if (!(myData[1] == localYear && myData[2] == localMonth && myData[3] == localDay))
       yCounter++;
	}
	myCSV.close();

    float tempFloaty = (totalCost); stringstream fs; fs << std::fixed << std::setprecision(2) << (tempFloaty); totalFlightCost = fs.str();
    tempFloaty = (totalCost/10); stringstream ss; ss << std::fixed << std::setprecision(2) << (tempFloaty); totalCommission = ss.str();
    int tempInty = (totalFlights); stringstream ts; ts << (tempInty); flightAmount = ts.str();

}
