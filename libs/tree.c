#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tree.h"


/*---------------Bin-Search-Tree------------------------------------*/

Node* addNode(Node* root, double data) {
    Node* newNode = (Node*) calloc(1, sizeof(Node));
    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;

    if (root == NULL) {
        return newNode;
    }

    Node* current = root;
    while (1) {
        if (data >= current->data) {
            if (current->right == NULL) {
                current->right = newNode;
                break;
            } else {
                current = current->right;
            }
        } else {
            if (current->left == NULL) {
                current->left = newNode;
                break;
            } else {
                current = current->left;
            }

        }
    }
    newNode->parent = current;
    return root;
}

enum NodeSide {
    NODE_LEFT_SIDE,
    NODE_RIGHT_SIDE,
    NODE_ROOT
};

Node* deleteNode(Node* root, Node* target) {
    if (target == NULL || root == NULL) return root;

    Node *returnValue = root;
    int n;

    if (target->parent == NULL) {
        n = NODE_ROOT;
    } else if (target->parent->left == target) {
        n = NODE_LEFT_SIDE;
    } else {
        n = NODE_RIGHT_SIDE;
    }

    if (target->right != NULL) {
        Node* current = target->right;
        while(current->left != NULL) {
            current = current->left;
        }
        if (current != target->right) {
            current->parent->left = NULL;
        } else {
            current->parent->right = NULL;
        }
        current->parent = target->parent;
        if (n == NODE_LEFT_SIDE) {
            target->parent->left = current;
        } else if (n == NODE_RIGHT_SIDE) {
            target->parent->right = current;
        } else if (n == NODE_ROOT) {
            returnValue = current;
        }
        current->left = target->left;
        current->right = target->right;
    } else {
        if (target->left != NULL) {
            target->left->parent = target->parent;
        }
        if (n == NODE_LEFT_SIDE) {
            target->parent->left = target->left;
        } else if (n == NODE_RIGHT_SIDE) {
            target->parent->right = target->left;
        } else if (n == NODE_ROOT) {
            returnValue = target->left;
        }
    }

    free(target);
    return returnValue;
}

Node* searchTree (Node* root, double data) {
    Node* current = root;
    while (fabs(current->data - data) > 1e-10) {
        if (data > current->data) {
            if (current->right != NULL) {
                    current = current->right;
            } else {
                return NULL;
            }
        } else {
            if (current->left != NULL) {
                    current = current->left;
            } else {
                return NULL;
            }
        }
    }
    return current;
}

Node* deleteValue (Node* root, double value) {
    return deleteNode(root, searchTree(root, value));
}

void _printTree(Node* root, char *tmp, int index) {
    if (root != NULL) {
        printf("%f %s\n", root->data, tmp);
    } else {
        return;
    }
    tmp[index] = 'r';
    _printTree(root->right, tmp, index + 1);
    tmp[index] = 'l';
    _printTree(root->left, tmp, index + 1);
    tmp[index] = '\0';

}

void printTree(Node *root) {
    int maxDeep = 1024;
    char *tmp = (char *) calloc(maxDeep, sizeof(char));
    printf("***\n");
    _printTree(root, tmp, 0);
    free(tmp);
}

void printNode(Node* node) {
    printf("*");
    if (node == NULL) {
        printf("NULL NODE\n");
        return;
    }
    if (node->parent != NULL) {
        printf("%11.2f\n", node->parent->data);
    } else {
        printf("      root\n");
    }
    printf("%12.2f\n", node->data);
    if (node->left != NULL) {
        printf("%8.2f", node->left->data);
    } else {
        printf(" null l  ");
    }
    if (node->right != NULL) {
        printf("%8.2f\n", node->right->data);
    } else {
        printf("  null r \n");
    }
    return;

}




void rotateLeft(Node* node) { //we have to change 6 pointers
    if (node->right == NULL) {
        return;
    }
    Node* pivot = node->right;
    pivot->parent = node->parent; //  1 can become root
    if (node->parent != NULL) {
        if (node->parent->left == node) {
            node->parent->left = pivot; //2
        } else {
            node->parent->right = pivot;
        }
    }
    node->right = pivot->left; //3
    if (pivot->left != NULL) {
        pivot->left->parent = node; //4
    }
    node->parent = pivot; //5
    pivot->left = node; //6
    return;

}

