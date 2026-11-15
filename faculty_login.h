#ifndef FACULTY_AUTH_H
#define FACULTY_AUTH_H

#include "file.h"
#include <iostream>
#include <string>

using namespace std;

inline string facultyLogin()
{
    string gmail, password;

    cout << "\n========== FACULTY LOGIN ==========\n";

    cout << "Enter Gmail: ";
    cin >> gmail;

    cout << "Enter Password: ";
    cin >> password;

    for (auto f : faculties)
    {
        if (f.getGmail() == gmail &&
            f.getPassword() == password)
        {
            cout << "\nSign-in successfully, now logging your account.\n";
            cout << "Welcome, " << f.getName() << "!\n";

            return f.getFacultyId();
        }
    }

    cout << "\nInvalid Gmail or Password.\n";
    return "";
}

#endif
