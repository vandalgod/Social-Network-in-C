#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(dir) _mkdir(dir)
#else
    #include <sys/stat.h>
    #include <sys/types.h>
    #define MKDIR(dir) mkdir(dir, 0755)
#endif
#include "friend.h"
#include "user.h"
#include "log.h"

// Ensure data directory exists
void ensure_data_directory() {
    MKDIR("data");
}

void send_request(const char *sender, const char *receiver) {
    if (strcmp(sender, receiver) == 0) {
        printf("You cannot send a friend request to yourself.\n");
        return;
    }
    
    // Check if receiver exists
    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) {
        printf("Error: Cannot access user database.\n");
        return;
    }
    
    char name[50], email[50], branch[50], hostel[50], pass[20], gender[10], hostel_status[5];
    int user_exists = 0;
    
    while (fscanf(fp, "%s %s %s %s %s %s %s", name, email, branch, hostel, pass, gender, hostel_status) != EOF) {
        if (strcasecmp(name, receiver) == 0) {
            user_exists = 1;
            break;
        }
    }
    fclose(fp);
    
    if (!user_exists) {
        printf("User '%s' does not exist.\n", receiver);
        return;
    }
    
    // Check if they are already friends
    fp = fopen("data/friends.txt", "r");
    if (fp) {
        char user1[50], user2[50];
        while (fscanf(fp, "%s %s", user1, user2) != EOF) {
            if ((strcasecmp(user1, sender) == 0 && strcasecmp(user2, receiver) == 0) ||
                (strcasecmp(user1, receiver) == 0 && strcasecmp(user2, sender) == 0)) {
                fclose(fp);
                printf("You are already friends with %s.\n", receiver);
                return;
            }
        }
        fclose(fp);
    }
    
    // Check if request already exists
    fp = fopen("data/requests.txt", "r");
    if (fp) {
        char from[50], to[50];
        while (fscanf(fp, "%s %s", from, to) != EOF) {
            if (strcasecmp(from, sender) == 0 && strcasecmp(to, receiver) == 0) {
                fclose(fp);
                printf("You have already sent a friend request to %s.\n", receiver);
                return;
            }
            
            if (strcasecmp(from, receiver) == 0 && strcasecmp(to, sender) == 0) {
                fclose(fp);
                printf("%s has already sent you a friend request. Check your requests to accept it.\n", receiver);
                return;
            }
        }
        fclose(fp);
    }
    
    // Send the request
    ensure_data_directory();
    fp = fopen("data/requests.txt", "a");
    if (!fp) {
        printf("Error: Could not open requests file.\n");
        return;
    }
    
    fprintf(fp, "%s %s\n", sender, receiver);
    fclose(fp);
    
    printf("Friend request sent to %s successfully!\n", receiver);
}

void show_and_accept_requests(const char *username) {
    FILE *fp = fopen("data/requests.txt", "r");
    if (!fp) {
        printf("No friend requests to display.\n");
        return;
    }
    
    char from[50], to[50];
    int found = 0;
    printf("\n--- Friend Requests ---\n");
    
    while (fscanf(fp, "%s %s", from, to) != EOF) {
        if (strcasecmp(to, username) == 0) {
            printf("From: %s\n", from);
            found = 1;
        }
    }
    fclose(fp);
    
    if (!found) {
        printf("You have no pending friend requests.\n");
        return;
    }
    
    char request_name[50];
    printf("\nEnter the name to accept (or type 'back' to return): ");
    scanf("%s", request_name);
    
    if (strcasecmp(request_name, "back") == 0) {
        return;
    }
    
    // Check if the request exists
    fp = fopen("data/requests.txt", "r");
    FILE *temp = fopen("data/requests_temp.txt", "w");
    int request_found = 0;
    
    while (fscanf(fp, "%s %s", from, to) != EOF) {
        if (strcasecmp(from, request_name) == 0 && strcasecmp(to, username) == 0) {
            request_found = 1;
            continue; // Skip this request as we're accepting it
        }
        fprintf(temp, "%s %s\n", from, to);
    }
    fclose(fp);
    fclose(temp);
    
    if (!request_found) {
        printf("No request found from %s.\n", request_name);
        remove("data/requests_temp.txt");
        return;
    }
    
    // Replace the original file
    remove("data/requests.txt");
    rename("data/requests_temp.txt", "data/requests.txt");
    
    // Add to friends list
    ensure_data_directory();
    fp = fopen("data/friends.txt", "a");
    if (!fp) {
        printf("Error: Could not update friends list.\n");
        return;
    }
    
    fprintf(fp, "%s %s\n", username, request_name);
    fclose(fp);
    
    printf("You are now friends with %s!\n", request_name);
}

void view_friends(const char *username) {
    FILE *fp = fopen("data/friends.txt", "r");
    if (!fp) {
        printf("You don't have any friends yet.\n");
        return;
    }
    
    char user1[50], user2[50];
    int found = 0;
    
    printf("\n--- Your Friends ---\n");
    while (fscanf(fp, "%s %s", user1, user2) != EOF) {
        if (strcasecmp(user1, username) == 0) {
            printf("- %s\n", user2);
            found = 1;
        } else if (strcasecmp(user2, username) == 0) {
            printf("- %s\n", user1);
            found = 1;
        }
    }
    fclose(fp);
    
    if (!found) {
        printf("You don't have any friends yet.\n");
    }
}

int is_friend(const char *user1, const char *user2) {
    FILE *fp = fopen("data/friends.txt", "r");
    if (!fp) return 0;
    
    char file_user1[50], file_user2[50];
    while (fscanf(fp, "%s %s", file_user1, file_user2) != EOF) {
        if ((strcasecmp(file_user1, user1) == 0 && strcasecmp(file_user2, user2) == 0) ||
            (strcasecmp(file_user1, user2) == 0 && strcasecmp(file_user2, user1) == 0)) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int are_friends(const char *u1, const char *u2) {
    return is_friend(u1, u2);
}

void add_friend(const char *user1, const char *user2) {
    if (strcmp(user1, user2) == 0) {
        printf("You cannot add yourself as a friend.\n");
        return;
    }

    if (!email_exists(user2)) {
        printf("User with email %s does not exist.\n", user2);
        return;
    }

    if (are_friends(user1, user2)) {
        printf("You are already friends with %s.\n", user2);
        return;
    }

    FILE *fp = fopen("data/friends.txt", "a");
    if (!fp) {
        printf("Error: Cannot open friends file.\n");
        return;
    }

    fprintf(fp, "%s %s\n", user1, user2);
    fclose(fp);

    printf("Friend request sent to %s successfully!\n", user2);
    log_event(user1, "Sent friend request");
}