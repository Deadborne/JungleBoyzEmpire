#pragma once
#include <string>
#include <vector>

class Card {
private:
	std::string* good;
	int* amount;
	std::string* action1;
	int* num1;
	std::string* action2;
	int* num2;
	std::string* operate;
	bool* isFive;

public:
	Card();
	Card(std::string gd, int num, std::string act1, int n1, std::string act2, int n2, std::string op, bool n5);
	Card(const Card& c);
	~Card();
	std::string getGood() const { return *good; }
	int getGoodAmount() const { return *amount; }
	std::string getAction1() const { return *action1; }
	int getNumA1() const { return *num1; }
	std::string getAction2() const { return *action2; }
	int getNumA2() const { return *num2; }
	std::string getOperator() const { return *operate; }
	bool getIsFive() const { return *isFive; }
	void printCard();
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
	~Deck();
	Deck(int players);
	Deck(const Deck &d);
	Card draw(int i);
	std::vector<Card> getDeck();
	void printDeck();
	std::vector<Card> getSpace();
};

class Hand {
private:
	std::vector<Card> cards;
public:
	Hand();
	~Hand();
	void setHand(Card c);
	std::vector<Card> getHand() const;
	void printHand();
};