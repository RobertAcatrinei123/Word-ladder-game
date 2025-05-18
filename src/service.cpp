#include "service.h"
#include "fileio.h"

void Service::initGraph(const std::string &filename)
{
    graph.clear();
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

std::vector<std::string> Service::getWords()
{
    return graph.getAllVertices();
}

void Service::clearGraph()
{
    graph.clear();
}

std::vector<std::string> Service::getShortestPath(const std::string &start, const std::string &end)
{
    return graph.shortestPath(start, end);
}

std::pair<std::string, std::string> Service::getStartEndWords()
{
    auto words = graph.getAllVertices();
    int i, j;
    srand(time(0));
    do
    {
        i = rand() % words.size();
        j = rand() % words.size();
    } while (i == j);
    return {words[i], words[j]};
}