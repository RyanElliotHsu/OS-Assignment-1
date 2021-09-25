//============================================================================
// Name         : A1body.cpp
// Author       : Ryan Elliot Hsu
// Date Created : 2021.9.5
// Date Modified: 2021.9.5 
// Copyright    : All rights are reserved
// Description  : Assignment #1 Body
//============================================================================

#include"A1.hpp"

using namespace std;

//============================================================================
Node::Node()
{
    key = new int[treeSize-1];
    SLL = new CourseNode**[treeSize-1];
    ptrArray = new Node**[treeSize];
}

BPTree::BPTree()
{
    root = NULL;
}

Node* BPTree::getRoot()
{
    return root;
}
void BPTree::setTreeSize(int order)
{
    treeSize = order;
}

CourseNode::CourseNode()
{
    next = NULL;
}

StudentCourseList::StudentCourseList()
{
    root = NULL;
}

void BPTree::initialize()
{
    int option;
    cout<<"1. Batch 100\n2. Batch 1000\n3. Batch 10000\n4. Batch 30000\n"<<endl;
    cout<<"Please select one of the above options (enter a number from 1-5): "<<endl;
    cin>>option;

    switch (option)
    {
    case 1:
        
        break;
    
    default:
        break;
    }

}

StudentCourseList* BPTree::search(int studID)
{
    if(root==NULL)
    {
        cout<<"B+ Tree is currently empty, please input data."<<endl;
        return NULL;
    }
    else
    {
        Node* cursor = root;
        Node* parent;

        //Traverse tree until finding leaf node -- potential individual function
        while (cursor->isLeaf == false)
        {
            parent = cursor;

            //Traverse node 
            for (int i = 0; i < cursor->size; i++)
            {

                //If key being inserted is smaller, we traverse to a child node
                if(studID < cursor->key[i])
                {
                    cursor = cursor->ptrArray[i];
                    break;
                }

                else if(studID == cursor->key[i])
                {
                    cursor = cursor->ptrArray[i+1];
                    break;
                }

                //If key being inserted is larger than all keys in node, traverse to the leftmost child node
                if(i == cursor->size-1)
                {
                    cursor = cursor->ptrArray[i+1]
                    break;
                }
            } 
        }

        if(studID == cursor->key[i])
        {
            return cursor->SLL[i];
        }

        else
        {
            cout<<"Student not found."<<endl;
            return NULL;
        }
    }
}

void BPTree::insertKey(int studID, string courseID, string courseName, string courseGrade)
{
    //Initiate the tree if root is currently null
    if(root==NULL)
    {
        root = new Node;
        root->key[0] = studID;
        root->isLeaf = true;
        root->size = 1;
    }

    StudentCourseList* SLL = search(studID);
    else if(SLL != NULL)
    {
        SLL.addCourse(courseID, courseName, courseGrade);
        return;
    }

    //Traverse tree until finding leaf node
    else
    {
        Node* cursor = root;
        Node* parent;

        //Traverse tree until finding leaf node -- potential individual function
        while (cursor->isLeaf == false)
        {
            parent = cursor;

            //Traverse node 
            for (int i = 0; i < cursor->size; i++)
            {

                //If key being inserted is smaller, we traverse to a child node
                if(x < cursor->key[i])
                {
                    cursor = cursor->ptrArray[i];
                    break;
                }

                //If key being inserted is larger than all keys in node, traverse to the leftmost child node
                if(i == cursor->size-1)
                {
                    cursor = cursor->ptrArray[i+1]
                    break;
                }
            }
        }

        if (cursor->size < treeSize)
        {
            int i = 0;
            //Move key to the correct position (move forward if larger to compared key)
            while (studID > cursor->key[i] && i < cursor->size){i++;}
            //Adjust index of keys behind inserted key 
            for(int j = cursor->size; j>i; j--)
            {
                cursor->key[j] = cursor->key[j-1];
                cursor->SLL[j] = cursor->SLL[j-1];
            }

            cursor->key[i] = studID;
            cursor->SLL[i]->root = new CourseNode;
            cursor->SLL[i]->root->courseID = courseID;
            cursor->SLL[i]->root->courseName = courseName;
            cursor->SLL[i]->root->courseGrade = courseGrade;
            cursor->SLL[i]->size = 1;

            cursor->size ++;
            cursor->ptrArray[cursor->size] = cursor->ptrArray[cursor->size-1];
            cursor->ptrArray[cursor->size-1] = NULL;
        }
        
        //number of keys == tree size so new leaf node is needed
        else
        {
            Node* newLeaf = new Node;
            newLeaf->isLeaf = true;

            //set up a temporary array to store all keys in the node + new key
            int tempNode[treeSize+1];
            for(int i = 0; i < treeSize; i++)
            {
                tempNode[i] = cursor->key[i];
            }

            int i = 0;
            int j = 0;

            //Traversing to the location where studID is to be inserted
            while (studID>tempNode[i] && i < treeSize) {i++;}

            for(int j = treeSize+1; j>i; j--)
            {
                tempNode[j] = tempNode[j-1];
            }

            tempNode[i] = studID;
            cursor->size = (treeSize+1)/2;  //left biased, if (tree size+1) is odd, newLeaf will be larger than cursor node by 1
            newLeaf->size = (treeSize+1) - cursor->size;
            cursor->ptrArray[cursor->size] = newLeaf;   //the end of cursor is connected to the start of newLeaf
            newLeaf->ptrArray[newLeaf->size] = cursor->ptrArray[treeSize];  //cursor's end pointer is shifted to newLeaf's end pointer
            cursor->ptrArray[treeSize] = NULL;

            for(int i=0; i<cursor->size; i++)
            {
                cursor->key[i] = tempNode[i];
            }

            for(int i=0, j=cursor->size; i<newLeaf->size; i++, j++)
            {
                newLeaf->key[i] = tempNode[j];
            }

            if(cursor == root)
            {
                Node* newRoot = new Node;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptrArray[0] = cursor;
                newRoot->ptrArray[1] = newLeaf;
                newRoot->isLeaf = false;
                newRoot->size = 1;
                root = newRoot;
            }

            else
            {
                insertInternal(newLeaf->key[0], parent, newLeaf);
            }
        }   
    }
}

