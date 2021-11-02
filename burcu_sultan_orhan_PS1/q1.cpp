#include <iostream>
using namespace std;

int main()
{
	int i, j, cont=0;

	for(i=3; i<100; i++)
	{
		for(j=2; j<i; j++)
		{
			if(i%j==0)
			{
				cont=1;
			}
		}
		if(cont==0)
		{
			cout<<i<<endl;
		}
		else
		{
			cont=0;
		}
	}
	return 0;
}