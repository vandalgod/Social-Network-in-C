#include <stdio.h>
#include <string.h>
#include <time.h>
#include <strings.h>
#include "post.h"
#include "log.h"
#include "friend.h"

void post_message(const char *user) {
    FILE *fp = fopen("data/messages.txt", "a");
    if (!fp) {
        printf("Error: Could not open messages file.\n");
        return;
    }
    
    char msg[256];
    printf("Enter message: ");
    getchar(); // Clear newline
    fgets(msg, 256, stdin);
    msg[strcspn(msg, "\n")] = 0; // Remove trailing newline
    
    // Store message with timestamp
    time_t now;
    time(&now);
    fprintf(fp, "%s|%ld|%s\n", user, now, msg);
    fclose(fp);
    log_event(user, "Posted a message");
}

void view_messages(const char *user) {
    FILE *fp = fopen("data/messages.txt", "r");
    if (!fp) {
        printf("No messages found.\n");
        return;
    }
    
    char sender[50], msg[256];
    long timestamp;
    int found = 0;
    
    printf("\nYour Messages:\n");
    while (fscanf(fp, "%[^|]|%ld|%[^\n]\n", sender, &timestamp, msg) != EOF) {
        if (strcasecmp(sender, user) == 0) {
            char time_str[30];
            strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&timestamp));
            printf("[%s] %s\n", time_str, msg);
            found = 1;
        }
    }
    if (!found) printf("You haven't posted any messages yet.\n");
    fclose(fp);
}

void view_friend_messages(const char *user) {
    FILE *fp = fopen("data/messages.txt", "r");
    if (!fp) {
        printf("No messages found.\n");
        return;
    }
    
    char sender[50], msg[256];
    long timestamp;
    int found = 0;
    
    printf("\nFriends Messages:\n");
    while (fscanf(fp, "%[^|]|%ld|%[^\n]\n", sender, &timestamp, msg) != EOF) {
        if (strcasecmp(sender, user) != 0 && are_friends(user, sender)) {
            char time_str[30];
            strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&timestamp));
            printf("[%s] %s: %s\n", time_str, sender, msg);
            found = 1;
        }
    }
    if (!found) printf("No messages from friends yet.\n");
    fclose(fp);
}
