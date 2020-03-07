#include "A1_functions.h"

char fMenu()
{
	char *i = new char[MAX]; 
	int size; 
	bool bFail = true; 
	string j;
	char returnValue;
	do
	{
		size = 0;
		cout << endl;
		cout << "Student ID  : 5985171" << endl;
		cout << "Student Name: Aaron Lim Cong Kai" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "Welcome to Weather Information Processing System!" << endl;
		cout << endl;
		cout << "1) Read in and process a configuration file" << endl;
		cout << "2) Display city map" << endl;
		cout << "3) Display cloud coverage map(cloudiness index)" << endl;
		cout << "4) Display cloud coverage map(LMH symbols)" << endl;
		cout << "5) Display atmospheric pressure map(pressure index)" << endl;
		cout << "6) Display atmospheric pressure map(LMH symbols)" << endl;
		cout << "7) Show weather forecast summary report" << endl;
		cout << "8) Quit" << endl;
		cout << endl;
		cout << "Enter your choice: ";
		cin >> j;
		cout << endl;
		
		for(int k = 0; k < j.length();k++)
		{
			i[k] = j[k];
			size++;
		}
		if(size == 1){
			returnValue = i[0];
			if(isdigit(returnValue))
				bFail = false;
			else
			{
				cout << "You entered an invalid value, please enter (1/2/3/4/5/6/7/8)" << endl;
				cout << endl;
			}
		}
		else
		{
			cout << "You entered an invalid value, please enter (1/2/3/4/5/6/7/8)" << endl;
			cout << endl;
		}

		cin.clear();
		cin.ignore(MAX, '\n');

	}while(bFail == true);
	return returnValue;
}

void choice1(int &sizeForCity, int &sizeForCloud, int &sizeForPressure, int &x, int &y, cityPressure cP[], cloudCoverage cC[], cityMap cM[], string filename, int &minX, int &minY){
	processing(filename, cP, cC, cM, sizeForCity, sizeForCloud, sizeForPressure, x, y, minX, minY);	     
}

string menu()
{
	bool ok = true;
	string inputFilename;
	do
	{
		cout << endl;
		cout << "[Read in and process a configuration file]" << endl;
	    	cout << "Please enter input filename(-1 to exit): ";
	    	cin >> inputFilename;
		fstream inputFile(inputFilename.c_str(), fstream::in);
		if(inputFilename == "-1")
		{
			ok = false;
		}
		else
		{
			if(!inputFile){
				inputFile.close();
				cout << inputFilename << " cannot be opened, please try again" << endl;
			}
			else{
				ok = false;
				inputFile.close();
			}
		}
	}while(ok == true);	
	return inputFilename;   	   
}


void getFileSize(string inputFilename, int &sizeForCity, int &sizeForCloud, int &sizeForPressure){
	//string *ptr = new string[MAX];
	int size = 0;
	fstream inputFile(inputFilename.c_str(), fstream::in);
	if(!inputFile){
		cout << inputFilename << " cannot be opened." << endl;
		inputFile.close();
	}
	string aLine;
	while(getline(inputFile, aLine)){
		size_t pos = aLine.find(".txt");
		if (pos != string::npos)
			sizeForCity = readCityFile("citylocation.txt");
			sizeForCloud = readCloudFile("cloudcover.txt");
			sizeForPressure = readPressureFile("pressure.txt");
	}
	inputFile.close();
}

int readCityFile (string filename)
{
    	fstream inputFile (filename.c_str(), fstream::in);
	if(!inputFile)
	{
		cout << filename << " does not exist" << endl;
		inputFile.close();
	}
	
	int size = 0;
	string aLine;
    	while (getline (inputFile, aLine))
    	{
		size++;
	}
	inputFile.close();
	return --size;
}

int readCloudFile (string filename)
{
    	fstream inputFile (filename.c_str(), fstream::in);
	if(!inputFile)
	{
		cout << filename << " does not exist" << endl;
		inputFile.close();
	}


	int size = 0;
	string aLine;
   	 while (getline (inputFile, aLine))
    	{
		size++;
	}
	inputFile.close();
	return --size;
}

