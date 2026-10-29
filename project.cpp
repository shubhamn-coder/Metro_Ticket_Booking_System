// Pune Metro Ticket Booking System (queue based)
// Build:  g++ -std=c++17 -O2 -o metro metro_booking.cpp
// Run:    ./metro

#include <queue>
#include<iostream>
using namespace std;
#define MAX_tickets 10
#define TOTAL_STATIONS 13

// Details of a person waiting in the queue
struct Passenger{
    string name;
    int from, to;   // station numbers
};

class Ticket_Book_System{
    private:
    int ticket_booked_count = 0;
    int total_fare = 0;   // money collected from booked tickets
    string stations[TOTAL_STATIONS] = {"PCMC Bhavan", "Sant Tukaram Nagar", "Nashik Phata",
                                       "Kasarwadi", "Phugewadi", "Dapodi", "Bopodi", "Khadki",
                                       "Shivaji Nagar", "District Court", "Kasba Peth",
                                       "Mahatma Phule Mandai", "Swargate"};
    // Ask for a station number till a valid one is entered
    int read_station(string message){
        int number;
        while(true){
            cout<<message;
            cin>>number;
            if(cin.fail()){      //letters were typed instead of a number
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else if(number>=1 && number<=TOTAL_STATIONS){
                return number;
            }
            cout<<"Invalid station number (1-"<<TOTAL_STATIONS<<"), see option 5"<<endl;
        }
    }
    public:
    queue <Passenger> q;
    string name;
    void add_in_queue(){
        Passenger p;
        cout<<"Enter the name: ";
        getline(cin, name);
        p.name = name;
        p.from = read_station("Enter source station number: ");
        p.to = read_station("Enter destination station number: ");
        if(p.from==p.to){
            cout<<"Source and destination cannot be same"<<endl;
            return;
        }
        q.push(p);
        cout<<"Successfully added the person in queue"<<endl;
    }
    void book_ticket(){
        if(ticket_booked_count==MAX_tickets){
            cout<<"No availability of tickets"<<endl; //No tickets are available
            return;
        }
        if(q.empty()){
            cout<<"No one is present in the queue"<<endl; //Queue is empty
        }
        else{
            Passenger p = q.front(); //Take a first and serve them
            int stops = p.from - p.to;
            if(stops<0) stops = -stops;       //number of stops between the two stations
            int fare = 10 + 5*(stops-1);      //Rs 10 for first stop, Rs 5 for each extra stop
            cout<<p.name<<" bought the ticket"<<endl;
            cout<<stations[p.from-1]<<" to "<<stations[p.to-1]<<endl;
            cout<<"Stops: "<<stops<<"  Fare: Rs "<<fare<<endl;
            q.pop(); //remove person from queue
            ticket_booked_count++; //increment count of booked tickets
            total_fare = total_fare + fare;
        }
    }
    void ticket_status(){
        cout<<"Availability of Tickets: "<<MAX_tickets-ticket_booked_count<<"/"<<MAX_tickets<<endl;
        cout<<"Waiting Count: "<<q.size()<<endl;
        cout<<"Total money collected: Rs "<<total_fare<<endl;
    }
    void waiting_list(){
        if(q.empty()){
            cout<<"Queue is empty"<<endl;
            return;
        }
        cout<<"Waiting List: "<<endl;
        queue <Passenger> temp =q;
        int i=1;
        while(!temp.empty()){
            cout<<i<<". "<<temp.front().name<<" ("<<stations[temp.front().from-1]
                <<" to "<<stations[temp.front().to-1]<<")"<<endl;
            temp.pop();
            i++;
        }
    }
    void show_stations(){
        for(int i=0; i<TOTAL_STATIONS; i++){
            cout<<i+1<<". "<<stations[i]<<endl;
        }
    }
};
int main(){
    Ticket_Book_System obj;
    int choice, ch1;
    do{
        cout<<"Pune Metro Ticket Booking System"<<endl;
        cout<<"1. Add in queue for ticket booking"<<endl;
        cout<<"2. Book the ticket"<<endl;
        cout<<"3. Avaiability of Ticket"<<endl;
        cout<<"4. Waiting list \n5. View stations \n6. Exit"<<endl;
        cout<<"Select the operation: ";
         cin>>choice;
        switch(choice){
            case 1: obj.add_in_queue(); break;
            case 2: obj.book_ticket(); break;
            case 3: obj.ticket_status(); break;
            case 4: obj.waiting_list(); break;
            case 5: obj.show_stations(); break;
            case 6: cout<<"Closing system.."<<endl; return 0; break;
            default: cout<<"Invalid Input"<<endl;
        }
        cout<<"Press 1 to continue/Press 0  to close ";
        cin>>ch1;  cout<<endl;
    } while(ch1==1);
}