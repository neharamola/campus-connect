#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Student {
    int id;
    string name;
    int total = 0;
    int present = 0;
};

struct Feedback {
    int studentId;
    int rating;
    string comment;
};

class AttendanceService {
private:
    vector<Student> students;

public:
    void addStudent(int id, string name) {
        Student s;
        s.id = id;
        s.name = name;
s.total = 0;
s.present = 0;
students.push_back(s);
        cout << "Student added successfully!\n";
    }

    void markAttendance(int id, char status) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            students[i].total++;

            if (status == 'Y' || status == 'y') {
                students[i].present++;
            }

            cout << "Attendance marked!\n";
            return;
        }
    }

    cout << "Student not found!\n";
}


    void displayAttendance() {
    for (int i = 0; i < students.size(); i++) {
        double percentage = 0;

        if (students[i].total > 0) {
            percentage =
                (double)students[i].present /
                students[i].total * 100;
        }

        cout << "\nID: " << students[i].id;
        cout << "\nName: " << students[i].name;
        cout << "\nAttendance: "
             << percentage << "%";

        cout << "\nCertificate Eligible: "
             << (percentage >= 75 ? "Yes" : "No")
             << "\n";
    }
}
};

class FeedbackService {
private:
    vector<Feedback> feedbackList;

public:
    void submitFeedback(int id, int rating, string comment) {
        if (rating < 1 || rating > 5) {
            cout << "Rating must be between 1 and 5!\n";
            return;
        }

        Feedback f;
f.studentId = id;
f.rating = rating;
f.comment = comment;
feedbackList.push_back(f);
        cout << "Feedback submitted successfully!\n";
    }

   void displayFeedback() {
    for (int i = 0; i < feedbackList.size(); i++) {
        cout << "\nStudent ID: "
             << feedbackList[i].studentId
             << "\nRating: "
             << feedbackList[i].rating << "/5"
             << "\nComment: "
             << feedbackList[i].comment << "\n";
    }
}

    void averageRating() {
    if (feedbackList.empty()) {
        cout << "No feedback available!\n";
        return;
    }

    int total = 0;

    for (int i = 0; i < feedbackList.size(); i++) {
        total += feedbackList[i].rating;
    }

    cout << "Average Rating: "
         << (double)total / feedbackList.size()
         << "/5\n";
}
};

int main() {
    AttendanceService attendance;
    FeedbackService feedback;

    int choice;

    do {
        cout << "\n--- Attendance & Feedback System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Mark Attendance\n";
        cout << "3. Display Attendance\n";
        cout << "4. Submit Feedback\n";
        cout << "5. Display Feedback\n";
        cout << "6. Average Rating\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter name: ";
            getline(cin >> ws, name);
            attendance.addStudent(id, name);
        }
        else if (choice == 2) {
            int id;
            char status;
            cout << "Enter student ID: ";
            cin >> id;
            cout << "Present? (Y/N): ";
            cin >> status;
            attendance.markAttendance(id, status);
        }
        else if (choice == 3) {
            attendance.displayAttendance();
        }
        else if (choice == 4) {
            int id, rating;
            string comment;
            cout << "Enter student ID: ";
            cin >> id;
            cout << "Enter rating (1-5): ";
            cin >> rating;
            cout << "Enter comment: ";
            getline(cin >> ws, comment);
            feedback.submitFeedback(id, rating, comment);
        }
        else if (choice == 5) {
            feedback.displayFeedback();
        }
        else if (choice == 6) {
            feedback.averageRating();
        }
        else if (choice != 0) {
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
