// компьютер угадывает число

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{

	cout << "\tWelcome to Inverse Guess My Number!\n\n";

	int number;
	cout << "Bring me the number from 1 to " << RAND_MAX - 1 << ": ";
	cin >> number;

	int tries = 0; // кол-во попыток компьютера
		
	srand(static_cast<unsigned int>(time(0))); // посев генератора
	int guess =  rand();// (rand() % number) + 1; // угадываемое число

	unsigned int start_time =  clock(); // начальное время
	
	do
	{
		if ((guess > number) or (guess < number))
		{
		guess = (rand() % (number)) + 1; // лёгкий хак
		++tries;
		}
		else
		{
		cout << "tries = " << ++tries << endl;
		}
	} while(guess != number);

	unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время

	cout << "\n\nI found youre number with tries = " << tries << endl;
	cout << "runtime: " << search_time << " ms" << endl;

	return 0;
}
