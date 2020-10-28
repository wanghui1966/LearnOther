#include "BinaryTree.h"

#include <iostream>

void TestTraverse()
{
	BinaryTree *bt = new BinaryTree;

	bt->PreOrderCreate();

	bt->PreOrderTraverse();
	bt->InOrderTraverse();
	bt->PostOrderTraverse();

	bt->PreOrderTraverseNot();
	bt->InOrderTraverseNot();
	bt->PostOrderTraverseNot();

	bt->LevelOrderTraverse();

	bt->OutPut();

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

void TestConvertDoubleLink()
{
	BinaryTree *bt = new BinaryTree;

	char seq[11] = "ebadckfhgi";
	if (bt->RebuildSortTree(seq, 10))
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

void TestConvertLeftAndRight()
{
	BinaryTree *bt = new BinaryTree;

	char seq[11] = "ebadckfhgi";
	if (bt->RebuildSortTree(seq, 10))
	{
		bt->PreOrderTraverse();
		bt->InOrderTraverse();
		bt->PostOrderTraverse();

		bt->ConvertLeftAndRight();

		bt->PreOrderTraverse();
		bt->InOrderTraverse();
		bt->PostOrderTraverse();
	}

	delete bt;
}

void TestCmp()
{
	BinaryTree *bt1 = new BinaryTree;
	BinaryTree *bt2 = new BinaryTree;

	std::cout << "bt1==bt2 = " << bt1->StructureCmp(bt2) << std::endl;

	char seq1[10] = "akgmrlpit";
	char seq2[10] = "akgmrlpiw";
	if (bt1->RebuildSortTree(seq1, 9))
	{
		std::cout << "bt1==bt2 = " << bt1->StructureCmp(bt2) << std::endl;
		if (bt2->RebuildSortTree(seq2, 9))
		{
			std::cout << "bt1==bt2 = " << bt1->StructureCmp(bt2) << std::endl;
		}
	}

	delete bt1;
	delete bt2;

	BinaryTree *bt3 = new BinaryTree;
	BinaryTree *bt4 = new BinaryTree;

	char seq3[10] = "akgmrlpit";
	char seq4[10] = "akgmrlpic";
	if (bt3->RebuildSortTree(seq3, 9) && bt4->RebuildSortTree(seq4, 9))
	{
		std::cout << "bt3==bt4 = " << bt3->StructureCmp(bt4) << std::endl;
	}

	delete bt3;
	delete bt4;
}

void TestCommon()
{
	BinaryTree *bt = new BinaryTree;

	char seq[11] = "ebadckfhgi";
	if (bt->RebuildSortTree(seq, 10))
	{
		bt->PreOrderTraverse();
		bt->InOrderTraverse();
		bt->PostOrderTraverse();

		int depth = bt->GetDepth();
		std::cout << "深度：" << depth << ", 叶子结点数量：" << bt->GetLeafNodeCount() << std::endl;
		for (int i = 1; i <= depth; ++i)
		{
			std::cout << "第" << i << "层结点数量：" << bt->GetNodeCountInLevelK(i) << std::endl;
		}

		bt->OutPut();
	}

	delete bt;
}

void TestSortTree()
{
	BinaryTree *bt = new BinaryTree;

	char seq[11] = "ebadckfhgi";
	if (bt->RebuildSortTree(seq, 10))
	{
		bt->PreOrderTraverse();
		bt->InOrderTraverse();
		bt->PostOrderTraverse();
	}

	delete bt;
}


void TestRebuildAVLTree()
{
	BinaryTree *bt = new BinaryTree;

	char seq[11] = "ebadckfhgi";
	bt->RebuildAVLTree(seq, 10);

	delete bt;
}

int main()
{
	//TestTraverse();
	//TestSortTree();
	//TestConvertDoubleLink();
	//TestConvertLeftAndRight();
	//TestCmp();
	//TestCommon();
	//TestRebuildTree();
	TestRebuildAVLTree();
	return 0;
}
