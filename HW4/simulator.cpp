#include <iostream>
#include "simulator.h"
#include <fstream>
#include <cstdlib>

#include <string>

using namespace std;
using std::string;

simulator::simulator() : filename1("circuit.txt"), filename2("input.txt")
{
	set_circuit_values(filename1);
	set_input_values(filename2);
	create_array();
	fill_circuit_array(filename1);
	fill_input_array(filename2);
	fill_gates_array();
	execution();
	print();
}

void simulator::set_circuit_values(string filename)
{
	ifstream circuit_file;
	circuit_file.open(filename);
	c_row=0;
	index=0;
	string s;
	int i=0, j=0;

	while(circuit_file >> s)
	{
		if(s== "INPUT" || s== "OUTPUT" || s== "NOT" || s== "AND" || s== "OR" || s== "FLIPFLOP" || s== "DECODER")
		{
			//if the string hits one of the above, that means a new row started
			c_row++;
			//i counts current rows element number, and j stores the max elements in a row
			//so if i is bigger than j, then j becomes i
			if(i>j)
			{
				j=i;
			}
			i=0;
		}
		else
		{
			//index counts the elements that is not one of above
			index++;
		}
		i++;
	}
	if(i>j)
	{
		j=i;
	}
	//circuit array's column number is equal to the max row length j
	c_column = j;

	circuit_file.close();
}

void simulator::set_input_values(string filename)
{
	char c;
	ifstream input_file;
	input_file.open(filename);
	i_column=1;
	i_row=0;

	while(input_file.get(c))
	{
		//if there is space, that means another integer is read before, so column number increments
		if(c==' ')
		{
			i_column++;
		}
		//if there is newline, that means another row will be read, so row number increments
		if(c=='\n')
		{
			i_row++;
		}
	}
	//i_column counts all the integers in a file, so if the program divides i_column with the row number, it gets 
	//the number of integers in a single row, which means column number
	i_column=i_column/i_row + 1;

	input_file.close();
}

void simulator::create_array()
{
	//creating arrays dynamically
	circuit = new string*[c_row];
	for(int i=0; i<c_row; i++)
	{
		circuit[i] = new string[c_column];
	}

	input = new int*[i_row];
	for(int i=0; i<i_row; i++)
	{
		input[i] = new int[i_column];
	}

	gates = new string[index];

	values = new int[index];
}

void simulator::fill_circuit_array(string filename)
{
	ifstream circuit_file;
	circuit_file.open(filename);

	int i=-1, j=0, k=0;
	string s;
	line_length = new int[c_row];

	while(circuit_file >> s)
	{
		if(s== "INPUT" || s== "OUTPUT" || s== "NOT" || s== "AND" || s== "OR" || s== "FLIPFLOP" || s== "DECODER")
		{
			if(i!=-1)
			{	
				//if string hits one of the above and i isn't in its initial value, that means a line is read
				//so the program fills the line_length array with this line's length(string number), which is counted j 
				line_length[k] = j;
				k++;
			}
			//i counts the lines, j counts the current line's string numbers(length)
			i++;
			j=0;
		}
		//i's line's j's element is stored in circuit
		circuit[i][j] = s;
		j++;
	}
	line_length[k] = j;

	circuit_file.close();
}

void simulator::fill_input_array(string filename)
{
	ifstream input_file;
	input_file.open(filename);
	//this is a standart for loop to store data from input.txt to input array
	for(int i=0; i<i_row; i++)
	{
		for(int j=0; j<i_column; j++)
		{
			input_file >> input[i][j];
		}
	}

	input_file.close();
}

void simulator::fill_gates_array()
{
	int i, j, k, x=0, cont=0;
	string s;
	//this for loop checks every row of circuit array
	for(i=0; i<c_row-1; i++)
	{
		//this for loop checks every element of the current row of the circuit array
		//loop starts at 1 because we dont need the first elements of the rows since they only declare types
		for(j=1; j<line_length[i]; j++)
		{
			//this for loop checks if the current element has already been placed in the array before
			//x counts the the numbers that is placed in gates[] array before  
			for(k=0; k<x; k++)
			{
				//if the current element matches any of the former ones, integer cont increments		
				if(circuit[i][j] == gates[k])
				{
					cont++;
				}
			}
			//if cont is equal to 0 that means the current element has not matched with any former elements
			//so the program adds it to the array
			if(cont==0)
			{	
				gates[x] = circuit[i][j];
				x++;
			}
			cont=0;
		}
		//if the type is output, program creates output_gates and output arrays
		if(circuit[i][0] == "OUTPUT")
		{
			output = new int*[i_row];
			for(int f=0; f<i_row; f++)
			{
				output[f] = new int[line_length[i]-1];
			}

			output_gates = new string[line_length[i]-1];
			k=0;
			for(j=1; j<line_length[i]; j++)
			{
				output_gates[k] = circuit[i][j];
			}
			o_row = i_row;
			o_column = line_length[i]-1;
		}
	}
}

