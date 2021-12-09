#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    float min_times[3];
    float summary_min = 100;
    int threads_min = 0;

    for (int i = 0; i < 3; i++)
    {
        min_times[i] = 1000;
    }
    for (int thrds = 0; thrds < 10; thrds++)
    {
            remove("tmp.txt");
            char sys[100] = "time -a -o tmp.txt -p ./main files 1000 ";
            sys[54] = thrds + '0';
            sys[55] = '\0';
            system(sys);
            
            FILE * f = fopen("tmp.txt", "r");
            char data[3][50];
            int i = 0;
            while (fgets(data[i], 50, f) != NULL)
            {
                i++;
            }
            float times[3];
            for (int j = 0; j < 3; j++)
            {
                char * buff = malloc(20);
                i = 0;
                while (data[j][i] != ' ')
                {
                    i++;
                }
                i++;
                int k = 0;
                
                while (data[j][i] != '\n' && data[j][i] != '\0')
                {
                    buff[k++] = data[j][i++];
                }
                buff[k] = '\0';
                times[j] = atof(buff);
                free(buff);
            }
            fclose(f);
            float summary = 0;
            for (int j = 0; j < 3; j++)
            {
                summary += times[j];
            }
            if (summary < summary_min)
            {
                summary_min = summary;
                for (int j = 0; j < 3; j++)
                {
                    min_times[j] = times[j];
                }
                threads_min = thrds;
            }
            sleep(1);
    }

    FILE * f = fopen("analysis.txt", "w");
    fprintf(f, "Optimal number of threads is: %d\nTIME:\n", threads_min);
    for (int j = 0; j < 3; j++)
    {
        fprintf(f, "%f\n", min_times[j]);
    }
    remove("tmp.txt");
    fclose(f);

    return 0;
}