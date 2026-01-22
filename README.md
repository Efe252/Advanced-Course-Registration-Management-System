NAME: EDERAGOGHENE EFEOGHENE IFECHUKWUDE

MATRIC NUMBER: 25/18368

URL:https://github.com/Efe252/Course-Registration-Management-System
**LIVE WEBSITE:** https://coursems.edgeone.app

# **SOFTWARE DEVELOPMENT LIFE CYCLE (SDLC)**

**Project Title:** *Course Registration Management System*
**SDLC Model Used:** *Waterfall Model*

---

## **1. Requirement Analysis**

The requirement analysis phase involves identifying and documenting the needs of users and the problems associated with manual course registration.

### **Problem Description**

In many academic institutions, course registration is performed manually. This process is slow, prone to errors such as duplicate registrations, missing records, and difficulty in tracking registered courses. There is a need for a computerized system to automate the course registration process.

---

### **Functional Requirements**

The Course Registration Management System shall:

* Allow entry of student names.
* Allow entry of course names.
* Allow students to register for courses.
* Prevent duplicate course registrations.
* Display registered courses for each student.

---

### **Non-Functional Requirements**

The system shall:

* Be easy to use and understand.
* Be reliable and accurate.
* Respond quickly to user inputs.
* Run on a computer system.
* Be maintainable and scalable.

---

## **2. System Design**

The system design phase defines how the system will be structured to meet the specified requirements.

### **System Architecture**

The system is designed as a **command-line software application** consisting of three major modules:

1. **Input Module**

   * Accepts student names.
   * Accepts course names.

2. **Processing Module**

   * Stores student records.
   * Validates course registration.
   * Prevents duplicate registrations.

3. **Output Module**

   * Displays registered courses for each student.

---

### **Data Design**

Each student record contains:

* Student name
* List of registered courses

The data is stored using a dictionary structure where:

```
Student Name → List of Courses
```

---

### **Process Design**

* When a student registers a course, the system checks if the student exists.
* If the student does not exist, a new record is created.
* If the course already exists in the student’s record, registration is denied.
* If not, the course is added to the student’s course list.

---

## **3. Implementation**

The implementation phase involves converting the system design into executable code.
The Course Registration Management System was implemented using the **Python programming language**.

All system terminologies such as *student*, *course*, *registration*, and *duplicate* used during the design phase were maintained consistently in the implementation.

---

## **4. Testing**

Testing ensures that the system functions correctly and meets all requirements.

### **Testing Approach**

* **Unit Testing:** Individual functions were tested independently.
* **Integration Testing:** Interaction between modules was tested.
* **System Testing:** The complete system was tested with multiple student and course entries.

---

### **Sample Test Case**

**Input:**
Student: Rex
Course: CSC203

**Expected Output:**
Course registered successfully

**Duplicate Input:**
CSC203 again

**Expected Output:**
Course already registered

**Result:**
✔ Test passed successfully

---

## **5. Deployment**

After successful testing, the Course Registration Management System was deployed as a **Python command-line application**.
The system can be executed on any computer system with Python installed.

---

## **6. Maintenance**

The maintenance phase focuses on improving and updating the system after deployment.

### **Maintenance Activities**

* Fixing errors discovered during use.
* Updating course registration rules.
* Improving system performance.
* Adding features such as persistent storage or graphical user interface.

---

## **Conclusion**

The Course Registration Management System successfully follows the complete Software Development Life Cycle using the Waterfall model. The system provides a reliable and efficient solution for automating course registration and demonstrates the practical application of software engineering principles.

