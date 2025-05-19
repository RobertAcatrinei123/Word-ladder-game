#include "profiledata.h"

std::ostream &operator<<(std::ostream &os, const ProfileData &profile)
{
    os << profile.name << " "
       << profile.startWord << " "
       << profile.endWord << " "
       << profile.ladder.size() << " ";
    for (const auto &word : profile.ladder)
    {
        os << word << " ";
    }
    os << profile.date << " "
       << profile.time << " "
       << profile.optimalSteps << "\n";
    return os;
}

std::istream &operator>>(std::istream &is, ProfileData &profile)
{
    is >> profile.name >> profile.startWord >> profile.endWord;
    int ladderSize;
    is >> ladderSize;
    profile.ladder.resize(ladderSize);
    for (int i = 0; i < ladderSize; ++i)
    {
        is >> profile.ladder[i];
    }
    is >> profile.date >> profile.time >> profile.optimalSteps;
    return is;
}

void ProfileData::setName(const std::string &name)
{
    this->name = name;
}

void ProfileData::setStartWord(const std::string &startWord)
{
    this->startWord = startWord;
}

void ProfileData::setEndWord(const std::string &endWord)
{
    this->endWord = endWord;
}

void ProfileData::setLadder(const std::vector<std::string> &ladder)
{
    this->ladder = ladder;
}

void ProfileData::setDateTime()
{
    time_t now = std::time(0);
    tm *ltm = localtime(&now);
    date = std::to_string(ltm->tm_mday) + "." +
           std::to_string(ltm->tm_mon + 1) + "." +
           std::to_string(ltm->tm_year + 1900);

    time = std::to_string(ltm->tm_hour) + ":" +
           std::to_string(ltm->tm_min);
}

void ProfileData::setOptimalSteps(int steps)
{
    this->optimalSteps = steps;
}

std::string ProfileData::getName() const
{
    return name;
}

std::string ProfileData::getStartWord() const
{
    return startWord;
}

std::string ProfileData::getEndWord() const
{
    return endWord;
}

std::vector<std::string> ProfileData::getLadder() const
{
    return ladder;
}

std::string ProfileData::getDate() const
{
    return date;
}

std::string ProfileData::getTime() const
{
    return time;
}

int ProfileData::getOptimalSteps() const
{
    return optimalSteps;
}

void ProfileData::clear()
{
    name.clear();
    startWord.clear();
    endWord.clear();
    ladder.clear();
    date.clear();
    time.clear();
    optimalSteps = 0;
}

