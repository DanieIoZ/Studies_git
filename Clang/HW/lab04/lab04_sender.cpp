// C libraries
#include<stdio.h>
#include<string.h>

// Linux Headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

int main(){


	/* Create new termios struct, 'o_tty' */
	struct termios o_tty;

	/* fill o_tty with 0*/
	memset (&o_tty, 0, sizeof o_tty);
	
	// printf(">> %d", o_tty.c_cflag.CSTOPB);
	/* setting up baudrate
	Set in/out baud rate to be 115200 
	cfsetispeed(&tty, B9600);
	cfsetospeed(&tty, B9600);*/ 


	/* open the serial port device */
	int hSerial = open("/dev/ttyACM1", O_RDWR| O_NONBLOCK | O_NDELAY);	

	/* Check for errors. in case you see error 'Permission denied', you are not part of dial out group.
	solve it by command 'sudo adduser $USER dialout' and put your user name instead of $USER. Log out and back
	for changes to happen.*/
	if ( hSerial< 0) {
		printf("Error %i from open: %s\n", errno, strerror(errno));
	}
	
	/* Get the attributes for a terminal */
	int iRetVal = tcgetattr (hSerial , &o_tty);

	/* message we want to send to NUCLEO */
	unsigned char chArrCmd[] = {'l', 'e', 'd', '1', '\0'};

	
	printf("sending %s\n",chArrCmd);
	/* send message */
	int n_written = write( hSerial, chArrCmd, sizeof(chArrCmd)-1 ); 

	printf("n_written returns %d\n",n_written);
        //while(1){;}	
	/* close the serial communication  */
	close(hSerial);
	
	return 0;
}
