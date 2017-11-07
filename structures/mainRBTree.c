#include "tree.h"
#include <stdlib.h>


int main(int argc, char** argv) {


    NodeRB* root = addNodeRB(NULL, 1.0);
    //printTreeRB(root);

    for (double i = -2.0; i < 3.0; ++i) {
        root = addNodeRB(root, i);
    }
    printTreeRB(root);

    root = deleteNodeRB(root, root->right);

    printTreeRB(root);

    root = deleteValueRB(root, 2.0);
    printTreeRB(root);

    return 0;

}
