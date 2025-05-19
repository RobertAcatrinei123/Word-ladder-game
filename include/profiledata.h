#pragma once

#include <string>
#include <vector>
#include <iostream>

class ProfileData
{
private:
    std::string name = "";
    std::string startWord = "";
    std::string endWord = "";
    std::vector<std::string> ladder = {};
    std::string date = "";
    std::string time = "";
    int optimalSteps = 0;

public:
    ProfileData() = default;
    friend std::ostream &operator<<(std::ostream &os, const ProfileData &profile);
    friend std::istream &operator>>(std::istream &is, ProfileData &profile);
    void setName(const std::string &name);
    void setStartWord(const std::string &startWord);
    void setEndWord(const std::string &endWord);
    void setLadder(const std::vector<std::string> &ladder);
    void setDateTime();
    void setOptimalSteps(int steps);
    std::string getName() const;
    std::string getStartWord() const;
    std::string getEndWord() const;
    std::vector<std::string> getLadder() const;
    std::string getDate() const;
    std::string getTime() const;
    int getOptimalSteps() const;
    void clear();
};