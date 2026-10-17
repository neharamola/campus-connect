#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include "entities.h"
using namespace std;

// Manages one event using the classes from entities.h.
// Waitlist = unconfirmed Registrations, kept in the order they were added.
class EventManager
{
private:
    Event event;
    vector<Student> students;
    vector<Registration> registrations;
    queue<Notification> notifications;
    int nextStudentId;
    int nextRegId;

    int findStudentId(const string& name) const
    {
        for (size_t i = 0; i < students.size(); i++)
            if (students[i].getName() == name) return students[i].getId();
        return -1;
    }
    string nameOf(int studentId) const
    {
        for (size_t i = 0; i < students.size(); i++)
            if (students[i].getId() == studentId) return students[i].getName();
        return "Unknown";
    }
    int confirmedCount() const
    {
        int c = 0;
        for (size_t i = 0; i < registrations.size(); i++)
            if (registrations[i].isConfirmed()) c++;
        return c;
    }
    int waitingCount() const
    {
        return (int)registrations.size() - confirmedCount();
    }
    int findRegistrationIndex(int studentId) const
    {
        for (size_t i = 0; i < registrations.size(); i++)
            if (registrations[i].getStudentId() == studentId) return (int)i;
        return -1;
    }

public:
    EventManager(const Event& e) : event(e), nextStudentId(1), nextRegId(1) {}

    void registerStudent(const string& name)
    {
        int sid = findStudentId(name);
        if (sid != -1 && findRegistrationIndex(sid) != -1)
        {
            cout << name << " is already registered or on the waitlist." << endl;
            return;
        }
        if (sid == -1)
        {
            sid = nextStudentId++;
            students.push_back(Student(sid, name, ""));
        }
        if (confirmedCount() < event.getCapacity())
        {
            registrations.push_back(Registration(nextRegId++, sid, event.getId(), true));
            cout << name << " registered successfully." << endl;
        }
        else
        {
            registrations.push_back(Registration(nextRegId++, sid, event.getId(), false));
            cout << name << " added to waitlist (position " << waitingCount() << ")." << endl;
        }
    }

    void cancelRegistration(const string& name)
    {
        int sid = findStudentId(name);
        int idx = (sid == -1) ? -1 : findRegistrationIndex(sid);
        if (idx == -1)
        {
            cout << name << " is not registered for this event." << endl;
            return;
        }
        bool wasConfirmed = registrations[idx].isConfirmed();
        registrations.erase(registrations.begin() + idx);

        if (!wasConfirmed)
        {
            cout << name << " removed from waitlist." << endl;
            return;
        }
        cout << name << " cancelled registration." << endl;

        // Promote the first waitlisted student (first unconfirmed registration)
        for (size_t i = 0; i < registrations.size(); i++)
        {
            if (!registrations[i].isConfirmed())
            {
                registrations[i].setConfirmed(true);
                string next = nameOf(registrations[i].getStudentId());
                notifications.push(Notification(registrations[i].getStudentId(),
                                                "Seat available! You are registered."));
                cout << next << " promoted from waitlist." << endl;
                break;
            }
        }
    }

    void showWaitlist() const
    {
        if (waitingCount() == 0)
        {
            cout << "Waitlist is empty." << endl;
            return;
        }
        cout << "Current Waitlist:" << endl;
        int pos = 1;
        for (size_t i = 0; i < registrations.size(); i++)
            if (!registrations[i].isConfirmed())
                cout << pos++ << ". " << nameOf(registrations[i].getStudentId()) << endl;
    }

    void showNotifications()
    {
        if (notifications.empty())
        {
            cout << "No notifications." << endl;
            return;
        }
        cout << "Notifications:" << endl;
        while (!notifications.empty())
        {
            cout << nameOf(notifications.front().getStudentId())
                 << " -> " << notifications.front().getMessage() << endl;
            notifications.pop();
        }
    }

    void showStatus() const
    {
        cout << "Event: " << event.getName()
             << " (" << event.getCategory() << ", " << event.getDate() << ")" << endl;
        cout << "Registered: " << confirmedCount() << "/" << event.getCapacity() << endl;
        cout << "Waiting: " << waitingCount() << endl;
    }
};

int main()
{
    // Event(id, name, date, category, clubId, capacity, registrationCount)
    Event robotics(1, "Robotics Workshop", "2026-11-05", "Technical", 1, 3, 0);
    EventManager workshop(robotics);

    int choice = -1;
    string name;

    do
    {
        cout << "\n===== CAMPUS CONNECT =====" << endl;
        cout << "1. Register Student" << endl
             << "2. Cancel Registration" << endl
             << "3. Show Waitlist" << endl
             << "4. Show Notifications" << endl
             << "5. Show Event Status" << endl
             << "0. Exit" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            choice = -1;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            cout << "Student Name: ";
            getline(cin, name);
            workshop.registerStudent(name);
            break;
        case 2:
            cout << "Student Name: ";
            getline(cin, name);
            workshop.cancelRegistration(name);
            break;
        case 3: workshop.showWaitlist(); break;
        case 4: workshop.showNotifications(); break;
        case 5: workshop.showStatus(); break;
        case 0: cout << "Goodbye!" << endl; break;
        default: cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}
