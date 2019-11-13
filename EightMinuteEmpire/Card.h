#pragma once
#include <string>
#include <vector>

class Card {
private:
	std::string good;
	int amount;
	std::string action1;
	int num1;
	std::string action2;
	int num2;
	std::string operate;
	bool isFive;

public:
	Card();
	Card(std::string gd, int num, std::string act1, int n1, std::string act2, int n2, std::string op, bool n5);
	Card(const Card& c);
	~Card();
	std::string getGood() const;
	int getGoodAmount() const;
	std::string getAction1() const;
	int getNumA1() const;
	std::string getAction2() const;
	int getNumA2() const;
	std::string getOperator() const;
	bool getIsFive() const;
	std::string printCard();
	std::string formatAction(std::string action, std::string number);
};

class Deck {
private:
	int players;
	std::vector<Card> deck;
	std::vector<Card> space;
	void initializeDeck(int players);
	void initializeSpace();
	void shuffleDeck();

public:
	Deck();
	Deck(int players);
	void draw();
	std::vector<Card> getDeck() const;
	std::vector<Card> getSpace() const;
	int getDeckSize() const;
	void printDeck();
	void eraseBack();
	void removeCard(int i);
};

class Hand {
private:
	std::vector<Card> cards;
public:
	Hand();
	~Hand();
	std::vector<Card> getHand() const;
	void printHand();
	void setHand(Card c);
	void swapHand(std::vector<Card> v);
};