int readPressureFile (string filename)
{
    	fstream inputFile (filename.c_str(), fstream::in);
	if(!inputFile)
	{
		cout << filename << " does not exist" << endl;
		inputFile.close();
	}


	int size = 0;
	string aLine;
    	while (getline (inputFile, aLine))
    	{
		size++;
	}
	inputFile.close();
	return --size;
}


void processing(string inputFilename, cityPressure cP[], cloudCoverage cC[], 
cityMap cM[], int sizeForCity, int sizeForCloud, int sizeForPressure, 
int &x, int &y, int &minX, int &minY)
{
	fstream inputFile (inputFilename.c_str(), fstream::in);
	if(!inputFile)
	{
		cout << inputFilename << " does not exist" << endl;
		inputFile.close();
	}
    	string aLine;
	string xSize;
	string ySize;
   	cout << endl;
   	int *xxx = new int[MAX];
   	int *yyy = new int[MAX];
  	int xc = 0;
   	int yc = 0;
    	string gridX;
    	string gridY;
    	while (getline (inputFile, aLine))
    	{
		if(aLine[0] != '/')
		{
			vector<string>tokenStringVector = tokenizeString(aLine, "=");
			for(int i = 0; i < tokenStringVector.size();i++)
			{
				if(tokenStringVector[i].compare("GridX_IdxRange") == 0)
				{
					gridX = tokenStringVector[i];
					xSize = tokenStringVector[++i];
					vector<string>temp = tokenizeString(xSize, "-");
					for(int j = 0; j < temp.size();j++)
					{
						xxx[xc] = atoi(temp[j].c_str());
						xc++;
					}
				}
				else if(!tokenStringVector[i].compare("GridY_IdxRange"))
				{
					gridY = tokenStringVector[i];
					ySize = tokenStringVector[++i];
					vector<string>temp = tokenizeString(ySize, "-");
					for(int j = 0; j < temp.size();j++)
					{
						yyy[yc] = atoi(temp[j].c_str());
						yc++;
					}
				}	  
			}
		}
		int size = x * y;
		size_t pos = aLine.find(".txt");
		if (pos != string::npos){
			cout << "Storing data from input file: " << aLine << endl;
			if(pos == 12){
				readCityFile("citylocation.txt", sizeForCity, cM);
				cout << endl;
			}
			else if(pos == 10){
				readCloudFile("cloudcover.txt", sizeForCloud, cC);
				cout << endl;
			}
			else if(pos == 8){
				readPressureFile("pressure.txt", sizeForPressure,cP);
				cout << endl;
			}
		}
	}
	cout << endl;
	if(xc!=0)
	{
		cout << "Reading in " << gridX << ": " << xxx[0] << "-" << xxx[1] << " done"<< endl;
		for(int i = 0; i<xc;i++)
		{
			if(i == 0){	
				minX = xxx[i];
			}
			else if(i == 1)
			{
				x = xxx[i] + 1;
			}
		}
	}

	if(yc!=0)
	{
		cout << "Reading in " << gridY << ": " << yyy[0] << "-" << yyy[1] << " done"<< endl;
		for(int i = 0; i<yc;i++)
		{
			if(i == 0)
				minY = yyy[i];
			else if(i == 1)
				y = yyy[i] + 1;
		}
	}

	
	cout << endl;
	
	cout << "All records successfully stored. Going back to main menu..." << endl;
	inputFile.close();
}


