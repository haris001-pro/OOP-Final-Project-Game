#include "WordScrambleRace.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>

namespace
{
    constexpr const char* Reset = "\033[0m";
    constexpr const char* Bold = "\033[1m";
    constexpr const char* Red = "\033[31m";
    constexpr const char* Green = "\033[32m";
    constexpr const char* Yellow = "\033[33m";
    constexpr const char* Cyan = "\033[36m";

    void divider()
    {
        std::cout << Cyan << "------------------------------------------------------" << Reset << '\n';
    }
}

WordScrambleRace::WordScrambleRace(int difficultyLevel)
    : Game("Word Scramble Race"), difficultyLevel(difficultyLevel)
{
    if (difficultyLevel == 1)
    {
        rounds = 5;
        hintsAllowed = 2;
    }
    else if (difficultyLevel == 2)
    {
        rounds = 6;
        hintsAllowed = 1;
    }
    else
    {
        rounds = 7;
        hintsAllowed = 0;
    }
}

void WordScrambleRace::play()
{
    lastScore = 0;
    std::vector<std::string> words = wordBank();
    std::shuffle(words.begin(), words.end(), randomEngine);

    divider();
    std::cout << Bold << Yellow << "WORD SCRAMBLE RACE" << Reset << '\n';
    divider();
    std::cout << "Unscramble each word before your attempts run out.\n";
    std::cout << "Type '?' for a hint. Hints available: " << Cyan << hintsAllowed
              << Reset << "\n\n";

    int hintsLeft = hintsAllowed;

    for (int round = 1; round <= rounds && round <= static_cast<int>(words.size()); ++round)
    {
        const std::string word = words.at(round - 1);
        const std::string scrambled = scrambleWord(word);
        bool solved = false;
        bool usedHint = false;

        divider();
        std::cout << Bold << "Round " << round << "/" << rounds << Reset
                  << " | Hints left: " << Cyan << hintsLeft << Reset << '\n';
        std::cout << "Scrambled word: " << Yellow << scrambled << Reset << '\n';

        for (int attempt = 1; attempt <= 3; ++attempt)
        {
            std::string guess;
            std::cout << "Guess " << attempt << "/3: ";
            std::cin >> guess;

            std::transform(guess.begin(), guess.end(), guess.begin(), [](unsigned char character) {
                return static_cast<char>(std::tolower(character));
            });

            if (guess == "?" && hintsLeft > 0)
            {
                --hintsLeft;
                usedHint = true;
                std::cout << Cyan << "Hint: starts with '" << word.front()
                          << "' and has " << word.length() << " letters.\n"
                          << Reset;
                --attempt;
                continue;
            }

            if (guess == "?" && hintsLeft == 0)
            {
                std::cout << Red << "No hints left. Take a shot.\n" << Reset;
                --attempt;
                continue;
            }

            if (guess == word)
            {
                solved = true;
                const int roundScore = calculateRoundScore(attempt, usedHint);
                lastScore += roundScore;
                std::cout << Green << "Correct. +" << roundScore << " pts\n\n"
                          << Reset;
                break;
            }

            std::cout << Yellow << "Not quite.\n" << Reset;
        }

        if (!solved)
        {
            std::cout << Red << "Round lost. Word was: " << word << "\n\n"
                      << Reset;
        }
    }

    divider();
    std::cout << "Word Scramble Race score: " << Green << lastScore << " pts"
              << Reset << '\n';
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int WordScrambleRace::getLastScore() const
{
    return lastScore;
}

std::vector<std::string> WordScrambleRace::wordBank() const
{
    if (difficultyLevel == 1)
    {
        return {"class", "object", "score", "array", "input", "logic", "debug", "stack"};
    }

    if (difficultyLevel == 2)
    {
        return {"inherit", "virtual", "pointer", "compile", "factory", "module", "private", "runtime"};
    }

    return {"polymorphism", "encapsulation", "abstraction", "composition", "leaderboard",
            "architecture", "integration", "responsibility"};
}

std::string WordScrambleRace::scrambleWord(const std::string& word)
{
    std::string scrambled = word;

    do
    {
        std::shuffle(scrambled.begin(), scrambled.end(), randomEngine);
    } while (scrambled == word && word.length() > 1);

    return scrambled;
}

int WordScrambleRace::calculateRoundScore(int attemptsUsed, bool usedHint) const
{
    const int baseScore = 150 * difficultyLevel;
    const int attemptBonus = (4 - attemptsUsed) * 40;
    const int hintPenalty = usedHint ? 60 : 0;
    return std::max(25, baseScore + attemptBonus - hintPenalty);
}
