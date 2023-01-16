/*
A simple code in C++ explaining how to use some pure virtual functions and enum classes
Player plays against the computer:)
https://www.youtube.com/watch?v=_PUEoDYpUyQ
https://adams.osu.edu/sites/adams/files/imce/4-H/STEM_Camp/Rock%20Paper%20Scissors%20Lizard%20Spock.pdf

RULES by Sam Kaas :
Scissors cuts Paper
Paper covers Rock
Rock crushes Lizard
Lizard poisons Spock
Spock smashes Scissors
Scissors decapitates Lizard
Lizard eats Paper
Paper disproves Spock
Spock vaporizes Rock
(and as it always has) Rock crushes Scissors...
*/
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <random>

enum class choise { rock, paper, scissors, lizard, Spock };

namespace utilities {

    template <typename T>
    static T rnd(T min, T max)
    {   // avoid a crash if min is greater than max
        if (min > max) std::swap(min, max);

        static std::random_device seeder;
        static std::mt19937 gen(seeder());

        typename std::conditional<std::is_integral<T>::value,
            std::uniform_int_distribution<T>, // for integral
            std::uniform_real_distribution<T> // for real numbers
        >::type distribution(min, max);

        return distribution(gen);
    }

    static choise computerHand()
    {   // only 4 possibilities
        int h = rnd(0, 4);

        if (h == 0)
            return choise::rock;
        else if (h == 1)
            return choise::paper;
        else if (h == 2)
            return choise::scissors;
        else if (h == 3)
            return choise::lizard;
        else return
            choise::Spock;
    }
    // check if the player wins against the computer
    static bool checkParty(choise p1, choise p2)
    {
        if (p1 == choise::rock)
        {
            if (p2 == choise::paper || p2 == choise::Spock)
                return false;
            if (p2 == choise::scissors || p2 == choise::lizard)
                return true;
        }

        if (p1 == choise::paper)
        {
            if (p2 == choise::scissors || p2 == choise::lizard)
                return false;
            if (p2 == choise::rock || p2 == choise::Spock)
                return true;
        }

        if (p1 == choise::scissors)
        {
            if (p2 == choise::rock || p2 == choise::Spock)
                return false;
            if (p2 == choise::paper || p2 == choise::lizard)
                return true;
        }

        if (p1 == choise::lizard)
        {
            if (p2 == choise::rock || p2 == choise::scissors)
                return false;
            if (p2 == choise::paper || p2 == choise::Spock)
                return true;
        }

        if (p1 == choise::Spock)
        {
            if (p2 == choise::paper || p2 == choise::lizard)
                return false;
            if (p2 == choise::rock || p2 == choise::scissors)
                return true;
        }

        return false;
    }
    // convert enum to char(s)
    static const char* enumToString(choise ch) throw()
    {
        switch (ch)
        {
        case choise::rock:
            return "Rock";
        case choise::paper:
            return "Paper";
        case choise::scissors:
            return "Scissors";
        case choise::lizard:
            return "Lizard";
        case choise::Spock:
            return "Spock";
        }
        // useless
        return "unexpected";
    }

    static void displayInfo()
    {
        std::cout << "1. Rock" << std::endl;
        std::cout << "2. Paper" << std::endl;
        std::cout << "3. Scissors" << std::endl;
        std::cout << "4. Lizard" << std::endl;
        std::cout << "5. Spock" << std::endl;
        std::cout << "Choose a hand boy : ";
    }
};
// base class with our virtual function setChoise
class base {

private:
    short score = 0;

public:
    base(const std::string& name) : m_name(name) {}
    ~base() = default;
    int getScore() { return score; }
    void addScore() { ++score; }
    // pure virtual function
    virtual void setChoice() = 0;

    std::string m_name;
    choise m_choise{};
};

class player1 : public base {

public:
    player1() : base("Player") {};
    ~player1() = default;

private:
    virtual void setChoice() override
    {
        utilities::displayInfo();
        int num;
        // waits an entry between 1 and 5
        do {
            std::cin >> num;
            std::cout << std::endl;
            system("cls");

            if (num == 1)
                m_choise = choise::rock;
            if (num == 2)
                m_choise = choise::paper;
            if (num == 3)
                m_choise = choise::scissors;
            if (num == 4)
                m_choise = choise::lizard;
            if (num == 5)
                m_choise = choise::Spock;
        } while (num <= 1 && num >= 5);
    }
};

class player2 : public base {

public:
    player2() : base("Computer") {};
    ~player2() = default;

private:
    virtual void setChoice() override {
        m_choise = utilities::computerHand();
    }
};

int main() {

    base* p1 = new player1();
    base* p2 = new player2();

    do {
        std::cout << p1->m_name << " " << p1->getScore() << " : " << p2->m_name << " " << p2->getScore() << std::endl;
        std::cout << std::endl;

        p1->setChoice();
        std::cout << p1->m_name << " plays -> " << utilities::enumToString(p1->m_choise) << std::endl;

        p2->setChoice();
        std::cout << p2->m_name << " plays -> " << utilities::enumToString(p2->m_choise) << std::endl;

        if (p1->m_choise == p2->m_choise) {
            std::cout << "Whoa! You got the same hand" << std::endl;
            std::cout << std::endl;

            continue;
        }

        if (utilities::checkParty(p1->m_choise, p2->m_choise))
        {
            std::cout << p1->m_name << " wins this game..." << std::endl;
            p1->addScore();
        }
        else {
            std::cout << p2->m_name << " wins this game..." << std::endl;
            p2->addScore();
        }

        std::cout << std::endl;

    } while (p1->getScore() < 3 && p2->getScore() < 3);
    // only three winning games
    std::cout << "Final Score :" << std::endl;
    std::cout << p1->m_name << " has " << p1->getScore() << " points" << std::endl;
    std::cout << p2->m_name << " has " << p2->getScore() << " points" << std::endl;
}