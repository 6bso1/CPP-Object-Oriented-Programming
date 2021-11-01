#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;

//This function generates random secret number
int generateSecretNum(int digit);
//This function checks whether the user's number is unique or not
int isUnique(int userNum, int digit);
//This function finds the first count
int firstCount(int secretNum, int userNum, int digit);
//This function finds the second count
int secondCount(int secretNum, int userNum, int digit);

int main(int argc, char const *argv[])
{
	srand(static_cast<int>(time(NULL)));
	//secret is secret number, dig is short for digit, temp and temp2 are short for temporary, cont is short for control
	int secret, dig, temp, temp2, cont;
	//num is user's number
	int i=0, j, num;
	//This if condition checks whether the command is to generate random unique number
	if(argv[1][0] == '-' && argv[1][1] == 'r')
	{
		//The program typecasts the digit number the user entered
		dig = (int)(argv[2][0]-48);
		//If user enters a digit number less than 1, program runs error
		if(dig < 1)
		{
			cout << "E0" << endl;

			return 0;
		}
		//The program generates secret number
		secret = generateSecretNum(dig);
	}
	//The program checks whether the command is to take the secret number the user entered
	else if(argv[1][0] == '-' && argv[1][1] == 'u')
	{
		//The program calculates the secret number's digit number
		dig = strlen(argv[2]);
		//This int is used to calculate the secret number the user entered
		int stepValue = 1;
		secret = 0;
		//The program typecasts the secret number from string form to the integer form, digit by digit
		for(j=dig-1; j>=0; j--)
		{
			secret += (int)(argv[2][j]-48)*stepValue;
			//The stepValue increments by 10 each time, since it represents the number's step value
			stepValue *= 10;
		}
		//The program checks whether the user's number is unique or not
		if(!isUnique(secret, dig))
		{
			cout << "E0" << endl;
			return 0;
		}
	}
	//If the user didn't enter the right commands, than the program runs error
	else
	{
		cout << "E0" << endl;
		return 0;
	}

	i=0;
	//This while loops checks whether the user managed to find the secret number for less than 100 tries
	while(i<=100)
	{
		//If the input that the user gave is not an integer, program runs error
		if(!(cin >> num))
		{
			cout << "E2" << endl;
			return 0;
		}
		i++;
		//Here the program uses the temporary variable temp, to keep the user's number and also use it
		temp = num;
		j=0;
		//This while loop checks whether the user's number's digit number matches the digit number the user decided at the beginning 
		//The program divides the number by 10 until it hits zero, and increments the variable j to count the digits
		while(temp!=0)
		{
			j++;
			temp = temp/10;
		}
		//If the digit numbers don't match, program runs error
		if(j != dig)
		{
			cout << "E1" << endl;
			return 0;
		}
		//If the user's number is not unique, program runs error
		if(!isUnique(num, dig))
		{
			cout << "E1" << endl;
			return 0;
		}
		//If the first count is equal to the digit number, that means the user found the secret number
		if(firstCount(secret, num, dig) == dig)
		{
			cout << "FOUND " << i << endl;
			return 0;
		}
		//If the user hıts 100 tries, program runs error
		else if(i==100)
		{
			cout << "FAILED" << endl;
			return 0;
		}
		//Else, program gives hints to the user
		else
		{
			cout << firstCount(secret, num, dig) << " " << secondCount(secret, num, dig) << endl;
		}
	}
	return 0;
}
//This function generates random secret number
int generateSecretNum(int digit)
{
	int i, j=0, num=0, stepValue=1, cont=0;
	int number[digit];
	//The program fills an array sized the digit number with random integers
	for(i=1; i<=digit; i++)
	{
		number[i] = (rand()%10);
		//This if condition makes sure that the first integer is not zero
		if(i==1 && number[i]==0)
		{
			i--;
		}
	}
	//With this for loop the program checks whether there are any same values in the array 
	for(i=1; i<=digit; i++)
	{
		for(j=digit; j>i; j--)
		{
			//If there are any same values in the array, the program tries to replace it with another integer that is not the same as any other value 
			if(number[i] == number[j])
			{
				//Starting with 9, the program tries to find that one integer that is different from all other values of the array
				for(int k=9; k>=0; k--)
				{
					for(int x=digit; x>=1; x--)
					{
						//If the variable k is equal to number[x], control variable cont increments
						if(k == number[x])
						{
							cont++;
						}
					}
					//If cont stays zero after the previous for loop, that means the variable k different from all others
					if(cont==0)
					{
						//The new element of the array becomes k
						number[i] = k;
						//cont is initialized again
						cont = 0;
						break;
					}
					cont=0;
				}

			}
		}
	}
	//The program found the steps that are different from each other, now it needs to create the number
	//stepValue is used for step values 
	for(i=digit; i>=1; i--)
	{
		//Ex: if the array is: {1, 2, 3}, in order to make the number 123, we need (3*1) + (2*1*10) + (1*1*10*10), that's why we increment and use the stepValue
		num = num + number[i]*stepValue;
		stepValue *= 10;
	}

	return num;
}
//This function checks whether the user's number is unique or not
int isUnique(int userNum, int digit)
{
	int number[digit];
	int i=0, j=0, cont=0;

	j=digit;
	//With this for loop the program fills an array with the steps of the number
	for(i=1; i<=digit; i++)
	{
		number[j] = userNum%10;
		userNum = userNum/10;
		j--;
	}
	//With this for loop the program checks whether the 2 elements of this array are the same
	for(i=1; i<=digit; i++)
	{
		for(j=digit; j>i; j--)
		{
			//If any two of the elements are the same, that means the number is not unique, the program returns 0
			if(number[i] == number[j])
			{
				return 0;
			}
		}
	}
	//If not, that means the number is unique and the program returns 1
	return 1;
}
//This function finds the first count
int firstCount(int secretNum, int userNum, int digit)
{
	int count=0, i;
	//With this for loop the program checks the user's number and the secret number digit by digit if the digits are the same
	for(i=0; i<digit; i++)
	{
		//Each turn, program checks the last digits
		if(secretNum%10 == userNum%10)
		{
			//If the digits are the same, count increments
			count++;
		}
		//After checking the last number, the program divides the number by 10 to get rid of the last digit that it already checked
		secretNum = secretNum/10;
		userNum = userNum/10;
	}

	return count;
}
//This function finds the second count
int secondCount(int secretNum, int userNum, int digit)
{
	//temporary variables temp1 and temp2 are used to store secret number and user's number, control variable cont is used to store te digit that will be checked
	int temp1, temp2, count=0, i, j;

	temp1 = secretNum;
	temp2 = userNum;
	//With this for loop the program checks every digit
	for(i=0; i<digit; i++)
	{
		//This for loop checks whether the cont is equal to the any of the digits of the temp2
		for(j=0; j<digit; j++)
		{
			//If the last digit of temp1 and temp2 are the same and they're not the same step value, count increments
			if(temp2%10 == temp1%10 && i!=j)
			{
				count++;
			}
			//The program gets rid of the last digit of temp2 since it checked it already
			temp2 = temp2/10;
		}
		//temp2 is initialized to user's number again, since the program will check for the next digit of the secret number
		temp2 = userNum;
		//The program gets rid of the last digit of the temp1 since it checked it already
		temp1 = temp1/10;
	}

	return count;
}