#include <stdio.h>
#include "log.h"

void log_event(const char *user, const char *action) {
    FILE *fp = fopen("data/logs.txt", "a");
    fprintf(fp, "%s: %s\n", user, action);
    fclose(fp);
}
