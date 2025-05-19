#pragma once

#include "profiledata.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class FileIO
{
public:
    static std::vector<std::string> importDict(const std::string &filename);
    static void exportProfile(const ProfileData &profile);
};