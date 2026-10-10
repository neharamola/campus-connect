# campus-connect
smart club and event management system

## About project

Right now, club and event info at most colleges is scattered everywhere — WhatsApp groups, Instagram posts, notice boards, paper sign-up sheets. Students miss out on events they'd actually want to go to, coordinators are stuck managing attendance by hand in Excel, and when an event fills up there's no fair way to handle people who still want in.

Campus Connect is our attempt at fixing that with one system that handles club/event discovery, registration, waitlists, attendance, and feedback, all in one place.

Some of what it does:
- Browse and search clubs/events, with basic recommendations based on what clubs you're already in
- Register for events, and get added to a fair first-come-first-served waitlist if it's full
- Coordinators can mark attendance
- Students can leave feedback after an event

We built the backend first in plain C++ (OOP + data structures), tested it through a console menu until we were sure it worked, and only then started building the actual UI on top of it.

## Team

- **Member 01** — Core Data & OOP. Built the shared Student/Club/Event classes and the hashmap-based lookups everyone else's code depends on.
- **Member 02** — Registration & Waitlist. Built the queue-based waitlist, registration/cancellation logic, and notifications.
- **Member 03** — Discovery & Recommendation. Search, sorting, and the graph-based recommendation logic.
- **Member 04** — Persistence & QA. Attendance, feedback, saving/loading data from files, and exception handling.

Everyone's handling their module end to end .

