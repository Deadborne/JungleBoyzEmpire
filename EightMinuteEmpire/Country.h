#pragma once
#include "stdafx.h"
#include <vector>


using namespace std;
class Country
{
private:
	int _countryId;
	int _continentId;
	int _countryOwner = -1;
	vector<int> _armiesPerPlayer{ 5,8,3,4,2 };
	vector<bool> _cities{ false, false, false, false, false };

public:
	Country(int _countryId, int _continentId);
	int getId();
	int getOwner();
	void buildCity(int _playerId);
	void setOwner(int _countryId);
	bool hasCity(int _playerId);
};