void readCityFile (string filename, int sizeForCity, cityMap cM[])
{
	string *temp = new string[sizeForCity];
	string *coords = new string[sizeForCity];
	int sizeTemp = 0;
	int sizeCoords = 0;
	int y = 0;
	int x = 0;
	int cityName = 0;
	int cityNum = 0;


  	fstream inputFile (filename.c_str(), fstream::in);
	if(!inputFile)
	{
		cout << filename << " does not exist" << endl;
		inputFile.close();
	}

	cout << filename;
	
	string aLine;
   	 while (getline (inputFile, aLine))
   	 {
		vector<string> left = tokenizeString (aLine, "[");
		for(int i = 0; i < left.size();i++)
		{
			if(left[i].compare("")){
				vector<string> right = tokenizeString(left[i], "]");
				for(int j = 0; j < right.size();j++){
					if(j%2!=0){
						temp[sizeTemp] = right[j];
						sizeTemp++;
					}
					else{
						coords[sizeCoords] = right[j];
						sizeCoords++;	 	 	 	 
					}
				}
			}
		}
	}
	int *mainY = new int[sizeForCity];
	int *mainX = new int[sizeForCity];
	for(int k = 0; k < sizeCoords; k++){
		vector<string> comma = tokenizeString(coords[k], ",");
		for(int l = 0; l < comma.size();l++){
			if(l%2!=0){
				mainY[y] = atoi(comma[l].c_str());
				y++;
			}
			else{
				mainX[x] = atoi(comma[l].c_str());
				x++;
			}
		}
	}


	//last few pointers for future use
	string *mainCityName = new string[sizeForCity];
	string *mainCityNum = new string[sizeForCity];
	for(int i = 0; i < sizeTemp;i++){
		vector<string> dash = tokenizeString(temp[i], "-");
		for(int j = 1; j < dash.size();j++){
			if(j%2==0){
				mainCityName[cityName] = dash[j];
				//cout << "City name " << cityName << ": " << mainCityName[cityName] << endl;
				cityName++;
			}
			else{
				mainCityNum[cityNum] = dash[j];
				//cout << "City num " << cityNum << ": " << mainCityNum[cityNum] << endl;
				cityNum++;
			}
		}
	}
	//using those pointers to point into city map
	for(int i = 0; i < sizeForCity;i++)
	{
		cM[i].x = mainX[i];
		cM[i].y = mainY[i];
		cM[i].cityName = mainCityName[i];
		cM[i].cityNum = mainCityNum[i];
		cM[i].cityNumber = atoi(mainCityNum[i].c_str());
	}
	cout << "...done" << endl;
	inputFile.close();
}


void readCloudFile (string filename, int sizeForCloud, cloudCoverage cC[])
{
	fstream inputFile (filename.c_str(), fstream::in);
	if(!inputFile)
	{
		cout << filename << " does not exist" << endl;
		inputFile.close();
	}
	cout << filename;
	string aLine;
	int size = 0;
    	while (getline (inputFile, aLine))
    	{
		vector<string> left = tokenizeString (aLine, "[");
		for(int i = 0; i < left.size();i++)
		{
			if(i==1)
			{
				vector<string> right = tokenizeString(left[i], "]");
				for(int j = 0; j < right.size();j++)
				{
					if(j == 0){
						vector<string> comma = tokenizeString(right[j], ",");
						for(int k = 0; k < comma.size();k++)
						{
							if(k == 0)
							{
								cC[size].x = atoi(comma[k].c_str());
							}
							else if(k ==1)
							{
								cC[size].y = atoi(comma[k].c_str());
							}
						}
					}
					else if(j == 1)
					{
						vector<string>minus = tokenizeString(right[j], "-");
						for(int l = 0; l < minus.size();l++)
						{
							if(l == 1)
							{
								cC[size].cloud = atoi(minus[l].c_str());
								cC[size].index = getIndex(cC[size].cloud);
								cC[size].LMH = getLMH(cC[size].cloud);
							}
						}
					}
				}
				size++;
			}
		}
	}
	cout << "...done" << endl;
	inputFile.close();
}

