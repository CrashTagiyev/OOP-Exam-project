#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<random>
#include<string>
#include<conio.h>
#include<windows.h>
using namespace std;
namespace AdminEnum {
	enum AdminChoices {
		CreateQUizz, StartQuizz, leaderboard, Back
	};
}
namespace GuestEnum {
	enum GuestChoices {
		StartQuizz, leaderboard, Back
	};
}
char _interface[7][2]{
	{'<','-'},
	{' ',' '},
	{' ',' '},
	{' ',' '},
	{' ',' '},
	{' ',' '},
	{' ',' '},
};

class question {
private:
	static int questionsStaticNumber;
	int questionsNumber = 0;
	string quest;
	string TrueAnswer;
	vector<string>answers;
	vector<int> randomlocker{ -1,-1,-1,-1 };
	bool usedOrNotQuestion = true;
	friend class Quizz;
public:
	vector<string>RandomAnswers;
	question() = default;
	question(string question, string TrueAnswer, string answer2, string answer3, string answer4) :quest(question), TrueAnswer(TrueAnswer) {
		answers.push_back(TrueAnswer);
		answers.push_back(answer2);
		answers.push_back(answer3);
		answers.push_back(answer4);
		RandomAnswerGenerator();
	}
	string getquestion() { return quest; }
	string getTrueAnswer() { return TrueAnswer; }
	vector<string> getAnswers() { return answers; }
	void PrintQuestion() {
		cout << getquestion() << endl;
	}
	void RandomAnswerGenerator() {
		int i = 0;
		while (true)
		{

			int random = 0 + rand() % (3 - 0 + 1);

			if (randomlocker[0] > -1 && randomlocker[1] > -1 && randomlocker[2] > -1 && randomlocker[3] > -1) {
				break;
			}
			else if (random == randomlocker[0] or random == randomlocker[1] or random == randomlocker[2] or random == randomlocker[3])
			{
				continue;
			}
			else
			{
				randomlocker[i] = random;
				i++;
			}

		}
		for (size_t i = 0; i < 4; i++) {

			RandomAnswers.push_back(answers[randomlocker[i]]);
		}
	}
	void printRandomAnswers() {
		cout << quest << endl;
		for (size_t i = 0; i < 4; i++) {

			cout << i + 1 << ":" << answers[randomlocker[i]] << endl;
		}
	}
	void printQuestionAndRandomAnswersToTheFile() {
		/*questionsNumber = ++questionsStaticNumber;*/
		fstream questionsFile(R"(C:\Users\Crash\Desktop\Questions.txt)", ios::out);
		questionsFile << "Question " << questionsNumber << ":" << quest << endl;
		RandomAnswerGenerator();
		for (size_t i = 0; i < 4; i++) {

			questionsFile << i + 1 << ':' << answers[randomlocker[i]] << endl;
			RandomAnswers.push_back(answers[randomlocker[i]]);
		}
		questionsFile << endl << endl;
	}
};
int question::questionsStaticNumber = 0;



class Guest {
	friend class Quizz;
	friend class Start;
	static int sID;
	int ID = 0;
	string GuestName;
	unsigned short Rscore = 0;
	unsigned short Wscore = 0;
	unsigned short passedScore = 0;
public:
	Guest() = default;
	Guest(const string& GuestName) :GuestName(GuestName) {
		ID = ++sID;
	}
	void showScore() {
		cout << "Right answers:" << getRscore() << endl;
		cout << "Wrong answers:" << getWscore() << endl;
	}
	unsigned short getRscore() { return Rscore; }
	unsigned short getWscore() { return Wscore; }
	unsigned short getPassed() { return passedScore; }
	string getGuestName() { return GuestName; }
	int getID() { return ID; }
	void operator=(const Guest other) {
		ID = other.ID;
		GuestName = other.GuestName;
		Rscore = other.Rscore;
		Wscore = other.Wscore;
	}
};
int Guest::sID = 0;
bool guestPrediCat(Guest& G1, Guest& G2) { return G1.getRscore() > G2.getRscore(); }

