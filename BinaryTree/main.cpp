#include "BinaryTree.h"

int main()
{
    BinaryTree *bt = new BinaryTree;
    bt->PreOrderCreate();

    bt->PreOrderTraverse();
    bt->InOrderTraverse();
    bt->PostOrderTraverse();

    bt->PreOrderTraverseNot();
    bt->InOrderTraverseNot();
    bt->PostOrderTraverseNot();

    delete bt;
    return 0;
}
