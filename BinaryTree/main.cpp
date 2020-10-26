#include "BinaryTree.h"

#include <iostream>

void TestAssist()
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
}

void TestRebuildTree()
{
	BinaryTree *bt = new BinaryTree;

	char pre_order_seq[10] = "abdefghic";
	char in_order_seq[10] = "dbfhgieac";
	if (bt->RebuildTreeByPreOrderAndInOrder(pre_order_seq, in_order_seq, 9))
	{
		bt->PreOrderTraverse();
		bt->InOrderTraverse();
		bt->PostOrderTraverse();
	}

	delete bt;
}

void TestSortTree()
{
	BinaryTree *bt = new BinaryTree;

	char seq[10] = "abdefghic";
	if (bt->RebuildSortTree(seq, 9))
	{
		bt->PreOrderTraverse();
		bt->InOrderTraverse();
		bt->PostOrderTraverse();
	}

	delete bt;
}

void TestConvertDoubleLink()
{
	BinaryTree *bt = new BinaryTree;

	char seq[10] = "abdefghic";
	if (bt->RebuildSortTree(seq, 9))
	{
		Node *first = nullptr;
		Node *last = nullptr;
		if (bt->ConvertDoubleLink(first, last))
		{
			std::cout << "从first循环遍历:";
			Node *p = first;
			while (p)
			{
				std::cout << p->data << " ";
				p = p->right;
			}
			std::cout << std::endl;

			std::cout << "从last循环遍历:";
			p = last;
			while (p)
			{
				std::cout << p->data << " ";
				p = p->left;
			}
			std::cout << std::endl;

			std::cout << "双向链表析构：";
			Node *tmp = nullptr;
			p = first;
			while (p)
			{
				tmp = p;
				p = p->right;
				std::cout << tmp->data << " ";
				delete tmp;
			}
			std::cout << std::endl;
			return;
		}
	}

	delete bt;
}

int main()
{
	//TestAssist();
	//TestRebuildTree();
	//TestSortTree();
	TestConvertDoubleLink();
	return 0;
}
