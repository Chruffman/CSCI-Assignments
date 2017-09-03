#include <cstdlib>
#include <iostream>

#include "linked_list.h"

using namespace std;

Linked_List::Linked_List(){
    head = NULL;
    curr = NULL;
    temp = NULL;
}

void Linked_List::Add_Node(int addData){
    node* n = new node;
    n->next = NULL;
    n->data = addData;

    if(head != NULL){
        curr = head;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = n;
    }
    else{
        head = n;
    }
}

void Linked_List::Delete_Node(int delData){
    node* delPtr = NULL;
    temp = head;
    curr = head;

    while(curr != NULL && curr->data != delData){
        temp = curr;
        curr = curr->next;
    }
    if (curr == NULL){
        cout << delData << "was not in the list\n";
        delete delPtr;
    }
    else{
       delPtr = curr;
       curr = curr->next;
       temp->next = curr;
       delete delPtr;
       cout << "The value " << delData << "was deleted\n";
    }
}
void Linked_List::PrintList(){
    while (curr != NULL){
        cout << curr->data << endl;
        curr = curr->next;
    }

}


