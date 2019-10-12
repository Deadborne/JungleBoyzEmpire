#pragma once
#include <vector>
using namespace std;
class Bid {
public:
	Bid();
	Bid(int bidAmount);
	~Bid();
	int* _bidAmount;
	void setBid(int playerId);
	int calculateBid(vector<int> bidList);
private:




};
