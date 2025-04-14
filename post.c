#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "post.h"
#include "friend.h"
#include "log.h"

void post_message(const char *username) {
    char message[500];
    
    printf("\n--- Create Post ---\n");
    printf("Enter your message (up to 500 characters): ");
    
    // The most reliable method - read one character at a time
    int i = 0;
    int c;
    
    // Read characters until newline or end of buffer
    while (i < 499 && (c = getchar()) != EOF && c != '\n') {
        message[i++] = c;
    }
    message[i] = '\0';  // Null terminate the string
    
    // Check if message is empty
    if (i == 0) {
        printf("Error: Empty message not allowed.\n");
        return;
    }
    
    // Get current timestamp
    time_t now = time(NULL);
    
    // Ensure data directory exists
    #ifdef _WIN32
        system("if not exist data mkdir data");
    #else
        system("mkdir -p data");
    #endif
    
    // Save to file
    FILE *fp = fopen("data/messages.txt", "a");
    if (!fp) {
        printf("Error: Could not save your message.\n");
        return;
    }
    
    fprintf(fp, "%s|%ld|%s\n", username, now, message);
    fclose(fp);
    
    printf("Message posted successfully!\n");
    log_event(username, "Posted a message");
}

void view_messages(const char *username) {
    FILE *fp = fopen("data/messages.txt", "r");
    if (!fp) {
        printf("No messages available.\n");
        return;
    }
    
    printf("\n--- Your Messages ---\n");
    
    char line[600];
    int count = 0;
    
    // Read line by line
    while (fgets(line, sizeof(line), fp) != NULL) {
        char user[50] = {0};
        char timestamp_str[50] = {0};
        char message[500] = {0};
        
        // Parse with sscanf to be more robust than strtok
        if (sscanf(line, "%[^|]|%[^|]|%[^\n]", user, timestamp_str, message) == 3) {
            // Check if this message belongs to the current user
            if (strcasecmp(user, username) == 0) {
                // Convert timestamp and format
                time_t timestamp = atol(timestamp_str);
                struct tm *timeinfo = localtime(&timestamp);
                char time_str[20];
                strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M", timeinfo);
                
                // Display the message
                printf("[%s] %s\n", time_str, message);
                count++;
            }
        }
    }
    
    fclose(fp);
    
    if (count == 0) {
        printf("You haven't posted any messages yet.\n");
    }
}

void view_friend_messages(const char *user) {
    FILE *fp = fopen("data/messages.txt", "r");
    if (!fp) {
        printf("No messages found.\n");
        return;
    }
    
    printf("\nFriends' Messages:\n");
    
    char line[600];
    int found = 0;
    
    // Read line by line
    while (fgets(line, sizeof(line), fp) != NULL) {
        char sender[50] = {0};
        char timestamp_str[50] = {0};
        char message[500] = {0};
        
        // Parse with sscanf to be more robust than strtok
        if (sscanf(line, "%[^|]|%[^|]|%[^\n]", sender, timestamp_str, message) == 3) {
            // Check if this message is from a friend
            if (strcasecmp(sender, user) != 0 && are_friends(user, sender)) {
                // Convert timestamp and format
                time_t timestamp = atol(timestamp_str);
                struct tm *timeinfo = localtime(&timestamp);
                char time_str[30];
                strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M", timeinfo);
                
                // Display the message
                printf("[%s] %s: %s\n", time_str, sender, message);
                found = 1;
            }
        }
    }
    
    fclose(fp);
    
    if (!found) {
        printf("No messages from friends found.\n");
    }
}

void create_post(const char *user) {
    char content[500];
    printf("Enter your post content (max 500 characters): ");
    scanf(" %[^\n]", content);

    FILE *fp = fopen("data/posts.txt", "a");
    if (!fp) {
        printf("Error: Cannot open posts file.\n");
        return;
    }

    fprintf(fp, "%s|%s\n", user, content);
    fclose(fp);

    printf("Post created successfully!\n");
    log_event(user, "Created a post");
}

void view_posts(const char *user) {
    FILE *fp = fopen("data/posts.txt", "r");
    if (!fp) {
        printf("No posts found.\n");
        return;
    }

    char post_user[50], content[500];
    int found = 0;

    printf("\n--- Posts ---\n");
    while (fscanf(fp, "%[^|]|%[^\n]\n", post_user, content) != EOF) {
        if (strcmp(user, post_user) == 0) {
            found = 1;
            printf("\n%s\n", content);
            printf("-------------------\n");
        }
    }

    fclose(fp);

    if (!found) {
        printf("No posts found for this user.\n");
    }
}