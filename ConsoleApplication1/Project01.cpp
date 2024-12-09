#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


/*
This code implements a Rock, Paper, Scissors game between a player and the computer, 
with multiple rounds and the ability to play again

*/
enum enGameChoices { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo {
    short roundNumber = 0;

    enGameChoices Player1Choice;
    enGameChoices computerChoice;
    enWinner winner;
    string winnderName;
};

struct stGameResultInfo {

    short gameRounds = 0;
    short Player1WinnsTimes = 0;
    short computerWinsTimes = 0;
    short drawTimes = 0;
    enWinner gameWinner;
    string winnerName = "";
};

short readhowManyRounds()
{
    short gameRounds = 0;

    do
    {
        cout << "How many rounds would like to play? ";
        cin >> gameRounds;
    } while (gameRounds < 1 || gameRounds > 10);

    return gameRounds;
}

int randomNumber(int from, int to)
{
    return rand() % (to - from + 1) + from;
}

string winnerName(enWinner winner)
{
    string arrWinnerName[3] = { "Player1","Computer","No winner" };
    return arrWinnerName[winner - 1];
}

enWinner roundWinner(stRoundInfo roundInfo)
{
    if (roundInfo.Player1Choice == roundInfo.computerChoice)
    {
        return enWinner::Draw;
    }

    switch (roundInfo.Player1Choice)
    {
    case enGameChoices::Rock:
        return (roundInfo.computerChoice == enGameChoices::Paper) ? enWinner::Computer : enWinner::Player1;
    case enGameChoices::Paper:
        return(roundInfo.computerChoice == enGameChoices::Scissors) ? enWinner::Computer : enWinner::Player1;
    case enGameChoices::Scissors:
        return (roundInfo.computerChoice == enGameChoices::Rock) ? enWinner::Computer : enWinner::Player1;


    }

    return enWinner::Player1;

}

string choiceName(enGameChoices choice)
{
    string arrgameChoice[3] = { "Rock", "Paper", "Scissors" };
    return arrgameChoice[choice - 1];

}

void setWinnerscreenColor(enWinner winner)
{
    switch (winner)
    {
    case enWinner::Player1:
        system("color 2F");
        break;

    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;

    default:
        system("color 6F"); // Yellow
        break;

    }
}

void printRoundResult(stRoundInfo roundInfo)
{
    cout << "\n____________ Round [" << roundInfo.roundNumber << "] ____________\n\n";
    cout << "Player1 Choice: " << choiceName(roundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << choiceName(roundInfo.computerChoice) << endl;
    cout << "Round winner: [" << roundInfo.winnderName << "]\n";
    cout << "__________________________________\n" << endl;

    setWinnerscreenColor(roundInfo.winner);
}

enWinner theGameWinner(short player1WinTimes, short computerWinTimes)
{
    if (player1WinTimes < computerWinTimes) return enWinner::Computer;
    if (computerWinTimes < player1WinTimes) return enWinner::Player1;

    return enWinner::Draw;


}

stGameResultInfo fillGameresult(int gameRounds, short player1winsTimes, short computerWinsTimes, short drawTimes)
{
    stGameResultInfo gameResults;

    gameResults.gameRounds = gameRounds;
    gameResults.Player1WinnsTimes = player1winsTimes;
    gameResults.computerWinsTimes = computerWinsTimes;
    gameResults.drawTimes = drawTimes;
    gameResults.gameWinner = theGameWinner(player1winsTimes, computerWinsTimes);
    gameResults.winnerName = winnerName(gameResults.gameWinner);

    return gameResults;
}

enGameChoices readPlayer1Choice()
{
    short choice = 1;

    do
    {
        cout << "\nYour choice: [1]Rock, [2]Paper, [3]Scissors ";
        cin >> choice;
    } while (choice < 1 || choice>3);
    return (enGameChoices)choice;
}

enGameChoices readComputrChice()
{
    return (enGameChoices)randomNumber(1, 3);
}

stGameResultInfo playGame(short howManyRounds)
{
    stRoundInfo roundInfo;
    short player1WinsTimes = 0, computerWinsTimes = 0, drawTimes = 0;

    for (short gameRound = 1; gameRound <= howManyRounds; gameRound++)
    {
        cout << "\nRound[" << gameRound << "] starts:\n";
        roundInfo.roundNumber = gameRound;
        roundInfo.Player1Choice = readPlayer1Choice();
        roundInfo.computerChoice = readComputrChice();
        roundInfo.winner = roundWinner(roundInfo);
        roundInfo.winnderName = winnerName(roundInfo.winner);

        if (roundInfo.winner == enWinner::Player1)
            player1WinsTimes++;
        else if (roundInfo.winner == enWinner::Computer)
            computerWinsTimes++;
        else
            drawTimes++;

        printRoundResult(roundInfo);


    }
    return fillGameresult(howManyRounds, player1WinsTimes, computerWinsTimes, drawTimes);

}

string tabs(short numberOfTabs)
{
    string t = "";

    for (int i = 1; i <= numberOfTabs; i++)
    {
        t += "\t";
    }
    return t;
}

void showGameOverScreen() {
    cout << tabs(2) << "**********************************************************\n\n";
    cout << tabs(2) << "                 +++ G a m e  O v e r +++\n";
    cout << tabs(2) << "**********************************************************\n\n";
}

void ShowFinalGameResults(stGameResultInfo gameResults) {
    cout << tabs(2) << "_____________________ [Game Results]_____________________\n\n";
    cout << tabs(2) << "Game Rounds        : " << gameResults.gameRounds << endl;
    cout << tabs(2) << "Player1 won times  : " << gameResults.Player1WinnsTimes << endl;
    cout << tabs(2) << "Computer won times : " << gameResults.computerWinsTimes << endl;
    cout << tabs(2) << "Draw times         : " << gameResults.drawTimes << endl;
    cout << tabs(2) << "Final Winner       : " << gameResults.winnerName << endl;
    cout << tabs(2) << "___________________________________________________________\n";
    setWinnerscreenColor(gameResults.gameWinner);
}

void resetScreen() {
    system("cls");
    system("color 0F");
}

void startGame()
{
    short playAgain = 'Y';

    do
    {
        resetScreen();
        stGameResultInfo gameResult = playGame(readhowManyRounds());
        showGameOverScreen();
        ShowFinalGameResults(gameResult);
        cout << endl << tabs(3) << "Do you want to play again? Y/N? ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');

}

int main()
{
    srand((unsigned)time(NULL));

    startGame();

}