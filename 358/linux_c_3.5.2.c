#include <stdio.h>
#include <string.h>
#include <dirent.h>

int ret_comm(char *fn)
{
  FILE *file;
  char str[100] = {0};

  file = fopen(fn, "r");
  if (file) {
    if (fscanf(file, "%s\n", str) != EOF) {
    }
    fclose(file);
    if (!strcmp(str, "genenv")) {
      return 1;
    }
  }
  return 0;
}


int main(void)
{
  struct dirent **namelist;
  int n;
  int count = 0;
  char str_[100] = {0};
  char buf[100] = {0};
  n = scandir("/proc/", &namelist, NULL, alphasort);
  if (n < 0)
    perror("scandir");
  else {
    while (n--) {
      snprintf(str_, 64, "%s", namelist[n]->d_name);
      if ((str_[0] >= 0x30) && (str_[0] <= 0x39)) {
        snprintf(buf, 64, "/proc/%s/comm", str_);
        count += ret_comm(buf);
      }
    }
  }
  printf("%d\n", count);
  return 0;
}
