#ifndef TREE_H
#define TREE_H
#include "iostream"
#include<QDebug>


class Tree
{
    class Book
    {
        friend class Tree;

        Book *Left;
        Book *Right;
        char author[80];
        char name[80];
        char way[80];
        Book ()
        {
            Left = NULL;
            Right = NULL;
        }
        ~Book()
        {
            // почему предупреждения , не знаю
         /*   delete [] author;
            delete [] name;
            delete [] way;*/
        }
    };

public:
    Book * Root;
    Tree()
    {
        Root = NULL;
    }
    ~Tree()
    {
        DeleteTree(Root);
    }
    void Add(Book *B);
    void DeleteTree(Book *b);
    void Search(char _name[]);
    void FillTree();
    void Write(Book *B);

};

#endif // TREE_H
