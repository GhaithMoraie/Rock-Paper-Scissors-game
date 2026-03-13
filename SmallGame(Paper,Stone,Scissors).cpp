#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;

int RandomNUmber(int From, int To)
{
	int Random = rand() % (To - From + 1) + From;

	return Random;

}

enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string NameWinner = "";

};

struct stGameResult
{
	short RoundNumber;
	short PlayerWinTime = 0;
	short ComputerWinTime = 0;
	short DrawTime = 0;
	enWinner Winner;
	string NameWinner = "";

};

enGameChoice PlayerChoice()
{
	short Choice = 0;

	do
	{
		cout << "Enter Choice:   1/Stone   2/Paper   3/Scioor?   ";
		cin >> Choice;

	} while (Choice < 1 || Choice>3);

	return enGameChoice(Choice);

}

enGameChoice ComputerChoice()
{
	return enGameChoice(RandomNUmber(1, 3));
}

string NameWinner(enWinner Winner)
{
	string arrNameWinner[3] = { "Player","Computer","Draw" };
	return arrNameWinner[Winner - 1];
}

string GameChoice(enGameChoice Choice)
{
	string arrGameChoice[3] = { "Stone","Paper","Scioors" };
	return arrGameChoice[Choice - 1];

}
enWinner WhoWinRound(stRoundInfo Roundinfo)
{

	if (Roundinfo.PlayerChoice == Roundinfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (Roundinfo.PlayerChoice)
	{
	case enGameChoice::Stone:
		if (Roundinfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Paper:
		if (Roundinfo.ComputerChoice == enGameChoice::Scissor)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissor:
		if (Roundinfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}

	return enWinner::Player;

}


void SetColorScreen(enWinner Winner)
{

	if (Winner == enWinner::Player)
	{
		system("color 2e");
	}
	else if (Winner == enWinner::Computer)
	{
		cout << "\a";
		system("color 4e");
	}
	else
		system("color 6e");


}

void PrintRoundInfo(stRoundInfo Roundinfo)
{
	cout << "\n-----------Round[" << Roundinfo.RoundNumber << "]----------\n";
	cout << "Player Choice: " << GameChoice(Roundinfo.PlayerChoice) << endl;
	cout << "ComputerChoice: " << GameChoice(Roundinfo.ComputerChoice) << "\n";
	cout << "Round Winner: " << Roundinfo.NameWinner << endl;
	cout << "--------------------------------------------------------------\n\n";

	SetColorScreen(Roundinfo.Winner);

}

enWinner WhoWonTheGame(short PlayerTime, short ComputerTime)
{

	if (PlayerTime > ComputerTime)
	{
		return enWinner::Player;
	}
	else if (ComputerTime > PlayerTime)
	{
		return enWinner::Computer;
	}
	else {
		return enWinner::Draw;
	}


}
stGameResult FillGameResult(short Roundnumber, short PlayerwinTime, short ComputerWinTime, short DrawTime)
{
	stGameResult Result;

	Result.RoundNumber = Roundnumber;
	Result.PlayerWinTime = PlayerwinTime;
	Result.ComputerWinTime = ComputerWinTime;
	Result.DrawTime = DrawTime;
	Result.Winner = WhoWonTheGame(PlayerwinTime, ComputerWinTime);
	Result.NameWinner = NameWinner(Result.Winner);

	return Result;

}

void ShowGameOver()
{
	cout << "\t\t_________________________________________________________\n";
	cout << "\t\t                +++G A M E  O V E R+++           \n";
	cout << "\t\t---------------------------------------------------------\n";

}
void PrintGameResult(stGameResult Result)
{


	cout << "\t\t------------------[Game Result]--------------------------\n";
	cout << "\t\tGame Round: " << Result.RoundNumber << "\n";
	cout << "\t\tPlayer Win Time:" << Result.PlayerWinTime << "\n";
	cout << "\t\tcomputer Win Time:" << Result.ComputerWinTime << "\n";
	cout << "\t\tDraw Time: " << Result.DrawTime << "\n";
	cout << "\t\tFinal Winner: " << Result.NameWinner << "\n";


}

stGameResult PlayGame(int HowMAnyRound)
{
	stRoundInfo Roundinfo;
	short PlayerWinTime = 0, ComputerWinTime = 0, DrawTime = 0;

	for (short Round = 1; Round <= HowMAnyRound; Round++)
	{
		cout << "\nRound[" << Round << "] Beging:\n";
		Roundinfo.RoundNumber = Round;
		Roundinfo.PlayerChoice = PlayerChoice();
		Roundinfo.ComputerChoice = ComputerChoice();
		Roundinfo.Winner = WhoWinRound(Roundinfo);
		Roundinfo.NameWinner = NameWinner(Roundinfo.Winner);

		if (Roundinfo.Winner == enWinner::Player)
		{
			PlayerWinTime++;
		}
		else if (Roundinfo.Winner == enWinner::Computer)
		{
			ComputerWinTime++;
		}
		else {
			DrawTime++;
		}

		PrintRoundInfo(Roundinfo);

	}

	return FillGameResult(HowMAnyRound, PlayerWinTime, ComputerWinTime, DrawTime);

}
int HowManyRound()
{

	int Round = 0;

	do
	{

		cout << "\nHow Many Round You Want t0 Play ? ";
		cin >> Round;

	} while (Round < 1 || Round>10);

	return Round;

}

void StartGame()
{
	char PlayAgain = 'y';

	do
	{
		stGameResult Game = PlayGame(HowManyRound());
		ShowGameOver();
		PrintGameResult(Game);

		cout << "\nDo Want To Play Agian? Y / y?  ";
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');


}
int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;

}