void rotateRight (Node* node) {
    if (node->left == NULL) {
        return;
    }

    Node* pivot = node->left;
    pivot->parent = node->parent;
    if (node->parent != NULL) {
        if (node->parent->left == node) {
            node->parent->left = pivot;
        } else {
            node->parent->right = pivot;
        }
    }

    node->left = pivot->right;
    if (pivot->right != NULL) {
        pivot->right->parent = node;
    }
    node->parent = pivot;
    pivot->right = node;
    return;

}


Node* findRoot(Node* node) {
    Node* current = node;
    while(current->parent != NULL){
        current = current->parent;
    }
    return current;
}

/*---------------Red-Black-Tree------------------------------------*/

NodeRB* NILleaf() {
    NodeRB* newNode = (NodeRB*) calloc(1, sizeof(NodeRB));
    newNode->color = 'n';
    return newNode;
}

NodeRB* insertNodeRB (NodeRB* root, double data) {
    NodeRB* newNode = (NodeRB*) calloc(1, sizeof(NodeRB));
    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->color = 'r'; // red


    if (root == NULL) {  //tree doesn`t exist
        NodeRB* leaf = NILleaf();
        NodeRB* leaf1 = NILleaf();

        newNode->right = leaf;
        leaf->parent = newNode;
        newNode->left = leaf1;
        leaf1->parent = newNode;
        return newNode;
    }

    NodeRB* leaf = NILleaf();

    NodeRB* current = root; //if tree exists
    while (1) {
        if (data >= current->data) {
            if (current->right->color == 'n') {  //current->right is NIL leaf
                newNode->right = current->right; //reattach NIL right leaf
                current->right->parent = newNode;

                current->right = newNode;

                newNode->left = leaf;
                leaf->parent = newNode;

                break;
            } else {
                current = current->right;
            }
        } else {
            if (current->left->color == 'n') {   //current->left is NIL leaf
                newNode->left = current->left; //reattach NIL left leaf
                current->left->parent = newNode;

                current->left = newNode;

                newNode->right = leaf;
                leaf->parent = newNode;
                break;
            } else {
                current = current->left;
            }

        }
    }
    newNode->parent = current;
    return newNode;


}

NodeRB* grandparent(NodeRB* node ) {
    if ((node != NULL) & (node->parent != NULL)) {
        return node->parent->parent;
    } else {
        return NULL;
    }
}

NodeRB* uncle(NodeRB* node) {
    NodeRB* g = grandparent(node);
    if ( g == NULL) {
        return NULL;
    }
    if (node->parent == g->left) {
        return g->right;
    } else {
        return g->left;
    }

}



NodeRB* stabInserted5 (NodeRB* node) {
    NodeRB* g = grandparent(node);
    node->parent->color = 'b';
    g->color = 'r';
    if ((node== node->parent->left) & (node->parent == g->left)) {
        rotateRightRB(g);
    } else {
        rotateLeftRB(g);
    }
    return g->parent;
}

NodeRB* stabInserted4(NodeRB* node) {
    NodeRB* g = grandparent(node);

    if((node == node->parent->right) & (node->parent == g->left)) {
        rotateLeftRB(node->parent);
        node = node->left;
    } else if ((node == node->parent->left) & (node->parent == g->right)) {
        rotateRightRB(node->parent);
        node = node->parent;
    }
    return stabInserted5(node);
}

NodeRB* stabInserted3 (NodeRB* node) {
    NodeRB* u = uncle(node);
    NodeRB* g;
    if ( (u != NULL) & (u->color == 'r')) {  //node->parent is red, see stabilize2
        node->parent->color = 'b';
        u->color = 'b';
        g = grandparent(node);
        g->color = 'r';
        return stabInserted1(g);
    } else {
        return stabInserted4(node);
    }

}



NodeRB* stabInserted2 (NodeRB* node) {
    if (node->parent->color == 'b') {
        return node->parent;
    } else {
        return stabInserted3(node);
    }
}



