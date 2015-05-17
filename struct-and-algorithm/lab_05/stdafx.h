#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>

using namespace std;

struct Item
{
	int serveTime;
	Item * next;
};

void inputData();
int dequeue();
void enqueue(int time);
void modelateQueue();
void createQueue();
int getRandomTime(int max);
void outputQueueWithGlue(Item * head, char glue[2]);
void processTick(int tick);