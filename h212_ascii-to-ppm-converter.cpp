// All the work herein is mine <03/07/2014>
// Kevin O'Neill keoneill@indiana.edu
// I have read http://studentaffairs.iub.edu/ethics/

#include <iostream>
#include <fstream>
#include <string>
#define asciiSet 127
#define colorBand 255

using namespace std;

const int size(250);

class PPM
{
private:
	string fileNameIn, fileNameOut;
	int num_rows, num_cols, brightestColor;
	string line;  // variable is used in getting each line from text file
	string fileLines[size]; // each element contains a line from text file
	char fileInArray[size][size]; // contains all characters from text file
	int imageArray[size][size];
	string ppmComments;
	bool color;
public:
	void setRowsCols();
	void setColor(bool val) {color = val;};
	void setBrightestColor(int new_limit) {brightestColor = new_limit;};
	void createArrayFromFile();
	void buildImageArray();
	void createPPMfile();
};


int main()
{
	PPM newPPM;

	newPPM.createArrayFromFile();
	newPPM.buildImageArray();	

	cout << "Would you like grayscale(0) or color(1)? ";
	int ans;
	cin >> ans;

	if (ans == 0)
	{
		newPPM.setColor(false);
		newPPM.setBrightestColor(asciiSet);
	}
	else
	{
		newPPM.setColor(true);
		newPPM.setBrightestColor(colorBand);
	}

	newPPM.createPPMfile();

	system("pause");
	return 0;
}

void PPM::createArrayFromFile()
{
	int len = 0;
	cout << "Enter name of text file: ";
	cin >> fileNameIn;

	setRowsCols(); // Gets the longest line -> Cols, and number of rows.
	
	//opening the input file
	ifstream file_in(fileNameIn, ios::in);
	if (! file_in)
	{
		cerr << fileNameIn << " could not be opened.";
		cout << endl;
		system("pause");
		exit(1);
	}
	cout << fileNameIn << " was opened." << endl;
	
	//fill one-dimensional array with each line of file
	for (int i = 0; getline(file_in, line); i++)
	{
		fileLines[i] = line;
	}

	//set elements of 2D array with empty spaces
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fileInArray[i][j] = ' ';
		}
	}

	//fill two-dimensional array with characters from each line in 'fileLines' array
	for (int iRow = 0; iRow < num_rows; iRow++)
	{
		string tempStr = fileLines[iRow];
		len = tempStr.length();
		for (int jCol = 0; jCol < len; jCol++)
		{
			fileInArray[iRow][jCol] = tempStr[jCol];
		}
	}

	file_in.close();
}

void PPM::setRowsCols() 

	//get the number of lines in file(rows) and the longest line(cols)
{
	int num_lines(0);
	int maxLen(0);
	int len(0);
	string line;
	
	//opening the input file
	ifstream file_in(fileNameIn, ios::in);
	if (! file_in)
	{
		cerr << fileNameIn << " could not be opened.";
		cout << endl;
		system("pause");
		exit(1);
	}
	cout << fileNameIn << " was opened." << endl;

	while (getline (file_in, line))
	{
		//cout << "The next line of the file is " << line << endl;
		//cout << line.length() << endl;
		num_lines++;
		len = line.length();
		if (len > maxLen)
		{
			maxLen = len;
		}
	}

	cout << "The longest line is " << maxLen << " character long." << endl;
	cout << "The number of lines is " << num_lines << endl;
	num_rows = num_lines;
	num_cols = maxLen;
}

void PPM::buildImageArray()
{
	for (int iRow = 0; iRow < num_rows; iRow++)
	{
		for (int jCol = 0; jCol < num_cols; jCol++)
		{
			char temp = fileInArray[iRow][jCol];
			if (temp == char(32) || temp == char(0))
			{
				imageArray[iRow][jCol] = 0;
			}
			else
				imageArray[iRow][jCol] = int(temp);
		}
	}
}

void PPM::createPPMfile()
{

	cout << "Enter name of new ppm file: ";
	cin >> fileNameOut;
	cout << "Enter any comments for ppm file: " << endl;
	cin.ignore();
	getline(cin, ppmComments);
	
	//opening the output file
	ofstream file_out(fileNameOut, ios::out);
	if (! file_out)
	{
		cerr << fileNameOut << " could not be opened.";
		cout << endl;
		system("pause");
		exit(1);
	}
	cout << fileNameOut << " was opened." << endl;
	
	//send data to .ppm file:
	if (color)		// if user selected color image
	{
		file_out << "P3" << endl;							// line 1 of .ppm file should read P2/grayscale, p3 color
		file_out << "# " << ppmComments << endl;			// line 2 starts with hash followed by any comments # <comments>
		file_out << num_cols << " " << num_rows << endl;	// line 3 is number of columns and rows
		file_out << brightestColor << endl;					// line 4 is brightest color, determines range
		
		for (int i = 0; i < num_rows; i++)					
		{
			for (int j = 0; j < num_cols; j++)
			{
				int temp = imageArray[i][j];
				if (temp >= 33 && temp <= 63) // lighter color -> red
				{
					file_out << temp*2 << " 0 0  ";
				}
				else if (temp >= 64 && temp <= 93) // darker color -> blue
				{
					file_out << "0 0 " << temp*2 << "  ";
				}
				else if (temp >= 94 && temp <= 126) // medium color ->green
				{
					file_out << temp << " " << temp+10 << " " << temp << "  ";
				}
				else // black
				{
					file_out << "0 0 0  ";
				}
			}
			file_out << endl;
		}
	}
	else // send grayscale image to ppm file
	{	
		file_out << "P2" << endl;							
		file_out << "# " << ppmComments << endl;			
		file_out << num_cols << " " << num_rows << endl;	
		file_out << brightestColor << endl;					

		for (int i = 0; i < num_rows; i++)				
		{
			for (int j = 0; j < num_cols; j++)
			{
				file_out << imageArray[i][j] << " ";
			}
			file_out << endl;
		}
	}


	file_out.close();

}
