#include "HighScore.h"


CHighScore::CHighScore(void)
{
}


CHighScore::~CHighScore(void)
{
}

void CHighScore::readHighScore()
{
	string line;
	std::ifstream HighScorefile("HighScore.txt");
	if(HighScorefile.is_open())
	{
		while (std::getline (HighScorefile, line))
		{
			std::cout << line << '\n';
		}
		HighScorefile.close();
	}
	else std::cout << "cannot open file";
}

void CHighScore::writeHighScore(int score)
{
	ifstream myFile("HighScore.txt");
	int tempScore;
	string tempName;

	if (myFile.is_open())
	{
		myFile >> tempScore;
		myFile.close();
	}
	else
		cout << "unable to open file.";

	if (score < tempScore)
	{
		score = tempScore;
		//name = tempName;
	}

	ofstream myFileWrite("HighScore.txt");

	if (myFileWrite.is_open())
	{
		//myFileWrite << name << " ";
		myFileWrite << score;
		myFileWrite.close();
	}
	else
		cout << "unable to open file";
}