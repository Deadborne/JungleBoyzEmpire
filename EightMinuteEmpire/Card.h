#pragma once
#include <string>
#include <vector>

using namespace std;

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
	//~Card();
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

	//!!!!!!!!!!!!!!!Welton from here
	virtual ~Card();

	//virtual void createdIn() = 0;



};

class TreeCard : public Card {
	//From the tree constructor, we would just call the Card constructor with the already known good type and some passed information
public:
	
	TreeCard(int goodAmount, string action1, int n1, string action2, int n2, string op, bool n5);
	~TreeCard();
};

class AnvilCard : public Card {
public:

	AnvilCard(int goodAmount, string action1, int n1, string action2, int n2, string op, bool n5);
	~AnvilCard();
};

class CarrotCard : public Card {
public:

	CarrotCard(int goodAmount, string action1, int n1, string action2, int n2, string op, bool n5);
	~CarrotCard();
};

class CoalCard : public Card {
public:

	CoalCard(int goodAmount, string action1, int n1, string action2, int n2, string op, bool n5);
	~CoalCard();
};

class ShardCard : public Card {
public:

	ShardCard(int goodAmount, string action1, int n1, string action2, int n2, string op, bool n5);
	~ShardCard();
};

class WildCard : public Card {
public:

	WildCard(int goodAmount, string action1, int n1, string action2, int n2, string op, bool n5);
	~WildCard();
};





class Deck {
private:
	int players;
	std::vector<Card> deck;
	std::vector<Card> space;
	std::vector<Card*> ptrCard;
	void initializeDeck(int players);
	void initializeSpace();
	void shuffleDeck();

public:
	Deck();
	Deck(int players);
	~Deck();
	void draw();
	std::vector<Card> getDeck() const;
	std::vector<Card> getSpace() const;
	int getDeckSize() const;
	void printDeck();
	void printDeckWhole();
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