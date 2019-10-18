// Классическая игра в угадывание чисел

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int maxNumber = 10; // глобальная переменная 

int main()
{
	cout << "\tWelcome to Guess My Number!\n\n";

	cout << "Difficult Levels\n\n";
	cout << "1 - Easy\n";
	cout << "2 - Normal\n";
	cout << "3 - Hard\n";
	cout << "Any other integer number - Super-easy\n\n";
	int choice;
	cout << "Choice: ";
	cin >> choice;

	try // ищем исключения внутри этого блока и отправляем их в соответствующий обработчик catch
    {
        // Если пользователь ввёл отрицательное число, то выбрасывается исключение
        if (choice < 0)
            throw "Can not take negative number!"; // выбрасывается исключение типа const char*
    }
    catch (...) // обработчик исключений 
    {
        cerr << "Are you normal?" << endl;
    }
	
	switch (choice)
	{
		case 1:
			cout << "You picked Easy.\n";
			::maxNumber = 100; // обращение к глобальной переменной
			break;
		case 2:
			cout << "You picked Normal.\n";
			::maxNumber = 1000;
			break;
		case 3:
			cout << "You picked Hard.\n";
			::maxNumber = 10000;
			break;
		default:
			cout << "You get a Super-easy level!\n";
	}

	cout << "\n\nYou range from 0 to " << ::maxNumber << "\n\n";
	
	srand(static_cast<unsigned int>(time(0))); // посев генератора
	int secretNumber = rand() % ::maxNumber + 1; // между 1 и maxNumber
	int tries = 0; // кол-во попыток
	int guess; // угадываемое число
	
	do
	{
		cout << "Enter a guess: ";
		cin >> guess;
		++tries;

		if (guess > secretNumber)
		{
			cout << "Too hight!\n\n";
		}
		else if (guess < secretNumber)
		{
			cout << "Too low!\n\n";
		}
		else
		{
			cout << "\nThat's it! You got it in " << tries << " guesses!\n";
		}
	} while (guess != secretNumber);

	return 0;
}

