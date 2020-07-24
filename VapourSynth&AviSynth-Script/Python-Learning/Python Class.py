import json

class Student:
    studentName = ""
    studentNumber = 0
    studentGender = True
    studentGrade = [0, 0, 0, 0, 0]

    def __init__(self, name, gender):
        self.studentName = name
        self.studentGender = gender

if __name__ == "__main__":
    student1 = Student("Mike", False)
    print(student1)
        
