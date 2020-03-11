#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H
#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree {
private:
    // Описание структуры узла со ссылками на детей
    struct Node {
        T key_; // значение ключа, содержащееся в узле
        Node * left_; // указатель на левое поддерево
        Node * right_; // указатель на правое поддерево
        Node * p_; // указатель на родителя !!! не используется
        // Конструктор узла
        Node(const T& key, Node * left = nullptr, Node * right= nullptr , Node * p =
                nullptr): key_(key), left_ (left), right_(right), p_(p) {};
    };
    // Дерево реализовано в виде указателя на корневой узел.
    Node * root_;

private:
    // функция для вставки в конкретный узел
    void insertNode (Node * node, const T& key) {
        if (key > node -> key_){
            if (node -> right_){
                insertNode(node -> right_, key);
            }
            else{
                node -> right_ = new Node(key);
            }
        }
        else{
            if (node -> left_){
                insertNode(node -> left_, key);
            }
            else{
                node -> left_ = new Node(key);
            }
        }
    }
    // рекурсивная функция удаления узла
    Node * deleteNode (Node * root, const T& key){
        if (root == nullptr) {
            return nullptr;
        }
        if (key == root -> key_){
            if (root -> left_ == nullptr){
                delete root;
                root = root -> right_;
            }
            else if (root -> right_ == nullptr){
                delete root;
                root = root -> left_;
            }
            else{
                Node * t = root -> right_;
                while (t -> left_) {
                    t = t -> left_;
                }
                root -> key_ = t -> key_;
                root -> right_ = deleteNode(root -> right_, root -> key_);
            }
        }
        else if (key < root -> key_){
            root -> left_ = deleteNode(root -> left_, key);
        }
        else{
            root -> right_ = deleteNode(root -> right_, key);
        }
        return root;
    }
    // Функция поиска адреса узла по ключу в бинарном дереве поиска
    Node * iterativeSearchNode (const T & key) const {
        Node * node = root_;
        while (node != nullptr && node -> key_ != key){
            if (key < node -> key_){
                node = node -> left_;
            }
            else{
                node = node -> right_;
            }
        }
        return node;
    }
    // Рекурсивные функции, представляющие
    // рекурсивные тела основных интерфейсных методов

    // Рекурсивная функция для освобождения памяти
    void deleteSubtree (Node * node) {
        if (node -> left_){
            deleteSubtree(node -> left_);
        }
        if (node -> right_){
            deleteSubtree(node -> right_);
        }
        delete node;
    }
    // Рекурсивная функция определения количества узлов дерева
    int countSubTree (Node * node) const {
        if (node == nullptr)
            return 0;
        return (1 + countSubTree (node -> left_) +
                countSubTree (node -> right_));
    }
    // Рекурсивная функция определения высоты дерева
    int heightSubTree (Node * node) const {
        if (node == nullptr){
            return 0;
        }
        return 1 + max(heightSubTree(node -> left_), heightSubTree(node -> right_));
    }
    // Рекурсивная функция для вывода изображения дерева в выходной поток
    void printNode (ostream & out, Node * root) const {
        // Изображение дерева заключается в круглые скобки.
        out << '(';
        if (root) {
// Для узлов дерева должна быть определена (или переопределена)
// операция вывода в выходной поток <<
            out << root -> key_;
            printNode(out, root -> left_);
            out << ',';
            printNode(out, root -> right_);
        }
        out << ')';
    }
    // Рекурсивная функция для организации обхода узлов дерева.
    void inorderWalk (ostream & out, Node * root) const {
        if (root) {
            inorderWalk(out, root -> left_);
            out << root -> key_;
            out << ' ';
            inorderWalk(out, root -> right_);
        }
    }

public:
    // Конструктор "по умолчанию" создает пустое дерево
    BinarySearchTree(): root_(nullptr){};
    // Деструктор освобождает память, занятую узлами дерева
    ~BinarySearchTree() {
        deleteSubtree(root_);
    }
    // итеративная вставка элемента
    void iterativeInsert (const T & key){
        if (!root_){
            root_ = new Node(key);
        }
        else{
            Node * node = root_;
            bool f = true;
            while(f){
                if (key > node -> key_){
                    if (node -> right_){
                        node = node -> right_;
                    }
                    else{
                        node -> right_ = new Node(key);
                        f = false;
                    }
                }
                else{
                    if (node -> left_){
                        node = node -> left_;
                    }
                    else{
                        node -> left_ = new Node(key);
                        f = false;
                    }
                }
            }
        }
    }
    // Вставка нового элемента в дерево, не нарушающая порядка
    // элементов. Вставка производится в лист дерева
    void recursiveInsert (const T& key) {
        if (root_ == nullptr){
            root_ = new Node(key);
        }
        else if (key > root_ -> key_){
            if (root_ -> right_){
                insertNode(root_ -> right_, key);
            }
            else{
                root_ -> right_ = new Node(key);
            }
        }
        else{
            if (root_ -> left_){
                insertNode(root_ -> left_, key);
            }
            else{
                root_ -> left_ = new Node(key);
            }
        }
    }
    // Печать строкового изображения дерева в выходной поток out
    void print (ostream & out) const {
        printNode(out, root_);
        out << endl;
    }
    // обход дерева слева направо
    void walk (ostream & out) const {
        inorderWalk(out, root_);
        out << endl;
    }
    // Функция поиска по ключу в бинарном дереве поиска
    bool iterativeSearch (const T & key) const {
        return (iterativeSearchNode(key) != nullptr);
    }
    // Удаление элемента из дерева, не нарушающее порядка элементов
    void deleteKey (const T & key) {
        root_ = deleteNode(root_, key);
    }
    // Определение количества узлов дерева
    int count () const {
        return countSubTree(root_);
    }
    // Определение высоты дерева
    int height () const {
        return heightSubTree(root_);
    }
};


#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
