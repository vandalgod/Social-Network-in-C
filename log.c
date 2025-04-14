#include <stdio.h>
#include <string.h>
#include <time.h>
#include "log.h"
#include "friend.h"

void log_event(const char *user, const char *action) {
    ensure_data_directory();
    
    if (!user || !action) {
        return; // Invalid parameters
    }
    
    FILE *fp = fopen("data/logs.txt", "a");
    if (!fp) {
        printf("Error: Could not open log file.\n");
        return;
    }
    
    // Add timestamp to log
    time_t now;
    time(&now);
    struct tm *timeinfo = localtime(&now);
    char timestamp[30];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    fprintf(fp, "[%s] %s: %s\n", timestamp, user, action);
    fclose(fp);
}