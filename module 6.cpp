#include "entities.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// compare by date
bool compareDate(Event a, Event b) {
    return a.getDate() < b.getDate();
}

// sort by dates
void sortEventByDates(vector<Event>& events) {
    sort(events.begin(), events.end(), compareDate);
}

// compare events by popularity
bool comparePopularity(Event a, Event b) {
    return a.getRegistrationCount() > b.getRegistrationCount();
}

// sort by popularity
void sortEventsByPopularity(vector<Event>& events) {
    sort(events.begin(), events.end(), comparePopularity);
}

int main() {
    vector<Event> events = {
        Event(1,"Robotics Workshop","Tech","2026/11/25",67,50,42),
        Event(2,"Chess Tournament","Games","2026/11/05",34,25,15),
        Event(3,"Code Clash Hackathon","Tech","2026/10/11",68,55,12),
        Event(4,"Cultural Night","Cultural","2026/12/01",44,46,7)
    };

    cout << " BEFORE SORTING:\n";
    for(int i=0; i<events.size(); i++) {
        cout << events[i].getDate() << " | "
             << events[i].getRegistrationCount() << " regs | "
             << events[i].getName() << endl;
    }

    sortEventByDates(events);
    cout << "\n Sorted Events By Dates:\n";
    for(int i=0; i<events.size(); i++) {
        cout << events[i].getDate() << " --> " << events[i].getName() << endl;
    }

    sortEventsByPopularity(events);
    cout << "\n Sorted Events By Popularity:\n";
    for(int i=0; i<events.size(); i++) {
        cout << events[i].getRegistrationCount() << " --> " << events[i].getName() << endl;
    }

    return 0;
}

