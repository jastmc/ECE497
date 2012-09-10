#include "BoneHeader.h"
#include <poll.h>
#include <signal.h>


//inherits
//
// int export_gpio(int gpio);
// int unexport_gpio(int gpio);
// int set_gpio_direction(int gpio, char* direction);
// int set_gpio_value(int gpio, int value);
// int set_gpio_edge(int gpio, char* edge);
// int gpio_fd_open(int gpio);
// int gpio_fd_close(int fd);
int keepgoing = 1;

//signal handler that breaks program loop and cleans up
void signal_handler(int sig){
	printf("^C pressed, unexporting gpios and exiting..\n");
	keepgoing = 0;
}

int main(int argc, char** argv){
	
	//variable declarations
	struct pollfd fdset[1];
	int nfds = 1;
	int timeout = 3000;
	int rc;
	int gpio1, gpio2;
	int gpio1_fd, gpio2_fd;
	int gpio2_value = 0;
		
	//check that at least two arguments are passed in
	if(argc < 3){
		printf("Usage: %s <input-gpio> <output-gpio>\n", argv[0]);
		printf("polls input-gpio, and writes value to output-gpio\n");
		fflush(stdout);
		return 1;
	}

	//set signal handler
	signal(SIGINT, signal_handler);

	//assign gpio values
	gpio1 = atoi(argv[1]);
	gpio2 = atoi(argv[2]);

	//argument 1 will be input
	export_gpio(gpio1);
	set_gpio_direction(gpio1, "in");
	set_gpio_edge(gpio1, "rising");
	gpio1_fd = gpio_fd_open(gpio1);

	//argument 2 will be output
	export_gpio(gpio2);
	set_gpio_direction(gpio2, "out");
	set_gpio_value(gpio2, gpio2_value);
	gpio2_fd = gpio_fd_open(gpio2);


	while(keepgoing){
		memset((void*)fdset, 0, sizeof(fdset));
	
		fdset[0].fd = gpio1_fd;
		fdset[0].events = POLLPRI;

		//fdset[1].fd = gpio2_fd;
		//fdset[1].events = POLLPRI;

		rc = poll(fdset, nfds, timeout);

		if (rc < 0){
			printf("\npoll() failed!\n");
			return 1;
		}
	
		if (rc == 0){
			printf(".");
		}

		if(fdset[0].revents & POLLPRI) {
			gpio2_value = ~(gpio2_value)&1;
			set_gpio_value(gpio2, gpio2_value);
		}			
		
	}

	gpio_fd_close(gpio1_fd);
	gpio_fd_close(gpio2_fd);
	unexport_gpio(gpio1);
	unexport_gpio(gpio2);

	return 0;
}
