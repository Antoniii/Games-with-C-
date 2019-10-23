// Угадывание слов с подсказками или без

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

string theWord;
string theHint;
int count;

int main()
{
	enum fields {WORD, HINT, NUM_FIELDS};
	const int NUM_WORDS = 5;

	//setlocale(LC_ALL, "Russian");

	cout << "\t\t\tWelcome to Word Jumble!\n\n";
	cout << "Угадайте слово.\n";
	cout << "Введите 'hint' для подсказки.\n";
	cout << "Введите 'FLUGGAENKDECHIOEBOLSEN' для ввыхода.\n";
	cout << "Выберите язык (ENG/RUS): ";
	string lang;
	cin >> lang;

	const string WORDS[NUM_WORDS][NUM_FIELDS]=
	{
		{"eight", "Turn me on the side and I'm everything, cut me in half and I'm nothing"},
		{"glasses", "These might help you see the answer."},
		{"dog", "cat'nt"},
		{"jumble", "It's what the game is all about."},
		{"everything","unnothing"},
	};

	const string RUWORDS[NUM_WORDS][NUM_FIELDS]=
	{
		{"пингвин", "Неофициальный символ Linux."},
		{"нидерланды", "Родина питона."},
		{"штрих", "I am a good man!"},
		{"словомеска", "Название этой игры."},
		{"синхрофазотрон","Популярный ускоритель частиц."},
	};

	srand(static_cast<unsigned int>(time(0)));
	int choice = (rand() % NUM_WORDS);

	if (lang == "ENG")
	{
		::theWord = WORDS[choice][WORD]; // слово, которое нужно угадать
		::theHint = WORDS[choice][HINT]; // подсказка
	}
	else
	{
		::theWord = RUWORDS[choice][WORD]; // слово, которое нужно угадать
		::theHint = RUWORDS[choice][HINT]; // подсказка
	}
	
	// Перемешанный вариант слова
	string jumble = ::theWord;
	int length = jumble.size();

	::count = length; // кол-во очков за игру
	
	for (int i = 0; i < length; ++i)
	{
		int index1 = (rand() % length);
		int index2 = (rand() % length);
		char temp = jumble[index1];
		jumble[index1] = jumble[index2];
		jumble[index2] = temp;
	}

	cout << "Ваше слово: " << jumble;
	string guess;
	cout << "\n\nВаш ответ: ";
	cin >> guess;

	while ((guess != theWord) && (guess != "FLUGGAENKDECHIOEBOLSEN"))
	{
		if (guess == "hint")
		{
			cout << ::theHint;
			::count -= 1; // штраф за использование подсказки
		}
		else
		{
			cout << "Это не то слово.";
		}
		cout << "\n\nВаш ответ: ";
		cin >> guess;
	} 

	if (guess == ::theWord)
	{
		cout << "\nВы отгадали слово!\n";
		cout << "Количество очков: " << ::count << endl;
	}
	cout << "\nБлагодарим вас за игру!\n";
	
	return 0;
}
