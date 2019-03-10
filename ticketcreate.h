#ifndef TICKETCREATE_H
#define TICKETCREATE_H
#include <iostream>

using namespace std;

class TicketCreate {
    public:
        TicketCreate(string title, int time[]); TicketCreate(string name, float TotalCost, char **first, char **second, string duration, string timeone, string timetwo);
        void SummaryIntro(string name, string depAirport, string arrAirport); void PrintFileSpalsh(); void ErrorPrompt(string errString);
        void Control(); void ExecuteSetter(int s); void Continue(); void CheckDateAndTime(); void DepartureCheck();

        // Getters
        int* TicketTime(); char **TicketData(); float getCost() {return JourneyCost;}

        // Setting Variable Classes
        void SetValue(int sMax, int wSet, int wLoop); void Update(int wSet, int s, int x);
        void UpdateCost(int crease, int s); void UpdateChar(int crease, int s);
        void UpdateDate(int crease, int s); void UpdateTime(int crease, int s);
        void Print(); void Print(int x); void Print(int x, int y, int s, int wSet, int wLoop);
    private:
        bool quitProgram, ticketControl, fCheck[8], DateCheck[5], backBool; float JourneyCost;
        string FlightCost, FlightDuration, ticketTitle; int dLim[5];

        // Departure Variables
        string DepartureAirport, DepartureDate, DepartureTime;
        int departureDay, departureMonth, departureYear, departureHour, departureMinute;

        // Arrival Variables
        string ArrivalAirport, ArrivalDate, ArrivalTime;
        int arrivalDay, arrivalMonth, arrivalYear, arrivalHour, arrivalMinute;

        // Setting Variable Classes
        string priceString, iataString, timeString, dateString;
        int dayInt, monthInt, yearInt, hourInt, minuteInt; float jCost;
};

class Summary {
    public:
        Summary(char **first, char **second);
        void Control(); void Print(int x); void Execute(int selected); string getName();
        void setName(); void setAddressOne(); void setAddressTwo(); void setAddressThree();
    private:
        bool quitProgram, backBool; string summaryTitle; char limitChar[25];
        string CustomerName, AddressLineOne, AddressLineTwo, AddressLineThree, REF;
};

class Report {
    public:
        Report(); void CalculateReport();
    private:
        int totalFlights; string totalCommission, totalFlightCost, flightAmount;
};

#endif // TICKETPROGRAM_H
