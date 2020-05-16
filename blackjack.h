#ifndef BLACKJACK_H_
#define BLACKJACK_H_
#include <vector>
class Card
{
    public:
        enum rank
        {
            ACE = 1,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING
        };
        enum type
        {
            CLUBS,DIAMONDS,HEARTS,SPADES
        };

        Card(rank, type);

        int getValue();
        void displayCard();

    private:
        rank private_Rank;
        type private_Type;
};

class Hand
{
    private:
       std::vector<Card> present_Cards;

    public:
        void add(Card);
        void clear();

        int getTotal() const;
        void showCards();
};

class Deck
{
    private:
        std::vector<Card> present_Cards;

    public:
        void populate();
        void shuffle();
        Card deal();
};

class AbstractPlayer: public Hand
{
    private:
        std::vector<Card> present_Cards;

    public:
        virtual bool isDrawing() const = 0;
        bool isBusted();
};

class ComputerPlayer: public AbstractPlayer
{
    private:
        std::vector<Card> present_Cards;

    public:
        bool isDrawing() const override;

};

class HumanPlayer: public AbstractPlayer
{
    private:
        std::vector<Card> present_Cards;

    public:
        bool isDrawing() const override;
        void announce(ComputerPlayer);
};

class BlackJackGame
{
    public:
        void play();

    private:
        Deck m_deck;
        ComputerPlayer m_casino;
};
#endif
