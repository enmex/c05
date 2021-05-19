#pragma once
#include <iostream>
#include "TreeException.h"
#include <vector>
#include <queue>
#include <iomanip>

struct treenode{
    int field;
    int key;
    treenode *left, *right;
};

class binary_tree {

private:
    treenode* btree;
    treenode* root;
    int size;
    int height;
public:
    binary_tree();
    binary_tree(const binary_tree&);
    binary_tree(binary_tree&&);
    ~binary_tree();
    binary_tree operator=(const binary_tree&);
    binary_tree operator=(binary_tree&&);
    void add(int, std::vector<int>);
    friend std::ostream& operator<<(std::ostream& out, const binary_tree& tree);
    void setRoot(int);
    int evenSum();
    bool isPositive();
    void clearLeaves();
    double average();
    bool isBTS();
    std::vector<int> find(int x);
    void pretty_print_rotate();

private:

    int evenSum(treenode* point);
    bool isPositive(treenode* point);
    int clearLeaves(treenode* &point);
    double sum(treenode* point);
    void find(int x, treenode* point, std::vector<int>&);//указывает на какой ветке (0 или 1)
    bool isBTS(treenode* point);

    void pretty_print_rotate(treenode* point, int level);

    static std::ostream& print_node(std::ostream& out, treenode* node){
        out << node->field;
        if(node->left!=nullptr){
            out << "->left[";
            print_node(out, node->left);
            out << "]";
        }
        if(node->right!=nullptr){
            out << "->right[";
            print_node(out, node->right);
            out << "]";
        }
        return out;
    }
};