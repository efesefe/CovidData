//Ýbrahim Efe Erer - 201911403 - section 3

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
struct country 
{
	char countryName[100];
	int totalCases;
	int totalDeaths;
	int totalRecovered;
	int totalTestnum;
	long long int countryPopulation;
};
void readData(char fileName[100],int countryNum,struct country *inputtedData,int *inputCount);//reads data from a file which name is entered by user
void showData(char countryName[100],struct country *countries,int countryNum);//shows information about a country 
void insertData(struct country *countries,int countryNum,int *inputted,int mustBe);//if user wants to input a country and its information by hand this function is used
void removeData(struct country *countries,int *countryNum);//removes the country and its data from the array
void updateData(struct country *countries,int *countryNum);//updates a country's data by hand
void sortCases(struct country *countries,int *countryNum);//sorts cases from country with more cases to country with less cases
void sortDeaths(struct country *countries,int *countryNum);//sorts deaths from country with more deaths to country with less deaths
int main(void)
{
	struct country *countries;
	int n,inputtedCountries = 0,decision,k;
	char c;
	char nameFile[100],nameCountry[100];
	do
	{
		printf("\n1. Read data from file\n");
		printf("2. Show Country data\n");
		printf("3. Insert Country data\n");
		printf("4. Remove Country Data\n");
		printf("5. Update Country data\n");
		printf("6. Sort Covid data based on total cases\n");
		printf("7. Sort Covid data based on total deaths\n");
		printf("8. Find and display the top  5 countries with largest  number of cases per person\n");
		printf("9. Write recent data to file 'recent.txt'\n");
		printf("10. Exit\n");
		scanf("%d",&decision);
		scanf("%c",&c);
		switch(decision)
		{
			case 1:
				printf("Enter number of countries: ");//user should enter total country number because we may want to add new countries in to array
				scanf("%d", &n);
				scanf("%c",&c);
				countries = (struct country*)calloc(n, sizeof(struct country));//reserves n struct country type spaces in the memory
				printf("Enter file name: ");
				gets(nameFile);
				readData(nameFile, n,countries,&inputtedCountries);
				/*inputted countries counts the number of countries inputted from the file so that if user wants to add new country to the end of the array we can locate the end index
				of the array*/
				break;
			case 2:
				printf("Enter name of the country: ");
				gets(nameCountry);
				showData(nameCountry,countries,n);
				break;
			case 3:
				insertData(countries,n,&inputtedCountries,n);
				break;
			case 4:
				removeData(countries,&inputtedCountries);
				break;
			case 5:
				updateData(countries,&inputtedCountries);
				break;
			case 6:
				sortCases(countries,&inputtedCountries);
				break;
			case 7:
				sortDeaths(countries,&inputtedCountries);
				break;
			case 8:
				sortCases(countries,&inputtedCountries);
				for(k = 0 ; k < 5 ; k++)
				{
					printf("%d. ",(k+1));
					puts(countries[k].countryName);
					printf("\n");
				}
				break;
			case 9:
				FILE *write;
				write = fopen("recent.txt","w");
				for(k = 0 ; k < inputtedCountries; k++)
				{
					fprintf(write,"%s/%d/%d/%d/%d/%lli\n",countries[k].countryName,countries[k].totalCases,countries[k].totalDeaths,countries[k].totalRecovered,countries[k].totalTestnum,countries[k].countryPopulation);
				}
				fclose(write);
				break;
			default:
				break;
		}
	}while(decision != 10);	
	return 0;
}
void readData(char fileName[100],int countryNum,struct country *inputtedData,int *inputCount)
{	
	long long int k,n,t,c,temp,sum = 0,num,countName;
	FILE *inFile;
	char countryString[100],anotherStringBitesTheDust[100];
	//countryString holds 1 line of data from file as a string
	//anotherStringBitesTheDust is used for countries with 2 or more worded names. Basically holds second part as a string and adds it to countryString
	inFile = fopen(fileName, "r");
	if (inFile == NULL)//Gives an error if the file cannot open or does not exist.
	{
		printf("Failed to open the file");
	}
	else
	{	
		n = 0;
		while(feof(inFile) == 0 && n < countryNum)//goes on till the end of the file or country limit
		{
			fscanf(inFile,"%s",countryString);//countryString holds the data as a string
			while(strlen(countryString)<20)//For the countries with more than 1 word names
			{
				anotherStringBitesTheDust[0] = ' ';//To add spaces between names of country
				fscanf(inFile,"%s",&anotherStringBitesTheDust[1]);
				strcat(countryString,anotherStringBitesTheDust);//adding the data after a space to countryString to hold the whole data of country
			}
			k = strlen(countryString);
			t = 0;
			c = 0;
			sum = 0;
			temp = t;
			while(countryString[t] != '/')//getting country name till the first '/'
			{	
				t++;
				c++;	
			}
			strncpy(inputtedData[n].countryName,countryString,c);	
			c = 0;
			t++;
			temp = t;
			while(countryString[t] != '/')//to count digits of the number
			{
				t++;
				c++;
			}
			c--;
			while(temp < t)//converting string numbers to integer for total cases of the country
			{
				sum += (countryString[temp] - '0') * pow(10,c);
				c--;
				temp++;
			}
			inputtedData[n].totalCases = sum;
			t++;
			c=0;
			sum = 0;
			temp = t;
			while(countryString[t] != '/')//to count digits of the number
			{
				t++;
				c++;
			}
			c--;	
			while(temp < t)//converting string numbers to integer for total deaths of the country
			{
				sum += (countryString[temp] - '0') * pow(10,c);
				c--;
				temp++;
			}
			inputtedData[n].totalDeaths = sum;
			t++;
			c=0;
			sum = 0;
			temp = t;
			while(countryString[t] != '/')//to count digits of the number
			{
				t++;
				c++;
			}
			c--;	
			while(temp < t)//converting string numbers to integer for total number of recovered people of the country
			{
				sum += (countryString[temp] - '0') * pow(10,c);
				c--;
				temp++;
			}
			inputtedData[n].totalRecovered = sum;
			t++;
			c=0;
			sum = 0;
			temp = t;
			while(countryString[t] != '/')//to count digits of the number
			{
				t++;
				c++;
			}
			c--;	
			while(temp < t)//converting string numbers to integer for total test number of the country
			{
				sum += (countryString[temp] - '0') * pow(10,c);
				c--;
				temp++;
			}
			inputtedData[n].totalTestnum = sum;
			t++;
			c=0;
			sum = 0;
			temp = t;
			while(countryString[t] != '/' && t < k)//to count digits of the number
			{
				t++;
				c++;
			}
			c--;	
			while(temp < t)//converting string numbers to integer for country population of the country
			{
				sum += (countryString[temp] - '0') * pow(10,c);
				c--;
				temp++;
			}
			inputtedData[n].countryPopulation = sum;	
			n++;
			*inputCount = n;
		}		
	}
	fclose(inFile);
}
void showData(char countryName[100],struct country *countries,int countryNum)
{
	int k,thisindex;
	bool found = false;
	for(k = 0 ; k < countryNum && found == false ; k++)
	{
		if(strcmp(countries[k].countryName,countryName) == 0)
		{
				found = true;
				thisindex = k;
		}	
	}
	if(found == true)//Checks if the country exists
	{
		printf("Name of the country: ");
		puts(countries[thisindex].countryName);
		printf("Total cases: %d\n",countries[thisindex].totalCases);
		printf("Total deaths: %d\n",countries[thisindex].totalDeaths);
		printf("Total recovered: %d\n",countries[thisindex].totalRecovered);
		printf("Total tests: %d\n",countries[thisindex].totalTestnum);
		printf("Country population: %d\n",countries[thisindex].countryPopulation);
	}
	else
	{
		printf("Enter a valid country name\n");
	}
}
void insertData(struct country *countries,int countryNum,int *inputted,int mustBe)
{
	char input[100];
	int k,count = 0;
	bool exists = false;
	printf("Enter name of the country: ");
	gets(input);
	for(k = 0 ; k < countryNum ; k++)
	{	
		if(strcmp(countries[k].countryName,input) == 0)
		{
			exists = true;//if country already exists it becomes true
		}
	}
	if(exists == true)
	{
		printf("This country data exist in the dataset\n");
	}
	else if(mustBe == *inputted)//if the array limit is reached we cannot enter new country
	{
		printf("You have reached the input limit!!!\n");
	}
	else
	{
		printf("Enter total cases: ");
		scanf("%d",&countries[*inputted].totalCases);
		printf("Enter total deaths: ");
		scanf("%d",&countries[*inputted].totalDeaths);
		printf("Enter total recovered: ");
		scanf("%d",&countries[*inputted].totalRecovered);
		printf("Enter total tests: ");
		scanf("%d",&countries[*inputted].totalTestnum);
		printf("Enter population of the country: ");
		scanf("%lli",&countries[*inputted].countryPopulation);
		strcpy(countries[*inputted].countryName ,input);
		*inputted = *inputted + 1;
	}
}
void removeData(struct country *countries,int *countryNum)
{
	char remove[100];//name of the country to be removed
	int k;
	bool thisis = false;//bool to check if the country already exists
	printf("Enter name of the country that you want to delete: ");
	gets(remove);
	for(k = 0 ;k < *countryNum ; k++)
	{
		if(strcmp(countries[k].countryName,remove) == 0)
		{
			thisis = true;
			while(k < *countryNum)
			{
				strcpy(countries[k].countryName,countries[k + 1].countryName);
				countries[k].countryPopulation = countries[k + 1].countryPopulation;
				countries[k].totalCases = countries[k + 1].totalCases;
				countries[k].totalDeaths= countries[k + 1].totalDeaths;
				countries[k].totalRecovered = countries[k + 1].totalRecovered;
				countries[k].totalTestnum = countries[k + 1].totalTestnum;
				k++;
			}
		}
	}
	if(thisis == true)
	{
		*countryNum = *countryNum - 1;
		printf("Choosen country removed from the array!\n");
	}
	else
	{
		printf("Error!");
	}
}
void updateData(struct country *countries,int *countryNum)
{
	char update[100];
	int k,temp;
	bool found = false;
	printf("Enter name of the country to be updated: ");
	gets(update);
	for(k = 0 ; k < *countryNum ; k++)//finds country to be updated
	{
		if(strcmp(countries[k].countryName,update) == 0)
		{
			temp = k;
			found = true;
			k = *countryNum;
		}
	}
	if(found == true)
	{
		printf("Enter new data for ");
		puts(update);
		printf("Total Cases: ");
		scanf("%d",&countries[temp].totalCases);
		printf("Total Deaths: ");
		scanf("%d",&countries[temp].totalDeaths);
		printf("Total Recovered: ");
		scanf("%d",&countries[temp].totalRecovered);
		printf("Total Tests: ");
		scanf("%d",&countries[temp].totalTestnum);
		printf("Population: ");
		scanf("%d",&countries[temp].countryPopulation);
	}
	else//gives an error message if the country could not found
	{
		printf("Error");
	}
}
void sortCases(struct country *countries,int *countryNum)
{
	int k , l;
	int temp[4];//temporary location on the memory for total cases,deaths,recovered and test number
	long long int poptem;//temporary location on the memory for population data
	char tem[100];//temporary location on the memory for name of the country
	for(k = 0 ; k < *countryNum ; k++)
	{
		strcpy(tem,countries[k].countryName);
		temp[0] = countries[k].totalCases;
		temp[1] = countries[k].totalDeaths;
		temp[2] = countries[k].totalRecovered;
		temp[3] = countries[k].totalTestnum;
		poptem = countries[k].countryPopulation;
		for(l = k ; l < *countryNum ; l++)
		{
			strcpy(tem,countries[k].countryName);
			temp[0] = countries[k].totalCases;
			temp[1] = countries[k].totalDeaths;
			temp[2] = countries[k].totalRecovered;
			temp[3] = countries[k].totalTestnum;
			poptem = countries[k].countryPopulation;
			if(countries[k].totalCases < countries[l].totalCases)
			{
				strcpy(countries[k].countryName,countries[l].countryName);
				countries[k].totalCases = countries[l].totalCases;
				countries[k].totalDeaths = countries[l].totalDeaths;
				countries[k].totalRecovered = countries[l].totalRecovered;
				countries[k].totalTestnum = countries[l].totalTestnum;
				countries[k].countryPopulation = countries[l].countryPopulation;
				strcpy(countries[l].countryName,tem);
				countries[l].totalCases = temp[0];
				countries[l].totalDeaths = temp[1];
				countries[l].totalRecovered = temp[2];
				countries[l].totalTestnum = temp[3];
				countries[l].countryPopulation= poptem;
				l--;
			}
		}
	}
	printf("Array is sorted by the number of cases!\n");
}
void sortDeaths(struct country *countries,int *countryNum)
{
	int k , l;
	int temp[4];//temporary location on the memory for total cases,deaths,recovered and test number
	long long int poptem;//temporary location on the memory for population data
	char tem[100];//temporary location on the memory for name of the country
	for(k = 0 ; k < *countryNum ; k++)
	{
		strcpy(tem,countries[k].countryName);
		temp[0] = countries[k].totalCases;
		temp[1] = countries[k].totalDeaths;
		temp[2] = countries[k].totalRecovered;
		temp[3] = countries[k].totalTestnum;
		poptem = countries[k].countryPopulation;
		for(l = k ; l < *countryNum ; l++)
		{
			strcpy(tem,countries[k].countryName);
			temp[0] = countries[k].totalCases;
			temp[1] = countries[k].totalDeaths;
			temp[2] = countries[k].totalRecovered;
			temp[3] = countries[k].totalTestnum;
			poptem = countries[k].countryPopulation;
			if(countries[k].totalDeaths < countries[l].totalDeaths)
			{
				strcpy(countries[k].countryName,countries[l].countryName);
				countries[k].totalCases = countries[l].totalCases;
				countries[k].totalDeaths = countries[l].totalDeaths;
				countries[k].totalRecovered = countries[l].totalRecovered;
				countries[k].totalTestnum = countries[l].totalTestnum;
				countries[k].countryPopulation = countries[l].countryPopulation;
				strcpy(countries[l].countryName,tem);
				countries[l].totalCases = temp[0];
				countries[l].totalDeaths = temp[1];
				countries[l].totalRecovered = temp[2];
				countries[l].totalTestnum = temp[3];
				countries[l].countryPopulation= poptem;
				l--;
			}
		}
	}
	printf("Array is sorted by the number of deaths!\n");
}