string getIndex(int index)
{
	string line = "";
	if((index >= 0) && (index < 10)){
		line = "0";
	}
	else if((index >= 10) && (index < 20)){
		line = "1";
	}
	else if((index >= 20) && (index < 30)){
		line = "2";
	}
	else if((index >= 30) && (index < 40)){
		line = "3";
	}
	else if((index >= 40) && (index < 50)){
		line = "4";
	}
	else if((index >= 50) && (index < 60)){
		line = "5";
	}
	else if((index >= 60) && (index < 70)){
		line = "6";
	}
	else if((index >= 70) && (index < 80)){
		line = "7";
	}
	else if((index >= 80) && (index < 90)){
		line = "8";
	}
	else if((index >= 90) && (index < 100)){
		line = "9";
	}
	return line;
}


string getLMH(int LMH)
{
	string line = "";
	if((LMH >= 0) && (LMH < 35))
		line = "L";
	else if((LMH >= 35) && (LMH < 65))
		line = "M";
	else
		line = "H";
	return line;
}


string avgLMH(float LMH)
{
	string line;
	if((LMH >= 0) && (LMH < 35))
		line = "L";
	else if((LMH >= 35) && (LMH < 65))
		line = "M";
	else
		line = "H";
	return line;
}


void readPressureFile (string filename, int sizeForPressure, cityPressure cP[])
{
    	fstream inputFile (filename.c_str(), fstream::in);
	if(!inputFile)
	{
		cout << filename << " does not exist" << endl;
		inputFile.close();
	}
	cout << filename;
	string aLine;
	int size = 0;
    	while (getline (inputFile, aLine))
    	{
		vector<string> left = tokenizeString (aLine, "[");
		for(int i = 0; i < left.size();i++)
		{
			if(i==1)
			{
				vector<string> right = tokenizeString(left[i], "]");
				for(int j = 0; j < right.size();j++)
				{
					if(j == 0){
						vector<string> comma = tokenizeString(right[j], ",");
						for(int k = 0; k < comma.size();k++)
						{
							if(k == 0)
							{
								cP[size].x = atoi(comma[k].c_str());
							}
							else if(k ==1)
							{
								cP[size].y = atoi(comma[k].c_str());
							}
						}
					}
					else if(j == 1)
					{
						vector<string>minus = tokenizeString(right[j], "-");
						for(int l = 0; l < minus.size();l++)
						{
							if(l == 1)
							{
								cP[size].pressure = atoi(minus[l].c_str());
								cP[size].index = getIndex(cP[size].pressure);
								cP[size].LMH = getLMH(cP[size].pressure);
							}
						}
					}
				}
				size++;
			}
		}
	}
	cout << "...done" << endl;
	inputFile.close();
}


vector<string> tokenizeString (string input, string delimiter)
{
	size_t pos = 0;
	string token;
	vector<string> result;

	while ((pos = input.find(delimiter)) != string::npos) 
	{
    		token = input.substr(0, pos);
    		result.push_back (token);
		input.erase(0, pos + delimiter.length());
	}
	result.push_back (input);
	return (result);
}


void drawCityLocation(cityMap cM[],int citySize, int x, int y, int minX, int minY)
{	
	cout << "----------------------------" << endl;
	cout << "Displaying city location map" << endl;
	cout << endl;
	bool okay = true;
	//  ************, according to size of x
	cout << "   ";

	for(int i = minY; i < y+2;i++){
		cout << "# ";
	}
	cout << endl;
	for(int i = x-1; i >= minX; i--)
	{
		//printing out " i", i starts from x - 1
		cout << " " << i << " #";
		for(int j = minY; j < y; j++)
		{
			//setting okay to true
			okay = true;
			for(int k = 0; k < citySize;k++)
			{
				if((cM[k].x == j) && (cM[k].y == i))
				{
					//if it is printed, set okay to false
					okay = false;
					cout << " " << cM[k].cityNum;
				}
			}
			//if okay is still true, print blank spaces
			if(okay == true)
				cout << "  ";
		}
		//ending it with #
		cout << " #" << endl;
	}


	//  ******************* depending on y value
	cout << "   ";
	for(int i = minY; i < y+2;i++){
		cout << "# ";
	}
	cout << endl;
	cout << "     ";
	for(int i = minY; i < y; i++){
		cout << i << " ";
	}

	cout << endl;
}


