#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "search.h"
#include "user.h"
#include "friend.h"

extern char global_user_name[50];

void str_tolower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void search_by_name(const char *name, const char *current_user_email) {
    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) {
        printf("No users found.\n");
        return;
    }
    
    char username[50], email[50], branch[50], hostel[50], pass[20], gender[10], hostel_status[5];
    int found = 0;
    int result_count = 0;
    int results[100];
    char found_names[100][50];
    
    printf("\n--- Search Results for '%s' ---\n", name);
    
    while (fscanf(fp, "%s %s %s %s %s %s %s", username, email, branch, hostel, pass, gender, hostel_status) != EOF) {
        if (strcmp(email, current_user_email) == 0) continue;
        
        char temp_username[50];
        strcpy(temp_username, username);
        str_tolower(temp_username);
        
        char temp_name[50];
        strcpy(temp_name, name);
        str_tolower(temp_name);
        
        if (strstr(temp_username, temp_name)) {
            printf("[%d] Name: %s\n", result_count + 1, username);
            printf("Email: %s\n", email);
            printf("Branch: %s\n", branch);
            if (strcmp(hostel_status, "Yes") == 0) {
                printf("Hostel: %s\n", hostel);
            }
            printf("Gender: %s\n", gender);
            printf("---------------------------\n");
            
            strcpy(found_names[result_count], username);
            results[result_count] = found;
            result_count++;
            found = 1;
        }
    }
    
    fclose(fp);
    
    if (!found) {
        printf("No matching users found.\n");
        return;
    }
    
    int choice;
    printf("\nDo you want to send a friend request?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Enter your choice: ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    if (choice == 1) {
        if (result_count == 1) {
            send_request(global_user_name, found_names[0]);
        } else if (result_count > 1) {
            int user_index;
            printf("Enter the number of the user to send a friend request: ");
            if (scanf("%d", &user_index) != 1 || user_index < 1 || user_index > result_count) {
                printf("Invalid selection.\n");
                while (getchar() != '\n');
                return;
            }
            while (getchar() != '\n');
            
            send_request(global_user_name, found_names[user_index - 1]);
        }
    }
}

void search_by_hostel(const char *hostel_search, const char *current_user_email) {
    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) {
        printf("No users found.\n");
        return;
    }
    
    char username[50], email[50], branch[50], hostel[50], pass[20], gender[10], hostel_status[5];
    int found = 0;
    int result_count = 0;
    int results[100];
    char found_names[100][50];
    
    printf("\n--- Search Results for Hostel '%s' ---\n", hostel_search);
    
    while (fscanf(fp, "%s %s %s %s %s %s %s", username, email, branch, hostel, pass, gender, hostel_status) != EOF) {
        if (strcmp(email, current_user_email) == 0) continue;
        
        if (strcmp(hostel_status, "Yes") == 0) {
            char temp_hostel[50];
            strcpy(temp_hostel, hostel);
            str_tolower(temp_hostel);
            
            char temp_search[50];
            strcpy(temp_search, hostel_search);
            str_tolower(temp_search);
            
            if (strstr(temp_hostel, temp_search)) {
                printf("[%d] Name: %s\n", result_count + 1, username);
                printf("Email: %s\n", email);
                printf("Branch: %s\n", branch);
                printf("Hostel: %s\n", hostel);
                printf("Gender: %s\n", gender);
                printf("---------------------------\n");
                
                strcpy(found_names[result_count], username);
                results[result_count] = found;
                result_count++;
                found = 1;
            }
        }
    }
    
    fclose(fp);
    
    if (!found) {
        printf("No matching users found.\n");
        return;
    }
    
    int choice;
    printf("\nDo you want to send a friend request?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Enter your choice: ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    if (choice == 1) {
        if (result_count == 1) {
            send_request(global_user_name, found_names[0]);
        } else if (result_count > 1) {
            int user_index;
            printf("Enter the number of the user to send a friend request: ");
            if (scanf("%d", &user_index) != 1 || user_index < 1 || user_index > result_count) {
                printf("Invalid selection.\n");
                while (getchar() != '\n');
                return;
            }
            while (getchar() != '\n');
            
            send_request(global_user_name, found_names[user_index - 1]);
        }
    }
}

void search_by_branch(const char *branch_search, const char *current_user_email) {
    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) {
        printf("No users found.\n");
        return;
    }
    
    char username[50], email[50], branch[50], hostel[50], pass[20], gender[10], hostel_status[5];
    int found = 0;
    int result_count = 0;
    int results[100];
    char found_names[100][50];
    
    printf("\n--- Search Results for Branch '%s' ---\n", branch_search);
    
    while (fscanf(fp, "%s %s %s %s %s %s %s", username, email, branch, hostel, pass, gender, hostel_status) != EOF) {
        if (strcmp(email, current_user_email) == 0) continue;
        
        char temp_branch[50];
        strcpy(temp_branch, branch);
        str_tolower(temp_branch);
        
        char temp_search[50];
        strcpy(temp_search, branch_search);
        str_tolower(temp_search);
        
        if (strstr(temp_branch, temp_search)) {
            printf("[%d] Name: %s\n", result_count + 1, username);
            printf("Email: %s\n", email);
            printf("Branch: %s\n", branch);
            if (strcmp(hostel_status, "Yes") == 0) {
                printf("Hostel: %s\n", hostel);
            }
            printf("Gender: %s\n", gender);
            printf("---------------------------\n");
            
            strcpy(found_names[result_count], username);
            results[result_count] = found;
            result_count++;
            found = 1;
        }
    }
    
    fclose(fp);
    
    if (!found) {
        printf("No matching users found.\n");
        return;
    }
    
    int choice;
    printf("\nDo you want to send a friend request?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Enter your choice: ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    if (choice == 1) {
        if (result_count == 1) {
            send_request(global_user_name, found_names[0]);
        } else if (result_count > 1) {
            int user_index;
            printf("Enter the number of the user to send a friend request: ");
            if (scanf("%d", &user_index) != 1 || user_index < 1 || user_index > result_count) {
                printf("Invalid selection.\n");
                while (getchar() != '\n');
                return;
            }
            while (getchar() != '\n');
            
            send_request(global_user_name, found_names[user_index - 1]);
        }
    }
}
