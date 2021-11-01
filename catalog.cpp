#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include "catalog.h"

using namespace std;

catalog::catalog()
{
	//this function fills the data array with the data.txt
	fill_data_array();
	//this function fills the commands array with the commands.txt
	fill_commands_array();
	operation();
}

void catalog::fill_data_array()
{
	string s;
	char c;
	ifstream d_file;
	d_file.open("data.txt");
	d_file >> s;
	int i=0, j=0, count=0, temp;

	if(s== "movie")
	{
		//temp is used for to store how many fields the catalog has
		temp = 5;
		//type is used for to store which catalog it is
		type = 3;
	}
	else if(s== "book")
	{
		temp = 5;
		type = 1;
	}
	else{
		temp = 4;
		type = 2;
	}

	while(d_file >> noskipws >> c)
	{
		//count variable counts the "'s, and if the "'s number is twice as the fields, that means new line of fields
		if(count == temp*2)
		{
			//i represents line number, so it increments
			i++;
			//count is initialized
			count=0;
			//since it's a new line, j is initialized too, since it represents the line's field number
			j=0;
		}
		if(c == '\"')
		{
			count++;
			//if the numbers of "'s is even, that means a new field is to be taken
			if(count%2 == 1 && count != 1)
			{
				//j represents the field number, so it increments
				j++;
			}
		}
		if(c != '\n')
		{
			data[i][j] += c;
		}
	}
	//field variable contains the number of lines of fields  
	field = i;
	d_file.close();
}

void catalog::fill_commands_array()
{
	string s;
	char c;
	ifstream c_file;
	c_file.open("commands.txt");
	int i=0, j=0, count=0;

	while(c_file >> noskipws >> c)
	{
		//if the char is white space, that means new field is getting taken
		if(c == ' ')
		{
			//j represents the field number, so it increments
			j++;
		}
		//if the char is newline, that means a new line of commands is getting taken
		else if(c == '\n')
		{
			//i represents the line number, so it increments
			i++;
			//j represents the field number of the current line, so it gets initialized
			j=0;
		}
		else if(c != '\"')
		{
			commands[i][j] += c;
		}
	}
	//index variable contains how many lines of commands are there 
	index = i;
	c_file.close();	
}

void catalog::operation()
{
	string fields[5];
	ofstream o_file;
	o_file.open("output.txt");
	int i, j, f_number, temp=0, count=0, omit=-1, cont=-1;
	string tempp;

	o_file << "Catalog Read: ";
	//if the type is 1, that means it's a book catalog
	if(type == 1)
	{
		o_file << "book" << endl;
		//f_number variable contains how many fields the catalog has
		f_number=4;
		//fields array contains the fields' names in order
		fields[0] = "title";
		fields[1] = "authors";
		fields[2] = "year";
		fields[3] = "tags";
	} 
	else if(type == 2)
	{
		o_file << "music" << endl;
		f_number=4;
		fields[0] = "title";
		fields[1] = "artists";
		fields[2] = "year";
		fields[3] = "genre";
	}
	else
	{
		o_file << "movie" << endl;
		f_number=5;
		fields[0] = "title";
		fields[1] = "director";
		fields[2] = "year";
		fields[3] = "genre";
		fields[4] = "starring";
	}
	//this for loops makes the loop happen as many times as there are lines of fields
	for(i=0; i<=field; i++)
	{
		for(j=i; j<field; j++)
		{
			//if two different lines' first field is the same, and it's not the former duplicate error
			//that means duplicate error
			if(data[i][0] == data[j][0] && i != j && i != temp)
			{
				temp = j;
				o_file << "Exception: duplicate entry" << endl; 
				for(int k=0; k<f_number; k++)
				{
					o_file << data[i][k];
				}
				o_file << endl;
				o_file << "Exception: duplicate entry" << endl;
				for(int k=0; k<f_number; k++)
				{
					o_file << data[j][k];
				}
				o_file << endl;
				break;
			}   
		}
	}
	//this for loops makes the loop happen as many times as there are lines of fields
	for(i=0; i<=field; i++)
	{
		for(j=0; j<f_number; j++)
		{
			//this count variable counts how many fields there are in the current line, based on the number of "'s
			if(data[i][j].find("\"") != string::npos)
			{
				count++;
			}
		}
		//if count doesnt match with f_number variable, that means there is a missing field exception
		if(count != f_number)
		{
			o_file << "Exception: missing field" << endl;
			//the program stores the line of the missing field entry in omit variable, because it'll get omited 
			omit = i;
			for(int k=0; k<f_number; k++)
			{
				o_file << data[i][k];
			}
			o_file << endl;
			count=0;
		}
		count=0;
	}
	o_file << index << " unique entries" << endl;
	//this for loop makes sure all the commands lines are operated
	for(i=0; i<index; i++)
	{
		//if the fşrst field is search, we're searching
		if(commands[i][0] == "search")
		{
			//this for loops search for the last field of the command, which is the field name that's searched
			for(j=0; j<=f_number; j++)
			{
				//if there's a match between the command and tha data fields,
				if(commands[i][3] == fields[j])
				{
					//cont variable contains its field number
					cont = j;
				}
			}
			//if cont is at its initial value, that means the command field is not found in data fields
			if(cont == -1)
			{
				o_file << "Exception: command is wrong" << endl;
				for(j=0; j<4; j++)
				{
					if(j%2 == 1)
					{
						o_file << "\"";
					}
					o_file << commands[i][j];
					if(j%2 == 1)
					{
						o_file << "\"";
					}
					o_file << " ";
				}
				o_file << endl;
			}
			//if command field is found in data fields, we search for the given field name
			else
			{
				for(j=0; j<4; j++)
				{
					if(j%2 == 1)
					{
						o_file << "\"";
					}
					o_file << commands[i][j];
					if(j%2 == 1)
					{
						o_file << "\"";
					}
					o_file << " ";
				}
				o_file << endl;
				//this for loop makes the program check every line of fields
				for(j=0; j<=field; j++)
				{
					//if any line matches and it's not the omitted line, then we found it
					if(data[j][cont].find(commands[i][1]) != string::npos && j != omit)
					{
						for(int k=0; k<f_number; k++)
						{
							o_file << data[j][k];
						}
						o_file << endl;
						break;
					}
				}
			}
			cont = -1;
		}

		if(commands[i][0] == "sort")
		{
			for(j=0; j<=f_number; j++)
			{
				if(commands[i][1] == fields[j])
				{
					cont = j;
				}
			}
			if(cont == -1)
			{
				o_file << "Exception: command is wrong" << endl;
			}
			for(j=0; j<2; j++)
			{
				if(j%2 == 1)
				{
					o_file << "\"";
				}
				o_file << commands[i][j];
				if(j%2 == 1)
				{
					o_file << "\"";
				}
				o_file << " ";
			}
			o_file << endl;
			temp=0;
			int* order = new int[field];
			int x=0;
			for(j=0; j<=field; j++)
			{
				for(int k=0; k<=field; k++)
				{
					if(data[j][cont] > data[k][cont] && data[j][cont] != "\"\" " && j!=omit)
					{
						temp++;
					}
				}
				if(data[j][cont]!= "\"\" " && j!= omit)
				{
					order[temp] = j;
					x++;
				}
				temp=0;
			}

			for(j=0; j<x; j++)
			{
				for(int w=0; w<f_number; w++)
				{
					o_file << data[order[j]][w];
				}
				o_file << endl;
			}
			cont = -1;
		}
	}
	o_file.close();
}