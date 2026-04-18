# 🏦 C Banking System

A modular console-based banking system written in C with file handling and transaction tracking.

---

## 🔥 Key Highlights

* Modular architecture (account, transaction, file modules)
* Transaction logging with timestamps
* Secure PIN-based authentication
* Input validation to prevent crashes

---

## 📸 Sample Output

```
1.Create Account
2.Deposit
3.Withdraw
4.Transfer
5.View Accounts
6.View Transactions
7.Exit
```

---

## 🚀 Features

* Create Account with PIN
* Deposit & Withdraw Money
* Transfer Money Between Accounts
* Transaction History with Timestamp
* Persistent Storage using Files

---

## 📁 Project Structure

```
c-banking-system/
├── main.c
├── account.c / account.h
├── file.c / file.h
├── transaction.c / transaction.h
```

---

## 🛠️ How to Run

```bash
gcc main.c account.c file.c transaction.c -o bank
./bank
```

---

## ⚙️ Technologies Used

* C Programming
* File Handling

---

## 🧠 What I Learned

* Modular programming in C
* File handling for persistent storage
* Managing multi-file projects
* Handling user input safely

---

## 📌 Notes

* Data is stored locally using files
* No database used (can be extended)
* Designed for learning system-level programming
