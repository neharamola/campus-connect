#ifndef ATTENDANCE_CERTIFICATE_H
#define ATTENDANCE_CERTIFICATE_H

#include "file.h"
#include <iostream>
#include <string>
#include <ctime>
#include <limits>

using namespace std;


inline string getAttendanceDate()
{
    time_t now = time(0);
    tm *t = localtime(&now);

    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", t);

    return date;
}


inline string findAttendanceClub(string fid)
{
    for (size_t i = 0; i < assignments.size(); i++)
    {
        if (assignments[i].getFacultyId() == fid)
        {
            return assignments[i].getClubId();
        }
    }

    return "";
}


inline int findAttendanceEvent(string eid)
{
    for (size_t i = 0; i < events.size(); i++)
    {
        if (events[i].getEventId() == eid)
        {
            return i;
        }
    }

    return -1;
}


inline int findAttendanceRecord(string eid, string sid)
{
    for (size_t i = 0; i < attendanceRecords.size(); i++)
    {
        if (attendanceRecords[i].getEventId() == eid &&
            attendanceRecords[i].getStudentId() == sid)
        {
            return i;
        }
    }

    return -1;
}


inline bool attendanceCertificateExists(string eid, string sid)
{
    for (size_t i = 0; i < certificates.size(); i++)
    {
        if (certificates[i].getEventId() == eid &&
            certificates[i].getStudentId() == sid)
        {
            return true;
        }
    }

    return false;
}


inline string generateAttendanceCertificateId()
{
    return "CERT" + to_string(101 + certificates.size());
}



inline void markEventAttendance(string fid)
{
    string cid = findAttendanceClub(fid);

    if (cid == "")
    {
        cout << "No club assigned to this faculty.\n";
        return;
    }

    string eid;

    cout << "\n========== FACULTY EVENTS ==========\n";

    bool found = false;

    for (size_t i = 0; i < events.size(); i++)
    {
        if (events[i].getClubId() == cid)
        {
            cout << events[i].getEventId() << " - "
                 << events[i].getName() << " - "
                 << events[i].getDate() << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "No events available.\n";
        return;
    }

    cout << "\nEnter Event ID: ";
    cin >> eid;

    int index = findAttendanceEvent(eid);

    if (index == -1 || events[index].getClubId() != cid)
    {
        cout << "Invalid Event ID.\n";
        return;
    }

    int count = 0;

    cout << "\n========== MARK ATTENDANCE ==========\n";

    for (size_t i = 0; i < registrations.size(); i++)
    {
        if (registrations[i].getTargetId() == eid &&
            registrations[i].getType() == "Event" &&
            registrations[i].getStatus() == "Active")
        {
            string sid = registrations[i].getStudentId();
            string status;

            cout << "\nStudent ID: " << sid;

            for (size_t j = 0; j < students.size(); j++)
            {
                if (students[j].getStudentId() == sid)
                {
                    cout << "\nStudent Name: "
                         << students[j].getName();
                    break;
                }
            }

            cout << "\nEnter P for Present or A for Absent: ";
            cin >> status;

            if (status == "P" || status == "p")
                status = "Present";
            else if (status == "A" || status == "a")
                status = "Absent";
            else
            {
                cout << "Invalid attendance. Skipped.\n";
                continue;
            }

            int recordIndex = findAttendanceRecord(eid, sid);

            if (recordIndex == -1)
            {
                Attendance a;

                a.setDetails(
                    eid,
                    sid,
                    status,
                    getAttendanceDate()
                );

                attendanceRecords.push_back(a);
            }
            else
            {
                attendanceRecords[recordIndex].setStatus(status);
            }

            count++;
        }
    }

    if (count == 0)
    {
        cout << "\nNo active event registrations found.\n";
        return;
    }

    saveAttendance();

    cout << "\nAttendance Saved Successfully.\n";
}



inline void viewEventAttendance(string fid)
{
    string cid = findAttendanceClub(fid);

    if (cid == "")
    {
        cout << "No club assigned to this faculty.\n";
        return;
    }

    int count = 0;

    cout << "\n========== EVENT ATTENDANCE ==========\n";

    for (size_t i = 0; i < attendanceRecords.size(); i++)
    {
        string eid = attendanceRecords[i].getEventId();
        int index = findAttendanceEvent(eid);

        if (index != -1 && events[index].getClubId() == cid)
        {
            cout << "\nEvent ID: " << eid;
            cout << "\nStudent ID: "
                 << attendanceRecords[i].getStudentId();
            cout << "\nStatus: "
                 << attendanceRecords[i].getStatus();
            cout << "\nDate: "
                 << attendanceRecords[i].getDate();
            cout << "\n-----------------------------\n";

            count++;
        }
    }

    if (count == 0)
        cout << "No attendance records found.\n";
}



inline void generateEventCertificates(string fid)
{
    string cid = findAttendanceClub(fid);

    if (cid == "")
    {
        cout << "No club assigned to this faculty.\n";
        return;
    }

    int count = 0;

    for (size_t i = 0; i < attendanceRecords.size(); i++)
    {
        string eid = attendanceRecords[i].getEventId();
        string sid = attendanceRecords[i].getStudentId();

        int index = findAttendanceEvent(eid);

        if (index != -1 &&
            events[index].getClubId() == cid &&
            attendanceRecords[i].getStatus() == "Present")
        {
            if (!attendanceCertificateExists(eid, sid))
            {
                Certificate c;

                c.setDetails(
                    generateAttendanceCertificateId(),
                    eid,
                    sid
                );

                certificates.push_back(c);
                count++;
            }
        }
    }

    if (count == 0)
    {
        cout << "\nNo new certificates to generate.\n";
    }
    else
    {
        saveCertificates();

        cout << "\n" << count
             << " Certificate(s) Generated Successfully.\n";
    }
}



inline void viewEventCertificates(string fid)
{
    string cid = findAttendanceClub(fid);

    if (cid == "")
    {
        cout << "No club assigned to this faculty.\n";
        return;
    }

    int count = 0;

    cout << "\n========== GENERATED CERTIFICATES ==========\n";

    for (size_t i = 0; i < certificates.size(); i++)
    {
        string eid = certificates[i].getEventId();
        int index = findAttendanceEvent(eid);

        if (index != -1 && events[index].getClubId() == cid)
        {
            cout << "\nCertificate ID: "
                 << certificates[i].getCertificateId();

            cout << "\nEvent Name: "
                 << events[index].getName();

            cout << "\nStudent ID: "
                 << certificates[i].getStudentId();

            cout << "\n-----------------------------\n";

            count++;
        }
    }

    if (count == 0)
        cout << "No certificates generated yet.\n";
}



inline void attendanceCertificateManagement(string fid)
{
    string cid = findAttendanceClub(fid);

    if (cid == "")
    {
        cout << "\nNo club assigned to this faculty.\n";
        return;
    }

    int choice;

    do
    {
        cout << "\n========== ATTENDANCE AND CERTIFICATES ==========\n";

        cout << "1. Mark Event Attendance\n";
        cout << "2. View Event Attendance\n";
        cout << "3. Generate Certificates\n";
        cout << "4. View Generated Certificates\n";
        cout << "5. Back\n";

        cout << "Enter choice: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice)
        {
            case 1:
                markEventAttendance(fid);
                break;

            case 2:
                viewEventAttendance(fid);
                break;

            case 3:
                generateEventCertificates(fid);
                break;

            case 4:
                viewEventCertificates(fid);
                break;

            case 5:
                cout << "Returning to Faculty Dashboard.\n";
                break;

            default:
                cout << "Invalid Choice.\n";
        }

    } while (choice != 5);
}

#endif