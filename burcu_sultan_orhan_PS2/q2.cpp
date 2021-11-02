#include <iostream>
#include <cstdlib>
#include <cctype>
using namespace std;

const int MAX_DIGIT = 20;

void input(int number[], int& numberSize);
void output(const int number[], int numberSize);
void add(int first[], int firstSize, int second[], int secondSize, int sum[], int& sumSize);

int main()
{
	int first[MAX_DIGIT+1], firstSize, second[MAX_DIGIT+1], secondSize, sum[MAX_DIGIT+1], sumSize;

	cout << "Large integer suuming program " << endl;
	cout << "Please enter an integer, 20 digits or less" << endl;
	input( first, firstSize);
	cout << "You entered " << endl;
	output( first, firstSize );
	cout << endl;
	cout << "Please enter another integer, 20 digits or less" << endl;
	input( second, secondSize);
	cout << "You entered " << endl;
	output( second, secondSize );
	cout << endl << endl;
	cout << "The sum is " << endl;
	output(first, firstSize);
	cout << endl;
	output(second, secondSize);
	cout << endl;
	cout << "---------------------------" << endl;
	add(first, firstSize, second, secondSize, sum, sumSize);
	cout << endl;

	return 0;
}

void input(int number[], int& numberSize)
{
	char ch;
	int i=0;
	numberSize=0;
	cin.get(ch);

	while('\n' != ch)
	{
		if(!isdigit(ch))
		{
			cout << "Non digit entered. Aborting " << endl;
			exit(1);
		}

		number[i] = int(ch) - int(0);
		i++;
		numberSize++;
		cin.get(ch);
	}

	if(numberSize>20)
	{
		cout << "Input size too large. Aborting " << endl;
		exit(1);
	}

	for(int k=0; k<numberSize/2; k++)
	{
		int temp = number[k];
		number[k] = number[numberSize - 1 - k];
		number[numberSize-1-k] = temp;
	}
}

void output(const int number[], int numberSize)
{
	int i;

	for(i=20; i>=numberSize; i--)
	{
		cout << " ";
	}
	for(i=numberSize-1; i>=0; i--)
	{
		cout << number[i];
	}
}

void add(int first[], int firstSize, int second[], int secondSize, int sum[], int& sumSize)
{
	int carry=0, largerSize;

	if(firstSize > secondSize)
	{
		for(int i= secondSize; i<firstSize; i++)
		{
			second[i] = 0;
			largerSize = firstSize;
		}
	}

	else
	{
		for(int i= firstSize; i<secondSize; i++)
		{
			first[i] = 0;
			largerSize = secondSize;
		}
	}

	for(int i=0; i<largerSize; i++)
	{
		sum[i] = first[i] + second[i] + carry;
		if(sum[i] > 9)
		{
			carry = 1;
			sum[i] = sum[i] - 10;
		}
		else
		{
			carry = 0;
		}
	}

	if(1 == carry)
	{
		if(largerSize == 20)
		{
			cout << "An overflow has occured. " << "The result is set to 0. " << endl;
			sumSize = 0;
			sum[0] = 0;
		}
		else
		{
			sum[largerSize] = carry;
			sumSize = largerSize+1;
		}
	}
	else
	{
		sumSize = largerSize;
	}

}