#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "file.h"
#include "admin.h"

#include "faculty_login.h"
#include "f_clubOview.h"
#include "f_eventManage.h"
#include "f_attendance_certificate.h"
#include "f_feedback.h"

#include "student_login.h"
#include "s_clubD.h"
#include "s_recomm.h"
#include "s_Res.h"
#include "s_record.h"

vector<Student> students;
vector<Faculty> faculties;
vector<Club> clubs;
vector<Assignment> assignments;
vector<Event> events;
vector<Registration> registrations;
vector<Attendance> attendanceRecords;
vector<Certificate> certificates;
vector<Feedback> feedbacks;

void facultyDashboard(string fid)
{
    int choice;

    do
    {
        cout << "\n========== FACULTY DASHBOARD ==========\n";

        cout << "1. Club Overview\n";
        cout << "2. Event Management\n";
        cout << "3. Attendance and Certificate\n";
        cout << "4. Feedback\n";
        cout << "5. Logout\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                clubOverview(fid);
                break;

            case 2:
                eventManagement(fid);
                break;

            case 3:
                attendanceCertificateManagement(fid);
                break;

            case 4:
                facultyFeedback(fid);
                break;

            case 5:
                cout << "Faculty Logged Out Successfully.\n";
                break;

            default:
                cout << "Invalid Choice.\n";
        }

    } while (choice != 5);
}

void studentDashboard(string sid)
{
    int choice;

    do
    {
        cout << "\n========== STUDENT DASHBOARD ==========\n";

        cout << "1. Club and Event Discovery\n";
        cout << "2. Recommendation Module\n";
        cout << "3. Registration Management\n";
        cout << "4. My Records\n";
        cout << "5. Logout\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                clubEventDiscovery();
                break;

            case 2:
                recommendationModule();
                break;

            case 3:
                registrationManagement(sid);
                break;

            case 4:
                studentRecords(sid);
                break;

            case 5:
                cout << "Student Logged Out Successfully.\n";
                break;

            default:
                cout << "Invalid Choice.\n";
        }

    } while (choice != 5);
}

void studentAccess()
{
    int choice;
    string sid;

    do
    {
        cout << "\n========== STUDENT ACCESS ==========\n";

        cout << "1. Student Sign in \n";
        cout << "2. Student Login\n";
        cout << "3. Back\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                studentSignup();
                break;

            case 2:
                sid = studentLogin();

                if (sid != "")
                {
                    studentDashboard(sid);
                }

                break;

            case 3:
                cout << "Returning to Main Menu.\n";
                break;

            default:
                cout << "Invalid Choice.\n";
        }

    } while (choice != 3);
}

int main()
{
    int choice;
    string fid;

    // Load all saved data
    loadData();

    do
    {
        cout << "\n========================================\n";
        cout << "       SMART CLUB MANAGEMENT SYSTEM\n";
        cout << "========================================\n";

        cout << "1. Admin Module\n";
        cout << "2. Faculty Module\n";
        cout << "3. Student Module\n";
        cout << "4. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                adminModule();
                break;

            case 2:
                fid = facultyLogin();

                if (fid != "")
                {
                    facultyDashboard(fid);
                }

                break;

            case 3:
                studentAccess();
                break;

            case 4:
                cout << "\nThank you for using "
                     << "Smart Club Management System.\n";
                break;

            default:
                cout << "Invalid Choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