NodeRB* stabInserted1 (NodeRB* node) {
    if (node->parent == NULL) {
        node->color = 'b';
        return node;
    } else {
        return stabInserted2(node);
    }
}



NodeRB* findRootRB(NodeRB* node) {
    NodeRB* current = node;
    while(current->parent != NULL) {
        current = current->parent;
    }
    return current;

}
void rotateLeftRB(NodeRB* node) { //we have to change 6 pointers
    if (node->right == NULL) {
        return;
    }
    NodeRB* pivot = node->right;
    pivot->parent = node->parent; //  1 can become root
    if (node->parent != NULL) {
        if (node->parent->left == node) {
            node->parent->left = pivot; //2
        } else {
            node->parent->right = pivot;
        }
    }
    node->right = pivot->left; //3
    if (pivot->left != NULL) {
        pivot->left->parent = node; //4
    }
    node->parent = pivot; //5
    pivot->left = node; //6
    return;

}

void rotateRightRB(NodeRB* node) {
    if (node->left == NULL) {
        return;
    }

    NodeRB* pivot = node->left;
    pivot->parent = node->parent;
    if (node->parent != NULL) {
        if (node->parent->left == node) {
            node->parent->left = pivot;
        } else {
            node->parent->right = pivot;
        }
    }

    node->left = pivot->right;
    if (pivot->right != NULL) {
        pivot->right->parent = node;
    }
    node->parent = pivot;
    pivot->right = node;
    return;

}

NodeRB* addNodeRB (NodeRB* root, double data) {
    NodeRB* a = insertNodeRB(root, data); //unstab inserted node
    a = stabInserted1(a); //stab node in tree
    a = findRootRB(a); // now a is a root
    return a;
}

NodeRB* sibling(NodeRB* node) {
    if (node->parent == NULL) {
        printf("No sibling!\n");
        return NULL;
    }
    if(node->parent->left == node) {
        return node->parent->right;
    } else {
        return node->parent->left;
    }
}

void replaceNodeRB (NodeRB* node, NodeRB* child) {
    child->parent = node->parent;

    if (node->parent != NULL) {
        if (node == node->parent->right) {
            node->parent->right = child;

        } else {
            node->parent->left = child;
        }
    }
    return;

}

NodeRB* searchTreeRB (NodeRB* root, double data) {
    if (fabs(root->data - data) < 1e-10) {
        return root;
    } else if (data >= root->data) {
        if (root->right->color != 'n') {
            return searchTreeRB(root->right, data);
        } else {
            return NULL;
        }
    } else {
        if (root->left->color != 'n') {
            return searchTreeRB(root->left, data);
        } else {
            return NULL;
        }
    }
}


NodeRB* _deleteNodeRB (NodeRB* node) {

    // printf("start deleting\n");
    // printNodeRB(node);
    // printNodeRB(node->left);
    // printNodeRB(node->right);

    // printf("%c %c", node->right->color, node->left->color);

    if ((node->right->color != 'n') && (node->left->color != 'n')) {
        // printf("deleteNodeRB if\n");
        NodeRB* current = node->right;
        while(current->left->color != 'n') {
            current = current->left;
        }
        node->data = current->data;
        node = current;
    }
    //printf("lalala");
    //NodeRB* root = findRoot(node);
    //printf("deleteNodeRB\n");
    //printTreeRB(root);
    return deleteWithOne(node);
}

NodeRB* deleteWithOne(NodeRB* node) {
    //node has no more than one not NILleaf child
    NodeRB* child;

    if (node->right->color != 'n') {
        child = node->right;
        free(node->left);

    } else {
        child = node->left;
        free(node->right);
    }
    //printNodeRB(child);

    replaceNodeRB(node, child);
    //printNodeRB(child);
    char nodeColor = node->color;
    free(node);

    if (nodeColor == 'b') {
        if (child->color == 'r') {
            child->color = 'b';
        } else {
            return stabDeleted1(child);  //we deleted one black node
        }
    }
    //printNodeRB(child);
    return child;

}

