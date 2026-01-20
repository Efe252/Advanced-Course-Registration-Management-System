# Course Registration Management System

students = {}

def register_course():
    name = input("Enter student name: ")
    course = input("Enter course name: ")

    if name not in students:
        students[name] = []

    if course in students[name]:
        print("Course already registered.")
    else:
        students[name].append(course)
        print("Course registered successfully.")

def view_courses():
    name = input("Enter student name: ")

    if name in students:
        print(f"Registered courses for {name}:")
        for course in students[name]:
            print("-", course)
    else:
        print("Student not found.")

while True:
    print("\n--- Course Registration Management System ---")
    print("1. Register Course")
    print("2. View Registered Courses")
    print("3. Exit")

    choice = input("Enter your choice: ")

    if choice == "1":
        register_course()
    elif choice == "2":
        view_courses()
    elif choice == "3":
        print("Exiting system...")
        break
    else:
        print("Invalid choice. Try again.")