class Quizz {
	friend class Start;
	//New question must have as a last character a question mark - '?'
	//size of  the answers cannot be lower than 3
	static vector<Guest> _Top10;
public:
	static vector<question>GeographyQuestions;
	static vector<question>CPPQuestions;
	static vector<question>ArihmeticQuestions;
	static vector<vector<question>>questions;
	fstream GeographyQuizzFile;
	fstream CppQuizzFile;
	fstream ArihmeticQuizzFile;
	fstream top10file;
	//constructor
	Quizz() {
		DefaultQuestions();
	}
	//methods
	void createQuiz() {

		string NewQuestion, trueAnswer, answer2, answer3, answer4;
		try
		{
			int choiceIndex = QuizzTypeInterfaceController();
			cout << "Write the question:";
			getline(cin, NewQuestion);
			if (NewQuestion[NewQuestion.size() - 1] != '?')
			{
				throw  exception("Write the question correctly write in the end question mark '?'");
			}
			cout << "Write the true answer:";
			getline(cin, trueAnswer);
			if (trueAnswer.size() < 3 || !(trueAnswer[0] >= '0') && !(trueAnswer[0] <= '9') || !(trueAnswer[0] >= 'a') && !(trueAnswer[0] <= 'z') || !(trueAnswer[0] >= 'A') && !(trueAnswer[0] <= 'Z'))
			{
				throw  exception("Size of the true answers must be more than 2");
			}
			cout << "Write the second answer:";
			getline(cin, answer2);
			if (answer2.size() < 3 || !(answer2[0] >= '0') && !(answer2[0] <= '9') || !(answer2[0] >= 'a') && !(answer2[0] <= 'z') || !(answer2[0] >= 'A') && !(answer2[0] <= 'Z'))
			{
				throw  exception("Size of the answers2 must be more than 2");
			}
			cout << "Write the third answer:";
			getline(cin, answer3);
			if (answer3.size() < 3 || !(answer3[0] >= '0') && !(answer3[0] <= '9') || !(answer3[0] >= 'a') && !(answer3[0] <= 'z') || !(answer3[0] >= 'A') && !(answer3[0] <= 'Z'))
			{
				throw  exception("Size of the answers3 must be more than 2");
			}
			cout << "Write the fourth answer:";
			getline(cin, answer4);
			if (answer4.size() < 3 || !(answer4[0] >= '0') && !(answer4[0] <= '9') || !(answer4[0] >= 'a') && !(answer4[0] <= 'z') || !(answer4[0] >= 'A') && !(answer4[0] <= 'Z'))
			{
				throw  exception("Size of the answers4 must be more than 2");
			}
			questions[choiceIndex].push_back(question(NewQuestion, trueAnswer, answer2, answer3, answer4));
			questions[choiceIndex].back().printQuestionAndRandomAnswersToTheFile();
			CreateFileByTypeOfTheQuizz(choiceIndex);
		}
		catch (const exception& ex)
		{
			cout << "Error:" << ex.what();
			Sleep(6000);
		}

	}

	void QuizTypeInterface() {
		cout << "\033[2J\033[1;1H";
		cout << endl;
		for (size_t i = 0; i < 3; i++)
		{
			cout << endl;
			switch (i)
			{
			case 0:cout << "Geography quizz: "; break;
			case 1:cout << "CPP quizz: "; break;
			case 2:cout << "Arihmetic quizz: "; break;
			}
			for (size_t j = 0; j < 2; j++)
			{
				cout << _interface[i][j];
			}
			cout << "\n\n";
		}
		cout << "\n\n";
	}

