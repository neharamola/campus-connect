#ifndef FACULTY_FEEDBACK_H
#define FACULTY_FEEDBACK_H

#include "file.h"
#include <iostream>
#include <string>

using namespace std;

// Find assigned club for feedback

inline string findFeedbackClub(string fid)
{
    for (auto a : assignments)
    {
        if (a.getFacultyId() == fid)
            return a.getClubId();
    }

    return "";
}

// View all event feedback

inline void viewAllEventFeedback(string cid)
{
    cout << "\n========== STUDENT EVENT FEEDBACK ==========\n";

    int count = 0;

    for (auto f : feedbacks)
    {
        for (auto e : events)
        {
            if (e.getEventId() == f.getEventId() &&
                e.getClubId() == cid)
            {
                cout << "\nFeedback ID: " << f.getFeedbackId();
                cout << "\nEvent Name: " << e.getName();
                cout << "\nStudent ID: " << f.getStudentId();
                cout << "\nFeedback: " << f.getMessage();
                cout << "\nDate: " << f.getDate() << endl;

                count++;
            }
        }
    }

    if (count == 0)
        cout << "No feedback available.\n";
}

// Faculty feedback menu

inline void facultyFeedback(string fid)
{
    string cid = findFeedbackClub(fid);

    if (cid == "")
    {
        cout << "\nNo club assigned to this faculty.\n";
        return;
    }

    int choice;

    do
    {
        cout << "\n========== FEEDBACK MANAGEMENT ==========\n";
        cout << "1. View All Event Feedback\n";
        cout << "2. Back to Faculty Dashboard\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                viewAllEventFeedback(cid);
                break;

            case 2:
                cout << "\nReturning to Faculty Dashboard.\n";
                break;

            default:
                cout << "\nInvalid Choice.\n";
        }

    } while (choice != 2);
}

#endif
