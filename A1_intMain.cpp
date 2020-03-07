#include "A1_functions.h"

int main ()
{ 
	char choice = 0;
	int sizeForCity = 0;
	int sizeForCloud = 0;
	int sizeForPressure = 0;
	int x = 0;
	int y = 0;
	int minX = 0;
	int minY = 0;
	cityPressure *cP = new cityPressure[MAX];
	cloudCoverage *cC = new cloudCoverage[MAX];
	cityMap *cM = new cityMap[MAX];
	cities *cit = new cities[MAX];
	int numberOfCities = 0;
	int cityMapSize = 0;
	do
	{
		choice = fMenu();
		if(choice == '1'){
			string filename = menu();
			if(filename != "-1")
			{
				getFileSize(filename, sizeForCity, sizeForCloud, sizeForPressure);
				choice1(sizeForCity, sizeForCloud, sizeForPressure, x, y, cP, cC, cM, filename, minX, minY);
			}
		}
	else if(choice == '2')
	{
		if(sizeForCity == 0)
		{
			cout << "You have not enter a config file" << endl;
			cout << endl;
		}
		else
		{
			drawCityLocation(cM, sizeForCity, x, y, minX, minY);
			cout << endl;
		}	 
	}
	else if(choice == '3')
	{
		if(sizeForCloud == 0)
		{
			cout << "You have not enter a config file" << endl;
			cout << endl;
		}
		else
		{
			drawCloudIndexLocation(cC, x, y, minX, minY);
			cout << endl;
		}
	}
	else if(choice == '4')
	{
		if(sizeForCloud == 0)
		{
			cout << "You have not enter a config file" << endl;
			cout << endl;
		}
		else
		{
			drawCloudLMHLocation(cC, x, y, minX, minY);
			cout << endl;
		}
	}
	else if(choice == '5')
	{
		if(sizeForPressure == 0)
		{
			cout << "You have not enter a config file" << endl;
			cout << endl;
		}
		else
		{
			drawPressureIndexLocation(cP, x, y, minX, minY);
			cout << endl;
		}
	}
	else if(choice == '6')
	{
		if(sizeForPressure == 0)
		{
			cout << "You have not enter a config file" << endl;
			cout << endl;
		}
		else
		{
			drawPressureLMHLocation(cP, x, y, minX, minY);
			cout << endl;
		}
	}
	else if(choice == '7')
	{
		if(sizeForCity == 0)
		{
			cout << "You have not enter a config file" << endl;
			cout << endl;
		}
		else
		{
			numberOfCities = getMaxMin(cM, cit, sizeForCity, x, y, minX, minY);
			getPerimeter(cM, cit, x, y, numberOfCities, cC, cP);
			getAvgIndexLMH(cit, x, y, numberOfCities, cP, cC);
			printSummary(cit, numberOfCities);
			cout << endl;
		}
	}
	else if(choice == '8')
	{
	
	}
	else
	{
		cout << "You entered an invalid value, please enter (1/2/3/4/5/6/7/8)" << endl;
		cout << endl;
	}
	}while(choice != '8');
	deletionOfPointers(cit, cM, cP, cC);
	return (0);
}