void BPTree::insertInternal(int studID, Node* cursor, Node* child)
{
    if (cursor->size < treeSize)
    {
        int i = 0;
        while (x > cursor->key[i] && i < cursor->size) {i++;}
  
        for (int j = cursor->size; j > i; j--)
        {
            cursor->key[j] = cursor->key[j - 1];
        }
  
        for (int j = cursor->size + 1; j > i + 1; j--)
        {
            cursor->ptrArray[j] = cursor->ptrArray[j - 1];
        }
  
        cursor->key[i] = x;
        cursor->size++;
        cursor->ptrArray[i + 1] = child;
    }

    else 
    {
        Node* newInternal = new Node;
        int virtualKey[treeSize + 1];
        StudentCourseList virtualSLL[treeSize + 1];
        Node* virtualPtr[treeSize + 2];
  
        for (int i = 0; i < treeSize; i++)
        {
            virtualKey[i] = cursor->key[i];
            virtualSLL[i] = cursor->SLL[i];
        }

        for (int i = 0; i < treeSize + 1; i++)
        {
            virtualPtr[i] = cursor->ptr[i];
        } 
  
        int i = 0, j;

        while (studID > virtualKey[i] && i < treeSize) { i++;}

        for (int j = treeSize + 1; j > i; j--)
        {
            virtualKey[j] = virtualKey[j - 1];
            virtualSLL[j] = virtualSLL[j - 1];
        }
  
        virtualKey[i] = studID;

        for (int j = treeSize + 2; j > i + 1; j--)
        {
            virtualPtr[j] = virtualPtr[j - 1];
        }
  
        virtualPtr[i + 1] = child;
        newInternal->isLeaf = false;
  
        cursor->size = (treeSize + 1) / 2;
        newInternal->size = treeSize - (treeSize + 1) / 2;

        for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++)
        {
            newInternal->key[i] = virtualKey[j];
            newInternal->SLL[i] = virtualSLL[j];
        }
  
        for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++)
        {
            newInternal->ptrArray[i] = virtualPtr[j];
        }
  
        if (cursor == root)
        {
  
            Node* newRoot = new Node;

            newRoot->key[0] = cursor->key[cursor->size];

            newRoot->ptrArray[0] = cursor;
            newRoot->ptrArray[1] = newInternal;
            newRoot->isLeaf = false;
            newRoot->size = 1;
            this->root = newRoot;
        }
  
        else 
        {
            insertInternal(cursor->key[cursor->size],findParent(root, cursor),newInternal);
        }
    }
}
  
Node* BPTree::findParent(Node* cursor, Node* child)
{
    Node* parent;
  
    if (cursor->isLeaf || (cursor->ptrArray[0])->isLeaf)
    {
        return NULL;
    }

    for (int i = 0; i < cursor->size + 1; i++)
    {

        if (cursor->ptrArray[i] == child)
        {
            parent = cursor;
            return parent;
        }

        else
        {
            parent = findParent(cursor->ptrArray[i],child);
            if (parent != NULL)
                return parent;
        }
    }

    return parent;
}

void BPTree::displayStudent(int studID)
{
    if(root == NULL)
    {
        cout<<"B+ Tree is currently empty, please initiate first.\n"<<endl;
    }
    else
    {
        Node* cursor = bpt.root;
        while(cursor)
    }
    
}

