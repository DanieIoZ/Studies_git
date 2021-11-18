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

        /* string to receive message */
        char chArrBuf [256];
        int n = read( hSerial, &chArrBuf , sizeof(chArrBuf) );
        /* pre-fill receive string with nulls. do you know why?  */
        memset (&chArrBuf , '\0', sizeof(chArrBuf) );

        FILE * f = fopen("result.txt", "w");


	while(n[0] != EOF){
		/* receive string */
		n = read( hSerial, &chArrBuf , sizeof(chArrBuf) );
		if (n==-1){
			memset (&chArrBuf , '\0', sizeof(chArrBuf) );
		}
		printf("received message: %s\n",chArrBuf);
                fputs(chArrBuf, f);
	}
        printf("END");
        fclose(f);
        /* close the serial communication  */
        close(hSerial);
        
        return 0;
}
