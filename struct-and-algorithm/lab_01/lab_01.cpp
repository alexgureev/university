#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#include <sstream>
#include <fstream>


FILE *fileResource, *fileOutResource;
char filename[20], outFilename[20];
char space = ' ';

using namespace std;

int getVowelsCounter(char * pCh);
string iterateWords(char lineContent[100]);
string getVowelestWord(string wordsArray[100], int wordsCount);
void updateAllLinesWithString(string lineSuffix);

void chooseFileName()
{
	puts("Please, enter filename for output result:");
	fflush(stdin);
	gets_s(filename);
}

/* 
 * Увести з клавіатури рядки і 
 * записати їх у текстовий файл. 
 */
void createFile()
{
	char answer;
	char inputString[100];
	
	if (strcmp(filename, "") == 0) {
		chooseFileName();
	}
	
	fileResource = fopen(filename, "w");

	do 
	{
		puts("input string:");
	    fflush(stdin);
		gets_s(inputString);
		fputs(inputString, fileResource);
		fputc('\n', fileResource);

		puts("continue ? [y / n]");
		answer = _getch();
	} while ((answer != 'n') && (answer != 'N'));
	
	fclose(fileResource);
}

/* 
 * У кожному непарному рядку визначити слово, що має найбільшу кількість голоcних. 
 */
void iterateLines()
{
	char lineContent[100];
	string resultString;
	int lineCounter = 0;
	
	fileResource = fopen(filename, "r");
	
	while (!feof(fileResource)) {
		fgets(lineContent, 100, fileResource);
		
		if (feof(fileResource)) {
			break;
		}

		lineCounter++;

		if (lineCounter % 2 == 0) {
			continue;
		}

		resultString += iterateWords(lineContent) + space;
	}

	fclose(fileResource);
	updateAllLinesWithString(resultString);
}

/*
* Дописати знайдені слова в кожний рядок файлу.
*/
void updateAllLinesWithString2(string lineSuffix)
{
	fstream afile;
	string line, stringToPut;

	afile.open(filename, ios::out | ios::in);
	
	while (afile.good())
	{
		getline(afile, line);
		stringToPut = line + space + lineSuffix;
		char ch[1024];
		strcpy(ch, stringToPut.c_str());
		//afile.write(ch, count(ch));
	}



	afile.close();
}

/*
* Дописати знайдені слова в кожний рядок файлу.
*/
void updateAllLinesWithString(string lineSuffix)
{
	char lineContent[100];
	
	fileResource = fopen(filename, "r");
	strcat(filename, ".tmp");
	fileOutResource = fopen(filename, "w+");

	while (!feof(fileResource)) {
		fgets(lineContent, 100, fileResource);

		if (feof(fileResource)) {
			break;
		}

		lineContent[strlen(lineContent) - 1] = ' ';
		fprintf(fileOutResource, "%s", lineContent);
		fputs(lineSuffix.c_str(), fileOutResource);
		fputc('\n', fileOutResource);
	}

	fclose(fileResource);
	fclose(fileOutResource);
}


/*
 * Iterate all words in line
 */
string iterateWords(char lineContent[100])
{
	int i = 0;
	string wordsArray[100];
	stringstream ssin(lineContent);

	while (ssin.good()){
		ssin >> wordsArray[i];
		++i;
	}

	return getVowelestWord(wordsArray, i);
}


string getVowelestWord(string wordsArray[100], int wordsCount)
{
	int max = 0, current = 0;
	string result;

	for (int counter = 0; counter < wordsCount - 1; counter++) {
		char word[100];
		std:copy(wordsArray[counter].begin(), wordsArray[counter].end(), word);
		current = getVowelsCounter(word);
		
		if (current >= max) {
			result = wordsArray[counter];
			max = current;
		}
	
	}

	return result;
}

/*
 * Count vowels in char variable
 */
int getVowelsCounter(char * word)
{
	int vowels = 0;

	while (*word)
	{
		if (strspn(word, "aeiou")) {
			vowels++;
		}

		word++;
	}

	return vowels;
}

int _tmain(int argc, _TCHAR* argv[])
{
	createFile();
	iterateLines();
	cout << "Result was outputed into file.";
	cin.get();
	return 0;
}
