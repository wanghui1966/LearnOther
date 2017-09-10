#ifndef BINARYTREE_H
#define BINARYTREE_H

typedef struct Node
{
    Node() : data(0), left(nullptr), right(nullptr) {}
    Node(char d) : data(d), left(nullptr), right(nullptr) {}

    char data;
    struct Node *left;
    struct Node *right;
}Node;

class BinaryTree{
public:
    BinaryTree();
    virtual ~BinaryTree();

public:
    // 释放结点
    void ReleaseNode(Node *&p);

    // 先序建立二叉树：安装二叉树先序方式输入结点，以空格作为结点分隔符号，-表示null叶结点
    void PreOrderCreate();
    void PreOrderCreateAssist(Node *&p);

    // 递归方式遍历，分别为先序、中序和后序
    void PreOrderTraverse();
    void InOrderTraverse();
    void PostOrderTraverse();

    void PreOrderTraverseAssist(Node **p);
    void InOrderTraverseAssist(Node *&p);
    void PostOrderTraverseAssist(Node *&p);

    // 非递归方式遍历，分别为先序、中序和后序
    void PreOrderTraverseNot();
    void InOrderTraverseNot();
    void PostOrderTraverseNot();

protected:
    Node *head;
    int num;
};

#endif
