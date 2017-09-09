#include <cstdlib>
#include "linked_list.h"

using namespace std;


int main(int argc, char** argv) {

    Linked_List Chris;

    Chris.Add_Node(11);
    Chris.Add_Node(1);
    Chris.Add_Node(4);
    Chris.Add_Node(6);
    Chris.PrintList();
    // should print a list of [11, 1, 4, 6] at this point

    Chris.Delete_Node(4);
    Chris.PrintList();
    // should print a list of [11, 1, 6] at this point


return 0;
}