NodeRB* stabDeleted1 (NodeRB* node) { //child became a root, we deleted black root
    if (node->parent == NULL) {
        return node;
    } else {
        return stabDeleted2(node);
    }
}

NodeRB* stabDeleted2 (NodeRB* node) { //child became smone`s child, imbalance
    NodeRB* s = sibling(node);
    if(s->color == 'r') {
        node->parent->color = 'r';
        s->color = 'b';
        if (node == node->parent->left) {
            rotateLeftRB(node->parent);
        } else {
            rotateRightRB(node->parent);
        }
    }
    return stabDeleted3(node); //havent finished
}

NodeRB* stabDeleted3 (NodeRB* node) {
    NodeRB* s = sibling(node);
    if (node->parent->color == 'b' && s->color == 'b' && s->left->color == 'b' && s->right->color == 'b') {
        s->color = 'r';
        return stabDeleted1(node->parent);
    } else {
        return stabDeleted4(node);
    }
}

NodeRB* stabDeleted4 (NodeRB* node) {
    NodeRB* s = sibling(node);
    if (node->parent->color == 'r' && s->color == 'b' && s->left->color == 'b' && s->right->color == 'b') {
        s->color = 'r';
        node->parent->color = 'b';
        return node->parent;
    } else {
        return stabDeleted5(node);
    }
}

NodeRB* stabDeleted5 (NodeRB* node) {
    NodeRB* s = sibling(node);
    if(node == node->parent->left && s->right->color == 'b' ) {
        s->color = 'r';
        s->left->color = 'b';
        rotateRightRB(s);
    } else if (node == node->parent->right && s->right->color =='b') {
        s->color = 'r';
        s->right->color = 'b';
        rotateLeftRB(s);
    }
    return stabDeleted6(node);
}


NodeRB* stabDeleted6 (NodeRB* node) {
    NodeRB* s = sibling(node);
    s->color = node->parent->color;
    node->parent->color = 'b';
    if (node == node->parent->left) {
        s->right->color = 'b';
        rotateLeftRB(node->parent);
    } else {
        s->left->color = 'b';
        rotateRightRB(node->parent);
    }
    return node;
}



NodeRB* deleteNodeRB(NodeRB* root, NodeRB* node) {
    if (node == NULL || node->color == 'n') {
        return root;
    }
    root = _deleteNodeRB(node);
    return findRootRB(root);
}


NodeRB* deleteValueRB (NodeRB* root, double data) {
    return deleteNodeRB(root, searchTreeRB(root, data));
}


const char* stringColor(NodeRB* node) {
    if (node->color == 'r') {
        return " red ";
    } else if (node->color == 'b') {
        return "black";
    } else {
        return " nil ";
    }
}

void _printTreeRB(NodeRB* root, char *tmp, int index) {
    if (root != NULL) {

        if (root->color != 'n') {
            printf("%15.4f %s %s\n", root->data, stringColor(root), tmp);
        } else {
            //printf("                %s %s\n",  stringColor(root), tmp); //do we print NIL leaves?
        }

    } else {
        return;
    }

    tmp[index] = 'r';
    _printTreeRB(root->right, tmp, index + 1);
    tmp[index] = 'l';
    _printTreeRB(root->left, tmp, index + 1);
    tmp[index] = '\0';

}

void printTreeRB(NodeRB *root) {
    int maxDeep = 1024;
    char *tmp = (char *) calloc(maxDeep, sizeof(char));
    printf("***\n");
    _printTreeRB(root, tmp, 0);
    free(tmp);
    return;
}

void printNodeRB(NodeRB* node) {
    printf("*");
    if (node == NULL) {
        printf("NULL NODE\n");
        return;
    }
    if (node->parent != NULL) {
        printf("%12.2f %s\n", node->parent->data, stringColor(node->parent));
    } else {
        printf("          root\n");
    }
    printf("%13.2f %s\n", node->data, stringColor(node));

    if (node->left != NULL) {
        printf("%7.2f %s", node->left->data, stringColor(node->left));
    }

    if (node->right != NULL) {
        printf("%7.2f %s\n", node->right->data, stringColor(node->right));
    }
    return;

}



