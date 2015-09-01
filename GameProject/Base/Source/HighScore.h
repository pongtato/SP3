#pragma once
#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class CHighScore

{
public:
	CHighScore(void);
	~CHighScore(void);

	void writeHighScore(string name[], int score[]);
	void readHighScore();
private:
};

