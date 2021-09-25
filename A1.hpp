//============================================================================
// Name         : A1header.cpp
// Author       : Ryan Elliot Hsu
// Date Created : 2021.9.5
// Date Modified: 2021.9.5 
// Copyright    : All rights are reserved
// Description  : Assignment #1 Header
//============================================================================

#include<iostream>
#include<fstream>
#include<math.h>
#include<list>
#include<sstream>
#include<string>

using namespace std;

//============================================================================

class Node
{
    private:
        int* key;
        int size;
        Node **ptrArray;
        bool isLeaf;
        StudentCourseList **SLL;
    public:
        Node();
        friend class BPTree;
        friend class StudentCourseList;
}

class BPTree
{
    private:
        Node* root;
        int treeSize;

    public:
        BPTree();
        Node* getRoot();
        void split();
        StudentCourseList* search(int studID);
        void displayStudent(int studID);
        void displayStudents(int ID1, int ID2);
        void insertKey(int studID, string courseID, string courseName, string grade);
        void deleteCourse(int studID, string courseID);
        void generalGPA();
        float GPA(int studID);
        float averageGPA(int ID1, int ID2);
        void initialize();
        void popularCourses();
        void setTreeSize(int order);
        friend class StudentCourseList;
}

class CourseNode
{
    private:
        CourseNode* next;
        string courseID;
        string courseName;
        string courseGrade;

    public:
        CourseNode();
        friend class BPTree;
        friend class StudentCourseList;

}

class StudentCourseList
{
    private:
        CourseNode* root;
        int studID;
        int size;
    public:
        StudentCourseList();
        void addCourse(string courseID, string courseName, string courseGrade);
        void deleteCourse(string courseID);
        friend class BPTree;
}

class StudentManager
{
    private:

    public:
        void insert(string parameter);  //insert information for a student's class
        void displayStudent(int studID);    //display all information regarding student with ID studID
        void displayRange(int ID1, int ID2);    //display all information regarding students with IDs ranging from ID1 to ID2
        int GPA(int studID);
        int averageGPA(int ID1, int ID2);  //computes the average GPA of students with IDs ranging from ID1 to ID2
        void popularCourse(int i);   //displays the top (i) courses in terms of number of enrolled students
        void verify();  //verifies all nodes of the indexing structure follow B+ tree properties
        void deleteCourse(int studID, string courseID);
        void display(); //display all content of the B+ tree
        void free();    //free all allocated space




}