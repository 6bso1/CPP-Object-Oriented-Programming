#ifndef CATALOG_H
#define CATALOG_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

class catalog
{
public:
	catalog();
	void operation();
	void fill_data_array();
	void fill_commands_array();

private:
	string filename1;
	string filename2;
	string data[100][5];
	string commands[100][4];
	int index;
	int type;
	int field;
};

#endif