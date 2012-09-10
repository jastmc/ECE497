//export gpio pin on the BeagleBone to prepare for usage
//
//USAGE: specify gpio # as an int
//
//written by: 	Andrew Miller
//Date:		9 September 2012
int export_gpio(int gpio);

//unexport gpio pin on the BeagleBone
//
//USAGE: specify gpio # as an int
//
//written by: 	Andrew Miller
//Date:		9 September 2012
int unexport_gpio(int gpio);

//set direction of gpio to either in or out specified by string
//
//USAGE: specify gpio # as an int
//USAGE: specify direction as a string of either "in" or "out"
//
//written by:	Andrew Miller
//Date:		9 September 2012
int set_gpio_direction(int gpio, char* direction);

//set value of gpio
//
//USAGE: specify gpio # as an int
//USAGE: specify value as an int of either 1 or 0
//
//written by:	Andrew Miller
//Date:		9 September 2012
int set_gpio_value(int gpio, int value);

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 127

int export_gpio(int gpio){
	FILE *fp;
	
	//open the export file
	if((fp = fopen("/sys/class/gpio/export", "ab")) == NULL){
		printf("Cannot open export file. \n");
		return 1;
	}
	
	//write specified gpio to export file
	fprintf(fp, "%d\n", gpio);
	fflush(fp);
	fclose(fp);
	
	//return 0 if everything runs correctly
	return 0;
}

int unexport_gpio(int gpio){
	FILE *fp;
	
	//open the unexport file
	if((fp = fopen("/sys/class/gpio/unexport", "ab")) == NULL){
		printf("Cannot open unexport file. \n");
		return 1;
	}

	//write specified gpio to unexport file
	fprintf(fp, "%d\n", gpio);
	fflush(fp);
	fclose(fp);

	return 0;
}

int set_gpio_direction(int gpio, char* direction){
	FILE *fp;
	char path[MAX_BUF];

	//create path using specified gpio
	snprintf(path, sizeof path,"/sys/class/gpio/gpio%d/direction", gpio);
	//open direction file
	if((fp = fopen(path, "w")) == NULL){
		printf("Cannot open specified direction file. Is gpio%d exported?\n", gpio);
		return 1;
	}

	//write "in" or "out" to direction file
	rewind(fp);
	fprintf(fp, direction);
	fflush(fp);
	fclose(fp);
}

int set_gpio_value(int gpio, int value){
	FILE *fp;
	char path[MAX_BUF];
	char direction[10];
	char* pdirection;
	pdirection = direction;
	
	//set value only if direction is out
	snprintf(path, sizeof path, "/sys/class/gpio/gpio%d/value", gpio);
	
	if((fp = fopen(path, "w")) == NULL){
		printf("Cannot open specified value file.\n", gpio);
		return 1;
	}

	//write 1 or 0 to value file
	rewind(fp);
	fprintf(fp, "%d\n", value);
	fflush(fp);
	fclose(fp);
}


	
	

	
	
	


