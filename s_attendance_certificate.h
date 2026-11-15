#ifndef STUDENT_RECORDS_H
#define STUDENT_RECORDS_H

#include "file.h"
#include <iostream>
#include <string>
#include <ctime>
#include <limits>

using namespace std;


// ========================================
// GET TODAY'S DATE
// ========================================

string getStudentRecordDate()
{
    time_t now = time(0);
    tm *t = localtime(&now);

    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", t);

    return date;
}


// ========================================
// FIND EVENT
// ========================================

int findStudentRecordEvent(string eid)
{
    for (int i = 0; i < events.size(); i++)
    {
        if (events[i].getEventId() == eid)
            return i;
    }

    return -1;
}


// ========================================
// CHECK STUDENT ATTENDANCE
// ========================================

bool studentWasPresent(string sid, string eid)
{
    for (int i = 0; i < attendanceRecords.size(); i++)
    {
        if (attendanceRecords[i].getStudentId() == sid &&
            attendanceRecords[i].getEventId() == eid &&
            attendanceRecords[i].getStatus() == "Present")
        {
            return true;
        }
    }

    return false;
}


// ========================================
// VIEW MY ATTENDANCE
// ========================================

void viewMyAttendance(string sid)
{
    int count = 0;

    cout << "\n========== MY ATTENDANCE ==========\n";

    for (int i = 0; i < attendanceRecords.size(); i++)
    {
        if (attendanceRecords[i].getStudentId() == sid)
        {
            string eid = attendanceRecords[i].getEventId();

            cout << "\nEvent ID: " << eid;

            int index = findStudentRecordEvent(eid);

            if (index != -1)
            {
                cout << "\nEvent Name: "
                     << events[index].getName();
            }

            cout << "\nAttendance: "
                 << attendanceRecords[i].getStatus();

            cout << "\nDate: "
                 << attendanceRecords[i].getDate();

            cout << "\n-----------------------------\n";

            count++;
        }
    }

    if (count == 0)
    {
        cout << "No attendance records found.\n";
    }
}


// ========================================
// VIEW MY CERTIFICATES
// ========================================

void viewMyCertificates(string sid)
{
    int count = 0;

    cout << "\n========== MY CERTIFICATES ==========\n";

    for (int i = 0; i < certificates.size(); i++)
    {
        if (certificates[i].getStudentId() == sid)
        {
            string eid = certificates[i].getEventId();

            cout << "\nCertificate ID: "
                 << certificates[i].getCertificateId();

            int index = findStudentRecordEvent(eid);

            if (index != -1)
            {
                cout << "\nEvent Name: "
                     << events[index].getName();

                cout << "\nEvent Date: "
                     << events[index].getDate();
            }

            cout << "\n-----------------------------\n";

            count++;
        }
    }

    if (count == 0)
    {
        cout << "No certificates generated yet.\n";
    }
}


// ========================================
// CHECK EXISTING FEEDBACK
// ========================================

bool studentFeedbackExists(string sid, string eid)
{
    for (int i = 0; i < feedbacks.size(); i++)
    {
        if (feedbacks[i].getStudentId() == sid &&
            feedbacks[i].getEventId() == eid)
        {
            return true;
        }
    }

    return false;
}


// ========================================
// GENERATE FEEDBACK ID
// ========================================

string generateStudentFeedbackId()
{
    return "FB" + to_string(101 + feedbacks.size());
}


// ========================================
// SUBMIT EVENT FEEDBACK
// ========================================

void submitStudentEventFeedback(string sid)
{
    string eid;
    string message;

    cout << "\n========== AVAILABLE EVENTS ==========\n";

    bool found = false;

    for (int i = 0; i < attendanceRecords.size(); i++)
    {
        if (attendanceRecords[i].getStudentId() == sid &&
            attendanceRecords[i].getStatus() == "Present")
        {
            string eventId = attendanceRecords[i].getEventId();

            int index = findStudentRecordEvent(eventId);

            if (index != -1)
            {
                cout << eventId << " - "
                     << events[index].getName() << endl;

                found = true;
            }
        }
    }

    if (!found)
    {
        cout << "No attended events available for feedback.\n";
        return;
    }

    cout << "\nEnter Event ID: ";
    cin >> eid;

    // Check attendance
    if (!studentWasPresent(sid, eid))
    {
        cout << "You must be present at the event to submit feedback.\n";
        return;
    }

    // Check duplicate feedback
    if (studentFeedbackExists(sid, eid))
    {
        cout << "You have already submitted feedback for this event.\n";
        return;
    }

    int index = findStudentRecordEvent(eid);

    if (index == -1)
    {
        cout << "Event not found.\n";
        return;
    }

    cout << "\nPlease submit your feedback.\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, message);

    if (message.empty())
    {
        cout << "Feedback cannot be empty.\n";
        return;
    }

    if (message.find('|') != string::npos)
    {
        cout << "Please do not use the | character in feedback.\n";
        return;
    }

    Feedback f;

    f.setDetails(
        generateStudentFeedbackId(),
        sid,
        eid,
        message,
        getStudentRecordDate()
    );

    feedbacks.push_back(f);

    saveFeedbacks();

    cout << "\nFeedback Submitted Successfully.\n";
}


// ========================================
// STUDENT RECORDS MENU
// ========================================

void studentRecords(string sid)
{
    int choice;

    do
    {
        cout << "\n========== MY RECORDS ==========\n";

        cout << "1. View My Attendance\n";
        cout << "2. View My Certificates\n";
        cout << "3. Submit Event Feedback\n";
        cout << "4. Back\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                viewMyAttendance(sid);
                break;

            case 2:
                viewMyCertificates(sid);
                break;

            case 3:
                submitStudentEventFeedback(sid);
                break;

            case 4:
                cout << "Returning to Student Dashboard.\n";
                break;

            default:
                cout << "Invalid Choice.\n";
        }

    } while (choice != 4);
}

#endif
