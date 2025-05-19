#include "fileio.h"

std::vector<std::string> FileIO::importDict(const std::string &filename)
{
    std::ifstream fin(filename);
    if (!fin)
    {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::vector<std::string> words;
    int len = -1;
    std::string word;
    while (fin >> word)
    {
        if (len == -1)
        {
            len = word.size();
        }
        else if (word.size() != len)
        {
            throw std::runtime_error("Inconsistent word length in file: " + filename);
        }
        words.push_back(word);
    }
    fin.close();
    return words;
}

void FileIO::exportProfile(const ProfileData &profile)
{
    std::ofstream fout(profile.getName() + ".txt", std::ios::app);
    if (!fout)
    {
        throw std::runtime_error("Could not open file: profiles.txt");
    }
    fout << profile;
    fout.close();
}