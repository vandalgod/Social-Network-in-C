#include <stdio.h>
#include <string.h>
#include "friend.h"
#include "log.h"

int are_already_friends(const char *user1, const char *user2) {
    FILE *fp = fopen("data/friends.txt", "r");
    char u1[50], u2[50];
    while (fscanf(fp, "%s %s", u1, u2) != EOF) {
        if ((strcmp(u1, user1) == 0 && strcmp(u2, user2) == 0) ||
            (strcmp(u1, user2) == 0 && strcmp(u2, user1) == 0)) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void send_request(const char *sender_name, const char *receiver_name) {
    if (are_already_friends(sender_name, receiver_name)) {
        printf("You are already friends with %s. Cannot send another request.\n", receiver_name);
        return;
    }

    // Check if request already exists
    FILE *check = fopen("data/requests.txt", "r");
    char s[50], r[50];
    while (fscanf(check, "%s %s", s, r) != EOF) {
        if (strcmp(s, sender_name) == 0 && strcmp(r, receiver_name) == 0) {
            fclose(check);
            printf("Friend request already sent to %s.\n", receiver_name);
            return;
        }
    }
    fclose(check);

    FILE *fp = fopen("data/requests.txt", "a");
    fprintf(fp, "%s %s\n", sender_name, receiver_name);
    fclose(fp);
    log_event(sender_name, "Sent friend request");
    printf("Friend request sent to %s.\n", receiver_name);
}

void show_and_accept_requests(const char *receiver_name) {
    FILE *fp = fopen("data/requests.txt", "r");
    FILE *temp = fopen("data/temp_requests.txt", "w");
    FILE *friends_fp = fopen("data/friends.txt", "a");
    char sender[50], receiver[50];
    int found = 0;

    printf("Friend requests for %s:\n", receiver_name);
    while (fscanf(fp, "%s %s", sender, receiver) != EOF) {
        if (strcmp(receiver, receiver_name) == 0) {
            found = 1;
            if (are_already_friends(sender, receiver_name)) {
                printf("%s already in your friend list. Skipping duplicate request.\n", sender);
                continue; // skip without adding to temp, remove from requests
            }

            printf("Request from: %s\n", sender);
            char choice;
            printf("Accept request from %s? (y/n): ", sender);
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                fprintf(friends_fp, "%s %s\n", sender, receiver);
                fprintf(friends_fp, "%s %s\n", receiver, sender);
                log_event(receiver, "Accepted friend request");
                printf("Friend request accepted from %s. You are friends now!\n", sender);
            } else {
                log_event(receiver, "Rejected friend request");
                printf("Friend request from %s rejected.\n", sender);
            }
        } else {
            fprintf(temp, "%s %s\n", sender, receiver); // keep unrelated
        }
    }

    fclose(fp);
    fclose(temp);
    fclose(friends_fp);
    remove("data/requests.txt");
    rename("data/temp_requests.txt", "data/requests.txt");

    if (!found) {
        printf("No pending friend requests.\n");
    }
}

void view_friends(const char *user_name) {
    FILE *fp = fopen("data/friends.txt", "r");
    char user1[50], user2[50];
    int count = 0;

    printf("\nYour Friends:\n");
    while (fscanf(fp, "%s %s", user1, user2) != EOF) {
        if (strcmp(user1, user_name) == 0) {
            printf("- %s\n", user2);
            count++;
        }
    }

    if (count == 0) {
        printf("You have no friends yet.\n");
    }

    fclose(fp);
}
