🎓 Student Management System (C++)
📌 Project Overview

The Student Management System is a menu-driven C++ project that allows users to manage student records. It demonstrates the use of Object-Oriented Programming (OOP), File Handling, Encryption, and CRUD Operations.

This project is useful for beginners to understand how to work with files and implement a complete system with Add, Display, Search, Update, and Delete functionalities.

🚀 Features

➕ Add Student → Enter roll no, name, and marks.

📋 Display All Students → View records in a formatted table.

🔍 Search Student → Search by roll number.

✏️ Update Student → Modify existing student details.

❌ Delete Student → Remove a student’s record.

🔐 File Encryption → Data stored in students.txt is encrypted for basic security.

🏷️ Grade Calculation → Auto-calculates grade based on marks.

🖥️ User-friendly Menu → Clear screen and pause for smooth navigation.

🛠️ Technologies Used

C++ (Core language)

File Handling (Persistent storage)

OOP Concepts (Classes & Objects)

Encryption (Caesar Cipher)

CRUD Operations

📂 Project Structure
Student-Management-System/
│-- main.cpp          # Source code
│-- students.txt      # Encrypted student data file (auto-created)
│-- README.md         # Project documentation

⚡ How to Run

Clone this repository or download the files.

Open a terminal/IDE and compile:

g++ main.cpp -o sms


Run the executable:

./sms


Use the menu to manage student records.

📊 Sample Output
===== Student Management System =====
1. Add Student
2. Display All Students
3. Search Student
4. Update Student
5. Delete Student
6. Exit
Enter your choice: 1
Enter Roll No: 101
Enter Name: Mayuri Maurya
Enter Marks for 3 subjects (0-100): 95 87 92
Student added successfully!


Formatted Display Example:

Roll      Name                 Marks1    Marks2    Marks3    Grade
----------------------------------------------------------------------
101       Mayuri Maurya        95        87        92        A
102       Sanika Belgavkar     80        85        82        B

📌 Future Enhancements

Add subject-wise dynamic marks entry.

Generate report cards in PDF format.

Integrate with MySQL database.

Add GUI (Qt/GTK) for better usability.

👩‍💻 Author
Mayuri Maurya
B.Sc.IT (2nd Yeaer)

If you like this project, don't forget to star the repo!

