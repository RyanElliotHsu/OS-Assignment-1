//============================================================================
// Name         : A1main.cpp
// Author       : Ryan Elliot Hsu
// Version      : 1.0
// Date Created : 2020.12.3
// Date Modified: 2020.12.5 
// Copyright    : All rights are reserved
// Description  : Assignment #3 Main
//============================================================================

#include"A1.hpp"
#include"A1.cpp"

using namespace std;

//============================================================================
int main()
{
    BPTree BPT;
    StudentManager STDM;
    string input;
    string command;
    string parameter;
    string treeOrder;

    cout<<"Please enter the order of the B+ tree: "<<endl;
    cin>>treeOrder;
    BPT.setTreeSize(treeOrder);
    cout<<"Please enter a command and corresponding parameters: "<<endl;
    getline(cin, input);
    command = input.substr(0,input.find(" "));
	parameter = input.substr(input.find(" ")+1);
    
    while(true)
    {   
        if (command == in)          BPT.initialize();
        else if (command == i)      STDM.insert(parameter);
        else if (command == f)      BPT.displayStudent(parameter);
        else if (command == r)      BPT.displayStudents(parameter);
        else if (command == g)      BPT.generalGPA(parameter);
        else if (command == t)      BPT.popularCourses(parameter);
        else if (command == v)      BPT.verify();
        else if (command == d)      BPT.deleteCourse(parameter);
        else if (command == p)      BPT.purge();
        else if (command == o)      BPT.displayTree();
        else if (command == e)      BPT.exit();

        else cout<<"\nCommand invalid, please enter again: "
        return 0;
    }

     






}