void drawCloudIndexLocation(cloudCoverage cC[], int x, int y, int minX, int minY)
{
	cout << "--------------------------" << endl;
	cout << "Displaying cloud index map" << endl;
	cout << endl;
	bool okay = true;
	int size = x * y;


	cout << "   ";
	for(int i = minY; i < y+2;i++){
		cout << "# ";
	}
	cout << endl;
	for(int i = x-1; i >= minX; i--)
	{
		cout << " " << i << " #";
		for(int j = minY; j < y; j++)
		{
			okay = true;
			for(int k = 0; k < size;k++)
			{
				if((cC[k].x == j) && (cC[k].y == i))
				{
					okay = false;
					cout << " " << cC[k].index;
				}
			}
			if(okay == true)


				cout << "  ";
		}
		cout << " #" << endl;
	}
	cout << "   ";
	for(int i = minY; i < y+2;i++){
		cout << "# ";
	}
	cout << endl;
	cout << "     ";
	for(int i = minY; i < y; i++){
		cout << i << " ";
	}

	cout << endl;
}


void drawCloudLMHLocation(cloudCoverage cC[], int x, int y, int minX, int minY)
{
	cout << "------------------------" << endl;
	cout << "Displaying cloud LMH map" << endl;
	cout << endl;
	bool okay = true;
	int size = x * y;


	cout << "   ";
	for(int i = minY; i < y+2;i++){
		cout << "# ";
	}
	cout << endl;
	for(int i = x-1; i >= minX; i--)
	{
		cout << " " << i << " #";
		for(int j = minY; j < y; j++)
		{
			okay = true;
			for(int k = 0; k < size;k++)
			{
				if((cC[k].x == j) && (cC[k].y == i))
				{
					okay = false;
					cout << " " << cC[k].LMH;
				}
			}
			if(okay == true)
				cout << "  ";
		}
		cout << " #" << endl;
	}
	cout << "   ";
	for(int i = minY; i < y+2;i++){
		cout << "# ";
	}
	cout << endl;
	cout << "     ";
	for(int i = minY; i < y; i++){
		cout << i << " ";
	}
	cout << endl;
}
void drawPressureIndexLocation(cityPressure cP[], int x, int y, int minX, int minY)
{
	cout << "-----------------------------" << endl;
	cout << "Displaying pressure index map" << endl;
	cout << endl;
	bool okay = true;
	int size = x * y;

	cout << "   ";
	for(int i = minY; i < y+2;i++){
		cout << "# ";
	}
	cout << endl;
	for(int i = x-1; i >= minX; i--)
	{
		cout << " " << i << " #";
		for(int j = minY; j < y; j++)
		{
			okay = true;
			for(int k = 0; k < size;k++)
			{
				if((cP[k].x == j) && (cP[k].y == i))
				{
					okay = false;
					cout << " " << cP[k].index;
				}
			}
			if(okay == true)
				cout << "  ";
		}
		cout << " #" << endl;
	}
	cout << "   ";
	for(int i = minY; i < y+2;i++){
		cout << "# ";
	}
	cout << endl;
	cout << "     ";
	for(int i = minY; i < y; i++){
		cout << i << " ";
	}
	cout << endl;
}


void drawPressureLMHLocation(cityPressure cP[], int x, int y, int minX, int minY)
{
	cout << "---------------------------" << endl;
	cout << "Displaying pressure LMH map" << endl;
	cout << endl;
	bool okay = true;
	int size = x * y;

	cout << "   ";
	for(int i = minY; i < y+2;i++){
		cout << "# ";
	}
	cout << endl;
	for(int i = x-1; i >= minX; i--)
	{
		cout << " " << i << " #";
		for(int j = minY; j < y; j++)
		{
			okay = true;
			for(int k = 0; k < size;k++)
			{
				if((cP[k].x == j) && (cP[k].y == i))
				{
					okay = false;
					cout << " " << cP[k].LMH;
				}
			}
			if(okay == true)
				cout << "  ";
		}
		cout << " #" << endl;
	}
	cout << "   ";
	for(int i = minY; i < y+2;i++){
		cout << "# ";
	}
	cout << endl;


	cout << "     ";
	for(int i = minY; i < y; i++){
		cout << i << " ";
	}
	cout << endl;
}