	int QuizzTypeInterfaceController() {
		_interface[0][0] = '<';
		_interface[0][1] = '-';
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 2; j++)
			{
				if (i > 0)
				{
					_interface[i][j] = ' ';
				}
			}
		}
		char a = 'i';
		int currentIndex = 0;
		while (a != 'e' and a != 'E') {
			QuizTypeInterface();
			a = _getch();
			if (a == 's' || a == 'S')
			{
				_interface[currentIndex][0] = ' ';
				_interface[currentIndex][1] = ' ';
				if (currentIndex + 1 == 3)
				{
					_interface[currentIndex][0] = ' ';
					_interface[currentIndex][1] = ' ';
					currentIndex = 0;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';

				}
				else
				{
					_interface[++currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';
				}

			}
			if (a == 'w' || a == 'W')
			{
				_interface[currentIndex][0] = ' ';
				_interface[currentIndex][1] = ' ';
				if (currentIndex - 1 == -1)
				{
					_interface[currentIndex][0] = ' ';
					_interface[currentIndex][1] = ' ';
					currentIndex = 2;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';

				}
				else
				{
					--currentIndex;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';
				}

			}
		}
		return currentIndex;
	}

	void CreateFileByTypeOfTheQuizz(int QuizTypeIndex) {

		if (QuizTypeIndex == 0)
		{
			GeographyQuizzFile.open(R"(C:\Users\Crash\Desktop\GeographyQuizz.txt)", ios::out);
			for (size_t i = 0; i < questions[QuizTypeIndex].size(); i++)
			{

				GeographyQuizzFile << endl << endl << i + 1 << "." << questions[QuizTypeIndex][i].getquestion() << endl;
				for (size_t j = 0; j < 4; j++)
				{
					GeographyQuizzFile << j + 1 << "." << questions[QuizTypeIndex][i].RandomAnswers[j] << endl;
				}
			}
			GeographyQuizzFile.close();
		}
		if (QuizTypeIndex == 1)
		{
			CppQuizzFile.open(R"(C:\Users\Crash\Desktop\CppQuizz.txt)", ios::out);
			for (size_t i = 0; i < questions[QuizTypeIndex].size(); i++)
			{

				CppQuizzFile << endl << endl << i + 1 << "." << questions[QuizTypeIndex][i].getquestion() << endl;
				for (size_t j = 0; j < 4; j++)
				{
					CppQuizzFile << j + 1 << "." << questions[QuizTypeIndex][i].RandomAnswers[j] << endl;
				}
			}
			CppQuizzFile.close();
		}
		if (QuizTypeIndex == 2)
		{
			ArihmeticQuizzFile.open(R"(C:\Users\Crash\Desktop\ArihmeticQuizz.txt)", ios::out);
			for (size_t i = 0; i < questions[QuizTypeIndex].size(); i++)
			{

				ArihmeticQuizzFile << endl << endl << i + 1 << "." << questions[QuizTypeIndex][i].getquestion() << endl;
				for (size_t j = 0; j < 4; j++)
				{
					ArihmeticQuizzFile << j + 1 << "." << questions[QuizTypeIndex][i].RandomAnswers[j] << endl;
				}
			}
			ArihmeticQuizzFile.close();
		}
	}

	void ShowInterface(int index, int QuizzTypeIndex) {
		cout << "\033[2J\033[1;1H";
		cout << questions[QuizzTypeIndex][index].getquestion();
		cout << endl;
		for (size_t i = 0; i < 7; i++)
		{
			cout << endl;
			if (i < 4)
			{
				cout << questions[QuizzTypeIndex][index].RandomAnswers[i] << ": ";
			}
			if (i == 4) { cout << "-------------------------\nPrevious:"; }
			if (i == 5) { cout << "Next:"; }
			if (i == 6) { cout << "Back to menu:"; }
			for (size_t j = 0; j < 2; j++)
			{
				cout << _interface[i][j];
			}
			cout << "\n\n";
		}
		cout << "\n\n";
	}
	int interfaceController(int index, int QuizzTypeIndex) {
		_interface[0][0] = '<';
		_interface[0][1] = '-';
		for (size_t i = 0; i < 7; i++)
		{
			for (size_t j = 0; j < 2; j++)
			{
				if (i > 0)
				{
					_interface[i][j] = ' ';
				}
			}
		}
		char a = 'i';
		int currentIndex = 0;
		while (a != 'e' and a != 'E') {
			ShowInterface(index, QuizzTypeIndex);
			a = _getch();
			if (a == 's' || a == 'S')
			{
				_interface[currentIndex][0] = ' ';
				_interface[currentIndex][1] = ' ';
				if (currentIndex + 1 == 7)
				{
					_interface[currentIndex][0] = ' ';
					_interface[currentIndex][1] = ' ';
					currentIndex = 0;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';

				}
				else
				{
					_interface[++currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';
				}

			}
			if (a == 'w' || a == 'W')
			{
				_interface[currentIndex][0] = ' ';
				_interface[currentIndex][1] = ' ';
				if (currentIndex - 1 == -1)
				{
					_interface[currentIndex][0] = ' ';
					_interface[currentIndex][1] = ' ';
					currentIndex = 6;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';

				}
				else
				{
					--currentIndex;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';
				}

			}
		}
		return currentIndex;
	}

	//this is the randomize vector trick i was find in the internet
	void RandomizeQuestions() {
		random_device rd;
		mt19937 g(rd());
		shuffle(questions[0].begin(), questions[0].end(), g);
		shuffle(questions[1].begin(), questions[1].end(), g);
		shuffle(questions[2].begin(), questions[2].end(), g);
	}

	//default questions i set.
	void DefaultQuestions() {
		GeographyQuestions.push_back(question("Amerikanin paytaxti haradi?", "DC Vashinqton", "baki", "gence", "kurdemir"));
		GeographyQuestions.push_back(question("Azerbaycanin paytaxti haradi?", "Baki", "Sumqayit", "gence", "kurdemir"));
		GeographyQuestions.push_back(question("Turkiyenin paytaxti haradi?", "Ankara", "baki", "gence", "kurdemir"));
		GeographyQuestions.push_back(question("Hindistanin paytaxti haradi?", "Dele", "baki", "gence", "kurdemir"));

		CPPQuestions.push_back(question("What is the pointer?", "Varaible that contain address of the value", "loop", "function", "container"));
		CPPQuestions.push_back(question("What arrays used for?", "for contain many elements", "for loop", "for inheritence", "for polimorphism"));
		CPPQuestions.push_back(question("Wich one of these operators we can`t use in operator overloading?", "::", "+", "==", ">"));
		CPPQuestions.push_back(question("How many byte is double?", "8", "1", "4", "16"));

		ArihmeticQuestions.push_back(question("10/2=?", "5", "2", "3", "4"));
		ArihmeticQuestions.push_back(question("77+33=?", "110", "100", "101", "111"));
		ArihmeticQuestions.push_back(question("88-22=?", "66", "99", "56", "76"));
		ArihmeticQuestions.push_back(question("99+11=?", "110", "210", "101", "100"));

		questions.push_back(GeographyQuestions);
		questions.push_back(CPPQuestions);
		questions.push_back(ArihmeticQuestions);

		CreateFileByTypeOfTheQuizz(0);
		CreateFileByTypeOfTheQuizz(1);
		CreateFileByTypeOfTheQuizz(2);
	}
	//  start overloading
	void correctTop10() {
		sort(_Top10.begin(), _Top10.end(), guestPrediCat);
	}
	void LeaderboardFile(int QTypeIndex) {
		string Quizztype;
		if (QTypeIndex == 0)Quizztype = "Geography";
		if (QTypeIndex == 1)Quizztype = "CPP";
		if (QTypeIndex == 2)Quizztype = "Arihmetic";
		top10file.open(R"(C:\Users\Crash\Desktop\Leaderboard.txt)", ios::out);
		for (size_t i = 0; i < _Top10.size(); i++)
		{
			top10file << i + 1 << ')' << _Top10[i].getGuestName() << "\nQuizz type:" << Quizztype << "\nCorrect answers:" << _Top10[i].getRscore() << "\n Wrong answers:" << _Top10[i].getWscore();
			top10file << endl;
		}
		top10file.close();
	}
	void startQuizz(Guest& Guest, int QTypeIndex) {
		RandomizeQuestions();
		int Rscore = 0;
		int Wscore = 0;
		int pass = 0;
		if (QTypeIndex == 3)
		{
			return;
		}
		for (size_t i = 0; i < questions[QTypeIndex].size(); i++)
		{
			int choice = interfaceController(i, QTypeIndex);
			if (choice == 4 and i < 1) { i = -1; continue; }

			if (choice < 4 and questions[QTypeIndex][i].RandomAnswers[choice] == questions[QTypeIndex][i].getTrueAnswer())
			{
				if (questions[QTypeIndex][i].usedOrNotQuestion == true)
				{
					++Rscore;
					questions[QTypeIndex][i].usedOrNotQuestion = false;
				}
			}
			else if (choice == 4 and i > 0) { i -= 2; }
			else if (choice == 5) {
				if (questions[QTypeIndex][i].usedOrNotQuestion == true)
				{
					++pass;
				}
				continue;
			}
			else if (choice == 6) {
				return;
			}
			else if (choice < 4 and questions[QTypeIndex][i].RandomAnswers[choice] != questions[QTypeIndex][i].getTrueAnswer()) {
				if (questions[QTypeIndex][i].usedOrNotQuestion == true)
				{
					++Wscore;
					questions[QTypeIndex][i].usedOrNotQuestion = false;
				}
			}
		}
		Guest.Rscore = Rscore;
		Guest.Wscore = Wscore;
		Guest.passedScore = pass;
		cout << "Right answers:" << Rscore << endl;
		cout << "Wrong answers:" << Wscore << endl;
		cout << "Passed answers:" << pass << endl;
		_Top10.push_back(Guest);
		LeaderboardFile(QTypeIndex);
		Sleep(3000);
	}
	void startQuizz(int QTypeIndex) {
		RandomizeQuestions();
		int Rscore = 0;
		int Wscore = 0;
		for (size_t i = 0; i < GeographyQuestions.size(); i++)
		{
			int choice = interfaceController(i, QTypeIndex);
			if (GeographyQuestions[i].RandomAnswers[choice] == GeographyQuestions[i].getTrueAnswer())
			{
				++Rscore;
			}
			else {
				++Wscore;
			}
		}
		cout << "Right answers:" << Rscore << endl;
		cout << "Wrong answers:" << Wscore << endl;
		Sleep(3000);
	}

};
vector<question>Quizz::GeographyQuestions;
vector<question>Quizz::CPPQuestions;
vector<question>Quizz::ArihmeticQuestions;
vector<vector<question>>Quizz::questions;
vector<Guest>Quizz::_Top10;

