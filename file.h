#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "entitie.h"

using namespace std;




extern vector<Student> students;
extern vector<Faculty> faculties;
extern vector<Club> clubs;
extern vector<Assignment> assignments;
extern vector<Event> events;
extern vector<Registration> registrations;
extern vector<Attendance> attendanceRecords;
extern vector<Certificate> certificates;
extern vector<Feedback> feedbacks;




inline void saveStudents()
{
    ofstream fout("students.txt");

    for (Student s : students)
    {
        fout << s.getStudentId() << "|"
             << s.getName() << "|"
             << s.getGmail() << "|"
             << s.getPassword() << endl;
    }

    fout.close();
}




inline void saveFaculties()
{
    ofstream fout("faculties.txt");

    for (Faculty f : faculties)
    {
        fout << f.getFacultyId() << "|"
             << f.getName() << "|"
             << f.getGmail() << "|"
             << f.getPassword() << endl;
    }

    fout.close();
}



inline void saveClubs()
{
    ofstream fout("clubs.txt");

    for (Club c : clubs)
    {
        fout << c.getClubId() << "|"
             << c.getName() << "|"
             << c.getCategory() << "|"
             << c.getDescription() << endl;
    }

    fout.close();
}




inline void saveAssignments()
{
    ofstream fout("assignments.txt");

    for (Assignment a : assignments)
    {
        fout << a.getFacultyId() << "|"
             << a.getClubId() << endl;
    }

    fout.close();
}




inline void saveEvents()
{
    ofstream fout("events.txt");

    for (Event e : events)
    {
        fout << e.getEventId() << "|"
             << e.getClubId() << "|"
             << e.getName() << "|"
             << e.getDate() << "|"
             << e.getCapacity() << endl;
    }

    fout.close();
}




inline void saveRegistrations()
{
    ofstream fout("registrations.txt");

    for (Registration r : registrations)
    {
        fout << r.getRegistrationId() << "|"
             << r.getStudentId() << "|"
             << r.getTargetId() << "|"
             << r.getType() << "|"
             << r.getStatus() << endl;
    }

    fout.close();
}




inline void saveAttendance()
{
    ofstream fout("attendance.txt");

    for (Attendance a : attendanceRecords)
    {
        fout << a.getEventId() << "|"
             << a.getStudentId() << "|"
             << a.getStatus() << "|"
             << a.getDate() << endl;
    }

    fout.close();
}




inline void saveCertificates()
{
    ofstream fout("certificates.txt");

    for (Certificate c : certificates)
    {
        fout << c.getCertificateId() << "|"
             << c.getEventId() << "|"
             << c.getStudentId() << endl;
    }

    fout.close();
}



inline void saveFeedbacks()
{
    ofstream fout("feedback.txt");

    for (Feedback f : feedbacks)
    {
        fout << f.getFeedbackId() << "|"
             << f.getStudentId() << "|"
             << f.getEventId() << "|"
             << f.getMessage() << "|"
             << f.getDate() << endl;
    }

    fout.close();
}




inline void loadData()
{
    string line;
    string id, name, gmail, password;
    string cid, category, description;
    string fid, eid, date, type, status;
    string target, message;
    string temp;

  

    students.clear();
    faculties.clear();
    clubs.clear();
    assignments.clear();
    events.clear();
    registrations.clear();
    attendanceRecords.clear();
    certificates.clear();
    feedbacks.clear();


    
    ifstream fin("students.txt");

    while (getline(fin, line))
    {
        stringstream ss(line);

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, gmail, '|');
        getline(ss, password, '|');

        Student s;
        s.setDetails(id, name, gmail, password);

        students.push_back(s);
    }

    fin.close();


   

    fin.open("faculties.txt");

    while (getline(fin, line))
    {
        stringstream ss(line);

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, gmail, '|');
        getline(ss, password, '|');

        Faculty f;
        f.setDetails(id, name, gmail, password);

        faculties.push_back(f);
    }

    fin.close();


   
    fin.open("clubs.txt");

    while (getline(fin, line))
    {
        stringstream ss(line);

        getline(ss, cid, '|');
        getline(ss, name, '|');
        getline(ss, category, '|');
        getline(ss, description, '|');

        Club c;
        c.setDetails(cid, name, category, description);

        clubs.push_back(c);
    }

    fin.close();


   

    fin.open("assignments.txt");

    while (getline(fin, line))
    {
        stringstream ss(line);

        getline(ss, fid, '|');
        getline(ss, cid, '|');

        Assignment a;
        a.setDetails(fid, cid);

        assignments.push_back(a);
    }

    fin.close();


   

    fin.open("events.txt");

    while (getline(fin, line))
    {
        stringstream ss(line);

        getline(ss, eid, '|');
        getline(ss, cid, '|');
        getline(ss, name, '|');
        getline(ss, date, '|');
        getline(ss, temp, '|');

        if (temp.empty())
            continue;

        Event e;
        e.setDetails(eid, cid, name, date, stoi(temp));

        events.push_back(e);
    }

    fin.close();


   

    fin.open("registrations.txt");

    while (getline(fin, line))
    {
        stringstream ss(line);

        getline(ss, id, '|');
        getline(ss, fid, '|');
        getline(ss, target, '|');
        getline(ss, type, '|');
        getline(ss, status, '|');

        Registration r;
        r.setDetails(id, fid, target, type, status);

        registrations.push_back(r);
    }

    fin.close();


   

    fin.open("attendance.txt");

    while (getline(fin, line))
    {
        stringstream ss(line);

        getline(ss, eid, '|');
        getline(ss, id, '|');
        getline(ss, status, '|');
        getline(ss, date, '|');

        Attendance a;
        a.setDetails(eid, id, status, date);

        attendanceRecords.push_back(a);
    }

    fin.close();


    

    fin.open("certificates.txt");

    while (getline(fin, line))
    {
        stringstream ss(line);

        getline(ss, id, '|');
        getline(ss, eid, '|');
        getline(ss, fid, '|');

        Certificate c;
        c.setDetails(id, eid, fid);

        certificates.push_back(c);
    }

    fin.close();


   
    fin.open("feedback.txt");

    while (getline(fin, line))
    {
        stringstream ss(line);

        getline(ss, id, '|');
        getline(ss, fid, '|');
        getline(ss, eid, '|');
        getline(ss, message, '|');
        getline(ss, date, '|');

        Feedback f;
        f.setDetails(id, fid, eid, message, date);

        feedbacks.push_back(f);
    }

    fin.close();

}

#endif
