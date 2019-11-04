#pragma once
#include <vector>
using namespace std;
class Bid {

public:
	Bid();
	Bid(int bidAmount);
	~Bid();
	int getBidAmount();
	int* getBidAmountPointer();
	int getDate();
	void setBid(int playerId);
	void setBid(int playerId, int maxBid);
	void setDate(int playerId);
	int calculateBid(vector<int> bidList);
	int calculateDate(vector<int> dateList);
private:
	int* _bidAmount;
	int* birthdate; // YYYYMMDD

};
