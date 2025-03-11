<h1 align="center"><b>Hey </b><img src="https://media.giphy.com/media/hvRJCLFzcasrR4ia7z/giphy.gif" width="35"></h1>

## 📋 Project Description

We are Team 1 in the C++ Project. Our project focuses on creating a user management system that includes user registration, login, and password management functionalities.

**About Us**  
We are a dedicated team working on a C++ project to build a robust user management system.

<div align="center">
    <img src="Diagram.png" width="500px" alt="Team Work Animation">
</div>

<h1 align=center>User Authentication System</h1> 

This project is a simple user authentication system implemented in C++. It allows users to register with a username and password, and then log in using their credentials. The system uses file-based storage to persist user data and includes basic password hashing and validation.

## Features
- **User Registration**: Users can register with a unique username and a password that meets specific complexity requirements.
- **User Login**: Registered users can log in using their username and password.
- **Password Hashing**: Passwords are hashed using a custom hashing algorithm combined with a randomly generated salt.
- **Password Validation**: Passwords must meet complexity requirements (minimum length, uppercase, lowercase, digits, and special characters).
- **File-based Storage**: User data is stored in a text file (`dataset.txt`).

## Classes and Components

### Istorage (Interface)
**Purpose**: Defines the interface for storage operations.

**Methods**:
- `addUser`: Adds a new user to the storage.
- `getdata`: Retrieves all user data from storage.
- `userExists`: Checks if a user exists in the storage.
- `getUserInfo`: Retrieves user information (hashed password and salt) by username.

### FileManager (Class)
**Purpose**: Implements the `Istorage` interface to manage user data in a file.

**Methods**:
- `addUser`: Adds a new user to the file.
- `getdata`: Reads all user data from the file.
- `userExists`: Checks if a user exists in the file.
- `getUserInfo`: Retrieves user information from the file.

### SaltGenerator (Class)
**Purpose**: Generates a random salt for password hashing.

**Methods**:
- `generateSalt`: Generates a random string of specified length.

### IHash (Interface)
**Purpose**: Defines the interface for password hashing.

**Methods**:
- `hashPassword`: Hashes the password.

### Hasher (Class)
**Purpose**: Implements the `IHash` interface to hash passwords using a custom algorithm.

**Methods**:
- `hashPassword`: Hashes the password by alternating characters with the salt and converting the result to a hexadecimal string.

### IValidator (Interface)
**Purpose**: Defines the interface for input validation.

**Methods**:
- `validate`: Validates the input (e.g., password).

### PasswordValidator (Class)
**Purpose**: Implements the `IValidator` interface to validate passwords.

**Methods**:
- `validate`: Ensures the password meets complexity requirements.

### IuserService (Interface)
**Purpose**: Defines the interface for user-related services.

**Methods**:
- `RegisterUser`: Registers a new user.
- `LoginUser`: Logs in an existing user.

### UserService (Class)
**Purpose**: Implements the `IuserService` interface to handle user registration and login.

**Methods**:
- `RegisterUser`: Registers a new user by generating a salt, hashing the password, and storing the user data.
- `LoginUser`: Logs in a user by verifying the username and password.

## SOLID Principles Implementation

### 1. Single Responsibility Principle (SRP)
Each class has a single responsibility and handles one aspect of the system:
- **FileManager** manages file storage operations (reading/writing user data).
- **SaltGenerator** is responsible for generating salts for password hashing.
- **Hasher** is responsible for hashing passwords.
- **PasswordValidator** validates password strength.
- **UserService** is responsible for user registration and login.
- **Istorage**, **IHash**, **IValidator**, and **IuserService** act as interfaces, ensuring that each class follows a specific contract.

🔹 **SRP is followed well** because each class has a distinct role.

---

### 2. Open/Closed Principle (OCP)
Your system is open for extension but closed for modification, meaning you can extend functionalities without modifying existing code:
- New hashing algorithms can be implemented by extending **IHash**.
- Different storage mechanisms (e.g., database, cloud storage) can be implemented by extending **Istorage**.
- Password validation rules can be modified by implementing a new validator class.

🔹 **OCP is well applied** because interfaces allow easy extension without modifying existing logic.

---

### 3. Liskov Substitution Principle (LSP)
LSP states that subtypes should be substitutable for their base types without breaking the program:
- **FileManager** correctly extends **Istorage**, meaning it can be used anywhere an **Istorage** is expected.
- **Hasher** correctly extends **IHash**, so another hashing algorithm can replace it without breaking functionality.
- **PasswordValidator** extends **IValidator**, allowing other validation mechanisms to be used interchangeably.

🔹 **LSP is followed**, as derived classes can replace base class references without issues.

---

### 4. Interface Segregation Principle (ISP)
ISP states that clients should not be forced to depend on interfaces they do not use:
- The interfaces (**Istorage**, **IHash**, **IValidator**, **IuserService**) ensure that each class implements only the methods it needs.
- For example, **Hasher** only deals with hashing, while **FileManager** handles storage.

🔹 **ISP is well implemented** since interfaces are properly separated based on functionality.

---

### 5. Dependency Inversion Principle (DIP)
DIP states that high-level modules should not depend on low-level modules; both should depend on abstractions:
- **UserService** depends on **Istorage** (instead of **FileManager** directly).
- **Hasher** is abstracted through **IHash**, making it easy to switch to another hashing technique.
- **PasswordValidator** implements **IValidator**, making password validation logic flexible.

🔹 **DIP is partially applied**. However, **UserService** directly instantiates **FileManager**, which could be improved by injecting dependencies.

---

## Usage

### Compile the Code:
```bash
g++ -o user_auth main.cpp
