#pragma once
#include <string>
#include <vector>
class Continent
{
private:
	int _continentId;
	std::string _continentName;
	int _continentOwnedByPlayer;
	
public:
	Continent::Continent(int _continentId);
	Continent::Continent(int _continentId, std::string _continentName);
	void setOwnerOfContinent(int _continentId, std::vector<int> _countries);


};