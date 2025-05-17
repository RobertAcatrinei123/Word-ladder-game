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
        void initGraph(const std::string &filename);
};