void simulator::execution()
{
	int i, j, k;
	//this for loop makes it sure that program runs every set of the inputs
	for(i=0; i<i_row; i++)
	{
		//this for loop checks for every row in circuit array
		for(j=0; j<c_row; j++)
		{
			//if string catches output row, program fills the output_gates array with this row
			if(circuit[j][0] == "OUTPUT")
			{
				//this for loop checks for every element in current	row
				for(k=0; k<line_length[j]-1; k++)
				{
					output_gates[k] = circuit[j][k+1];
				}
			}
			if(circuit[j][0] == "INPUT")
			{
				//this for loop checks for every element in current row
				for(k=0; k<i_column; k++)
				{
					//the first elements of the gates[] array were the input gates' names
					//so the first elements of the values[] array are input gates' values, meanıng input array's values
					values[k] = input[i][k];
				}
			}
			if(circuit[j][0] == "AND")
			{
				//this for loop checks every element in gates[] array
				for(k=0; k<index; k++)
				{
					//this if condition finds the output element's position (index) in the gates[] array, which is int k
					if(gates[k] == circuit[j][1])
					{
						//two input gates, output gate, output gate's index(k) and input line(i) are sent to and func
						and_operator(circuit[j][2], circuit[j][3], circuit[j][1], k, i);
					}
				}	
			}
			if(circuit[j][0] == "OR")
			{
				//this for loop checks every element in gates[] array
				for(k=0; k<index; k++)
				{
					//this if condition finds the output element's position (index) in the gates[] array, which is int k
					if(gates[k] == circuit[j][1])
					{
						//two input gates, output gate, output gate's index(k) and input line(i) are sent to or func
						or_operator(circuit[j][2], circuit[j][3], circuit[j][1], k, i);
					}
				}
			}
			if(circuit[j][0] == "NOT")
			{
				//this for loop checks every element in gates[] array
				for(k=0; k<index; k++)
				{
					//this if condition finds the output element's position (index) in the gates[] array, which is int k	
					if(gates[k] == circuit[j][1])
					{
						//input gate, output gate, output gate's index(k) and input line(i) are sent to not func
						not_operator(circuit[j][2], circuit[j][1], k, i);
					}
				}
			}
			if(circuit[j][0] == "FLIPFLOP")
			{
				//this for loop checks every element in gates[] array
				for(k=0; k<index; k++)
				{
					//this if condition finds the output element's position (index) in the gates[] array, which is int k
					if(gates[k] == circuit[j][1])
					{
						//if the input line number is 0 (this is the first inputs) that means input value of this is 0
						if(i==0)
						{
							values[k] = 0;
						}
						//input gate, output gate, output gate's index(k) and input line(i) are sent to flipflop func
						flipflop_operator(circuit[j][2], circuit[j][1], k, i);
					}
				}
			}
			if(circuit[j][0] == "DECODER")
			{
				int temp;
				//these two for loops find which of the input gates' index in gates[] array is bigger
				for(k=0; k<index; k++)
				{
					if(gates[k] == circuit[j][6])
					{
						temp = k;
					}
				}
				for(k=0; k<index; k++)
				{
					if(gates[k] == circuit[j][5])
					{
						if(temp>k)
						{
							k = temp;
						}
						//input gates, input gates' index(k) and input line(i) are sent to decoder func
						decoder_operator(circuit[j][5], circuit[j][6], k, i);
					}
				}
			}
		}
	}
}

