/* getppid */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main (void)
{
    pid_t pid;
    char str_file[256] = {0};
    char str[999];

    pid = getpid ();
    snprintf(str_file, 64, "/proc/%d/status", pid);

    FILE *file;
    file = fopen(str_file, "r");
    if (file) {
        while (fscanf(file, "%s\n", str) != EOF) {
            if (!strcmp(str, "PPid:")) {
                if (fscanf(file, "%s\n", str) != EOF) {
                    printf("%s\n", str);
                    break;
                }
            }
        }
        fclose(file);
    }

    return 0;
}