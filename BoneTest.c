#include "BoneHeader.h"
//inherits
//
// int exort_gpio(int gpio);
// int set_gpio_direction(int gpio, char* direction);
// int set_gpio_value(int gpio, int value);
int main(int argc, char** argv){
	export_gpio(60);
	set_gpio_direction(60, "out");
	set_gpio_direction(60, "in");
	set_gpio_value(60, 1);
	set_gpio_direction(60, "out");
	set_gpio_value(60, 1);
	unexport_gpio(60);
	return 0;
}
