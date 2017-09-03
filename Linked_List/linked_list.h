/* This is a practice linked list project based on Paul's Programming from YouTube

Created on August 25, 2016
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H


class Linked_List{
private:

    struct node{
        int data;
        node* next;
    };

    node* head;
    node* curr;
    node* temp;



public: //This is where the functions go that access the private data

    Linked_List(); //constructor

    void Add_Node(int addData);

    void Delete_Node(int delData);

    void PrintList();
};
#endif // LINKED_LIST_H