class Start {
public:
	Quizz quizzProgram;
	static vector<Guest>_Guests;
	string pass = "";
	vector<char>LocalGuestsInterface;
	Start() {
		quizzProgram;
		instruction();
	}
	//methods
	void instruction() {
		cout << "Intruction.";
		cout << "For control the cursor clickfor:\n  upper 'W'\nlower 'S' \n selecting 'E'";
		Sleep(5000);
		cout << "\033[2J\033[1;1H";
	}
	//            Login interface
	void loginInterface() {
		cout << "\033[2J\033[1;1H";
		cout << endl;
		for (size_t i = 0; i < 4; i++)
		{
			if (i == 0)cout << "Admin:";
			else if (i == 1)cout << "Guest:";
			else if (i == 2)cout << "Continue with one of the guests:";
			else if (i == 3)cout << "Show Leaderboard";
			else if (i == 4)cout << "Exit:";
			for (size_t j = 0; j < 2; j++)
			{
				cout << _interface[i][j];
			}
			cout << "\n\n";
		}
		cout << "\n\n";
	}
	int logInterfaceController() {
		_interface[0][0] = '<';
		_interface[0][1] = '-';
		for (size_t i = 0; i < 5; i++)
		{
			for (size_t j = 0; j < 2; j++)
			{
				if (i > 0)
				{
					_interface[i][j] = ' ';
				}
			}
		}
		char a = 'i';
		int currentIndex = 0;
		while (a != 'e' and a != 'E') {
			loginInterface();
			a = _getch();
			if (a == 's' || a == 'S')
			{
				_interface[currentIndex][0] = ' ';
				_interface[currentIndex][1] = ' ';
				if (currentIndex + 1 == 5)
				{
					_interface[currentIndex][0] = ' ';
					_interface[currentIndex][1] = ' ';
					currentIndex = 0;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';

				}
				else
				{
					_interface[++currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';
				}

			}
			if (a == 'w' || a == 'W')
			{
				_interface[currentIndex][0] = ' ';
				_interface[currentIndex][1] = ' ';
				if (currentIndex - 1 == -1)
				{
					_interface[currentIndex][0] = ' ';
					_interface[currentIndex][1] = ' ';
					currentIndex = 4;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';

				}
				else
				{
					--currentIndex;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';
				}

			}
		}
		return currentIndex;
	}

	//           Admin Interface
	void AdminInterface() {
		cout << "\033[2J\033[1;1H";
		cout << endl;
		for (size_t i = 0; i < 4; i++)
		{
			if (i == 0)cout << "Create new quizz:";
			else if (i == 1)cout << "Start quizz:";
			else if (i == 2)cout << "Show leaderboard:";
			else if (i == 3)cout << "Back:";
			for (size_t j = 0; j < 2; j++)
			{
				cout << _interface[i][j];
			}
			cout << "\n\n";
		}
		cout << "\n\n";
	}
	int AdminInterfaceController() {
		_interface[0][0] = '<';
		_interface[0][1] = '-';
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 2; j++)
			{
				if (i > 0)
				{
					_interface[i][j] = ' ';
				}
			}
		}
		char a = 'i';
		int currentIndex = 0;
		while (a != 'e' and a != 'E') {
			AdminInterface();
			a = _getch();
			if (a == 's' || a == 'S')
			{
				_interface[currentIndex][0] = ' ';
				_interface[currentIndex][1] = ' ';
				if (currentIndex + 1 == 4)
				{
					_interface[currentIndex][0] = ' ';
					_interface[currentIndex][1] = ' ';
					currentIndex = 0;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';

				}
				else
				{
					_interface[++currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';
				}

			}
			if (a == 'w' || a == 'W')
			{
				_interface[currentIndex][0] = ' ';
				_interface[currentIndex][1] = ' ';
				if (currentIndex - 1 == -1)
				{
					_interface[currentIndex][0] = ' ';
					_interface[currentIndex][1] = ' ';
					currentIndex = 3;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';

				}
				else
				{
					--currentIndex;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';
				}

			}
		}
		return currentIndex;
	}
	//           Guest Interface
	void GuestInterface() {
		cout << "\033[2J\033[1;1H";
		cout << endl;
		for (size_t i = 0; i < 4; i++)
		{
			if (i == 0)cout << "Start quizz:";
			else if (i == 1)cout << "Show leaderboard:";
			else if (i == 2)cout << "Back:";
			for (size_t j = 0; j < 2; j++)
			{
				cout << _interface[i][j];
			}
			cout << "\n\n";
		}
		cout << "\n\n";
	}
	int GuestInterfaceController() {
		_interface[0][0] = '<';
		_interface[0][1] = '-';
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 2; j++)
			{
				if (i > 0)
				{
					_interface[i][j] = ' ';
				}
			}
		}
		char a = 'i';
		int currentIndex = 0;
		while (a != 'e' and a != 'E') {
			GuestInterface();
			a = _getch();
			if (a == 's' || a == 'S')
			{
				_interface[currentIndex][0] = ' ';
				_interface[currentIndex][1] = ' ';
				if (currentIndex + 1 == 3)
				{
					_interface[currentIndex][0] = ' ';
					_interface[currentIndex][1] = ' ';
					currentIndex = 0;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';

				}
				else
				{
					_interface[++currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';
				}

			}
			if (a == 'w' || a == 'W')
			{
				_interface[currentIndex][0] = ' ';
				_interface[currentIndex][1] = ' ';
				if (currentIndex - 1 == -1)
				{
					_interface[currentIndex][0] = ' ';
					_interface[currentIndex][1] = ' ';
					currentIndex = 2;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';

				}
				else
				{
					--currentIndex;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';
				}

			}
		}
		return currentIndex;
	}
	void showLeaderboard() {
		try
		{
			if (quizzProgram._Top10.size() == 0)
			{
				throw exception("Leaderboard is empty");
			}
			quizzProgram.correctTop10();
			for (size_t i = 0; i < quizzProgram._Top10.size(); i++)
			{
				cout << i + 1 << "." << quizzProgram._Top10[i].getGuestName() << endl;
				cout << "RIght answers:" << quizzProgram._Top10[i].getRscore() << endl;
				cout << "Wrong answers:" << quizzProgram._Top10[i].getWscore() << endl;
				cout << "Passed answers:" << quizzProgram._Top10[i].getPassed() << endl;
				cout << "\n\n";
			}
		}
		catch (const std::exception& ex)
		{
			cout << ex.what();
		}
		Sleep(3000);
	}

	void QuizStartTypeChoiceInterface() {
		cout << "\033[2J\033[1;1H";
		cout << endl;
		for (size_t i = 0; i < 4; i++)
		{
			if (i == 0)cout << "Geography quizz:";
			else if (i == 1)cout << "CPP quizz:";
			else if (i == 2)cout << "Arihmetic quizz:";
			else if (i == 3)cout << "Back to main menu:";
			for (size_t j = 0; j < 2; j++)
			{
				cout << _interface[i][j];
			}
			cout << "\n\n";
		}
		cout << "\n\n";
	}
	int QuizStartTypeChoiceInterfaceController() {
		_interface[0][0] = '<';
		_interface[0][1] = '-';
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 2; j++)
			{
				if (i > 0)
				{
					_interface[i][j] = ' ';
				}
			}
		}
		char a = 'i';
		int currentIndex = 0;
		while (a != 'e' and a != 'E') {
			QuizStartTypeChoiceInterface();
			a = _getch();
			if (a == 's' || a == 'S')
			{
				_interface[currentIndex][0] = ' ';
				_interface[currentIndex][1] = ' ';
				if (currentIndex + 1 == 4)
				{
					_interface[currentIndex][0] = ' ';
					_interface[currentIndex][1] = ' ';
					currentIndex = 0;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';

				}
				else
				{
					_interface[++currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';
				}

			}
			if (a == 'w' || a == 'W')
			{
				_interface[currentIndex][0] = ' ';
				_interface[currentIndex][1] = ' ';
				if (currentIndex - 1 == -1)
				{
					_interface[currentIndex][0] = ' ';
					_interface[currentIndex][1] = ' ';
					currentIndex = 3;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';

				}
				else
				{
					--currentIndex;
					_interface[currentIndex][0] = '<';
					_interface[currentIndex][1] = '-';
				}

			}

		}
		return currentIndex;
	}

	void ChoiceGuestToContinueInterface() {
		cout << "\033[2J\033[1;1H";
		cout << endl;

		for (size_t i = 0; i < _Guests.size(); i++)
		{
			cout << _Guests[i].getGuestName();
			cout << " " << LocalGuestsInterface[i];

			cout << "\n\n";
		}
		cout << "\n\n";
	}

	int choiceGuestToCOntinueInterfaceController() {
		try
		{
			if (_Guests.size() == 0)
			{
				throw exception("Guests does not exist");
			}

			LocalGuestsInterface[0] = '<';
			for (size_t i = 0; i < _Guests.size(); i++)
			{
				for (size_t j = 0; j < 2; j++)
				{
					if (i > 0)
					{
						_interface[i][j] = ' ';
					}
				}
			}
			char a = 'i';
			int currentIndex = 0;
			while (a != 'e' and a != 'E') {

				ChoiceGuestToContinueInterface();
				a = _getch();
				if (a == 's' || a == 'S')
				{
					LocalGuestsInterface[currentIndex] = ' ';
					if (currentIndex + 1 == _Guests.size())
					{
						LocalGuestsInterface[currentIndex] = ' ';
						currentIndex = 0;
						LocalGuestsInterface[currentIndex] = '<';

					}
					else
					{
						LocalGuestsInterface[++currentIndex] = '<';
					}

				}
				if (a == 'w' || a == 'W')
				{
					LocalGuestsInterface[currentIndex] = ' ';
					if (currentIndex - 1 == -1)
					{
						LocalGuestsInterface[currentIndex] = ' ';
						currentIndex = _Guests.size() - 1;
						LocalGuestsInterface[currentIndex] = '<';

					}
					else
					{
						--currentIndex;
						LocalGuestsInterface[currentIndex] = '<';
					}

				}
			}
			return currentIndex;
		}
		catch (const std::exception& ex)
		{
			cout << ex.what();
			Sleep(3000);
			return -1;
		}
	}

	void adminMenu() {
		int AdminChoice = AdminInterfaceController();
		switch (AdminChoice)
		{
		case AdminEnum::CreateQUizz:quizzProgram.createQuiz();
			break;
		case AdminEnum::StartQuizz:
			int QuizzType;
			QuizzType = QuizStartTypeChoiceInterfaceController();
			quizzProgram.startQuizz(QuizzType);
			break;
		case AdminEnum::leaderboard:showLeaderboard();
			break;
		case AdminEnum::Back:start();
			break;
		}
		adminMenu();
	}

	void guestMenu() {
		string newGuestName;
		Guest newGuest;
		static int newGuestIndex = -1;
		try
		{
			cout << "\033[2J\033[1;1H";
			cout << "Write the Guest name;";
			getline(cin, newGuestName);
			for (size_t i = 0; i < _Guests.size(); i++)
			{
				if (newGuestName == _Guests[i].getGuestName())
				{
					throw exception("This name is already exist.");
				}
			}
			newGuest.GuestName = newGuestName;
			_Guests.push_back(newGuest);
			for (size_t i = 0; i < _Guests.size(); i++)
			{
				LocalGuestsInterface.push_back(' ');

			}

		}
		catch (const exception& ex)
		{
			cout << ex.what();
			Sleep(3000);
			return;
		}

		int GuestChoice = GuestInterfaceController();
		switch (GuestChoice)
		{
		case GuestEnum::StartQuizz:
			int QuizzType;
			QuizzType = QuizStartTypeChoiceInterfaceController();
			quizzProgram.startQuizz(_Guests[++newGuestIndex], QuizzType);
			break;
		case GuestEnum::leaderboard:
			showLeaderboard();
			break;
		case GuestEnum::Back:return;
			break;
		}
	}

	void start() {
		int choice = logInterfaceController();
		if (choice == 0)
		{
			cout << "write the admins password(pass is 'admin')";
			getline(cin, pass);
			if (pass == "admin") {
				//cout << "\033[2J\033[1;1H";
				cout << endl << pass << endl;

				cout << "Right password\n";
				Sleep(2000);
				adminMenu();
			}
			else {

				//cout << "\033[2J\033[1;1H";
				cout << endl << pass << endl;
				cout << "Wrong password program started again\n";
				Sleep(4000);
				start();
			}
		}
		else if (choice == 1) {
			guestMenu();
		}
		else if (choice == 2) {
			int guestChoice = choiceGuestToCOntinueInterfaceController();
			if (guestChoice < 0)
			{
				start();
			}
			int guestTypeChoice = QuizStartTypeChoiceInterfaceController();
			if (guestTypeChoice >= 0 and guestTypeChoice <= 2)
			{
				quizzProgram.startQuizz(guestTypeChoice);
			}
			else if (guestTypeChoice == 3) start();
		}
		else if (choice == 3) { showLeaderboard(); }
		else if (choice == 4) { return; }
		start();
	}
};
vector<Guest>Start::_Guests;



void main() {
	srand(time(0));
	Start s;
	s.start();
}