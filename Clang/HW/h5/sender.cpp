// C libraries
#include<stdio.h>
#include<string.h>

#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>
// Linux Headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
//#include <conio.h>
int user_input = 1;
int hSerial;
int accept = 0;
int from_file = 0;

char filename[100];

pthread_mutex_t mtx;

void *thread1(void *v)
{
	char comm[64];
	int len = 0;
	char c = 0;
	while ((c = getchar()) > 0)
	{
		if (c != ';')
		{
			if (c != '\n')
			comm[len++] = c;
			continue;
		}
		else
		{
			comm[len] = ';';
			len = 0;
		}
		accept = 0;
		if (strcmp(comm, "CLEAR;") == 0)
		{
			accept = 1;
		}
		else
		{
			int i = 0;

			char tmp[20];
			while (comm[i] != ' ' && comm[i] != ';' && comm[i] != '\0' && comm[i] != '\n')
			{
				tmp[i] = comm[i];
				i++;
			}

			tmp[i] = '\0';
			if (strcmp(tmp, "DRAW:CIRCLE") == 0)
			{
				int data[3];
				data[2] = 10;
				int rec = sscanf( comm, "DRAW:CIRCLE %d,%d,%d;", &data[0], &data[1], &data[2] );
				if (rec < 2)
				{
					printf("Invalid input:( \n");
				}
				else
				{
					accept = 1;
				}
			}
			else if (strcmp(tmp, "DRAW:LINE") == 0)
			{
				int data[4];
				int rec = sscanf( comm, "DRAW:LINE %d,%d,%d,%d;", &data[0], &data[1], &data[2], &data[3] );
				if (rec < 4)
				{
					printf("Invalid input:( \n");
				}	
				else
				{
					accept = 1;
				}
			}
			else
			{
				printf("Invalid input :( \n");
			}
		}

		//////////////
		if (!accept)
			continue;
		int i = 0;
		if (strcmp(comm, "") != 0)
		{
			while (from_file) {}
			//pthread_mutex_lock(&mtx);
			while (comm[i] != '\n' && comm[i] != '\0')
			{
				char sending[2];
				sending[0] = comm[i++];
				int n_written = write(hSerial, sending, 1);
				usleep(40000);
			}
			//pthread_mutex_unlock(&mtx);
		}
		accept = 0;

		comm[0] = '\0';
	}
	user_input = 0;
    return 0;
}   

void *mainthread(void *v)
{
	FILE* f = fopen(filename, "r");
	char message[256];
    while (!feof(f))
    {
		memset(&message, '\0', sizeof(message));
		char c;
		int m_len = 0;
		while ((c = fgetc(f)) > 0)
		{
			if (c != ';')
			{
				if (c != '\n')
				message[m_len++] = c;
				continue;
			}
			else
			{
				message[m_len] = ';';
				m_len = 0;
				break;
			}
		}
		int i = 0;
		if (strcmp(message, "") != 0)
		{
			while (accept) {}
			from_file = 1;
			while (message[i] != '\n' && message[i] != '\0')
			{
				char sending[2];
				sending[0] = message[i++];
				int n_written = write(hSerial, sending, 1);
				usleep(40000);
			}
			printf("SENT: %s\n", message);
			from_file = 0;
		}
    }
	fclose(f);
	return 0;
}

int main(int argc, char * argv[]){


	/* Create new termios struct, 'o_tty' */
	struct termios o_tty;

	/* fill o_tty with 0*/
	memset (&o_tty, 0, sizeof(o_tty));
	strcpy(filename, "data.txt");
	if (argc > 1)
	{
		strcpy(filename,argv[1]);
	}
	// printf(">> %d", o_tty.c_cflag.CSTOPB);
	/* setting up baudrate
	Set in/out baud rate to be 115200 
	cfsetispeed(&tty, B9600);
	cfsetospeed(&tty, B9600);*/ 

	/* open the serial port device */
	hSerial = open("/dev/ttyACM0", O_RDWR| O_NONBLOCK | O_NDELAY);	

	/* Check for errors. in case you see error 'Permission denied', you are not part of dial out group.
	solve it by command 'sudo adduser $USER dialout' and put your user name instead of $USER. Log out and back
	for changes to happen.*/
	if ( hSerial< 0) {
		printf("Error %i from open: %s\n", errno, strerror(errno));
	}
	pthread_mutex_init(&mtx, NULL);
	pthread_t th;
	pthread_create(&th, NULL, thread1, NULL);

	pthread_t th_main;
	pthread_create(&th_main, NULL, mainthread, NULL);
	/* Get the attributes for a terminal */
	int iRetVal = tcgetattr (hSerial , &o_tty);


	while (user_input) {}

	close(hSerial);
	return 0;
}
