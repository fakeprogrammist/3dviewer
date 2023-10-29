#include "config.h"

void config_save(const char *address, const char *paramerts) {
  FILE *file;
  //    int ERROR = 0;
  file = fopen(address, "w");
  fputs(paramerts, file);
  fclose(file);
  //    return 0;
}

int config_load(const char *address, structconfig *config) {
  FILE *file;
  int ERROR = 0;
  file = fopen(address, "r");
  char stored[800];  // однострочный массив длинной 800
  char *istr;
  if (!file) {
    ERROR = 1;  // файл отсутствует или неоткрылся
  } else {
    fgets(stored, 800, file);
    config->color_background_r = atof(stored);
    istr = strtok(stored, " ");
    istr = strtok(NULL, " ");
    config->color_background_g = atof(istr);
    istr = strtok(NULL, " ");
    config->color_background_b = atof(istr);

    istr = strtok(NULL, " ");
    config->color_line_r = atof(istr);
    istr = strtok(NULL, " ");
    config->color_line_g = atof(istr);
    istr = strtok(NULL, " ");
    config->color_line_b = atof(istr);

    istr = strtok(NULL, " ");
    config->color_vertex_r = atof(istr);
    istr = strtok(NULL, " ");
    config->color_vertex_g = atof(istr);
    istr = strtok(NULL, " ");
    config->color_vertex_b = atof(istr);

    istr = strtok(NULL, " ");
    config->size_line = atoi(istr);
    istr = strtok(NULL, " ");
    config->type_line = atoi(istr);

    istr = strtok(NULL, " ");
    config->size_vertex = atoi(istr);
    istr = strtok(NULL, " ");
    config->type_vertex = atoi(istr);

    istr = strtok(NULL, " ");
    config->projection = atoi(istr);

    fclose(file);
  }
  return ERROR;
}
