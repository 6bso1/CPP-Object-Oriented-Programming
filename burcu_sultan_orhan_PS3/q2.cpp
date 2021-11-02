#include <iostream>
using namespace std;

class Money
{
public:
	int getDollars();
	int getCents();
	void setDollars(int d);
	void setCents(int c);
	double getAmount();
private:
	int dollars;
	int cents;
};

int Money::getDollars()
{
	return dollars;
}

int Money::getCents()
{
	return cents;
}

void Money::setDollars(int d) 
{
	dollars = d;
}

void Money::setCents(int c)
{
	cents=c;
}

double Money::getAmount()
{
	return static_cast<double>(cents)/100;
}

int main()
{
	Money m1,m2;
	m1.setDollars(20);
	m1.setCents(35);
	m2.setDollars(0);
	m2.setCents(98);

	cout<<m1.getDollars()<<"."<<m1.getCents()<<endl;
	cout<<m1.getAmount()<<endl;
	cout<<m2.getAmount()<<endl;

	cout<<"Changing m1's dollars to 50"<<endl;
	m1.setDollars(50);
	cout<<m1.getAmount()<<endl;

	cout<<"Enter a character to exit"<<endl;
	char wait;
	cin>>wait;
	return 0;

}