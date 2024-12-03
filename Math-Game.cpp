#include <iostream>
#include <cstdlib>

using namespace std;

enum enQuestionsLevel { EsayLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

string GetOpTypeSymbole(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy ", "Med", "Hard", "Mix " };
	return arrQuestionLevelText[QuestionLevel - 1];
}

int RandomNumber(int from, int to)
{
	int randNum = rand() % (to - from + 1) + from;
	return randNum;
}

void SetScreenColor(bool Right)
{
	if (Right)
	{
		system("color 2F");
	}
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

short ReadHowManyQuestions()
{
	short NumberOfQuestions = 0;
	do
	{
		cout << "How Many Questions do you Want To Answer ? ";
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);
	return NumberOfQuestions;
}

enQuestionsLevel  ReadQuestionsLevel()
{
	short QuestionLevel = 0;
	do
	{
		cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4);
	return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
	short OpType;
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mult, [4] Div, [5] Mix ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);
	return (enOperationType)OpType;
}


struct stQuestion {
	int Number1 = 0;
	int number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};


struct stQuizz {
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionsLevel QuestionLevel;
	enOperationType OpType;
	short NumberOfWrongAnswer = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};



int SimpleCalculator(int number1, int number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return number1 + number2;
	case enOperationType::Sub:
		return number1 - number2;
	case enOperationType::Mult:
		return number1 * number2;
	case enOperationType::Div:
		return number1 / number2;
	default:
		return number1 + number2;
	}
}


enOperationType GetRandomOperationType()
{
	int Op = RandomNumber(1, 4);
	return (enOperationType)Op;
}


stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;
	if (QuestionLevel == enQuestionsLevel::Mix)
	{
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}
	if (OpType == enOperationType::MixOp)
	{
		OpType = GetRandomOperationType();
	}

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::EsayLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.number2, Question.OperationType);

		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionsLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.number2, Question.OperationType);

		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.number2, Question.OperationType);

		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
	return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
	}
}

int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}


void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].number2 << " ";
	cout << GetOpTypeSymbole(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n_____________" << endl;
}


void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswer++;

		cout << "Wrong Answer :-( \n";
		cout << "The Right Answer is: ";

		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-) \n";
	}
	cout << endl;
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}


void AskAndCorrectQuestionListAnswer(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswer);

	/*if (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswer)
	{
		Quizz.isPass = true;
	}
	else
	{
		Quizz.isPass = false;
	}*/
}

string GetFinalResultText(bool Pass)
{
	if (Pass)
		return  "PASS :-)";
	else
		return "FAIL :-(";
}

void PrintQuizzResult(stQuizz Quizz)
{
	cout << "\n";
	cout << "____________________________\n\n";

	cout << " Final Result is " << GetFinalResultText(Quizz.isPass);

	cout << "\n___________________________\n\n";

	cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level    : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
	cout << "OpType             : " << GetOpTypeSymbole(Quizz.OpType) << endl;
	cout << "Number of Right Answer: " << Quizz.NumberOfWrongAnswer << endl;

	cout << "______________________________\n";
}



void PlayMathGame()
{
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswer(Quizz);
	PrintQuizzResult(Quizz);
}



void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StarGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		PlayMathGame();

		cout << endl << "Do You Want To Play Again? Y/N? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{

	srand((unsigned)time(NULL));

	StarGame();

	return 0;
}