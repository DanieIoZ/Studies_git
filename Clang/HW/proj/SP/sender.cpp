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
	int reply = 0;
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
			comm[len+1] = '\0';
			accept = 1;

			len = 0;
		}
		//////////////
		if (accept)
			if (strcmp(comm, "") != 0)
			{
				int i = 0;

				while (from_file) {}
				//pthread_mutex_lock(&mtx);
				while (comm[i] != '\n' && comm[i] != '\0')
				{
					char sending[2];
					sending[0] = comm[i++];
					int n_written = write(hSerial, sending, 1);
					usleep(20000);
				}
				//pthread_mutex_unlock(&mtx);
				accept = 0;
				comm[0] = '\0';
			}
		
	}
	user_input = 0;
    return 0;
}   

void *mainthread(void *v)
{
	FILE* f = fopen(filename, "r");
	char message[40][128];
	int cmd = 0;
    while (!feof(f))
    {
		char c;
		int m_len = 0;
		while ((c = fgetc(f)) > 0)
		{
			if (c != ';')
			{
				if (c != '\n')
				message[cmd][m_len++] = c;
				continue;
			}
			else
			{
				message[cmd][m_len] = ';';
				message[cmd][m_len+1] = '\0';
				m_len = 0;
				break;
			}
		}
		cmd += 1;
	}
	fclose(f);
	int cur_cmd = -1;
	char chArr[64];
	char chArrBuf[1];
	while (1)
	{
		if (accept)
			continue;
		chArrBuf[0] = 0;
		int n = read( hSerial, &chArrBuf , 1 );
		if ((n > 0) && (chArrBuf[0] > 0))
		{
			int j = 0;
			int timer = 5000;
			int cur_time = 0;
			int received = 1;
			while ((chArrBuf[0] != '\n') && (cur_time < timer) && (chArrBuf[0] > 0))
			{
				if (accept)
					continue;
				if (n > 0)
				{
					if (chArrBuf[0] > 0 && chArrBuf[0] != '\n')
					{
						chArr[j] = chArrBuf[0];
						j += 1;
						cur_time = 0;
					}
				}
				// else
				// {
				// 	printf("wting\n");
				// 	cur_time += 10;
				// 	usleep(10000);
				// }
				// if (cur_time > timer)
				// {
				// 	j = 0;
				// 	received = 0;
				// 	break;
				// }
				n = read( hSerial, &chArrBuf , 1 );
			}
			chArr[j] = '\0';
			if (received)
			{
				if (strcmp(chArr, "JOYDOWN") == 0)
				{
					if (strcmp(message[cur_cmd], "") != 0)
					{
						if (cur_cmd < cmd-1)
							cur_cmd += 1;
						while (accept) {}
						from_file = 1;
						int i = 0;
						while (message[cur_cmd][i] != '\n' && message[cur_cmd][i] != '\0')
						{
							char sending[2];
							sending[0] = message[cur_cmd][i];
							i += 1;
							int n_written = write(hSerial, sending, 1);
							usleep(10000);
						}
						from_file = 0;
					}
					
				}
				else if (strcmp(chArr, "JOYUP") == 0)
				{
					if (cur_cmd > 0)
						cur_cmd -= 1;
					if (strcmp(message[cur_cmd], "") != 0)
					{
						while (accept) {}
						from_file = 1;
						int i = 0;
						while (message[cur_cmd][i] != '\n' && message[cur_cmd][i] != '\0')
						{
							char sending[2];
							sending[0] = message[cur_cmd][i];
							i += 1;
							int n_written = write(hSerial, sending, 1);
							usleep(10000);
						}
						from_file = 0;
					}
				}
				else
				{
					printf("%s\n", chArr);
				}
				memset(&chArr, '\0', sizeof(chArr));

			}
			j = 0;
		}
	}
	return 0;
}

int main(int argc, char * argv[]){


	/* Create new termios struct, 'o_tty' */
	struct termios o_tty;

	/* fill o_tty with 0*/
	memset (&o_tty, 0, sizeof(o_tty));
	strcpy(filename, "commands.txt");
	if (argc > 1)
	{
		strcpy(filename,argv[1]);
	}

	hSerial = open("/dev/ttyACM0", O_RDWR| O_NONBLOCK | O_NDELAY);	
	if ( hSerial< 0) {
		printf("Error %i from open: %s\n", errno, strerror(errno));
	}
	int iRetVal = tcgetattr (hSerial , &o_tty);

	pthread_mutex_init(&mtx, NULL);
	pthread_t th;
	pthread_create(&th, NULL, thread1, NULL);

	pthread_t th_main;
	pthread_create(&th_main, NULL, mainthread, NULL);
	/* Get the attributes for a terminal */

	while (user_input) {}

	close(hSerial);
	return 0;
}
