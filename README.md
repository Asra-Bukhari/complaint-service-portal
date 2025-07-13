# Complaint Service Portal

A console-based Complaint Management System developed in **C++** using core data structures. This was a semester project focused on building a practical and efficient system to handle user complaints with registration, retrieval, prioritization, and country-wise filtering features.

---

## 🛠️ Project Versions

### 🔹 `code.cpp`
Implements complaint management using:
- **AVL Trees** – for balanced complaint ID storage and fast search.
- **Priority Queues** – to manage urgent complaints efficiently.
- **Linked Lists** – to track user data and general storage.
- **Manual Lookup** – to retrieve user or complaint info by country or name.

### 🔹 `hashedCode.cpp`
An **optimized version** using:
- **Hash Tables** – for O(1) complaint/user ID lookups.
- Same complaint/user features as the base version, but with **improved performance**.

---

## 🎯 Features

- **Register a New User**
- **Register a New Complaint** with priority and country
- **View All Registered Users**
- **View All Complaints**
- **Search Complaints** by:
  - User name
  - Country
  - Complaint ID
- **Increase Complaint Priority**
- **Efficient Retrieval**:
  - By AVL Tree or Hashing (depending on version)
- **Complaint Status Service**:
  - Serve and update high-priority complaints first

---

## 💻 How to Run (Visual Studio)

> **Note**: Project is developed for Windows using **Visual Studio**

### 🔧 Steps:

1. Open **Visual Studio**
2. Create a new **C++ Console Application**
3. Delete the default `main.cpp`
4. Add either `code.cpp` *or* `hashedCode.cpp`:
   - Right-click on **Source Files > Add > Existing Item...**
   - Select your file (e.g., `hashedCode.cpp`)
5. Right-click the file and choose **"Set as Startup Item"**
6. Click **Build > Build Solution** (or press `Ctrl+Shift+B`)
7. Run using **Ctrl + F5** (Start Without Debugging)

---

## 📁 Project Structure

```bash
├── code.cpp            # Version using AVL tree, priority queue, linked list
├── hashedCode.cpp      # Version using hash tables for faster retrieval
└── README.md           # Project documentation
```

## 🧠 Data Structures Used

| **Data Structure**  | **Purpose in the System**                                                                                            |
| ------------------- | -------------------------------------------------------------------------------------------------------------------- |
| **AVL Tree**        | To store complaints in a balanced binary search tree, ensuring fast insertion, deletion, and search by Complaint ID. |
| **Hash Table**      | Used in the `hashedCode.cpp` version to enable constant-time (`O(1)`) lookup for complaints and users by ID.         |
| **Priority Queue**  | To automatically prioritize and serve high-priority complaints before lower ones.                                    |
| **Linked List**     | For maintaining sequences of users and complaints in insertion order (especially for viewing all data).              |
| **String Matching** | Used to search complaints by country or user name through linear or hash-based lookup.                               |

---

## 🌍 Use Case Examples

- Complaint registration by users in multiple countries
- Automatic prioritization and servicing of urgent cases
- Filtering complaints by user or region
- Efficient record lookups by complaint ID or user

---

## 💡 Future Enhancements

- 🔐 User authentication and roles (admin, user)
- 💾 File-based persistence
- 🌐 UI or GUI integration
- 🗂️ Complaint category tagging and status updates

---

## 👩‍🎓 Author

**Asra Bukhari**  
This project was built as a semester-long submission for the **Data Structures** course.

- GitHub: [@Asra-Bukhari](https://github.com/Asra-Bukhari)
- Repo: [Complaint Management System](https://github.com/Asra-Bukhari/complaint-service-portal)

---

## 📜 License

This project is open-source and available for use in learning, research, and educational projects. Attribution is appreciated.

