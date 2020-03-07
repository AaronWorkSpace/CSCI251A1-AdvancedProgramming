#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <cctype>

using namespace std;

/*
1) read in and process a configuration file
2) display city map
3) display cloud coverage map (cloudiness index)
4) display cloud coverage map (LMH symbols)
5) display atmospheric pressure map (pressure index)
6) display atmospheric pressure map (LMH symbols)
7) show weather forecast summary report
*/

struct cities;
struct cityMap;
struct cloudCoverage;
struct cityPressure;

vector<string> tokenizeString (string, string);
char fMenu();
string menu();
void choice1(int &, int &, int &, int &, int &, cityPressure [], cloudCoverage [], cityMap [], string, int&, int&);
void getFileSize(string, int &, int &, int &);
void processing(string, cityPressure [], cloudCoverage [], cityMap [], int, int, int, int &, int &, int &, int &);
void readCityFile (string, int, cityMap []);
void readCloudFile (string, int, cloudCoverage []);
string getIndex(int);
string getLMH(int);
void readPressureFile (string, int, cityPressure []);
int readPressureFile (string);
int readCloudFile (string);
int readCityFile (string);
void drawCityLocation(cityMap [],int, int, int, int, int);
void drawCloudIndexLocation(cloudCoverage [], int, int, int, int);
void drawCloudLMHLocation(cloudCoverage [], int, int, int, int);
void drawPressureIndexLocation(cityPressure [], int, int, int, int);
void drawPressureLMHLocation(cityPressure [], int, int, int, int);
int getMaxMin(cityMap [], cities [], int, int, int, int, int);
void getPerimeter(cityMap [], cities [], int, int, int, cloudCoverage C[], cityPressure []);
void getAvgIndexLMH(cities [], int, int, int, cityPressure [], cloudCoverage []);
void printSummary(cities [], int);
void deletionOfPointers(cities cit [], cityMap [], cityPressure [], cloudCoverage []);
int const MAX = 9999;

struct cities{
	int minX;
	int minY;
	int maxX;
	int maxY;
	int cityNumber;
	float avgCloudIndex;
	float avgPressureIndex;
	string avgCloudLMH;
	string avgPressureLMH;
	float probabilityOfRain;
	string cityName;
};


struct cityMap{
	int x;
	int y;
	int cityNumber;
	string cityName;
	string cityNum;
};


struct cloudCoverage
{
	int x;
	int y;
	int cloud;
	string index;
	string LMH;
	int perimeter;
};

struct cityPressure
{
	int x;
	int y;
	int pressure;
	string index;
	string LMH;
	int perimeter;
};

