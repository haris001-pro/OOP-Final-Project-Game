#pragma once

#include "Game.h"

#include <random>
#include <string>
#include <vector>

class WordScrambleRace final : public Game
{
public:
    explicit WordScrambleRace(int difficultyLevel);
    void play() override;
    int getLastScore() const;

private:
    int difficultyLevel;
    int rounds;
    int hintsAllowed;
    int lastScore{};
    std::mt19937 randomEngine{std::random_device{}()};

    std::vector<std::string> wordBank() const;
    std::string scrambleWord(const std::string& word);
    int calculateRoundScore(int attemptsUsed, bool usedHint) const;
};
