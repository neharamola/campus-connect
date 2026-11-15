#ifndef EVENT_MANAGEMENT_H
#define EVENT_MANAGEMENT_H

#include "file.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Find assigned club

inline string findEventClub(string fid)
{
    for (auto a : assignments)
    {
        if (a.getFacultyId() == fid)
            return a.getClubId();
    }

    return "";
}

// Generate event ID

inline string generateEventId()
{
    return "E" + to_string(101 + events.size());
}

// Create event

inline void createFacultyEvent(string cid)
{
    string name, date;
    int capacity;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nEnter Event Name: ";
    getline(cin, name);

    cout << "Enter Event Date (YYYY-MM-DD): ";
    getline(cin, date);

    cout << "Enter Registration Capacity: ";
    cin >> capacity;

    if (capacity <= 0)
    {
        cout << "\nCapacity must be greater than zero.\n";
        return;
    }

    string eid = generateEventId();

    Event e;
    e.setDetails(eid, cid, name, date, capacity);

    events.push_back(e);
    saveEvents();

    cout << "\nEvent Created Successfully!\n";
    cout << "Event ID: " << eid << endl;
}

// View all assigned club events

inline void viewFacultyEvents(string cid)
{
    cout << "\n========== CLUB EVENTS ==========\n";

    int count = 0;

    for (auto e : events)
    {
        if (e.getClubId() == cid)
        {
            cout << "\nEvent ID: " << e.getEventId();
            cout << "\nEvent Name: " << e.getName();
            cout << "\nDate: " << e.getDate();
            cout << "\nCapacity: " << e.getCapacity() << endl;
            count++;
        }
    }

    if (count == 0)
        cout << "No events available.\n";
}

// Update event date

inline void updateFacultyEventDate(string cid)
{
    string eid, date;

    cout << "\nEnter Event ID: ";
    cin >> eid;

    for (auto &e : events)
    {
        if (e.getEventId() == eid && e.getClubId() == cid)
        {
            cout << "Enter New Event Date (YYYY-MM-DD): ";
            cin >> date;

            e.setDate(date);
            saveEvents();

            cout << "\nEvent Date Updated Successfully.\n";
            return;
        }
    }

    cout << "\nEvent not found in your assigned club.\n";
}

// Event management menu

inline void eventManagement(string fid)
{
    string cid = findEventClub(fid);

    if (cid == "")
    {
        cout << "\nNo club assigned to this faculty.\n";
        return;
    }

    int choice;

    do
    {
        cout << "\n========== EVENT MANAGEMENT ==========\n";
        cout << "1. Create New Event\n";
        cout << "2. View All Events\n";
        cout << "3. Update Event Date\n";
        cout << "4. Back to Faculty Dashboard\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                createFacultyEvent(cid);
                break;

            case 2:
                viewFacultyEvents(cid);
                break;

            case 3:
                updateFacultyEventDate(cid);
                break;

            case 4:
                cout << "\nReturning to Faculty Dashboard.\n";
                break;

            default:
                cout << "\nInvalid Choice.\n";
        }

    } while (choice != 4);
}

#endif
