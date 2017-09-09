#include <cstdlib>
#include <iostream>

#include "linked_list.h"

using namespace std;

Linked_List::Linked_List(){  // constructor
    head = NULL;
    curr = NULL;
    temp = NULL;
}

void Linked_List::Add_Node(int addData){
    node* n = new node;  // create new node pointer and have it point to the new node 'n'
    n->next = NULL;  // point n to the next section of the node and point it to the end of the list
    n->data = addData;  // put the input data in the data section of the node

    if(head != NULL){  // if a list exists, proceed
        curr = head;
        while(curr->next != NULL){  // iterate to the end of the list
            curr = curr->next;
        }
        curr->next = n;
    }
    else{  // the head points to the new node if there is an empty list
        head = n;
    }
}

void Linked_List::Delete_Node(int delData){
    node* delPtr = NULL;  // create a new node pointer and point it to NULL
    temp = head;  // point temp and curr to the beginning of the list
    curr = head;

    while(curr != NULL && curr->data != delData){ // while loop to pass through the list until the data to delete is found
        temp = curr;  // temp stays one step behind curr in order to allow for patching up of the list once the data is deleted
        curr = curr->next;
    }
    if (curr == NULL){  // if the search makes it to the end of the list, the data does not exist
        cout << delData << " was not found in the list.\n";
        delete delPtr;
    }
    else{
       delPtr = curr;  // pointing to the node we want to delete
       curr = curr->next;  // advance current pointer
       temp->next = curr;  // temp pointer (one step behind curr) can patch up the list by pointing the next section of the node to curr
       if (delPtr == head) {
        head = head->next;
        temp = NULL;
       }
       delete delPtr;  // delete the data
       cout << "The value " << delData << " was deleted from the list.\n";
    }
}
void Linked_List::PrintList(){
    curr = head;
    while (curr != NULL){
        cout << curr->data << endl;
        curr = curr->next;
    }

}