//pass in individually
float probabilityOfRain(string pressure, string cloud)
{
	float i = 0;
	if(pressure == "L" && cloud == "H")
		i = 90;
	else if(pressure == "L" && cloud == "M")
		i = 80;
	else if(pressure == "L" && cloud == "L")
		i = 70;
	else if(pressure == "M" && cloud == "H")
		i = 60;
	else if(pressure == "M" && cloud == "M")
		i = 50;
	else if(pressure == "M" && cloud == "L")
		i = 40;
	else if(pressure == "H" && cloud == "H")
		i = 30;
	else if(pressure == "H" && cloud == "M")
		i = 20;
	else if(pressure == "H" && cloud == "L")
		i = 10;
	return i;
}


//pass in individually
void printOutOfProbabilityOfRain(float rain)
{
	if(rain >= 90){
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
		cout << "\\\\\\\\\\" << endl;
	}


	else if(rain >= 80 && rain < 90){
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
		cout << " \\\\\\\\" << endl;
	}


	else if(rain >= 70 && rain < 80){
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
		cout << "  \\\\\\" << endl;
	}
	else if(rain >= 60 && rain < 70){
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
		cout << "   \\\\" << endl;
	}
	else if(rain >= 50 && rain < 60){
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
		cout << "    \\" << endl;
	}
	else if(rain >= 40 && rain < 50){
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
	}
	else if(rain >= 30 && rain < 40){
		cout << "~~~" << endl;
		cout << "~~~~" << endl;
	}
	else if(rain >= 20 && rain < 30){
		cout << "~~" << endl;
		cout << "~~~" << endl;
	}
	else{
		cout << "~" << endl;
		cout << "~~" << endl;
	}
}


int getMaxMin(cityMap cM[], cities cit [], int sizeOfCity, int x, int y, int miniX, int miniY)
{
	int size = x * y;
	int numberOfCity = 0;
	int minX, minY, maxX, maxY;

	for(int i = 0; i < sizeOfCity; i++)
	{
		if(numberOfCity < cM[i].cityNumber){
			numberOfCity = cM[i].cityNumber;
		}
	}

	for(int i =0; i < numberOfCity; i++)
	{	
		cities cityy;
		cityy.cityNumber = i+1;
		cit[i] = cityy;
	}
	for(int i = 0; i < numberOfCity; i++)
	{
		minX = 9999;
		minY = 9999;
		maxX = 0;
		maxY = 0;
		for(int j = 0; j < size; j++)
		{
			if(cM[j].cityNumber == i+1){
				//getting the minimum of x
				if(minX > cM[j].x)
				{
					minX = cM[j].x;
				}
				//getting the minimum of y
				if(minY > cM[j].y)
				{
					minY = cM[j].y;
				}
				//getting the maximum of x
				if(maxX < cM[j].x)
				{
					maxX = cM[j].x;
				}
				//getting the maximum of y
				if(maxY < cM[j].y)
				{
					maxY = cM[j].y;
				}
			}
		}
		//checking if the minimum and maximum is out of grid
		if(minX - 1 >= miniX)
		{
			cit[i].minX = minX - 1;
		}
		else
		{
			cit[i].minX = minX;
		}
		if(minY - 1 >= miniY)
		{
			cit[i].minY = minY - 1;
		}
		else
		{
			cit[i].minY = minY;
		}
		if(maxX +1 <= x)
		{
			cit[i].maxX = maxX + 1;
		}
		else
		{
			cit[i].maxX = maxX;
		}
		if(maxY+1 <= y)
		{
			cit[i].maxY = maxY + 1;
		}
		else
		{
			cit[i].maxY = maxY;
		}
	}

	for(int i = 0; i < numberOfCity; i++)
	{
		for(int j = 0; j < sizeOfCity; j++)
		{
			if(cM[j].cityNumber == i+1)
			{
				cit[i].cityName = cM[j].cityName;
			}	 
		}
	}
	//returning number of cities
	return numberOfCity;
}


