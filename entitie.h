#ifndef ENTITIES_H
#define ENTITIES_H

#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    string studentId;
    string name;
    string gmail;
    string password;

public:
    void setDetails(string id, string n, string g, string p)
    {
        studentId = id;
        name = n;
        gmail = g;
        password = p;
    }

    string getStudentId() { return studentId; }
    string getName() { return name; }
    string getGmail() { return gmail; }
    string getPassword() { return password; }
    void setPassword(string p) { password = p; }
};

class Faculty
{
private:
    string facultyId;
    string name;
    string gmail;
    string password;

public:
    void setDetails(string id, string n, string g, string p)
    {
        facultyId = id;
        name = n;
        gmail = g;
        password = p;
    }

    string getFacultyId() { return facultyId; }
    string getName() { return name; }
    string getGmail() { return gmail; }
    string getPassword() { return password; }
    void setPassword(string p) { password = p; }
};

class Club
{
private:
    string clubId;
    string name;
    string category;
    string description;

public:
    void setDetails(string id, string n, string c, string d)
    {
        clubId = id;
        name = n;
        category = c;
        description = d;
    }

    string getClubId() { return clubId; }
    string getName() { return name; }
    string getCategory() { return category; }
    string getDescription() { return description; }
};

class Assignment
{
private:
    string facultyId;
    string clubId;

public:
    void setDetails(string fid, string cid)
    {
        facultyId = fid;
        clubId = cid;
    }

    string getFacultyId() { return facultyId; }
    string getClubId() { return clubId; }
};

class Event
{
private:
    string eventId;
    string clubId;
    string name;
    string date;
    int capacity;

public:
    void setDetails(string eid, string cid, string n,
                    string d, int cap)
    {
        eventId = eid;
        clubId = cid;
        name = n;
        date = d;
        capacity = cap;
    }

    string getEventId() { return eventId; }
    string getClubId() { return clubId; }
    string getName() { return name; }
    string getDate() { return date; }
    int getCapacity() { return capacity; }

    void setDate(string d) { date = d; }
};

class Registration
{
private:
    string registrationId;
    string studentId;
    string targetId;
    string type;
    string status;

public:
    void setDetails(string rid, string sid, string tid,
                    string t, string s)
    {
        registrationId = rid;
        studentId = sid;
        targetId = tid;
        type = t;
        status = s;
    }

    string getRegistrationId() { return registrationId; }
    string getStudentId() { return studentId; }
    string getTargetId() { return targetId; }
    string getType() { return type; }
    string getStatus() { return status; }

    void setStatus(string s) { status = s; }
};

class Attendance
{
private:
    string eventId;
    string studentId;
    string status;
    string date;

public:
    void setDetails(string eid, string sid, string s, string d)
    {
        eventId = eid;
        studentId = sid;
        status = s;
        date = d;
    }

    string getEventId() { return eventId; }
    string getStudentId() { return studentId; }
    string getStatus() { return status; }
    string getDate() { return date; }

    void setStatus(string s) { status = s; }
};

class Certificate
{
private:
    string certificateId;
    string eventId;
    string studentId;

public:
    void setDetails(string cid, string eid, string sid)
    {
        certificateId = cid;
        eventId = eid;
        studentId = sid;
    }

    string getCertificateId() { return certificateId; }
    string getEventId() { return eventId; }
    string getStudentId() { return studentId; }
};

class Feedback
{
private:
    string feedbackId;
    string studentId;
    string eventId;
    string message;
    string date;

public:
    void setDetails(string fid, string sid, string eid,
                    string msg, string d)
    {
        feedbackId = fid;
        studentId = sid;
        eventId = eid;
        message = msg;
        date = d;
    }

    string getFeedbackId() { return feedbackId; }
    string getStudentId() { return studentId; }
    string getEventId() { return eventId; }
    string getMessage() { return message; }
    string getDate() { return date; }
};

#endif
