#ifndef REGISTRATION_MANAGEMENT_H
#define REGISTRATION_MANAGEMENT_H

#include "file.h"
#include <iostream>
#include <string>
using namespace std;

// Generate Registration ID

inline string generateRegistrationId()
{
    return "R" + to_string(101 + registrations.size());
}

// Register for Club

inline void registerForClub(string sid)
{
    string cid;
    bool found = false;

    cout << "\n========== AVAILABLE CLUBS ==========\n";

    for (auto c : clubs)
        cout << c.getClubId() << " - " << c.getName() << endl;

    cout << "\nEnter Club ID: ";
    cin >> cid;

    for (auto c : clubs)
    {
        if (c.getClubId() == cid)
            found = true;
    }

    if (!found)
    {
        cout << "Club not found.\n";
        return;
    }

    for (auto r : registrations)
    {
        if (r.getStudentId() == sid &&
            r.getTargetId() == cid &&
            r.getType() == "Club" &&
            r.getStatus() == "Active")
        {
            cout << "Already registered in this club.\n";
            return;
        }
    }

    Registration r;
    r.setDetails(generateRegistrationId(), sid, cid,
                 "Club", "Active");

    registrations.push_back(r);
    saveRegistrations();

    cout << "Club Registration Successful!\n";
}

// Cancel Club Membership

inline void cancelClubMembership(string sid)
{
    string cid;

    cout << "\nEnter Club ID: ";
    cin >> cid;

    for (auto &r : registrations)
    {
        if (r.getStudentId() == sid &&
            r.getTargetId() == cid &&
            r.getType() == "Club" &&
            r.getStatus() == "Active")
        {
            r.setStatus("Cancelled");
            saveRegistrations();

            cout << "Club Membership Cancelled Successfully.\n";
            return;
        }
    }

    cout << "Club Membership Not Found.\n";
}

// Promote First Student From Waitlist

inline void promoteNextStudent(string eid)
{
    for (auto &r : registrations)
    {
        if (r.getTargetId() == eid &&
            r.getType() == "Event" &&
            r.getStatus() == "Waiting")
        {
            r.setStatus("Active");

            cout << "\nA seat has become available!\n";
            cout << "Student " << r.getStudentId()
                 << " has been promoted from the waitlist.\n";

            return;
        }
    }
}

// Register for Event

inline void registerForEvent(string sid)
{
    string eid;
    int index = -1;

    cout << "\n========== AVAILABLE EVENTS ==========\n";

    for (auto e : events)
    {
        cout << e.getEventId() << " - "
             << e.getName() << " - "
             << e.getDate() << endl;
    }

    cout << "\nEnter Event ID: ";
    cin >> eid;

    for (int i = 0; i < (int)events.size(); i++)
    {
        if (events[i].getEventId() == eid)
            index = i;
    }

    if (index == -1)
    {
        cout << "Event not found.\n";
        return;
    }

    // Check existing registration

    for (auto r : registrations)
    {
        if (r.getStudentId() == sid &&
            r.getTargetId() == eid &&
            r.getType() == "Event" &&
            (r.getStatus() == "Active" ||
             r.getStatus() == "Waiting"))
        {
            cout << "Already registered or waiting for this event.\n";
            return;
        }
    }

    // Count active registrations

    int count = 0;

    for (auto r : registrations)
    {
        if (r.getTargetId() == eid &&
            r.getType() == "Event" &&
            r.getStatus() == "Active")
        {
            count++;
        }
    }

    Registration r;

    // Check event capacity

    if (count >= events[index].getCapacity())
    {
        r.setDetails(generateRegistrationId(), sid, eid,
                     "Event", "Waiting");

        registrations.push_back(r);
        saveRegistrations();

        cout << "\nEvent is full.\n";
        cout << "You have been added to the waiting list.\n";
    }
    else
    {
        r.setDetails(generateRegistrationId(), sid, eid,
                     "Event", "Active");

        registrations.push_back(r);
        saveRegistrations();

        cout << "Event Registration Successful!\n";
    }
}

// Cancel Event Registration

inline void cancelEventRegistration(string sid)
{
    string eid;

    cout << "\nEnter Event ID: ";
    cin >> eid;

    for (auto &r : registrations)
    {
        if (r.getStudentId() == sid &&
            r.getTargetId() == eid &&
            r.getType() == "Event" &&
            (r.getStatus() == "Active" ||
             r.getStatus() == "Waiting"))
        {
            bool wasActive = (r.getStatus() == "Active");

            r.setStatus("Cancelled");

            cout << "\nEvent Registration Cancelled Successfully.\n";

            // Promote next student only if an active
            // registration was cancelled

            if (wasActive)
            {
                promoteNextStudent(eid);
            }

            saveRegistrations();
            return;
        }
    }

    cout << "Event Registration Not Found.\n";
}

// View Event Waitlist

inline void viewEventWaitlist()
{
    string eid;
    int position = 1;
    bool found = false;

    cout << "\nEnter Event ID: ";
    cin >> eid;

    cout << "\n========== EVENT WAITLIST ==========\n";

    for (auto r : registrations)
    {
        if (r.getTargetId() == eid &&
            r.getType() == "Event" &&
            r.getStatus() == "Waiting")
        {
            cout << position << ". Student ID: "
                 << r.getStudentId() << endl;

            position++;
            found = true;
        }
    }

    if (!found)
    {
        cout << "No students in the waiting list.\n";
    }
}

// Registration Menu

inline void registrationManagement(string sid)
{
    int choice;

    do
    {
        cout << "\n========== REGISTRATION MANAGEMENT ==========\n";
        cout << "1. Register for Club\n";
        cout << "2. Cancel Club Membership\n";
        cout << "3. Register for Event\n";
        cout << "4. Cancel Event Registration\n";
        cout << "5. View Event Waitlist\n";
        cout << "6. Back\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                registerForClub(sid);
                break;

            case 2:
                cancelClubMembership(sid);
                break;

            case 3:
                registerForEvent(sid);
                break;

            case 4:
                cancelEventRegistration(sid);
                break;

            case 5:
                viewEventWaitlist();
                break;

            case 6:
                cout << "Returning to Dashboard.\n";
                break;

            default:
                cout << "Invalid Choice.\n";
        }

    } while (choice != 6);
}

#endif
