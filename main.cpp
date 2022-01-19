#include <iostream>
#include "externalFunctions.h"

int main() {
    Dictionary<int, int> d1;
    d1.insert(5, 2);
    d1.insert(1, 2);
    d1.insert(6, 2);
    d1.insert(5, 5);
    d1.insert(7, 2);
    d1.insert(10, 2);
    d1.insert(2, 2);
    d1.remove(10);
    d1.insert(3, 2);
    d1.insert(87, 2);
    d1.insert(100, 67);
    d1.insert(8, 99);
    d1.insert(50, 99);
    d1.insert(22, 99);
    d1.insert(34, 99);
    d1.insert(39, 99);
    d1.printPrittier();
    Dictionary<std::string, int> dFile;
    read_file("file.txt", dFile);
    return 0;
}
