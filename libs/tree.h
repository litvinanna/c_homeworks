#ifndef TREE_GUARD_H
#define TREE_GUARD_H


/*---------------Bin-Search-Tree------------------------------------*/

typedef struct NodeStruct {
    struct NodeStruct * parent;
    struct NodeStruct * right;
    struct NodeStruct * left;
    double data;
} Node;

Node* addNode(Node* root, double data);
Node* deleteNode(Node* root, Node* target);
Node* searchTree (Node* root, double data);
Node* deleteValue (Node* root, double data);

void printTree (Node* root);
void printNode(Node* node);


void rotateLeft(Node* node);
void rotateRight(Node* node);

Node* findRoot(Node* node);

/*---------------Red-Black-Tree------------------------------------*/

typedef struct NodeStructRB {
    struct NodeStructRB * parent;
    struct NodeStructRB * right;
    struct NodeStructRB * left;
    double data;
    char color; // r red     b black   n NIL (black) leaf
} NodeRB;

NodeRB* insertNodeRB(NodeRB* root, double data);
NodeRB* addNodeRB (NodeRB* root, double data);
//NodeRB* deleteNodeRB (NodeRB* root, NodeRB* target);
NodeRB* searchTreeRB (NodeRB* root, double data);
NodeRB* deleteValueRB (NodeRB* root, double data);

NodeRB* stabInserted1 (NodeRB* node);
NodeRB* stabInserted2 (NodeRB* node);
NodeRB* stabInserted3 (NodeRB* node);
NodeRB* stabInserted4 (NodeRB* node);
NodeRB* stabInserted5 (NodeRB* node);

void rotateLeftRB (NodeRB* node);
void rotateRightRB (NodeRB* node);

void printTreeRB (NodeRB* root);
void printNodeRB (NodeRB* node);

NodeRB* sibling(NodeRB* node);
void replaceNodeRB(NodeRB* node, NodeRB* child);
NodeRB* deleteNodeRB (NodeRB* root, NodeRB* node);
NodeRB* deleteWithOne(NodeRB* node);

NodeRB* stabDeleted1(NodeRB* node);
NodeRB* stabDeleted2 (NodeRB* node);
NodeRB* stabDeleted3 (NodeRB* node);
NodeRB* stabDeleted4 (NodeRB* node);
NodeRB* stabDeleted5 (NodeRB* node);
NodeRB* stabDeleted6 (NodeRB* node);










#endif // TREE_GURAD_H
