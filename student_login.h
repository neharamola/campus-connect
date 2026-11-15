#ifndef STUDENT_AUTH_H
#define STUDENT_AUTH_H

#include "file.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

inline void studentSignup()
{
    string id, name, gmail, password, confirm;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nEnter Student ID: ";
    getline(cin, id);

    for (auto s : students)
    {
        if (s.getStudentId() == id)
        {
            cout << "Student ID already registered.\n";
            return;
        }
    }

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Gmail: ";
    getline(cin, gmail);

    if (gmail.size() < 10 ||
        gmail.substr(gmail.size() - 10) != "@gmail.com")
    {
        cout << "Please enter a valid Gmail.\n";
        return;
    }

    for (auto s : students)
    {
        if (s.getGmail() == gmail)
        {
            cout << "Gmail already registered.\n";
            return;
        }
    }

    cout << "Create Password: ";
    getline(cin, password);

    cout << "Confirm Password: ";
    getline(cin, confirm);

    if (password != confirm)
    {
        cout << "Passwords do not match.\n";
        return;
    }

    Student s;
    s.setDetails(id, name, gmail, password);

    students.push_back(s);
    saveStudents();

    cout << "\nStudent Sign in Successfully!\n";
}

inline string studentLogin()
{
    string id, password;

    cout << "\nEnter Student ID: ";
    cin >> id;

    cout << "Enter Password: ";
    cin >> password;

    for (auto s : students)
    {
        if (s.getStudentId() == id &&
            s.getPassword() == password)
        {
            cout << "\nLogin Successful!\n";
            cout << "Welcome, " << s.getName() << "!\n";

            return s.getStudentId();
        }
    }

    cout << "\nInvalid Student ID or Password.\n";
    return "";
}

#endif
