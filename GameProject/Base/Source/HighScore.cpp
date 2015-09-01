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

void CHighScore::writeHighScore(string name[], int score[])
{

	std::ofstream HighScorefile("HighScore.txt");

	int tempInt;
	string tempName;

	cout << "working" << endl;
	readHighScore();

	if(HighScorefile.is_open())
	{
		HighScorefile << name << " ";
		HighScorefile << score << std::endl;
		HighScorefile.close();
	}
	else std::cout << "unable to open file";
}