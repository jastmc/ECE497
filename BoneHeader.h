//export gpio pin on the BeagleBone to prepare for usage
//
//USAGE: specify gpio # as an int
//
//written by: 	Andrew Miller
//Date:		9 September 2012
int export_gpio(int gpio);

//set direction of gpio to either in or out specified by string
//
//USAGE: specify gpio # as an int
//USAGE: specify direction as a string of either "in" or "out"
//
//written by:	Andrew Miller
//Date:		9 September 2012
int set_gpio_direction(int gpio, char* direction);

int set_gpio_value(int gpio, int value);
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

int set_gpio_direction(int gpio, char* direction){
	FILE *fp;
	char* path;

	//create path using specified gpio
	sprintf(path, "/sys/class/gpio/gpio%d/direction", gpio);
	//open direction file
	if((fp = fopen(path, "w")) == NULL){
		printf("Cannot open specified direction file. Is gpio%d exported?\n", gpio);
		return 1;
	}

	//write "in" or "out" to direction file
	rewind(fp);
	fprintf(fp, direction, gpio);
	fflush(fp);
	fclose(fp);
}

int set_gpio_value(int gpio, int value){
	FILE *fp;
	char* path;
	char direction[10];
	char* pdirection;
	pdirection = direction;

	//create path using specified gpio
	sprintf(path, "/sys/class/gpio/gpio%d/direction", gpio);	
	
	if((fp = fopen(path, "r")) == NULL){
		printf("Cannot open specified direction file. is gpio %d exported?\n", gpio);
	}
	
	if(fgets(direction, sizeof direction, fp) != NULL){
		fflush(fp);
		/*if(!strcmp(pdirection, "in")){
			printf("Direction is set to 'in'. Cannot change value\n");
			return 1;
		}*/
	}

	printf("direction is %s\n", direction);

	fflush(fp);
	fclose(fp);

}
	
	

	
	
	


