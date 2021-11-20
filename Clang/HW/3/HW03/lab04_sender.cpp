// C libraries
#include<stdio.h>
#include<string.h>

// Linux Headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
//#include <conio.h>


int main(){


	/* Create new termios struct, 'o_tty' */
	struct termios o_tty;

	/* fill o_tty with 0*/
	memset (&o_tty, 0, sizeof(o_tty));
	
	// printf(">> %d", o_tty.c_cflag.CSTOPB);
	/* setting up baudrate
	Set in/out baud rate to be 115200 
	cfsetispeed(&tty, B9600);
	cfsetospeed(&tty, B9600);*/ 


	/* open the serial port device */
	int hSerial = open("/dev/ttyACM0", O_RDWR| O_NONBLOCK | O_NDELAY);	

	/* Check for errors. in case you see error 'Permission denied', you are not part of dial out group.
	solve it by command 'sudo adduser $USER dialout' and put your user name instead of $USER. Log out and back
	for changes to happen.*/
	if ( hSerial< 0) {
		printf("Error %i from open: %s\n", errno, strerror(errno));
	}
	
	/* Get the attributes for a terminal */
	int iRetVal = tcgetattr (hSerial , &o_tty);

	FILE* f = fopen("homework-t.txt", "r");

	char message[256];
    while (!feof(f))
    {
		memset(&message, '\0', sizeof(message));
		fgets(message,256,f);
		int i = 0;
		while (message[i] != '\0')
		{
			char sending[2];
			sending[0] = message[i++];
			printf("%c", sending[0]);
			int n_written = write(hSerial, sending, 1);
			usleep(40000);
		}
		
    }
	message[0] = -1;
	int n_written = write( hSerial, message, sizeof(message)-1); 
	fclose(f);
	close(hSerial);
	
	return 0;
}
