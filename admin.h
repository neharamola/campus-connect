#ifndef ADMIN_H
#define ADMIN_H

#include "file.h"
#include <iostream>
#include <limits>

using namespace std;



inline string generateFacultyId()
{
    return "F" + to_string(101 + faculties.size());
}



inline string generateClubId()
{
    return "C" + to_string(101 + clubs.size());
}



inline void addFaculty()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string name, gmail, password;

    cout << "\nEnter Faculty Name: ";
    getline(cin, name);

    cout << "Enter Gmail: ";
    getline(cin, gmail);

    if (gmail.size() < 10 ||
        gmail.substr(gmail.size() - 10) != "@gmail.com")
    {
        cout << "Please enter a valid Gmail address.\n";
        return;
    }

    for (auto f : faculties)
    {
        if (f.getGmail() == gmail)
        {
            cout << "This Gmail is already registered.\n";
            return;
        }
    }

    cout << "Create Password: ";
    getline(cin, password);

    string fid = generateFacultyId();

    Faculty f;
    f.setDetails(fid, name, gmail, password);

    faculties.push_back(f);
    saveFaculties();

    cout << "\nFaculty Added Successfully!\n";
    cout << "Faculty ID: " << fid << endl;
}



inline void viewFaculty()
{
    cout << "\n========== FACULTY LIST ==========\n";

    if (faculties.empty())
    {
        cout << "No faculty available.\n";
        return;
    }

    for (auto f : faculties)
    {
        cout << "\nFaculty ID: " << f.getFacultyId();
        cout << "\nName: " << f.getName();
        cout << "\nGmail: " << f.getGmail() << endl;
    }
}



inline void createClub()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string name, category, description;

    cout << "\nEnter Club Name: ";
    getline(cin, name);

    cout << "Enter Club Category: ";
    getline(cin, category);

    cout << "Enter Club Description: ";
    getline(cin, description);

    string cid = generateClubId();

    Club c;
    c.setDetails(cid, name, category, description);

    clubs.push_back(c);
    saveClubs();

    cout << "\nClub Created Successfully!\n";
    cout << "Club ID: " << cid << endl;
}



inline void viewClubs()
{
    cout << "\n========== CLUB LIST ==========\n";

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



inline void assignFaculty()
{
    if (faculties.empty() || clubs.empty())
    {
        cout << "\nPlease add faculty and create clubs first.\n";
        return;
    }

    viewFaculty();

    string fid, cid;

    cout << "\nEnter Faculty ID: ";
    cin >> fid;

    bool facultyFound = false;

    for (auto f : faculties)
    {
        if (f.getFacultyId() == fid)
        {
            facultyFound = true;
            break;
        }
    }

    if (!facultyFound)
    {
        cout << "Faculty not found.\n";
        return;
    }

  

    for (auto a : assignments)
    {
        if (a.getFacultyId() == fid)
        {
            cout << "This faculty is already assigned to a club.\n";
            return;
        }
    }

    viewClubs();

    cout << "\nEnter Club ID: ";
    cin >> cid;

    bool clubFound = false;

    for (auto c : clubs)
    {
        if (c.getClubId() == cid)
        {
            clubFound = true;
            break;
        }
    }

    if (!clubFound)
    {
        cout << "Club not found.\n";
        return;
    }

    

    for (auto a : assignments)
    {
        if (a.getClubId() == cid)
        {
            cout << "This club already has a faculty assigned.\n";
            return;
        }
    }

    Assignment a;
    a.setDetails(fid, cid);

    assignments.push_back(a);
    saveAssignments();

    cout << "\nFaculty Assigned Successfully!\n";
}



inline void adminModule()
{
    string username, password;

    cout << "\n========== ADMIN LOGIN ==========\n";

    cout << "Enter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    if (username != "admin" || password != "admin123")
    {
        cout << "\nInvalid Admin Login.\n";
        return;
    }

    int choice;

    do
    {
        cout << "\n========== ADMIN MENU ==========\n";
        cout << "1. Add Faculty\n";
        cout << "2. View Faculty\n";
        cout << "3. Create Club\n";
        cout << "4. View Clubs\n";
        cout << "5. Assign Faculty to Club\n";
        cout << "6. Logout\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addFaculty();
                break;

            case 2:
                viewFaculty();
                break;

            case 3:
                createClub();
                break;

            case 4:
                viewClubs();
                break;

            case 5:
                assignFaculty();
                break;

            case 6:
                cout << "\nAdmin Logged Out Successfully.\n";
                break;

            default:
                cout << "\nInvalid Choice.\n";
        }

    } while (choice != 6);
}

#endif
