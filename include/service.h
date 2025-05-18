#pragma once

#include "graph.h"
#include <string>
#include <vector>
#include <unordered_map>

class Service
{
private:
    Graph<std::string> graph;

public:
    std::vector<std::string> getWords();
    void initGraph(const std::string &filename);
    void clearGraph();
    std::vector<std::string> getShortestPath(const std::string &start, const std::string &end);
    std::pair<std::string, std::string> getStartEndWords();
};