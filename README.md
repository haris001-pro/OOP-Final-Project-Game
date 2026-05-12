# Word Scramble Race

## Overview

Word Scramble Race is a competitive CLI-based word puzzle game developed in C++ using Object-Oriented Programming principles. The player is given scrambled words and must correctly guess the original word within a limited number of attempts.

The game supports multiple difficulty levels, a scoring system, hints, colorful terminal UI, and randomized gameplay to create an engaging arcade-style experience.

This game is designed as a modular component of the larger **GameArcade** framework and can be integrated into any system that supports the provided `Game` base class interface.

---

# Features

* Randomized word scrambling
* Easy, Medium, and Hard difficulty levels
* Competitive score system
* Hint system
* Colored terminal UI
* Multiple rounds per game
* Replayable gameplay
* Modular and plug-and-play architecture
* Runtime polymorphism support through `Game*`

---

# Gameplay Rules

1. A scrambled word is displayed to the player.
2. The player has 3 attempts to guess the correct word.
3. The player may type `?` to use a hint (if hints are available).
4. Correct answers award points based on:

   * difficulty level
   * attempts used
   * hint usage
5. The final score is displayed after all rounds are completed.

---

# Difficulty Levels

## Easy

* 5 rounds
* 2 hints allowed
* Short/simple words

## Medium

* 6 rounds
* 1 hint allowed
* Moderate-length words

## Hard

* 7 rounds
* No hints
* Long and advanced words

---

# OOP Concepts Demonstrated

## Encapsulation

Game state such as:

* score
* difficulty
* rounds
* hints

is stored privately inside the class.

---

## Inheritance

`WordScrambleRace` inherits from the provided abstract `Game` base class.

```cpp
class WordScrambleRace : public Game
```

---

## Polymorphism

The game can be executed through a base class pointer:

```cpp
Game* game = new WordScrambleRace(2);
game->play();
```

---

## Abstraction

The `Game` base class provides a common interface using:

```cpp
virtual void play() = 0;
```

---

## Modularity

The game is self-contained and independently portable. It can be integrated into any compatible arcade framework without modifying internal logic.

---

# File Structure

```text
WordScrambleRace/
│
├── WordScrambleRace.h
├── WordScrambleRace.cpp
└── README.md
```

---

# Scoring System

Points are calculated using:

* difficulty multiplier
* remaining attempts
* hint penalties

Higher difficulties reward more points.

---

# Integration Support

This game is designed to be plug-and-play.

To integrate:

1. Include the header file
2. Create a `WordScrambleRace` object
3. Store it using a `Game*`
4. Call `play()`

Example:

```cpp
WordScrambleRace scramble(2);
Game* game = &scramble;
game->play();
```

---

# Technologies Used

* C++
* STL (`vector`, `algorithm`, `string`)
* Runtime polymorphism
* ANSI terminal colors
* Object-Oriented Programming principles

---

# Author

Developed as part of the CSC-213 Object-Oriented Programming project.
