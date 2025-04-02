#include<iostream>
#include<cstdlib>
using namespace std;
enum enoprationtype { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };
enum enquestionlevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

struct stquestion
{
	int number1 = 0;
	int number2 = 0;
	enoprationtype oprationtype;
	enquestionlevel questionlevel;
	int correctanswer = 0;
	int playeranswer = 0;
	bool answerresult = false;


};
struct stquizz
{
	stquestion questionliste[100];
	short numberofquestion;
	enquestionlevel questionlevel;
	enoprationtype optype;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;


};





enquestionlevel ReadQuestionsLevel()
{
	short QuestionLevel = 0;
	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel >4);
	return (enquestionlevel)QuestionLevel;
}
short ReadHowManyQuestions()
{
	short NumberOfQuestions;
	do
	{
		cout << "How Many Questions do you want to answer ? ";
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions < 1 || NumberOfQuestions >10);

	return NumberOfQuestions;
}
enoprationtype ReadOpType()
{
	short OpType;
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType >5);

	return (enoprationtype)OpType;
}

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}
enoprationtype GetRandomOperationType()
{
	short op = RandomNumber(1, 4);
	return (enoprationtype)op;
}
int simplecalculator(int number1, int number2, enoprationtype optype)
{
	switch (optype)
	{
	case enoprationtype::Add:
		return number1 + number2;
	case enoprationtype::Sub:
		return number1 - number2;
	case enoprationtype::Mult:
		return number1 * number2;
	case enoprationtype::Div:
		return number1 / number2;
	default:
		return number1 + number2;
	}

}

stquestion genratequestion(enquestionlevel questionlevel, enoprationtype optype)
{
	stquestion question;
	if (questionlevel == enquestionlevel::EasyLevel)
	{
		questionlevel = (enquestionlevel)RandomNumber(1, 3);
	}
	if (optype == enoprationtype::MixOp)
	{
		optype = GetRandomOperationType();
	}
	question.oprationtype = optype;
	switch (questionlevel)
	{
	case enquestionlevel::EasyLevel:
		question.number1 = RandomNumber(1, 10);
		question.number2 = RandomNumber(1, 10);

		question.correctanswer = simplecalculator(question.number1, question.number2, question.oprationtype);
		question.questionlevel = questionlevel;
		return question;

	case enquestionlevel::MedLevel:
		question.number1 = RandomNumber(10, 50);
		question.number2 = RandomNumber(10, 50);

		question.correctanswer = simplecalculator(question.number1, question.number2, question.oprationtype);
		question.questionlevel = questionlevel;
		return question;

	case enquestionlevel::HardLevel:
		question.number1 = RandomNumber(50, 100);
		question.number2 = RandomNumber(50, 100);

		question.correctanswer = simplecalculator(question.number1, question.number2, question.oprationtype);
		question.questionlevel = questionlevel;
		return question;
	}

	return question;

}
void genratequizzquestion(stquizz& quizz)
{
	for (short question = 0; question < quizz.numberofquestion; question++)
	{
		quizz.questionliste[question] = genratequestion(quizz.questionlevel, quizz.optype);
	}
}

string GetOpTypeSymbol(enoprationtype OpType)
{
	switch (OpType)
	{
	case enoprationtype::Add:
		return"+";
	case enoprationtype::Sub:
		return"-";
	case enoprationtype::Mult:
		return"x";
	case enoprationtype::Div:
		return"/";
	default:
		return"Mix";
	}
}
void printthequestion(stquizz& quizz, short questionnumber)
{
	cout << "\n";
	cout << "question [" << questionnumber + 1 << "/" << quizz.numberofquestion << "] \n\n";
	cout << quizz.questionliste[questionnumber].number1 << endl;
	cout << quizz.questionliste[questionnumber].number2 << " ";
	cout << GetOpTypeSymbol(quizz.questionliste[questionnumber].oprationtype);
	cout << "\n___________" << endl;

}
int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;

	return Answer;
}
void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
		system("color 4F");
	cout << "\a";
}

void CorrectTheQuestionAnswer(stquizz& quizz, short questionnumber)
{
	if (quizz.questionliste[questionnumber].playeranswer != quizz.questionliste[questionnumber].correctanswer)
	{
		quizz.questionliste[questionnumber].answerresult = false;
		quizz.NumberOfWrongAnswers++;

		cout << "worng answer :-( \n";
		cout << "the right answer is: ";
		cout << quizz.questionliste[questionnumber].correctanswer;
		cout << "\n";
	}
	else
	{
		quizz.questionliste[questionnumber].answerresult = true;
		quizz.NumberOfRightAnswers++;

		cout << "right answer :-)";
	}
	cout << endl;
	SetScreenColor(quizz.questionliste[questionnumber].answerresult);

}

void askandcorrectquestionisanswers(stquizz& quizz)
{
	for (short questionnumber = 0; questionnumber < quizz.numberofquestion; questionnumber++)
	{
		printthequestion(quizz, questionnumber);
		quizz.questionliste[questionnumber].playeranswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(quizz, questionnumber);

		quizz.isPass = (quizz.NumberOfRightAnswers >= quizz.NumberOfRightAnswers);

	}
}

string getfinalresultstext(bool pass)
{
	if (pass)
		return "pass :-)";
	else
		return "fail :-(";
}
string getquestionleveltext(enquestionlevel questionlevel)
{
	string arrquestionleveltext[4] = { "easy", "med","hard","mix" };
	return arrquestionleveltext[questionlevel - 1];
}
string getoptypesymbol(enoprationtype optype)
{
	switch (optype)
	{
	case enoprationtype::Add:
		return "+";
	case enoprationtype::Sub:
		return "-";
	case enoprationtype::Mult:
		return "*";
	case enoprationtype::Div:
		return "/";
	default:
		return "mix";
	}
}

void printquizzresults(stquizz quizz)
{
	cout << "\n";
	cout << "_________________________________\n\n";
	cout << "final results is " << getfinalresultstext(quizz.isPass) << endl;
	cout << "__________________________________\n\n";

	cout << "number of questions: " << quizz.numberofquestion << endl;
	cout << "questions level    : " << getquestionleveltext(quizz.questionlevel) << endl;
	cout << "optype             : " << getoptypesymbol(quizz.optype) << endl;
	cout << "number of right answers: " << quizz.NumberOfRightAnswers << endl;
	cout << "number of wrong answers: " << quizz.NumberOfWrongAnswers << endl;
	cout << "__________________________________\n";

}
void playmathgame()
{
	stquizz quizz;
	quizz.numberofquestion = ReadHowManyQuestions();
	quizz.questionlevel = ReadQuestionsLevel();
	quizz.optype = ReadOpType();

	genratequizzquestion(quizz);
	askandcorrectquestionisanswers(quizz);

	printquizzresults(quizz);

}
void resetscreen()
{
	system("cls");
	system("color 0F");
}

void startgame()
{
	char playagain = 'Y';
	do
	{
		resetscreen();
		playmathgame();
		cout << "do you want to play again? Y/N?";
		cin >> playagain;
	} while (playagain == 'Y' || playagain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	startgame();
	return 0;

}
