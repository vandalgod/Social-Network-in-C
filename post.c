#include <stdio.h>
#include <string.h>
#include "post.h"
#include "log.h"

void post_message(const char *user) {
    FILE *fp = fopen("data/messages.txt", "a");
    char msg[256];
    printf("Enter message: ");
    getchar(); // Clear newline
    fgets(msg, 256, stdin);
    fprintf(fp, "%s: %s", user, msg);
    fclose(fp);
    log_event(user, "Posted a message");
}
