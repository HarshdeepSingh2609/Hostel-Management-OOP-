# 🏫 Hostel & Mess Management System (C++ OOP Project)

A console-based Object-Oriented C++ project to manage hostel accommodations and mess billing for students. Built using modular `.h` and `.cpp` files, demonstrating core C++ concepts like **OOP**, **DSA**, and **file handling**.

---

## 📚 Features

### 👤 Admin Functionalities
- Add student records
- Modify student details
- Delete student data
- View all records
- Manage room allotment
- Generate accommodation bills
- 🔐 Password-protected admin login
- 🔎 Search students by Year of Joining (YOJ)
- 📊 View Top 5 students by highest mess bills
- 🧾 Group students by branch
- 👥 View all roommates of a student

### 👨‍🎓 Student Functionalities
- Login with hashed student ID and password
- View personal student record
- View pending mess & accommodation bills
- Pay mess bills

### 🍽️ Mess Management
- Add / Remove food items
- View mess menu
- Order food items
- Generate mess bills
- Pay mess bills

---

## 💡 OOP Concepts Used

| Concept            | How It’s Used                                                 |
|--------------------|---------------------------------------------------------------|
| **Classes & Objects** | `software`, `hostel`, `mess` classes                        |
| **Inheritance**       | `software` inherits from both `hostel` & `mess`             |
| **Polymorphism**      | `delete_data()` function overridden in both base classes    |
| **Abstraction**       | Logical separation using methods like `bill()` and `menu()` |
| **Encapsulation**     | Data members are private, accessed via public methods       |

---

## 📂 Data Structures & Algorithms Used

| DSA Technique       | Application                                                 |
|---------------------|-------------------------------------------------------------|
| **Sorting (std::sort)**    | Sort students by mess bills or other fields              |
| **Max-Heap (priority_queue)** | Retrieve Top 5 students with highest mess dues          |
| **Binary Search**          | Search students by Year of Joining (YOJ)                 |
| **Hashing (unordered_map)**| Group students by branch                                |
| **File Handling**          | Persistent data storage for student, room & mess data    |

---

## 🔐 Security Features

| Feature                   | Description                                           |
|---------------------------|-------------------------------------------------------|
| **Hashed Passwords**      | Both admin and student passwords are stored securely |
| **Login Validation**      | Ensures only valid credentials can access the system  |

---

## 📈 Analytics Features

| Feature                      | Description                                               |
|------------------------------|-----------------------------------------------------------|
| **Top 5 by Mess Bill**       | Displays students with the highest outstanding bills      |
| **Search by Year of Joining**| Fast YOJ filtering using binary search                    |
| **Group by Branch**          | Organizes student data branch-wise using hash maps       |
| **Roommate Finder**          | View roommates of any student using shared room numbers   |

---

## 🧱 Modularity

The system is split into multiple logical files:
- `main.cpp` – Entry point and login menu
- `software.cpp` – Inherited admin & student system controls
- `hostel.cpp` – Hostel-specific operations (rooms, roommates, billing)
- `mess.cpp` – Food ordering and mess bill calculations
- `*.h` – All corresponding class declarations and definitions

---

## 💻 Tech Stack

- **Language**: C++
- **Paradigm**: Object-Oriented Programming (OOP)
- **Persistence**: File handling using `.txt` files
- **Platform**: Console-based application

---
