//
#include "WorldClock_2.0.h"

// Function 'displaytListOfAllKnownTZ' to display all available timezones
void displaytListOfAllKnownTZ()
{
	// 
	char* command = "awk '/^Z/ { print $2 }; /^L/ { print $3 }' /usr/share/zoneinfo/tzdata.zi";
	char tz[100];

	//
    FILE *cmd=popen(command, "r");

	//
	while(fgets(tz, 500, cmd))
	{
		//
		printf("%s", tz);
	}

	//
	pclose(cmd);
}

// Function 'getListOfAllKnownTZ' to get all available timezones
/*char** getListOfAllKnownTZ()
{
	// 
	char* command = "awk '/^Z/ { print $2 }; /^L/ { print $3 }' /usr/share/zoneinfo/tzdata.zi";
	char* arrayOfTZ[500];
	char* currentTZ;
	int i = 0;

	//
	char tz[100];

	//
    FILE *cmd=popen(command, "r");

	//
	while(fgets(tz, 500, cmd))
	{
		printf("%s", tz);

		//
		arrayOfTZ[i] = tz;

		printf("%s\n", arrayOfTZ[i]);

		//
		i++;
	}

	//
	pclose(cmd);

	//
	return arrayOfTZ;
}*/

// Funtion 'getWorldClock_2_0ForWishedTZ' to get date and time for the wished timezone
struct worldClock_2_0 getWorldClock_2_0ForWishedTZ(char* wishedTZ)
{
	// Definition of all necessary variables
    char* worldClock_2_0ChoosenTZ = malloc(30);
	char fullSize = strlen("TZ=") + strlen(" date") + strlen(" +%Y_%m_%d_%U_%u_%H_%M_%S") + strlen(wishedTZ);
	char c;
	int i = 0;
	int j = 0;
    FILE *cmd;
	char* extrArray;
	struct worldClock_2_0 resultWorldClock_2_0;
	int valOfTrans = 0;

	// Definition of the bash command to have date and time for the choosen timezone
	char* completeCommand = (char*) malloc(fullSize);
	strcat(completeCommand, "TZ=");
	strcat(completeCommand, wishedTZ);
	strcat(completeCommand, " date");
	strcat(completeCommand, " +%Y_%m_%d_%U_%u_%H_%M_%S");

	// Execution of the command "TZ={wishedTZ} date +'%Y_%m_%d_%U_%u_%H_%M_%S'" to have the date and time for the wished timezone via the 'cmd' file
    cmd=popen(completeCommand, "r");

	//
    while((c = fgetc(cmd)) != EOF)
	{
		//
    	worldClock_2_0ChoosenTZ[i] = c;

		// Incrementation of the 'i' incrementor's value
		i++;
	}
	
	// Close the file 'cmd'
    pclose(cmd);

	// Conversion of the first extract element of the WorldClock_2_0 to an integer
	extrArray = strtok(worldClock_2_0ChoosenTZ, "_");

	// Loop to extract all elements of the WorldClock_2_0 to an integer and put them in the 'resultWorldClock_2_0' struct WorldClock_2_0
	while(extrArray != NULL) {

		//valOfTrans = (int)extrArray;
		sscanf(extrArray, "%d", &valOfTrans);

		//
		switch(j)
		{
			case 0 : resultWorldClock_2_0.year = valOfTrans; break;
			case 1 : resultWorldClock_2_0.month = valOfTrans; break;
			case 2 : resultWorldClock_2_0.dmonth = valOfTrans; break;
			case 3 : resultWorldClock_2_0.nweek = valOfTrans; break;
			case 4 : resultWorldClock_2_0.dweek = valOfTrans; break;
			case 5 : resultWorldClock_2_0.hour = valOfTrans; break;
			case 6 : resultWorldClock_2_0.minute = valOfTrans; break;
			case 7 : resultWorldClock_2_0.second = valOfTrans; break;
		}

		// 
    	extrArray = strtok(NULL, "_");

		// Incrementation of the 'j' incrementor's value
		j++;
   	}

	// Return the date and time for the choosen timezone
    return resultWorldClock_2_0;
}

// Funtion 'sprintfWorldClock_2_0' to return date and time from a struct WorldClock_2_0 object as a string
char* sprintfWorldClock_2_0(struct worldClock_2_0 worldClock_2_0ToDisplay)
{
	//
	char* s_year = malloc(4 * sizeof(char));
	char* s_month = malloc(2 * sizeof(char));
	char* s_dmonth = malloc(2 * sizeof(char));
	char* s_nweek = malloc(2 * sizeof(char));
	char* s_dweek = malloc(2 * sizeof(char));
	char* s_hour = malloc(2 * sizeof(char));
	char* s_minute = malloc(2 * sizeof(char));
	char* s_second = malloc(2 * sizeof(char));

	// Definition of the 'resultString' string which will contain the result
	char* resultString = malloc(100 * sizeof(char));

	//
	sprintf(s_year, "%d", worldClock_2_0ToDisplay.year);
	if(worldClock_2_0ToDisplay.month < 10){sprintf(s_month, "0%d", worldClock_2_0ToDisplay.month);}else{sprintf(s_month, "%d", worldClock_2_0ToDisplay.month);}
	if(worldClock_2_0ToDisplay.dmonth < 10){sprintf(s_dmonth, "0%d", worldClock_2_0ToDisplay.dmonth);}else{sprintf(s_dmonth, "%d", worldClock_2_0ToDisplay.dmonth);}
	if(worldClock_2_0ToDisplay.hour < 10){sprintf(s_hour, "0%d", worldClock_2_0ToDisplay.hour);}else{sprintf(s_hour, "%d", worldClock_2_0ToDisplay.hour);}
	if(worldClock_2_0ToDisplay.minute < 10){sprintf(s_minute, "0%d", worldClock_2_0ToDisplay.minute);}else{sprintf(s_minute, "%d", worldClock_2_0ToDisplay.minute);}
	if(worldClock_2_0ToDisplay.second < 10){sprintf(s_second, "0%d", worldClock_2_0ToDisplay.second);}else{sprintf(s_second, "%d", worldClock_2_0ToDisplay.second);}
	if(worldClock_2_0ToDisplay.nweek < 10){sprintf(s_nweek, "0%d", worldClock_2_0ToDisplay.nweek);}else{sprintf(s_nweek, "%d", worldClock_2_0ToDisplay.nweek);}
	if(worldClock_2_0ToDisplay.dweek < 10){sprintf(s_dweek, "0%d", worldClock_2_0ToDisplay.dweek);}else{sprintf(s_dweek, "%d", worldClock_2_0ToDisplay.dweek);}	

	//
	sprintf(resultString, "date : %s/%s/%s | time : %s:%s:%s | number of the day in the week : %s | number of the week in the year : %s |", s_dmonth, s_month, s_year, s_hour, s_minute, s_second, s_dweek, s_nweek);

	// Return the date and time as a string
	return resultString;
}

//
enum OS getCurrentOS()
{
	//
	#if defined(_WIN32)
    	return windows;
	#elif defined(_WIN64)
		return windows;
	#elif defined(__CYGWIN__)
		return windows;
	#elif defined(unix)
		return unix;
	#elif defined(__unix)
		return unix;
	#elif defined(__unix__)
		return unix;
	#elif defined(__APPLE__)
		return macOS;
	#elif defined(__MACH__)
		return macOS;
	#elif defined(__linux__)
		return linux;
	#elif defined(__FreeBSD__)
		return freeBSD;
	#elif defined(__ANDROID__)
		return android;
	#else
		return undefined;
	#endif
}