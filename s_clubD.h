#ifndef CLUB_EVENT_DISCOVERY_H
#define CLUB_EVENT_DISCOVERY_H

#include "file.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cctype>

using namespace std;



inline string discoveryLower(string str)
{
    for (int i = 0; i < (int)str.length(); i++)
        str[i] = tolower((unsigned char)str[i]);

    return str;
}



inline string discoveryDate()
{
    time_t now = time(0);
    tm *t = localtime(&now);

    string d = to_string(1900 + t->tm_year) + "-";

    if (t->tm_mon + 1 < 10)
        d += "0";

    d += to_string(t->tm_mon + 1) + "-";

    if (t->tm_mday < 10)
        d += "0";

    d += to_string(t->tm_mday);

    return d;
}



inline int discoveryFindClub(string cid)
{
    for (int i = 0; i < (int)clubs.size(); i++)
    {
        if (clubs[i].getClubId() == cid)
            return i;
    }

    return -1;
}



inline void displayAllClubs()
{
    cout << "\n========== AVAILABLE CLUBS ==========\n";

    if (clubs.empty())
    {
        cout << "No clubs available.\n";
        return;
    }

    for (auto c : clubs)
    {
        cout << "\nClub ID: " << c.getClubId();
        cout << "\nClub Name: " << c.getName();
        cout << "\nCategory: " << c.getCategory();
        cout << "\nDescription: " << c.getDescription() << endl;
    }
}



inline void displayDiscoveryEvents()
{
    cout << "\n========== UPCOMING EVENTS ==========\n";

    string today = discoveryDate();
    int count = 0;

    for (auto e : events)
    {
        if (e.getDate() >= today)
        {
            int index = discoveryFindClub(e.getClubId());

            cout << "\nEvent ID: " << e.getEventId();
            cout << "\nEvent Name: " << e.getName();

            if (index != -1)
                cout << "\nClub: " << clubs[index].getName();

            cout << "\nDate: " << e.getDate();
            cout << "\nAvailable Capacity: " << e.getCapacity() << endl;

            count++;
        }
    }

    if (count == 0)
        cout << "No upcoming events found.\n";
}



inline void searchDiscoveryClubs()
{
    int choice;
    string key;

    cout << "\n1. Search by Club Name\n";
    cout << "2. Search by Category\n";
    cout << "Enter choice: ";
    cin >> choice;

    cin.ignore();

    cout << "Enter search text: ";
    getline(cin, key);

    key = discoveryLower(key);

    int count = 0;

    for (auto c : clubs)
    {
        string value;

        if (choice == 1)
            value = c.getName();
        else if (choice == 2)
            value = c.getCategory();
        else
        {
            cout << "Invalid choice.\n";
            return;
        }

        if (discoveryLower(value).find(key) != string::npos)
        {
            cout << "\nClub ID: " << c.getClubId();
            cout << "\nClub Name: " << c.getName();
            cout << "\nCategory: " << c.getCategory();
            cout << "\nDescription: " << c.getDescription() << endl;

            count++;
        }
    }

    if (count == 0)
        cout << "\nNo matching clubs found.\n";
}



inline void searchDiscoveryEvents()
{
    int choice;
    string key;

    cout << "\n1. Search by Event Name\n";
    cout << "2. Search by Club Category\n";
    cout << "Enter choice: ";
    cin >> choice;

    cin.ignore();

    cout << "Enter search text: ";
    getline(cin, key);

    key = discoveryLower(key);

    int count = 0;

    for (auto e : events)
    {
        int index = discoveryFindClub(e.getClubId());

        if (index == -1)
            continue;

        string value;

        if (choice == 1)
            value = e.getName();
        else if (choice == 2)
            value = clubs[index].getCategory();
        else
        {
            cout << "Invalid choice.\n";
            return;
        }

        if (discoveryLower(value).find(key) != string::npos)
        {
            cout << "\nEvent ID: " << e.getEventId();
            cout << "\nEvent Name: " << e.getName();
            cout << "\nClub: " << clubs[index].getName();
            cout << "\nDate: " << e.getDate() << endl;

            count++;
        }
    }

    if (count == 0)
        cout << "\nNo matching events found.\n";
}



inline void clubEventDiscovery()
{
    int choice;

    do
    {
        cout << "\n========== CLUB AND EVENT DISCOVERY ==========\n";
        cout << "1. View All Clubs\n";
        cout << "2. View Upcoming Events\n";
        cout << "3. Search Clubs\n";
        cout << "4. Search Events\n";
        cout << "5. Back to Student Dashboard\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                displayAllClubs();
                break;

            case 2:
                displayDiscoveryEvents();
                break;

            case 3:
                searchDiscoveryClubs();
                break;

            case 4:
                searchDiscoveryEvents();
                break;

            case 5:
                cout << "\nReturning to Student Dashboard.\n";
                break;

            default:
                cout << "\nInvalid Choice.\n";
        }

    } while (choice != 5);
}

#endif
