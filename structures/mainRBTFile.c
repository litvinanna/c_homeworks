#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>



void _printTreeRBLinear(NodeRB* node) {
    if (node->color != 'n') {
        printf("%8.4lf  ", node->data);
    } else return;

    _printTreeRBLinear(node->right);
    _printTreeRBLinear(node->left);
    return;

}

void printTreeRBLinear(NodeRB* node) {
    _printTreeRBLinear(node);
    printf("\n");
}
/*
void _printTreeRBLinearPart(NodeRB* node, NodeRB* left, NodeRB* right) {
    if (node->color != 'n'&& node != left && node != right) {
        printf("%8.4lf  ", node->data);
    } else return;

    _printTreeRBLinearPart(node->right, left, right);
    _printTreeRBLinearPart(node->left, left, right);
    return;

}

void printTreeRBLinearPart(NodeRB* node,  NodeRB* left, NodeRB* right) {
    _printTreeRBLinearPart(node, left, right);
    printf("\n");
}
*/


void _printTreeRBPart(NodeRB* root, double left, double right) {
    if (root->color == 'n') {
        return;
    }

    if (root->data >= left && root->data < right) {
        printf("%8.4lf  ", root->data);
    }
    if (root->left->data >= left) {
        _printTreeRBPart(root->left, left, right);
    }
    if (root->right->data <= right) {
        _printTreeRBPart(root->right, left, right);
    }

}
void printTreeRBPart(NodeRB* root, double a, double b) {
    _printTreeRBPart(root, a, b);
    printf("\n");
}




int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Missing file name\n");
        return 0;
    }

    char *fileName = argv[1];

    printf("File name: %s\n", fileName);

    FILE *file = fopen(fileName, "r");

    if (!file) {
        printf("File is not found\n");
        return 0;
    }

    NodeRB* root = NULL;
    double number;
    while(!feof(file)) {
        fscanf(file, "%lf\n", &number);
        root = addNodeRB(root, number);
    }

    printTreeRB(root);

    while(1) {
        double a;
        double b;
        printf("Enter two doubles 'a b', where a<b (enter '0.0 0.0' to exit)\n");
        scanf("%lf %lf", &a, &b);
        if (a == 0.0 && b == 0.0) {
            break;
        }

        printf("< a  ");
        printTreeRBPart(root, -DBL_MAX, a);
        printf(">=a, <b");
        printTreeRBPart(root, a, b);
        printf(">= b  ");
        printTreeRBPart(root, b, DBL_MAX);
        printf("\n");
    }
    return 0;
}
