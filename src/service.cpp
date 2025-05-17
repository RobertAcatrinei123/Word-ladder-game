#include "service.h"
#include "fileio.h"

void Service::initGraph(const std::string &filename)
{
    auto words = FileIO::importDict(filename);
    std::unordered_map<std::string, std::vector<std::string>> wordMap;
    for (const auto &word : words)
    {
        std::string copystr = word;
        for (int i = 0; i < word.size(); i++)
        {
            copystr[i] = '*';
            wordMap[copystr].push_back(word);
            copystr[i] = word[i];
        }
    }

    for (const auto &pair : wordMap)
    {
        for (const auto &neighbor1 : pair.second)
        {
            for (const auto &neighbor2 : pair.second)
            {
                if (neighbor1 == neighbor2)
                    continue;

                graph.addEdge(neighbor1, neighbor2);
            }
        }
    }
}