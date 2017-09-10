#include "BinaryTree.h"

#include <iostream>
#include <stack>

BinaryTree::BinaryTree()
: head(nullptr)
, num(0)
{

}

BinaryTree::~BinaryTree()
{
    std::cout << "析构函数：" << std::endl;
    ReleaseNode(head);
}

void BinaryTree::ReleaseNode(Node *&p)
{
    if(!p)
    {
        return;
    }
    else
    {
        ReleaseNode(p->left);
        ReleaseNode(p->right);
        std::cout << "删除结点：" << p->data << std::endl;
        delete p;
        p = nullptr;
    }
}

void BinaryTree::PreOrderCreate()
{
    std::cout << "先序建立二叉树：" << std::endl;
    PreOrderCreateAssist(head);
    std::cout << std::endl << std::endl;
}

void BinaryTree::PreOrderCreateAssist(Node *&p)
{
    char temp;
    std::cin >> temp;
    if(temp == '-')
    {
        return;
    }
    else
    {
        p = new Node(temp);
        ++num;
        PreOrderCreateAssist(p->left);
        PreOrderCreateAssist(p->right);
    }
}

void BinaryTree::PreOrderTraverse()
{
    std::cout << "先序遍历二叉树：" << std::endl;
    PreOrderTraverseAssist(&head);
    std::cout << std::endl << std::endl;
}

void BinaryTree::PreOrderTraverseAssist(Node **p)
{
    if(*p)
    {
        std::cout << (*p)->data << " ";
        PreOrderTraverseAssist(&((*p)->left));
        PreOrderTraverseAssist(&((*p)->right));
    }
}

void BinaryTree::InOrderTraverse()
{
    std::cout << "中序遍历二叉树：" << std::endl;
    InOrderTraverseAssist(head);
    std::cout << std::endl << std::endl;
}

void BinaryTree::InOrderTraverseAssist(Node *&p)
{
    if(p)
    {
        InOrderTraverseAssist(p->left);
        std::cout << p->data << " ";
        InOrderTraverseAssist(p->right);
    }
}

void BinaryTree::PostOrderTraverse()
{
    std::cout << "后序遍历二叉树：" << std::endl;
    PostOrderTraverseAssist(head);
    std::cout << std::endl << std::endl;
}

void BinaryTree::PostOrderTraverseAssist(Node *&p)
{
    if(p)
    {
        PostOrderTraverseAssist(p->left);
        PostOrderTraverseAssist(p->right);
        std::cout << p->data << " ";
    }
}

void BinaryTree::PreOrderTraverseNot()
{
    std::cout << "先序遍历二叉树(非递归)：" << std::endl;
    std::stack<Node*> s;
    if(head)
    {
        s.push(head);
    }

    while(!s.empty())
    {
        Node *p = s.top();
        s.pop();
        if(p)
        {
            std::cout << p->data << " ";
            if(p->right)
            {
                s.push(p->right);
            }
            if(p->left)
            {
                s.push(p->left);
            }
        }
    }
    std::cout << std::endl << std::endl;
}

void BinaryTree::InOrderTraverseNot()
{
    std::cout << "中序遍历二叉树(非递归)：" << std::endl;
    std::stack<Node*> s;
    if(head)
    {
        s.push(head);
    }

    Node *p;
    while(!s.empty())
    {
        while(p = s.top())
        {
            s.push(p->left);
        }

        s.pop();

        if(!s.empty())
        {
            p = s.top();
            s.pop();
            std::cout << p->data << " ";
            s.push(p->right);
        }
    }
    std::cout << std::endl << std::endl;
}

void BinaryTree::PostOrderTraverseNot()
{
    std::cout << "后序遍历二叉树(非递归)：" << std::endl;
    std::stack<Node*> s;
    if(head)
    {
        s.push(head);
    }
    Node *current = s.top(); 
    s.pop();
    Node *preVisited = nullptr; 
    while(current != nullptr || !s.empty())
    {
        while(current)
        {
            s.push(current);
            current = current->left;
        }
        current = s.top();
        
        if(current->right == nullptr || current->right == preVisited)
        {
            std::cout << current->data << " ";
            preVisited = current;
            s.pop();
            current = nullptr;
        }
        else
        {
            current = current->right;
        }
    }
    std::cout << std::endl << std::endl;
}
