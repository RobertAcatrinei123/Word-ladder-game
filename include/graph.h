#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <iostream>

template <typename T>
class Graph
{
private:
    std::unordered_map<T, std::vector<T>> adj;

public:
    void addEdge(const T &src, const T &dest)
    {
        if (std::find(adj[src].begin(), adj[src].end(), dest) == adj[src].end())
        {
            adj[src].push_back(dest);
            adj[dest].push_back(src);
        }
    }

    std::vector<T> getNeighbors(const T &node) const
    {
        auto it = adj.find(node);
        if (it != adj.end())
        {
            return it->second;
        }
        return std::vector<T>();
    }

    std::vector<T> shortestPath(const T &start, const T &end) const
    {
        std::unordered_map<T, T> prev;
        std::queue<T> q;

        q.push(start);
        prev[start] = start;

        while (!q.empty())
        {
            T current = q.front();
            q.pop();

            if (current == end)
            {
                std::vector<T> path;
                for (T curr = end; curr != start; curr = prev[curr])
                {
                    path.push_back(curr);
                }
                path.push_back(start);
                std::reverse(path.begin(), path.end());
                return path;
            }

            for (const T &neighbor : getNeighbors(current))
            {
                if (prev.find(neighbor) == prev.end())
                {
                    q.push(neighbor);
                    prev[neighbor] = current;
                }
            }
        }
        return std::vector<T>();
    }
};