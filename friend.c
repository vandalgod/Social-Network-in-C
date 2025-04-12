#include <stdio.h>
#include <string.h>
#include "friend.h"
#include "log.h"

int user_exists_by_name(const char *name) {
    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) return 0;
    
    char uname[50], email[50], branch[50], hostel[50], pass[20], gender[10], hostel_status[5];
    while (fscanf(fp, "%s %s %s %s %s %s %s", 
                  uname, email, branch, hostel, pass, gender, hostel_status) != EOF) {
        if (strcasecmp(uname, name) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int are_friends(const char *u1, const char *u2) {
    FILE *fp = fopen("data/friends.txt", "r");
    if (!fp) return 0;
    
    char f1[50], f2[50];
    while (fscanf(fp, "%s %s", f1, f2) != EOF) {
        if ((strcasecmp(f1, u1) == 0 && strcasecmp(f2, u2) == 0) ||
            (strcasecmp(f1, u2) == 0 && strcasecmp(f2, u1) == 0)) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int is_request_already_sent(const char *sender, const char *receiver) {
    FILE *fp = fopen("data/requests.txt", "r");
    if (!fp) return 0;
    
    char s[50], r[50];
    while (fscanf(fp, "%s %s", s, r) != EOF) {
        if (strcasecmp(s, sender) == 0 && strcasecmp(r, receiver) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void send_request(const char *sender_name, const char *receiver_name) {
    if (strcasecmp(sender_name, receiver_name) == 0) {
        printf("You can't send a request to yourself.\n");
        return;
    }

    if (!user_exists_by_name(receiver_name)) {
        printf("User '%s' does not exist.\n", receiver_name);
        return;
    }

    if (are_friends(sender_name, receiver_name)) {
        printf("You are already friends with %s.\n", receiver_name);
        return;
    }

    if (is_request_already_sent(sender_name, receiver_name)) {
        printf("Friend request to %s is already sent.\n", receiver_name);
        return;
    }

    FILE *fp = fopen("data/requests.txt", "a");
    if (!fp) {
        printf("Error: Could not save friend request.\n");
        return;
    }
    fprintf(fp, "%s %s\n", sender_name, receiver_name);
    fclose(fp);

    log_event(sender_name, "Sent friend request");
    printf("Friend request sent to %s.\n", receiver_name);
}

void show_and_accept_requests(const char *receiver_name) {
    FILE *fp = fopen("data/requests.txt", "r");
    if (!fp) {
        printf("No pending friend requests.\n");
        return;
    }
    
    FILE *temp = fopen("data/temp_requests.txt", "w");
    if (!temp) {
        fclose(fp);
        printf("Error: Could not process friend requests.\n");
        return;
    }
    
    FILE *friends_fp = fopen("data/friends.txt", "a");
    if (!friends_fp) {
        fclose(fp);
        fclose(temp);
        printf("Error: Could not process friend requests.\n");
        return;
    }
    
    char sender[50], receiver[50];
    int found = 0;

    while (fscanf(fp, "%s %s", sender, receiver) != EOF) {
        if (strcasecmp(receiver, receiver_name) == 0) {
            printf("Friend request from: %s\nAccept (y/n)? ", sender);
            char choice;
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                fprintf(friends_fp, "%s %s\n%s %s\n", sender, receiver, receiver, sender);
                printf("Friend request accepted from %s. You are now friends!\n", sender);
                log_event(receiver_name, "Accepted friend request");
            } else {
                printf("Friend request from %s rejected.\n", sender);
                log_event(receiver_name, "Rejected friend request");
            }
            found = 1;
        } else {
            fprintf(temp, "%s %s\n", sender, receiver);
        }
    }

    fclose(fp); fclose(temp); fclose(friends_fp);
    remove("data/requests.txt");
    rename("data/temp_requests.txt", "data/requests.txt");

    if (!found) {
        printf("No pending friend requests.\n");
    }
}

void view_friends(const char *user_name) {
    FILE *fp = fopen("data/friends.txt", "r");
    if (!fp) {
        printf("You have no friends yet.\n");
        return;
    }
    
    char u1[50], u2[50];
    int found = 0;

    printf("\n👥 Friends of %s:\n", user_name);
    while (fscanf(fp, "%s %s", u1, u2) != EOF) {
        if (strcasecmp(u1, user_name) == 0) {
            printf("• %s\n", u2);
            found = 1;
        }
    }
    if (!found) printf("You have no friends yet.\n");
    fclose(fp);
}
