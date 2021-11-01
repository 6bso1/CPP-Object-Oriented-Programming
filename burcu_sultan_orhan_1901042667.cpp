#include <iostream>
using namespace std;

class ppmImage
{
public:
	int read_ppm(const string source_ppm_file_name, ppmImage& destination_object);
	int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object);

	int test_addition(const string filename_image1, const string filename_image2, const string filename_image3);
	int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3);
	int test_print(const string filename_image1);
	int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice);
	ppmImage single_color(const ppmImage& source, int color_choice);
}

int main(int argc, char **argv)
{

	
	return 0;
}

