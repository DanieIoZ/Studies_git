#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>

#define MAX_FILES 1000

DIR* FD;
struct dirent*  in_file;

char    buffer[BUFSIZ];

pthread_mutex_t mtx;

char * folder;

int files_number;
int th_number;
int chars[52];

int current_thread_number = 0;

char * files[MAX_FILES];

void *thread1(void *v)
{
    pthread_mutex_lock(&mtx);
    int start_file = current_thread_number++;
    pthread_mutex_unlock(&mtx);

    int local_chars[52];

    for (size_t i = start_file; i < files_number; i+th_number)
    {
        FILE * entry_file = fopen(files[i], "r");

        while (fgets(buffer, BUFSIZ, entry_file) != NULL)
        {
            int i = 0;
            while (buffer[i] != '\0')
            {
                if (buffer[i] >= 'A' && buffer[i] <= 'Z')
                {
                    local_chars[buffer[i] - 'A']++;
                }
                else if (buffer[i] >= 'a' && buffer[i] <= 'z')
                {
                    local_chars[buffer[i] - 'a' + 26]++;
                }
                i++;
            }
        }

        fclose(entry_file);
    }
    
    pthread_mutex_lock(&mtx);
    for (size_t i = 0; i < 52; i++)
    {
        chars[i] += local_chars[i];
    }
    
    pthread_mutex_unlock(&mtx);
}   

int main(int argc, char * argv[])
{
    if ((FD = opendir(argv[1])) == NULL) 
    {
        fprintf(stderr, "Error : Failed to open input directory\n");
        return 1;
    }
    folder = strcat(argv[1], "/"); 
    
    files_number = atoi(argv[2]);
    th_number = atoi(argv[3]);

    int current_file = 0;

    FILE*   entry_file;
    if (argv[3] == 0)
    {
        while ((in_file = readdir(FD)) && current_file < files_number) 
        {
            if (!strcmp (in_file->d_name, "."))
                continue;
            if (!strcmp (in_file->d_name, ".."))    
                continue;
            char dir[100];
            strcpy(dir, folder);
            
            entry_file = fopen(strcat(dir, in_file->d_name), "r");
            if (entry_file == NULL)
            {
                fprintf(stderr, "Error : Failed to open entry file\n");
                fclose(entry_file);
                return 1;
            }


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
            current_file++;
        }
    }
    else
    {
        while ((in_file = readdir(FD)) && current_file < files_number) 
        {
            if (!strcmp (in_file->d_name, "."))
                continue;
            if (!strcmp (in_file->d_name, ".."))    
                continue;
            strcpy(files[current_file], folder);
            files[current_file] = strcat(files[current_file], in_file->d_name);
            current_file++;
        }


        // pthread_t thrds[th_count];
        // pthread_mutex_init(&mtx, NULL);

        // for (size_t i = 0; i < th_count; i++)
        // {
        //     pthread_create(&thrds[i], NULL, thread1, NULL);
        // }
        
    }
    
    // for (int i = 0; i < 26; i++)
    // {
    //     printf("%c: %d\n", i + 'A', chars[i]);
    // }
    // for (int i = 0; i < 26; i++)
    // {
    //     printf("%c: %d\n", i + 'a', chars[i+26]);
    // }
    
    for (size_t i = 0; i < files_number; i++)
    {
        printf("%s\n", files[i]);
    }
    

    return 0;
}