#ifndef CLUB_OVERVIEW_H
#define CLUB_OVERVIEW_H

#include "file.h"
#include <iostream>
#include <string>

using namespace std;



inline string findOverviewClub(string fid)
{
    for (auto a : assignments)
    {
        if (a.getFacultyId() == fid)
            return a.getClubId();
    }

    return "";
}



inline int findOverviewClubIndex(string cid)
{
    for (int i = 0; i < (int)clubs.size(); i++)
    {
        if (clubs[i].getClubId() == cid)
            return i;
    }

    return -1;
}



inline void viewFacultyClubDetails(string cid)
{
    int index = findOverviewClubIndex(cid);

    if (index == -1)
    {
        cout << "\nClub not found.\n";
        return;
    }

    cout << "\n========== CLUB DETAILS ==========\n";
    cout << "Club ID: " << clubs[index].getClubId() << endl;
    cout << "Club Name: " << clubs[index].getName() << endl;
    cout << "Category: " << clubs[index].getCategory() << endl;
    cout << "Description: " << clubs[index].getDescription() << endl;
}



inline void viewMemberStatistics(string cid)
{
    int total = 0, active = 0;

    for (auto r : registrations)
    {
        if (r.getTargetId() == cid &&
            r.getType() == "Club")
        {
            if (r.getStatus() == "Active")
                active++;

            if (r.getStatus() != "Cancelled")
                total++;
        }
    }

    cout << "\n========== MEMBER STATISTICS ==========\n";
    cout << "Total Registered Students: " << total << endl;
    cout << "Active Students: " << active << endl;
}



inline void viewActiveStudentDetails(string cid)
{
    cout << "\n========== ACTIVE STUDENTS ==========\n";

    int count = 0;

    for (auto r : registrations)
    {
        if (r.getTargetId() == cid &&
            r.getType() == "Club" &&
            r.getStatus() == "Active")
        {
            for (auto s : students)
            {
                if (s.getStudentId() == r.getStudentId())
                {
                    cout << "\nStudent ID: " << s.getStudentId();
                    cout << "\nName: " << s.getName();
                    cout << "\nGmail: " << s.getGmail() << endl;
                    count++;
                }
            }
        }
    }

    cout << "\nTotal Active Students: " << count << endl;

    if (count == 0)
        cout << "No active students found.\n";
}



inline void viewEventStatistics(string cid)
{
    int total = 0;

    for (auto e : events)
    {
        if (e.getClubId() == cid)
            total++;
    }

    cout << "\n========== EVENT STATISTICS ==========\n";
    cout << "Total Events Organized: " << total << endl;
}



inline void clubOverview(string fid)
{
    string cid = findOverviewClub(fid);

    if (cid == "")
    {
        cout << "\nNo club assigned to this faculty.\n";
        return;
    }

    int choice;

    do
    {
        cout << "\n========== CLUB OVERVIEW ==========\n";
        cout << "1. View Club Details\n";
        cout << "2. View Member Statistics\n";
        cout << "3. View Active Student Details\n";
        cout << "4. View Event Statistics\n";
        cout << "5. Back to Faculty Dashboard\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                viewFacultyClubDetails(cid);
                break;

            case 2:
                viewMemberStatistics(cid);
                break;

            case 3:
                viewActiveStudentDetails(cid);
                break;

            case 4:
                viewEventStatistics(cid);
                break;

            case 5:
                cout << "\nReturning to Faculty Dashboard.\n";
                break;

            default:
                cout << "\nInvalid Choice.\n";
        }

    } while (choice != 5);
}

#endif