void simulator::and_operator(string input1, string input2, string out, int i, int j)
{
	int k, value1, value2;
	//this for loop checks every gates[] element until it finds our input gates
	for(k=0; k<i; k++)
	{
		if(gates[k] == input1)
		{
			//if input gate 1 is equal to k'th element of gates[] array, then its value is k'th element of values[] array
			value1 = values[k];
		}
		if(gates[k] == input2)
		{
			value2 = values[k];
		}
	}
	int total = value1+value2;
	//if the two inputs' addition is not equal to 2 (both of them being 1), that means output is 0
	if(total==0 || total==1)
	{
		//our output gate was the i'th element of the gates[] array so its value will be the i'th element of values[] array
		values[i] = 0;
	}
	else
	{
		values[i] = 1;
	}
	//if the output of this gate is equal to output of the whole circuit, program stores it in output array also
	if(out == output_gates[0])
	{
		output[j][0] = values[i];
	}
}

void simulator::or_operator(string input1, string input2, string out, int i, int j)
{
	int k, value1, value2;
	//this for loop checks every gates[] element until it finds our input gates
	for(k=0; k<i; k++)
	{
		//if input gate 1 is equal to k'th element of gates[] array, then its value is k'th element of values[] array
		if(gates[k] == input1)
		{
			value1 = values[k];
		}
		if(gates[k] == input2)
		{
			value2 = values[k];
		}
	}
	int total = value1+value2;
	//if the two inputs' addition is not equal to 0 (both of them being 0), that means output is 0
	if(total==0)
	{
		//our output gate was the i'th element of the gates[] array so its value will be the i'th element of values[] array
		values[i] = 0;
	}
	else
	{
		values[i] = 1;
	}
	//if the output of this gate is equal to output of the whole circuit, program stores it in output array also
	if(out == output_gates[0])
	{
		output[j][0] = values[i];
	}
}

void simulator::not_operator(string input, string out, int i, int j)
{
	int k, value;
	//this for loop checks every gates[] element until it finds our input gate
	for(k=0; k<i; k++)
	{
		//if input gate is equal to k'th element of gates[] array, then its value is k'th element of values[] array
		if(gates[k] == input)
		{
			value = values[k];
		}
	}

	if(value==0)
	{
		values[i] = 1;
	}
	else
	{
		values[i] = 0;
	}
	if(out == output_gates[0])
	{
		output[j][0] = values[i];
	}
}

void simulator::flipflop_operator(string input, string out, int i, int j)
{
	int k, value1, value2;
	//value 2 is the value already stored in the values array of the former flipflop gate's index (i)
	value2 = values[i];
	//this for loop checks every gates[] element until it finds our input gate
	for(k=0; k<i; k++)
	{
		//if input gate is equal to k'th element of gates[] array, then its value is k'th element of values[] array
		if(gates[k] == input)
		{
			value1 = values[k];
		}
	}

	int total = value1+value2;

	if(total==1)
	{
		values[i] = 1;
	}
	else
	{
		values[i] = 0;
	}
	if(out == output_gates[0])
	{
		output[j][0] = values[i];
	}
}

void simulator::decoder_operator(string input1, string input2, int i, int j)
{
	int val, k, value1, value2;
	//this for loop checks every gates[] element until it finds our input gates
	for(k=0; k<=i; k++)
	{
		//if input gate 1 is equal to k'th element of gates[] array, then its value is k'th element of values[] array
		if(gates[k] == input1)
		{
			value1 = values[k];
		}
		if(gates[k] == input2)
		{
			value2 = values[k];
		}
	}
	//since the decoder output consists of three 0's and one 1, we only have to find which element will be 1
	//that's what the int val is used for, storing the data of which element will be 1
	//if both of the inputs are 0, that means 0th element will be 1
	if(value1 + value2 == 0)
	{
		val=0;
	}
	//if first input is 0 and the second is 1, that means 1st element will be zero
	else if(value1 == 0 && value2 == 1)
	{
		val=1;
	}
	//if first input is 1 and the second is 0, that means 2nd element will be zero
	else if(value1 == 1 && value2 == 0)
	{
		val=2;
	}
	//if first input is 1 and the second is 1, that means 3rd element will be zero
	else
	{
		val=3;
	}
	//this for loop fills the output array
	for(int x=0; x<4; x++)
	{
		//if the index hits val, that means it's time for 1
		if(x==val)
		{
			output[j][x] = 1;
			values[i] = 1;
			i++;
		}
		//else, it just fills 0's
		else
		{
			output[j][x] = 0;
			values[i] = 0;
			i++;
		}
	}
}

void simulator::print()
{
	//this for loop prints the output array to the output.txt
	for(int i=0; i<o_row; i++)
	{
		for(int j=0; j<o_column; j++)
		{
			cout << output[i][j] << " ";
		}
		cout << endl;
	}
}