void BPTree::displayStudents(int ID2, int ID2)
{


}

void StudentCourseList::addCourse(string courseID, string courseName, string courseGrade)
{
    CourseNode* cursor = root;
    while(cursor->next != NULL)
    {
        cursor = cursor->next;
    }
    cursor->next = new CourseNode;
    cursor = cursor->next;
    cursor->courseID = courseID;
    cursor->courseName = courseName;
    cursor->courseGrade = courseGrade;
    return;
}

void BPTree::deleteCourse(int studID, string courseID)
{
    StudentCourseList* SLL = search(studID);
    if (studentCourses == NULL)
    {
        cout<<"Student not found."<<endl;
        return;
    }

    else
    {
        cursor = &SLL->root;
        int i = 0;
        while (cursor->next != NULL)
        {
            if (&SLL->size == 1)
            {
                cout<<"Student currently has one class remaining, unable to delete."<<endl;
                return;
            }

            if (cursor->courseID == courseID)
            {
                &SLL->deleteCourse(courseID, i);
                return;
            }
            cursor = cursor->next;
            i++
        }
        
        cout<<"Student <"<<studID<<"> is not enrolled in course <"<<courseID<<">."<<endl;

    }

}

void StudentCourseList::deleteCourse(string courseID, int position)
{
    CourseNode* cursor = root;
    CourseNode* prev = root;

    while (position != 0)
    {
        prev = cursor;
        cursor = cursor->next;
        position--;
    }

    prev->next = cursor->next;
    delete cursor;
    cursor = NULL;  
    cout<<"Course <"<<courseID<<"> deleted from classes of student <"<<this->studID<<">."<<endl;
}

void BPTree::generalGPA()
{


}

float BPTree::GPA(StudentCourseList* SLL)
{
    CourseNode* cursor = &SLL->root;
    float sum = 0;
    while (cursor != NULL)
    {
        if (cursor->courseGrade == "A+")
        {
            sum+=4.3;
        }
        else if (cursor->courseGrade == "A")
        {
            sum+=4.0;
        }
        else if (cursor->courseGrade == "A-")
        {
            sum+=3.7;
        }
        else if (cursor->courseGrade == "B+")
        {
            sum+=3.3;
        }
        else if (cursor->courseGrade == "B")
        {
            sum+=3.0;
        }
        else if (cursor->courseGrade == "B-")
        {
            sum+=2.7;
        }
        else if (cursor->courseGrade == "C+")
        {
            sum+=2.3;
        }
        else if (cursor->courseGrade == "C")
        {
            sum+=2.0;
        }
        else if (cursor->courseGrade == "C-")
        {
            sum+=1.7;
        }
        else if (cursor->courseGrade == "D+")
        {
            sum+=1.3;
        }
        else if (cursor->courseGrade == "D")
        {
            sum+=1.0;
        }
        else if (cursor->courseGrade == "D-")
        {
            sum+=0.7;
        }
        else if (cursor->courseGrade == "F")
        {
            sum+=0.0;
        }

        cursor = cursor->next;
    }
    
    return sum/(&SLL->size);
}

float BPTree::averageGPA(int ID1, int ID2)
{
    Node* cursor = this->root;
    float numStudents = 0;
    float sumGPA = 0;

    //traverse the tree by going through all the leftmost pointers until we reach the leaf node
    while (cursor->isLeaf == false)
    {
        cursor = cursor->ptrArray[0];
    }

    //traverse until we find student with ID1
    while (cursor->ptrArray[cursor->size+1] != NULL)
    {
        for(int i=0; i<=size; i++)
        {
            sumGPA += GPA(cursor->SLL[i]);
            numStudents++;
        }
    }

    //after reaching the leftmost leaf node, we start traversing the leaf nodes from left to right
    while (cursor->ptrArray[cursor->size+1] != NULL)
    {
        for(int i=0; i<=size; i++)
        {
            sumGPA += GPA(cursor->SLL[i]);
            numStudents++;
        }
    }
    return sumGPA/numStudents;
}

void BPTree::popularCourses()
{


}


void StudentManager::insert(string parameter)
{

}

void StudentManager::displayStudent(int studID)
{

}

void StudentManager::displayRange(int ID1, int ID2)
{

}

int StudentManager::GPA(int studID)
{
    SLL = BPTree::search(studID);
    if(SLL == NULL)
    {
        cout<<"Unable to calculate average GPA."<<endl;
        return 0;
    }
    else
    {

    }

}

int StudentManager::averageGPA(int ID1, int ID2)
{

}

void StudentManager::popularCourse(int i)
{

}

void StudentManager::verify()
{

}

void StudentManager::deleteCourse(int studID, string courseID)
{

}

void StudentManager::display()
{

}

void StudentManager::free()
{

}
