#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Student
{
    int rollNo;
    char name[50];
    int age;
    char course[50];
};

void addStudent()
{
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    cout << "\nEnter Roll Number: ";
    cin >> s.rollNo;

    cin.ignore();

    cout << "Enter Name: ";
    cin.getline(s.name, 50);

    cout << "Enter Age: ";
    cin >> s.age;

    cin.ignore();

    cout << "Enter Course: ";
    cin.getline(s.course, 50);

    file.write((char*)&s, sizeof(s));
    file.close();

    cout << "\nStudent Added Successfully!\n";
}

void displayStudents()
{
    Student s;
    ifstream file("students.dat", ios::binary);

    cout << "\n===== STUDENT RECORDS =====\n";

    while(file.read((char*)&s, sizeof(s)))
    {
        cout << "\nRoll No : " << s.rollNo;
        cout << "\nName    : " << s.name;
        cout << "\nAge     : " << s.age;
        cout << "\nCourse  : " << s.course;
        cout << "\n--------------------------";
    }

    file.close();
}

void searchStudent()
{
    int roll;
    bool found = false;

    Student s;
    ifstream file("students.dat", ios::binary);

    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    while(file.read((char*)&s, sizeof(s)))
    {
        if(s.rollNo == roll)
        {
            cout << "\nStudent Found:";
            cout << "\nRoll No : " << s.rollNo;
            cout << "\nName    : " << s.name;
            cout << "\nAge     : " << s.age;
            cout << "\nCourse  : " << s.course;

            found = true;
            break;
        }
    }

    if(!found)
        cout << "\nStudent Not Found!\n";

    file.close();
}

void updateStudent()
{
    int roll;
    bool found = false;

    Student s;
    fstream file("students.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;

    while(file.read((char*)&s, sizeof(s)))
    {
        if(s.rollNo == roll)
        {
            cout << "\nEnter New Name: ";
            cin.ignore();
            cin.getline(s.name, 50);

            cout << "Enter New Age: ";
            cin >> s.age;

            cin.ignore();

            cout << "Enter New Course: ";
            cin.getline(s.course, 50);

            int pos = file.tellg();
            file.seekp(pos - sizeof(s));

            file.write((char*)&s, sizeof(s));

            found = true;

            cout << "\nRecord Updated Successfully!\n";
            break;
        }
    }

    if(!found)
        cout << "\nStudent Not Found!\n";

    file.close();
}

void deleteStudent()
{
    int roll;
    bool found = false;

    Student s;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    while(file.read((char*)&s, sizeof(s)))
    {
        if(s.rollNo == roll)
        {
            found = true;
            continue;
        }

        temp.write((char*)&s, sizeof(s));
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found)
        cout << "\nStudent Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n\n===== STUDENT MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";

        cin >> choice;

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!";
        }

    } while(choice != 6);

    return 0;
}