#include "pch.h"
#include <iostream>
#include <ctime>
#include "binary_tree.h"
using namespace std;

int main(int args, char* argv[]){
    binary_tree tree;
    tree.setRoot(70);
    srand(time(0));
    vector<int> res;
    vector<int> path;



    int k;
    for (int i = 2; i < 16 + rand()%((32-16)+16); i++) {
        k = i;
        while (k > 0) {
            path.push_back(k % 2);
            k /= 2;
        }
        path.pop_back();
        for (int j = 0; j < path.size(); j++) {
            res.push_back(path[path.size()-1-j]);
        }
        tree.add(1 + (rand() % ((20 - 1) + 1)) , res);
        path.clear();
        res.clear();
    }

    cout << tree << endl;
    tree.pretty_print_rotate();
    cout << "Is it a binary tree search: " << tree.isBTS() << endl;
    cout << "Find 15 [ ";
    vector<int> pathh = tree.find(15);
    for(int i = 0; i < pathh.size(); i++){
        cout << pathh[i] << " ";
    }
    cout << "]" << endl;

    cout << "Total of even numbers " << tree.evenSum() << endl;
    cout << "Are all of the elements positive: " << tree.isPositive() << endl;

    cout << "Average " << tree.average() << endl;

    cout << "Cut the leaves" << endl;
    tree.clearLeaves();
    tree.pretty_print_rotate();
}