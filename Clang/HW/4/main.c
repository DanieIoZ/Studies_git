#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define MAX_FILES 1000

DIR* FD;
struct dirent*  in_file;


pthread_mutex_t mtx;
pthread_mutex_t mtx2;

char * folder;

int files_number;
int th_number;
int chars[52];

int current_thread_number = 0;

char * files[MAX_FILES];

int total_num = 0;

void *thread1(void *v)
{
    pthread_mutex_lock(&mtx);
    int start_file = current_thread_number++;
    pthread_mutex_unlock(&mtx);

    int * local_chars = malloc(52 * sizeof(int));
    char * local_buffer = malloc(BUFSIZ);

    for (int i = start_file; i < files_number; i+=th_number)
    {
        FILE * entry_file = fopen(files[i], "r");
        while (fgets(local_buffer, BUFSIZ, entry_file) != NULL)
        {
            int i = 0;
            while (local_buffer[i] != '\0')
            {
                if (local_buffer[i] >= 'A' && local_buffer[i] <= 'Z')
                {
                    local_chars[local_buffer[i] - 'A']++;
                }
                else if (local_buffer[i] >= 'a' && local_buffer[i] <= 'z')
                {
                    local_chars[local_buffer[i] - 'a' + 26]++;
                }
                i++;
            }
        }

        fclose(entry_file);
    }
    free(local_buffer);
    free(local_chars);
    pthread_mutex_lock(&mtx2);
    for (size_t i = 0; i < 52; i++)
    {
        chars[i] += local_chars[i];
    }
    total_num++;
    pthread_mutex_unlock(&mtx2);

    return 0;
}   

int main(int argc, char * argv[])
{
    if ((FD = opendir(argv[1])) == NULL) 
    {
        fprintf(stderr, "Error : Failed to open input directory\n");
        return 1;
    }

    files_number = atoi(argv[2]);
    th_number = atoi(argv[3]);

    int current_file = 0;

    folder = strcat(argv[1], "/"); 
    printf("Thread number is: %d\n", th_number);
    while ((in_file = readdir(FD)) && current_file < files_number) 
    {

            if (!strcmp (in_file->d_name, "."))
                continue;
            if (!strcmp (in_file->d_name, ".."))    
                continue;
            char * dir = malloc(100);
            strcpy(dir, folder);
            strcat(dir, in_file->d_name);
            files[current_file] = dir;
            current_file++;
    }

    if (th_number == 0)
    {
        printf("Starting sequental\n");
        char buffer[BUFSIZ];

        for (int i = 0; i < files_number; i++)
        {
            FILE * entry_file = fopen(files[i], "r");
            while (fgets(buffer, BUFSIZ, entry_file) != NULL)
            {
                int i = 0;
                while (buffer[i] != '\0')
                {
                    if (buffer[i] >= 'A' && buffer[i] <= 'Z')
                    {
                        chars[buffer[i] - 'A']++;
                    }
                    else if (buffer[i] >= 'a' && buffer[i] <= 'z')
                    {
                        chars[buffer[i] - 'a' + 26]++;
                    }
                    i++;
                }
            }

            fclose(entry_file);
        }
    }
    else
    {
        printf("Running parallel\n");
        
        pthread_t thrds[th_number];
        pthread_mutex_init(&mtx, NULL);
        pthread_mutex_init(&mtx2, NULL);
        
        for (int i = 0; i < th_number; i++)
        {
            printf("Spawning thread %d\n", i);
            pthread_create(&thrds[i], NULL, thread1, NULL);
        }
    }
    
    while (total_num != th_number) {}

    printf("Printing LFT\n\n");
    for (int i = 0; i < 26; i++)
    {
        printf("%c: %d\n", i + 'A', chars[i]);
    }
    for (int i = 0; i < 26; i++)
    {
        printf("%c: %d\n", i + 'a', chars[i+26]);
    }
    
    for (int i = 0; i < files_number; i++)
    {
        free(files[i]);
    }

    return 0;
}