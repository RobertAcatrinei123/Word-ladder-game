#pragma once

#include "graph.h"
#include "profiledata.h"
#include <string>
#include <vector>
#include <unordered_map>

class Service
{
private:
    Graph<std::string> graph;
    ProfileData profile;

public:
    std::vector<std::string> getWords();
    void initGraph(const std::string &filename);
    void clearGraph();
    bool neighbours(const std::string &word1, const std::string &word2);
    std::vector<std::string> getShortestPath(const std::string &start, const std::string &end);
    std::pair<std::string, std::string> getStartEndWords();
    void setProfileName(const std::string &name);
    void setProfileStartWord(const std::string &startWord);
    void setProfileEndWord(const std::string &endWord);
    void setProfileLadder(const std::vector<std::string> &ladder);
    void setProfileDateTime();
    void setProfileOptimalSteps(int steps);
    std::string getProfileName() const;
    std::string getProfileStartWord() const;
    std::string getProfileEndWord() const;
    std::vector<std::string> getProfileLadder() const;
    std::string getProfileDate() const;
    std::string getProfileTime() const;
    int getProfileOptimalSteps() const;
    void clearProfile();
    void saveProfile();
    void incrementHints();
    std::vector<std::string> getUniqueWordsFromProfile(std::string name) const;
};