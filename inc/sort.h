#ifndef __SORT_H__
 #define __SORT_H__
 #include "config.h"
 
 /*sorting control*/
		#define INCREASING 1
		#define DECREASING 2
		#define NUMBER_DATA 1
		#define STRING_DATA 0
		#define ID_DATA 3
		#define CHANGED 1
		#define DONTCHANGED 0
 
 void bubbleSort(USER * list, int listSize, int sortType, int dataType);
 static void switchPosition(USER *list, int index);
 static int sortIncreasingString(USER *list, int index);
 static int sortIncreasingNumber(USER *list, int index);
 static int sortIcreasingById(USER *list, int index);
 static int sortDecreasingById(USER *list, int index);
 static int sortDecreasingString(USER *list, int index);
 static int sortDecreasingNumber(USER *list, int index);
 
#endif
