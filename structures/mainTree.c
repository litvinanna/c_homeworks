#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {

    Node *root = addNode(NULL, 5);

    addNode(root, 1);
    addNode(root, 10);
    addNode(root, 7);
    addNode(root, 8);
    addNode(root, 11);
    addNode(root, 3);

    printTree(root);

    Node* another = NULL;
    int array[] = {6, 3, 10, 1, 5, 8, 12, 4, 7, 9, 11, 13};
    for (int i = 0; i<12; ++i) {
        another = addNode(another, array[i]);
    }
    printTree(another);
    another = deleteNode(another, searchTree(another, 10));
    printTree(another);


    Node* tree1 = NULL;
    int a[] = {1, 0, 2};
    for (int j = 0; j<3; ++j) {
        tree1 = addNode(tree1, a[j]);

    }
    printTree(tree1);

    rotateLeft(tree1);
    //rotateRight(tree1);
    tree1 = findRoot(tree1);
    printTree(tree1);



    return 0;
}
