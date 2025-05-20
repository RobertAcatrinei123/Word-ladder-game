#include "service.h"
#include "fileio.h"
#include <unordered_set>

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
    } while (i == j || neighbours(words[i], words[j]));
    return {words[i], words[j]};
}

bool Service::neighbours(const std::string &word1, const std::string &word2)
{
    if (word1.size() != word2.size())
        return false;

    int count = 0;
    for (int i = 0; i < word1.size(); i++)
    {
        if (word1[i] != word2[i])
            count++;
    }
    return count == 1;
}

void Service::setProfileName(const std::string &name)
{
    profile.setName(name);
}

void Service::setProfileStartWord(const std::string &startWord)
{
    profile.setStartWord(startWord);
}

void Service::setProfileEndWord(const std::string &endWord)
{
    profile.setEndWord(endWord);
}

void Service::setProfileLadder(const std::vector<std::string> &ladder)
{
    profile.setLadder(ladder);
}

void Service::setProfileDateTime()
{
    profile.setDateTime();
}

void Service::setProfileOptimalSteps(int steps)
{
    profile.setOptimalSteps(steps);
}

std::string Service::getProfileName() const
{
    return profile.getName();
}

std::string Service::getProfileStartWord() const
{
    return profile.getStartWord();
}

std::string Service::getProfileEndWord() const
{
    return profile.getEndWord();
}

std::vector<std::string> Service::getProfileLadder() const
{
    return profile.getLadder();
}

std::string Service::getProfileDate() const
{
    return profile.getDate();
}

std::string Service::getProfileTime() const
{
    return profile.getTime();
}

int Service::getProfileOptimalSteps() const
{
    return profile.getOptimalSteps();
}

void Service::clearProfile()
{
    profile.clear();
}

void Service::saveProfile()
{
    FileIO::exportProfile(profile);
}

void Service::incrementHints()
{
    profile.incrementHints();
}

std::vector<std::string> Service::getUniqueWordsFromProfile(std::string name) const
{
    std::unordered_set<std::string> words;
    std::ifstream fin(name + ".txt");
    if (!fin)
    {
        throw std::runtime_error("Could not open file: " + name + ".txt");
    }
    ProfileData profile;
    while (fin >> profile)
    {
        for (const auto &word : profile.getLadder())
        {
            words.insert(word);
        }
    }
    fin.close();
    return std::vector<std::string>(words.begin(), words.end());
}