#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

int main() {
    BinarySearchTree <int> t; // создаем пустое дерево
    // добавляем узлы
    t.recursiveInsert(10);
    t.iterativeInsert(3);
    t.recursiveInsert(20);
    t.iterativeInsert(15);
    t.recursiveInsert(30);
    t.iterativeInsert(2);
    t.recursiveInsert(5);
    t.iterativeInsert(32);
    t.recursiveInsert(22);
    // Вывод узлов дерева в выходной поток
    t.print(cout);
    // Поиск в дереве по ключу
    bool keyFound = t.iterativeSearch(15); // поиск должен быть успешным
    cout << "Key " << 15 <<
         (keyFound ? " found successfully" : " not found") <<  " in the tree" << endl;
    keyFound = t.iterativeSearch(23); // поиск должен быть неудачным
    cout << "Key " << 23 <<
         (keyFound ? " found successfully" : " not found") <<
         " in the tree" << endl;

    // определение высоты и количества узлов дерева
    cout << "height = " << t.height() << endl;
    cout << "count = " << t.count() << endl;
    // инфиксный проход по дереву
    t.walk(cout);
    // удаление узла из дерева
    t.deleteKey(10);
    t.print(cout);
    t.deleteKey(32);
    t.print(cout);
    t.deleteKey(30);
    t.print(cout);
    // проверка на удаление несуществующего узла
    t.deleteKey(3000);
    t.print(cout);
    return 0;
}