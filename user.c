#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "friend.h"
#include "post.h"
#include "search.h"
#include "log.h"

char global_user_name[50];  // Define global user name

int user_email_exists(const char *email) {
    FILE *fp = fopen("data/users.txt", "r");
    char name[50], branch[50], hostel[50], email_check[100], password[50];

    if (!fp) return 0;

    while (fscanf(fp, "%s %s %s %s %s", name, email_check, branch, hostel, password) != EOF) {
        if (strcmp(email_check, email) == 0) {
            fclose(fp);
            return 1; // email already registered
        }
    }

    fclose(fp);
    return 0;
}

int user_name_exists(const char *name) {
    FILE *fp = fopen("data/users.txt", "r");
    char name_check[50], email[50], branch[50], hostel[50], password[50];

    if (!fp) return 0;

    while (fscanf(fp, "%s %s %s %s %s", name_check, email, branch, hostel, password) != EOF) {
        if (strcmp(name_check, name) == 0) {
            fclose(fp);
            return 1; // name already exists
        }
    }

    fclose(fp);
    return 0;
}

void register_user() {
    char name[50], email[50], branch[50], hostel[50], password[20];

    printf("\n--- User Registration ---\n");
    printf("Enter Name: ");
    scanf("%s", name);

    if (user_name_exists(name)) {
        printf("\n❌ This username is already taken. Please choose a different name.\n");
        return;
    }

    printf("Enter Email (xxx@srmap.edu.in): ");
    scanf("%s", email);

    if (user_email_exists(email)) {
        printf("\n❌ This email is already registered. Please log in or use another email.\n");
        return;
    }

    printf("Enter Branch: ");
    scanf("%s", branch);
    printf("Enter Hostel: ");
    scanf("%s", hostel);
    printf("Enter Password: ");
    scanf("%s", password);

    FILE *fp = fopen("data/users.txt", "a");
    fprintf(fp, "%s %s %s %s %s\n", name, email, branch, hostel, password);
    fclose(fp);
    printf("Registration successful!\n");
    log_event(email, "Registered successfully");
}

int login_user(char email[]) {
    char file_name[50], file_email[50], file_branch[50], file_hostel[50], file_pass[20];
    char password[20];
    int found = 0;

    printf("\n--- User Login ---\n");
    printf("Enter Email: ");
    scanf("%s", email);
    printf("Enter Password: ");
    scanf("%s", password);

    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) {
        printf("Error opening user database!\n");
        return 0;
    }

    while (fscanf(fp, "%s %s %s %s %s", file_name, file_email, file_branch, file_hostel, file_pass) != EOF) {
        if (strcmp(email, file_email) == 0 && strcmp(password, file_pass) == 0) {
            found = 1;
            strcpy(global_user_name, file_name); // set logged-in name
            break;
        }
    }

    fclose(fp);

    if (found) {
        printf("Login successful! Welcome, %s!\n", global_user_name);
        log_event(email, "Logged in successfully");
        return 1;
    } else {
        printf("Invalid credentials!\n");
        log_event(email, "Failed login attempt");
        return 0;
    }
}

void user_dashboard(char email[]) {
    int option;
    char friend_name[50], search_key[50];

    while (1) {
        printf("\n--- %s's Dashboard ---\n", global_user_name);
        printf("1. Send Friend Request (by name)\n");
        printf("2. Accept Friend Request\n");
        printf("3. Post a Message\n");
        printf("4. Search User\n");
        printf("5. View Friends\n");
        printf("6. Logout\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter Name to send friend request: ");
                scanf("%s", friend_name);
                send_request(global_user_name, friend_name);
                break;
            case 2:
                show_and_accept_requests(global_user_name);
                break;
            case 3:
                post_message(global_user_name);
                break;
            case 4:
                printf("Enter name/email to search: ");
                scanf("%s", search_key);
                search_user(search_key);
                break;
            case 5:
                view_friends(global_user_name);
                break;
            case 6:
                log_event(email, "Logged out");
                printf("Logged out successfully.\n");
                return;
            default:
                printf("Invalid option! Try again.\n");
        }
    }
}