void getPerimeter(cityMap cM[], cities cit[], int x, int y, int numberOfCity, cloudCoverage cC[], cityPressure cP[])
{
	int minX;
	int minY;
	int maxX;
	int maxY;
	int size = x * y;

	//ssetting all perimeter to 9999, invalid number
	for(int i = 0; i < size; i++)
	{
		cC[i].perimeter = 9999;
		cC[i].perimeter = 9999;
	}
	
	for(int i = 0;i < numberOfCity; i++)
	{
		//getting number of cities
		minX = cit[i].minX;
		minY = cit[i].minY;
		maxX = cit[i].maxX;
		maxY = cit[i].maxY;
		for(int j = 0; j < size; j++)
		{
			//getting individual grids for x
			for(int k = minX; k <= maxX; k++)
			{
				//getting individual grids for y
				for(int l = minY; l <= maxY; l++)
				{
					if(k == cP[j].x && l == cP[j].y)
					{
						//setting individual grid to become perimeter
						cP[j].perimeter = i+1;
						cC[j].perimeter = i+1;
					}
				}
			}
		}
	}
}


void getAvgIndexLMH(cities cit[], int x, int y, int numberOfCity, cityPressure cP[], cloudCoverage cC[])
{
	//variables to store the addition of things
	int avgPressure;
	//getting the size of the city
	int sizeOfCity;
	int avgCloud;
	int size = x*y;
	//getting city by city
	for(int i = 0; i<numberOfCity; i++)
	{
		//setting all to 0
		avgPressure =0;
		sizeOfCity = 0;
		avgCloud = 0;
		//cout << "set all to 0" << endl;
		for(int k = 0; k<size; k++)
		{
			//cout << cP[k].perimeter << endl;
			if(cP[k].perimeter == i+1){
				//cout << "set avgPressure/cloud" << endl;
				avgPressure += cP[k].pressure;
				avgCloud += cC[k].cloud;
				sizeOfCity += 1;
			}
		}
		//setting all variables inside the cities
		cit[i].avgPressureIndex = roundf(((double)avgPressure / sizeOfCity) * 100)/100;
		cit[i].avgCloudIndex = roundf(((double)avgCloud / sizeOfCity) * 100)/100;
		cit[i].avgPressureLMH = getLMH(cit[i].avgPressureIndex);
		cit[i].avgCloudLMH = getLMH(cit[i].avgCloudIndex);
		cit[i].probabilityOfRain = probabilityOfRain(cit[i].avgPressureLMH, cit[i].avgCloudLMH);
	}
}


void printSummary(cities cit[], int numberOfCities)
{
	cout << "Weather Forecast Summary Report" << endl;
	cout << "-------------------------------" << endl;
	for(int i = numberOfCities-1; i >= 0; i--)
	{
		cout << fixed << setprecision(2)
		<< "City Name : " << cit[i].cityName << endl
		<< "City ID   : " << cit[i].cityNumber << endl
		<< "Ave Cloud Cover (ACC)   :" << cit[i].avgCloudIndex << " (" << cit[i].avgCloudLMH << ")" << endl
		<< "Ave Pressure (ACC)      :" << cit[i].avgPressureIndex << " (" << cit[i].avgPressureLMH << ")" << endl
		<< "Probability of Rain     :" << cit[i].probabilityOfRain << endl;
		printOutOfProbabilityOfRain(cit[i].probabilityOfRain);
		cout << endl;
	}
}


void deletionOfPointers(cities cit[], cityMap cM[], cityPressure cP[], cloudCoverage cC[])
{
	delete [] cit;
	delete [] cM;
	delete [] cP;
	delete [] cC;
}


