# Hostel-Management-OOP
# 🏫 Hostel & Mess Management System (C++ OOP Project)

A console-based Object-Oriented C++ project to manage hostel accommodations and mess billing for students. Built using modularized `.h` and `.cpp` files and demonstrates key OOP concepts such as **inheritance**, **abstraction**, **polymorphism**, and **encapsulation**.

---

## 📚 Features

### 👤 Admin Functionalities
- Add student records
- Modify student details
- Delete student data
- View all records
- Manage room allotment
- Generate accommodation bills

### 👨‍🎓 Student Functionalities
- View their own records (secured by ID and password)
- View pending mess and accommodation bills
- Pay mess bills

### 🍽️ Mess Management
- Add/Remove food items
- View mess menu
- Order food items
- Generate and pay mess bills

---

## 💡 OOP Concepts Used

| Concept        | How It’s Used                              |
|----------------|---------------------------------------------|
| **Classes & Objects** | `software`, `hostel`, `mess` classes |
| **Inheritance** | `software` inherits from `hostel` & `mess` |
| **Polymorphism** | `delete_data()` overridden in both base classes |
| **Abstraction** | Functions like `add_data`, `bill`, `mess_billing` abstract away internal logic |
| **Encapsulation** | Member variables are private, accessed via public methods |

---


