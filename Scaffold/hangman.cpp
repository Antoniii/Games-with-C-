// Виселица

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <fstream>
using namespace std;

int main()
{
	const int MAX_WRONG = 8;
	ifstream file;
	
	vector <string> stages;
	stages.push_back("\n");
	stages.push_back("__________");
	stages.push_back("|        |");
	stages.push_back("|        |");
	stages.push_back("|        0");
	stages.push_back("|       /|\\");
	stages.push_back("|       / \\");
	stages.push_back("|");

	vector <string>::const_iterator iter; // объявление константного итератора

	file.open("words.txt"); 
	int counter = 0;
	string currentLine;
    while(getline(file, currentLine))//читаем пока чтение из файла по строкам возможно
    {
        counter++;
    }
    file.close();

    int maxNumber = counter;

	srand(static_cast<unsigned int>(time(0)));
	int Number = rand() % maxNumber + 1; // между 1 и maxNumber

	file.open("words.txt"); 
	string s;
	int count = 0;
	while(1)
	{
		++count;
		getline(file,s);
		if(count == Number)
		break;
	}
 	file.close();
 
	transform(s.begin(), s.end(), s.begin(), ::toupper); // преобразование из строчных в ЗАГЛАМНЫЕ
 	
	const string THE_WORD = s;
		
	int wrong = 0;
	string soFar(THE_WORD.size(), '_');
	string used ="";
	cout << "Welcome to Hangman. Good luck!\n";

	while ((wrong < MAX_WRONG) && (soFar != THE_WORD))
	{
		cout << "\n\nYou have " << (MAX_WRONG - wrong) << " incorrect guesses left.\n";
		cout << "\nYou've used the following letters:\n" << used << endl;
		cout << "\nSo far. The word is:\n" << soFar << endl;

		char guess;
		cout << "\n\nEnter your guess: ";
		cin >> guess;
		guess = toupper(guess);

		while (used.find(guess) != string::npos)
		{
			cout << "\nYou've already guessed " << guess << endl;
			cout << "Enter your guess: ";
			cin >> guess;
			guess = toupper(guess);
		}

		used += guess;

		if (THE_WORD.find(guess) != string::npos)
		{
			cout << "That's right! " << guess << " is in the word.\n";
			for (int i = 0; i < THE_WORD.length(); ++i)
			{
				if (THE_WORD[i] == guess)
				{
					soFar[i] = guess; 
				}
			}
		}
		else
		{
			cout << "Sorry, " << guess << " isnt't in the word.\n";
			++wrong;
			cout << wrong;
			/*
			for (int i = 0; i <= wrong; ++i)
			{
				cout << stages[i]; // нужно сделать через итератор
			}
			*/
			for (iter = stages.begin(); iter != stages.begin() + wrong ; ++iter)
			{
				cout << *iter << endl;
			}
		}
	}

	if (wrong == MAX_WRONG)
	{
		cout << "\nYou've been hanged!";
	}
	else
	{
		cout << "\nYou guessed it!";
	}

	cout << "\nThe word was " << THE_WORD << endl;
	return 0;
}
