#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class FileIO
{
public:
    static std::vector<std::string> importDict(const std::string &filename);
};