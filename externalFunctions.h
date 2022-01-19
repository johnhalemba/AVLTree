//
// Created by Jan Halemba on 08/01/2022.
//
#include <iostream>
#include <fstream>
#include "Dictionary.h"
#ifndef TREE_EXTERNALFUNCTIONS_H
#define TREE_EXTERNALFUNCTIONS_H

void read_file(std::string file_name, Dictionary<std::string, int>& dict)
{
    std::ifstream file;
    file.open("file.txt");
    if (!file.is_open())
    {
        std::cerr << "File not opened!" << std::endl;
    }
    std::string word;
    while (file >> word)
    {
        std::string temp = "";
        for (auto w : word)
        {
            temp += w;
            if ((int)w < 97 && int(w) > 122)
            {
                if (dict.search(word))
                {
                    dict.get(word)->addInfo();
                    continue;
                }
                dict.insert(word, 1);
                temp = "";
            }
            if (w == word[word.length()-1])
            {
                if (dict.search(word))
                {
                    dict.get(word)->addInfo();
                    continue;
                }
                dict.insert(word, 1);
                temp = "";
            }


        }
    }
}

#endif //TREE_EXTERNALFUNCTIONS_H