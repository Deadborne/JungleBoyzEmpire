#pragma once
class GameObserver
{
public:
	~GameObserver();
	virtual void Update() = 0;

protected:
	GameObserver();
};
