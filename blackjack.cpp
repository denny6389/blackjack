#include "blackjack.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

Card::Card(rank player_Rank, type player_Type) {
    private_Rank = player_Rank;
    private_Type = player_Type;
}

int Card::getValue() {
    if (private_Rank < 11)
        return private_Rank;
    else
        return 10;
}

void Card::displayCard() {
    char num;
    char type;

    switch (private_Type)
    {
        case CLUBS:
            type = 'C';
            break;

        case DIAMONDS:
            type = 'D';
            break;

        case HEARTS:
            type = 'H';
            break;

        case SPADES:
            type = 'S';
            break;
    }

    switch(private_Rank)
    {
        case ACE:
            num='1';
            break;

        case TWO:
            num='2';
            break;

        case THREE:
            num='3';
            break;

        case FOUR:
            num='4';
            break;

        case FIVE:
            num='5';
            break;

        case SIX:
            num='6';
            break;

        case SEVEN:
            num='7';
            break;

        case EIGHT:
            num='8';
            break;

        case NINE:
            num='9';
            break;

        case TEN:
            num='0';
            break;

        case JACK:
            num='J';
            break;

        case QUEEN:
            num='Q';
            break;

        case KING:
            num='K';
            break;

        default:
            break;
    }
    if (num == '0') {
      std::cout<<"10"<<type<<"\t";
    }
    else {
      std::cout<<num<<type<<"\t";
    }
}


void Hand::add(Card card) {
    present_Cards.push_back(card);
}

void Hand::clear() {
    present_Cards.clear();
}

int Hand::getTotal() const {

    int sum = 0;
    int Ace = 0;

    for (Card card : present_Cards)
    {
        if (card.getValue()!= 1) {
            sum += card.getValue();
        }
        else
            Ace ++;
    }
    for (int i = 0; i<Ace; i++) {
        if (sum + 11 <= 21) {
            sum += 11;
        }
        else {
            sum += 1;
        }
    }
    return sum;
}

void Hand::showCards() {
    for (Card card: present_Cards)
        card.displayCard();
}

void Deck::populate() {
    present_Cards.clear();
    for(Card::rank rank = Card::ACE; rank <= Card::KING; rank = (Card::rank)(rank+1))
    {
        for (Card::type type = Card::CLUBS; type <= Card::SPADES; type = (Card::type)(type+1))
        {
            present_Cards.push_back(Card(rank,type));
        }
    }
}

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto gen = std::default_random_engine(seed);
    std::shuffle(present_Cards.begin(), present_Cards.end(), gen);
}

Card Deck::deal() {
    int n = present_Cards.size();
    Card deal_Card = present_Cards[n - 1];
    present_Cards.erase(present_Cards.end() - 1);
    return deal_Card;
}

bool AbstractPlayer::isBusted() {
    return getTotal()>21;
}


bool HumanPlayer::isDrawing() const {
    char choice;
    std::cout<<"Do you want to drow? (y/n):";
    while(1) {
      std::cin>>choice;
      switch(choice)
      {
        case 'y':
            return true;

        case 'n':
            return false;

        default:
            std::cout<<"Invalid Input. Please type again. Do you want to drow? (y/n):";
      }
    }
}

void HumanPlayer::announce(ComputerPlayer casino) {
    if(casino.getTotal() == getTotal())
        std::cout<<"Push: No one wins"<<std::endl;

    else if(casino.getTotal()< getTotal())
        std::cout<<"Player wins"<<std::endl;

    else if(casino.getTotal()>getTotal())
        std::cout<<"Casino wins"<<std::endl;
}

bool ComputerPlayer::isDrawing() const {
    return getTotal()<=16;
}


void BlackJackGame::play() {
    m_deck.populate();
    m_deck.shuffle();
    m_casino.clear();

    HumanPlayer player;
    player.clear();

    bool cont;

    m_casino.add(m_deck.deal());
    player.add(m_deck.deal());
    player.add(m_deck.deal());

    std::cout<<"Casino: ";
    m_casino.showCards();
    std::cout<<"["<<m_casino.getTotal()<<"]"<<std::endl;

    std::cout<<"Player: ";
    player.showCards();
    std::cout<<"["<<player.getTotal()<<"]"<<std::endl;
    cont = player.isDrawing();

    while(cont)
    {
        player.add(m_deck.deal());
        std::cout<<"Player: ";
        player.showCards();
        std::cout<<"["<<player.getTotal()<<"]"<<std::endl;
        if (player.isBusted())
        {
            std::cout<<"Player busts. Casino wins"<<std::endl;
            return;
        }
        cont = player.isDrawing();
    }
    cont = m_casino.isDrawing();
    while(cont)
    {
        m_casino.add(m_deck.deal());
        std::cout<<"Casino: ";
        m_casino.showCards();
        std::cout<<"["<<m_casino.getTotal()<<"]"<<std::endl;
        if (m_casino.isBusted())
        {
            std::cout<<"Player wins. Casino busts"<<std::endl;
            return;
        }
        cont = m_casino.isDrawing();
    }
    player.announce(m_casino);
}
