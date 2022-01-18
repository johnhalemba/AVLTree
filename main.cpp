#include <iostream>
#include "externalFunctions.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Dictionary<int, int> d1;
    d1.insert(5, 2);
    d1.insert(1, 2);
    d1.insert(6, 2);
    Dictionary<std::string, int> dFile;
    read_file("file.txt", dFile);
    return 0;
}
