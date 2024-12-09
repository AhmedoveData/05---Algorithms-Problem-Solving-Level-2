
#include <iostream>
using namespace std;

/*
This C++ program is a math quiz game where users answer questions based
on randomly generated arithmetic problems. The difficulty of the questions
and the type of operations (addition, subtraction, multiplication, and division)
can be chosen by the user
*/


enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };
enum enOperationType { Add = 1, Sub = 2, Multi = 3, Div = 4, MixOp = 5 };

string getOperationTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add: return "+";
    case enOperationType::Sub: return "-";
    case enOperationType::Multi: return "*";
    case enOperationType::Div: return "/";
    default: return "Mix";

    }
}

string quetionLevelText(enQuestionLevel questionLevel)
{
    string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix" };

    return arrQuestionLevelText[questionLevel - 1];
}


int randomNumber(int from, int to)
{
    return rand() % (to - from + 1) + from;
}

void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F"); // turn screen to Green
    else
    {
        system("color 4F"); // turn screen to Red
        cout << "\a"; // beep sound
    }
}

short readHowManyQuestion()
{
    short numberOfQuestion;

    do
    {
        cout << "How many questions would you like to answer? ";
        cin >> numberOfQuestion;
    } while (numberOfQuestion < 1 || numberOfQuestion>10);
    return numberOfQuestion;
}

enQuestionLevel readquetsionLevel()
{
    short questionLevel = 0;

    do
    {
        cout << "What level would you like to play? [1] Easy, [2] Med, [3] Hard, [4] Mix ";
        cin >> questionLevel;
    } while (questionLevel < 1 || questionLevel > 4);

    return (enQuestionLevel)questionLevel;
}

enOperationType readOperationType()
{
    short opType;

    do
    {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> opType;

    } while (opType < 1 || opType>5);
    return (enOperationType)opType;

}

struct stQuestion
{
    int number1 = 0;
    int number2 = 0;
    enOperationType operationType;
    enQuestionLevel questionLevel;
    int correctAnswer = 0;
    int playerAnswer = 0;
    bool answerResult = false;
};

struct stQuizz
{
    stQuestion questionList[100];
    short numberOfQuestions;
    enQuestionLevel questionLivel;
    enOperationType operationType;
    short numberOfCorrectAnwers = 0;
    short numberOfWrongAnswers = 0;
    bool isPass = false;
};

int simpleCalculater(int number1, int number2, enOperationType opType)
{
    switch (opType)
    {
    case enOperationType::Add: return number1 + number2;
    case enOperationType::Div: return number1 / number2;
    case enOperationType::Multi: return number1 * number2;
    case enOperationType::Sub: return number1 - number2;
    default: return number1 + number2;
    }
}

enOperationType getRandomOperationType()
{
    int op = randomNumber(1, 4);

    return (enOperationType)op;


}

stQuestion generateQuestion(enQuestionLevel questionLevel, enOperationType operationType)
{
    stQuestion question;

    if (questionLevel == enQuestionLevel::MixLevel)
    {
        questionLevel = (enQuestionLevel)randomNumber(1, 3);
    }

    if (operationType == enOperationType::MixOp)
    {
        operationType = getRandomOperationType();
    }
    question.operationType = operationType;

    switch (questionLevel)
    {
    case enQuestionLevel::Easy:
        question.number1 = randomNumber(1, 10);
        question.number2 = randomNumber(1, 10);
        break;
    case enQuestionLevel::Med:
        question.number1 = randomNumber(10, 100);
        question.number2 = randomNumber(10, 100);
        break;

    case enQuestionLevel::Hard:
        question.number1 = randomNumber(100, 1000);
        question.number2 = randomNumber(100, 1000);
        break;
    }
    question.correctAnswer = simpleCalculater(question.number1, question.number2, question.operationType);
    question.questionLevel = questionLevel;

    return question;
}

void generateQuizz(stQuizz& quizz)
{
    for (short question = 0; question < quizz.numberOfQuestions; question++)
    {
        quizz.questionList[question] = generateQuestion(quizz.questionLivel, quizz.operationType);
    }

}

int readQuestionAnswer()
{
    int answer = 0;
    cin >> answer;

    return answer;
}

void printTheQuestion(stQuizz& quizz, short questionNumber)
{
    cout << "\n";
    cout << "Question [" << questionNumber + 1 << "/" << quizz.numberOfQuestions << "] \n\n";
    cout << quizz.questionList[questionNumber].number1 << endl;
    cout << quizz.questionList[questionNumber].number2 << " ";
    cout << getOperationTypeSymbol(quizz.questionList[questionNumber].operationType);
    cout << "\n_________" << endl;
}

void correctTheQuestionAnswer(stQuizz& quizz, short questionNuber)
{
    if (quizz.questionList[questionNuber].playerAnswer != quizz.questionList[questionNuber].correctAnswer)
    {
        quizz.questionList[questionNuber].answerResult = false;
        quizz.numberOfWrongAnswers++;

        cout << "Wrong Answer :-( \n";
        cout << "The correct answer is: ";
        cout << quizz.questionList[questionNuber].correctAnswer;
        cout << "\n";
    }
    else
    {
        quizz.questionList[questionNuber].answerResult = true;
        quizz.numberOfCorrectAnwers++;
    }
    cout << endl;

    SetScreenColor(quizz.questionList[questionNuber].answerResult);
}

void askAndCorrectQuestionListAnswers(stQuizz& quizz)
{
    for (short questionNumber = 0; questionNumber < quizz.numberOfQuestions; questionNumber++)
    {
        printTheQuestion(quizz, questionNumber);
        quizz.questionList[questionNumber].playerAnswer = readQuestionAnswer();
        correctTheQuestionAnswer(quizz, questionNumber);

    }

    quizz.isPass = (quizz.numberOfCorrectAnwers >= quizz.numberOfWrongAnswers);
}

string getFinalResultText(bool pass)
{
    if (pass) return "Pass!";
    else return "Fail";
}

void printQuizzResults(stQuizz quizz) {
    cout << "\n";
    cout << "______________________________\n\n";
    cout << " Final Results is " << getFinalResultText(quizz.isPass);
    cout << "\n______________________________\n\n";
    cout << "Number of Questions: " << quizz.numberOfQuestions << endl;
    cout << "Questions Level    : " << quetionLevelText(quizz.questionLivel) << endl;
    cout << "OpType             : " << getOperationTypeSymbol(quizz.operationType) << endl;
    cout << "Number of Right Answers: " << quizz.numberOfCorrectAnwers << endl;
    cout << "Number of Wrong Answers: " << quizz.numberOfWrongAnswers << endl;
    cout << "______________________________\n";
}

void playMathGame()
{
    stQuizz quizz;

    quizz.numberOfQuestions = readHowManyQuestion();
    quizz.questionLivel = readquetsionLevel();
    quizz.operationType = readOperationType();

    generateQuizz(quizz);
    askAndCorrectQuestionListAnswers(quizz);
    printQuizzResults(quizz);
}

void resetScreen() {
    system("cls");
    system("color 0F");
}

void startGame()
{
    char playAgain = 'Y';

    do
    {
        resetScreen();
        playMathGame();
        cout << "Do you want play again y/n";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');


}

int main()
{
    srand((unsigned)time(NULL));

    startGame();

}