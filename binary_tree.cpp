#include "pch.h"
#include "binary_tree.h"

binary_tree::binary_tree() : root(nullptr), size(0) {
    height = 0;
    btree = new treenode;
    btree->field = 0;
    btree->right = nullptr;
    btree->left = nullptr;
    root = btree;
}

binary_tree::binary_tree(const binary_tree& tree) : btree(tree.btree), root(tree.btree), size(tree.size), height(tree.height) {}

binary_tree::binary_tree(binary_tree&& tree) : btree(tree.btree), root(tree.root), size(tree.size), height(tree.height) {
    tree.btree = nullptr;
    tree.root = nullptr;
    tree.size = 0;
    tree.height = 0;
}
binary_tree::~binary_tree(){
    btree = nullptr;
    root = nullptr;
    height = 0;
    size = 0;
    delete btree;
    delete root;
}

void binary_tree::setRoot(int x){
    root->field = x;
}

void binary_tree::add(int x, std::vector<int> path){
    if(path.size()==0 || path.size() > height+1){
        throw TreeException("Неверно задан путь");
    }
    if (height < path.size()) {
        height = path.size();
    }
    btree = root;
    for(int i = 0; i < path.size()-1; i++){
        if(path[i]){
            btree = btree->right;
        }
        else{
            btree = btree->left;
        }
    }

    treenode* temp = new treenode;
    temp->field = x;
    temp->left = nullptr;
    temp->right = nullptr;
    if(path[path.size()-1]){
        btree->right = temp;
    }
    else{
        btree->left = temp;
    }
    temp = nullptr;
    delete temp;
    size++;
}

std::ostream& operator<<(std::ostream& out, const binary_tree& tree){
    return binary_tree::print_node(out, tree.root);
}

int binary_tree::evenSum(treenode* point){ 
    int sum = 0;
    if(point!=nullptr){
        if(point->field%2==0){
            sum++;
        }
        sum+=evenSum(point->left);
        sum+=evenSum(point->right);
    }
    return sum;
}
int binary_tree::evenSum(){
    return evenSum(root);
}
bool binary_tree::isPositive(treenode* point){
    if(point!=nullptr){
        if(point->field < 0){
            return false;
        }
        else if(!isPositive(point->left)){
            return false;
        }
        return isPositive(point->right);
    }
    return true;
}
bool binary_tree::isPositive(){
    return isPositive(root);
}

int binary_tree::clearLeaves(treenode* &point){
    if(point->left==nullptr && point->right==nullptr){
        point = nullptr;
        delete point;
        return 0;
    }
    if(point->left!=nullptr){
        clearLeaves(point->left);
    }
    if(point->right!=nullptr){
        clearLeaves(point->right);
    }
    return 0;
}
void binary_tree::clearLeaves(){
    clearLeaves(root);
}
double binary_tree::sum(treenode* point){
    double summ = 0.0;
    summ+=point->field;
    if(point->right!=nullptr){
        summ+=sum(point->right);
    }
    if(point->left!=nullptr){
        summ+=sum(point->left);
    }
    return summ;

}
double binary_tree::average(){
    return (sum(root->right)+sum(root->left))/(double)size;
}

void binary_tree::find(int x, treenode* point, std::vector<int>& path){
    if(!point){ return; }
    if(point->field == x){
        throw TreeException("");
    }
    if(point->left!=nullptr){
        path.emplace_back(0);
        find(x, point->left, path);
    }
    if(point->right!=nullptr){
        path.emplace_back(1);
        find(x, point->right, path);
    }
    if (path.size() != 0) {
        path.pop_back();
    }
    return;
}
std::vector<int> binary_tree::find(int x){
    std::vector<int> path;
    try{
        find(x, root, path);
    }
    catch(TreeException e){
        return path;
    }
    return {-1};
}

void binary_tree::pretty_print_rotate(treenode* point, int level){
    if(point){
        pretty_print_rotate(point->right, level+1);
        for(int i = 0; i < level; i++) {std::cout << "\t";}
        std::cout << point->field << std::endl;
        pretty_print_rotate(point->left, level+1);
    }
}

void binary_tree::pretty_print_rotate(){
    pretty_print_rotate(root, 1);
}

bool binary_tree::isBTS(){
    try{
        return isBTS(root);
    }
    catch(TreeException e){
        return false;
    }
    return true;
}
bool binary_tree::isBTS(treenode* point){
    if(point->right){
        if(point->field > point->right->field){
            throw TreeException("");
        }
        return isBTS(point->right);
    }
    if(point->left){
        if(point->field < point->left->field){
            throw TreeException("");
        }
        return isBTS(point->left);
    }
    return true;
}