#include <iostream>
#include <cstdlib>
using namespace std;
int HowManyRounds() {
	int Number = 0;
	do {
		cout << "How many rounds:" << endl;
		cin >> Number;
	} while (Number < 1 || Number>10);
	return Number;
}
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };
int RandomNumber(int from, int to) {
	int RandNum = rand() % (to - from + 1) + from;
	return RandNum;
}
struct stRoundInfo {
	int RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};
struct stGameResults {
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner WinnerGame;
	string WinnerName = "";
};
enGameChoice ReadPlayer1Choice() {
	short PlayerChoice;
	do {
		cout << "Your choice : [1]:Stone [2]:Paper [3]:Scissors " << endl;
		cin >> PlayerChoice;
	} while (PlayerChoice < 1 || PlayerChoice>3);
	return enGameChoice( PlayerChoice);
}
enGameChoice GetComputerChoice() {
	return enGameChoice(RandomNumber(1, 3));
}
enWinner WhoWinnerTheRound(stRoundInfo RoundInfo) {
	if (RoundInfo.ComputerChoice == RoundInfo.Player1Choice)
		return enWinner::Draw;


	switch (RoundInfo.Player1Choice) {
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors) {
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper) {
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone) {
			return enWinner::Computer;
		}
		break;
	}
	// if you reach here then player1 winner;
	return enWinner::Player;
		
}
string WinnerName(enWinner Winner) {
	string arrWinnreName[3] = { "Player1","Computer","NoWinner" };
	return arrWinnreName[Winner - 1];



	/*
	if (Winner == enWinner::Player)
		return "Player 1";
	else if (Winner == enWinner::Computer)
		return "Computer";
	else
		return "NoWinner";*/
}
string ChoiceName(enGameChoice Choice) {
	string arrGameChoice[3] = { "Stone","Paper","Scissors" };
	return arrGameChoice[Choice - 1];
}
void SetWinnerScreenColor(enWinner Winner) {
	switch (Winner) {
	case enWinner::Computer:
		system("Color 4F");
			cout << "\a";
			break;
	case enWinner::Player:
		system("Color 2F");
		break;
	default:
			system("Color 6F");
		break;
	}
}
void PrintRoundResult(stRoundInfo RoundInfo) {
	cout << "___________ Round [" << RoundInfo.RoundNumber << "]___________" << endl;
	cout << "Your Choice     : " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Winner          : " << RoundInfo.WinnerName << endl;
	cout << "_____________________________________" << endl;
	SetWinnerScreenColor(RoundInfo.Winner);
}
enWinner WhoWonTheGame(short Player1WinTimes,short ComputerWinTimes){
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Player;
	else if (Player1WinTimes < ComputerWinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}
stGameResults FillGameResults(short GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes) {
	stGameResults GameResults;
	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.WinnerGame = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.WinnerGame);
	return GameResults;
}
stGameResults PlayGame(short HowManyRounds) {
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	for (short GameRound = 1;GameRound <= HowManyRounds;GameRound++) {
		cout << "\nRound [" << GameRound << "] begins : \n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWinnerTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		

		if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else if (RoundInfo.Winner == enWinner::Player)
			Player1WinTimes++;
		else
			DrawTimes++;

		PrintRoundResult(RoundInfo);
	}
	return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}
string Tabs(short NumberOfTabs) {
	string t = "";
	for (int i = 1;i < NumberOfTabs;i++) {
		t = t + "\t";
		cout << t;
	}
	return t;
}
void ShowGameOverScreen() {
	cout << Tabs(2) << "_________________________________________________________\n\n";
	cout << Tabs(2) << "                  ++++G a m e  O v e r ++++\n";
	cout << Tabs(2) << "_________________________________________________________\n\n";

}
void ShowFinalGameResults(stGameResults GameResults) {
	cout << Tabs(2) << "___________________ [ Game Results ]____________________\n\n";
	cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player1 won times  : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer won times :" << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw times   : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final winner :" << GameResults.WinnerName << endl;
	cout << Tabs(2) << "_____________________________________________________" << endl;
	SetWinnerScreenColor(GameResults.WinnerGame);
}
void ResetScreen() {
	system("cls");
	system("Color 0F");
}
void StartGame() {
	char PLayAgain = 'y';
	do {
		ResetScreen();
		stGameResults GameResults = PlayGame(HowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << endl << Tabs(3) << "Do you want to play again  Y/N ";
		cin >> PLayAgain;
	} while (PLayAgain == 'y' || PLayAgain == 'Y');
}

int main() {
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}
