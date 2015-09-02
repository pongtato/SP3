#pragma once
#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

class CHighScore

{
public:
	CHighScore(void);
	~CHighScore(void);

	void writeHighScore(int score);
	void readHighScore();
private:
};

