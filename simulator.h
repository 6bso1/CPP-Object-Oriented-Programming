#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <fstream>
#include <cstdlib>

#include <string>

using namespace std;
using std::string;


class simulator
{
public:
	simulator();
	//this function determines the component numbers of a dynamic array which will be used to store circuit.txt data 
	void set_circuit_values(string filename);
	//this function determines the component numbers of a dynamic array which will be used to store input.txt data 
	void set_input_values(string filename);
	//this function creates arrays dynamically
	void create_array();
	//this function reads circuit.txt file and fills circuit array with the file's data
	void fill_circuit_array(string filename);
	//this function reads input.txt file and fills input array with the file's data
	void fill_input_array(string filename);
	//this function fills the gates string array with various gates names, which will be very useful later on
	void fill_gates_array();
	//this function is the one that is actually executinig the simulation
	void execution();
	//this function operates as logical AND 
	void and_operator(string input1, string input2, string out, int i, int j);
	//this function operates as logical OR
	void or_operator(string input1, string input2, string out, int i, int j);
	//this function operates as logical NOT
	void not_operator(string input, string out, int i, int j);
    //this function operates as logical FLIP FLOP
	void flipflop_operator(string input, string out, int i, int j);
	//this function operates as logical DECODER
	void decoder_operator(string input1, string input2, int i, int j);
	//this function prints the outputs to output.txt
	void print();
	
private:
	string filename1; 
	string filename2; 
	//this is the 2D string array which is filled with circuit.txt data 
	string** circuit;
	//this is the 2D int array which is filled with input.txt data 
	int** input;
	//next two arrays need to be understood together. string array "gates" is the array that stores the gates' names 
	//and int array "values" is the array that stores these gates' values. the index of the arrays correspond each other
	//for example: if gates[3] = "and1", then values[3] equals to and1's value. meaning: values[x] = gates[x]'s value 
	string* gates;
	int* values;
	//this array is used to store the lengths of the circuit array's components
	int* line_length;
	//this array stores the output gates' names
	string* output_gates;
	//this array stores the output values
	int** output;
	//this indicates output array's row number
	int o_row;
	//this indicates output array's column number
	int o_column;
	//this indicates gates and values arrays' element number
	int index;
	//this indicates circuit array's row number
	int c_row;
	//this indicates circuit array's column number
	int c_column;
	//this indicates input array's row number
	int i_row;
	//this indicates input array's column number
	int i_column; 
};

#endif
