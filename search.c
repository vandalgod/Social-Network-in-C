#define _GNU_SOURCE /* Add this for strcasestr */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "search.h"
#include "user.h"

/* If your system doesn't support strcasestr even with _GNU_SOURCE, 
   uncomment this implementation */
/*
char *strcasestr(const char *haystack, const char *needle) {
    if (!*needle) return (char*)haystack;
    
    size_t haystack_len = strlen(haystack);
    size_t needle_len = strlen(needle);
    
    if (haystack_len < needle_len) return NULL;
    
    for (size_t i = 0; i <= haystack_len - needle_len; i++) {
        if (strncasecmp(haystack + i, needle, needle_len) == 0) {
            return (char*)(haystack + i);
        }
    }
    
    return NULL;
}
*/

// Convert string to lowercase
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
    
    printf("\n--- Search Results for '%s' ---\n", name);
    
    while (fscanf(fp, "%s %s %s %s %s %s %s", username, email, branch, hostel, pass, gender, hostel_status) != EOF) {
        // Skip current user
        if (strcmp(email, current_user_email) == 0) continue;
        
        // Check if name contains search term (case-insensitive)
        char temp_username[50];
        strcpy(temp_username, username);
        str_tolower(temp_username);
        
        char temp_name[50];
        strcpy(temp_name, name);
        str_tolower(temp_name);
        
        if (strstr(temp_username, temp_name)) {
            printf("Name: %s\n", username);
            printf("Email: %s\n", email);
            printf("Branch: %s\n", branch);
            if (strcmp(hostel_status, "Yes") == 0) {
                printf("Hostel: %s\n", hostel);
            }
            printf("Gender: %s\n", gender);
            printf("---------------------------\n");
            found = 1;
        }
    }
    
    fclose(fp);
    
    if (!found) {
        printf("No matching users found.\n");
    }
}

void search_by_email(const char *email_search, const char *current_user_email) {
    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) {
        printf("No users found.\n");
        return;
    }
    
    char username[50], email[50], branch[50], hostel[50], pass[20], gender[10], hostel_status[5];
    int found = 0;
    
    printf("\n--- Search Results for '%s' ---\n", email_search);
    
    while (fscanf(fp, "%s %s %s %s %s %s %s", username, email, branch, hostel, pass, gender, hostel_status) != EOF) {
        // Skip current user
        if (strcmp(email, current_user_email) == 0) continue;
        
        // Check if email contains search term (case-insensitive)
        char temp_email[50];
        strcpy(temp_email, email);
        str_tolower(temp_email);
        
        char temp_search[50];
        strcpy(temp_search, email_search);
        str_tolower(temp_search);
        
        if (strstr(temp_email, temp_search)) {
            printf("Name: %s\n", username);
            printf("Email: %s\n", email);
            printf("Branch: %s\n", branch);
            if (strcmp(hostel_status, "Yes") == 0) {
                printf("Hostel: %s\n", hostel);
            }
            printf("Gender: %s\n", gender);
            printf("---------------------------\n");
            found = 1;
        }
    }
    
    fclose(fp);
    
    if (!found) {
        printf("No matching users found.\n");
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
    
    printf("\n--- Search Results for Hostel '%s' ---\n", hostel_search);
    
    while (fscanf(fp, "%s %s %s %s %s %s %s", username, email, branch, hostel, pass, gender, hostel_status) != EOF) {
        // Skip current user
        if (strcmp(email, current_user_email) == 0) continue;
        
        // Only search users who stay in hostels
        if (strcmp(hostel_status, "Yes") == 0) {
            // Check if hostel contains search term (case-insensitive)
            char temp_hostel[50];
            strcpy(temp_hostel, hostel);
            str_tolower(temp_hostel);
            
            char temp_search[50];
            strcpy(temp_search, hostel_search);
            str_tolower(temp_search);
            
            if (strstr(temp_hostel, temp_search)) {
                printf("Name: %s\n", username);
                printf("Email: %s\n", email);
                printf("Branch: %s\n", branch);
                printf("Hostel: %s\n", hostel);
                printf("Gender: %s\n", gender);
                printf("---------------------------\n");
                found = 1;
            }
        }
    }
    
    fclose(fp);
    
    if (!found) {
        printf("No matching users found.\n");
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
    
    printf("\n--- Search Results for Branch '%s' ---\n", branch_search);
    
    while (fscanf(fp, "%s %s %s %s %s %s %s", username, email, branch, hostel, pass, gender, hostel_status) != EOF) {
        // Skip current user
        if (strcmp(email, current_user_email) == 0) continue;
        
        // Check if branch contains search term (case-insensitive)
        char temp_branch[50];
        strcpy(temp_branch, branch);
        str_tolower(temp_branch);
        
        char temp_search[50];
        strcpy(temp_search, branch_search);
        str_tolower(temp_search);
        
        if (strstr(temp_branch, temp_search)) {
            printf("Name: %s\n", username);
            printf("Email: %s\n", email);
            printf("Branch: %s\n", branch);
            if (strcmp(hostel_status, "Yes") == 0) {
                printf("Hostel: %s\n", hostel);
            }
            printf("Gender: %s\n", gender);
            printf("---------------------------\n");
            found = 1;
        }
    }
    
    fclose(fp);
    
    if (!found) {
        printf("No matching users found.\n");
    }
}

void search_users(const char *query) {
    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) {
        printf("Error: Cannot open users file.\n");
        return;
    }

    char name[50], email[50], branch[50], hostel[50], pass[20], gender[10], hostel_status[5];
    int found = 0;

    printf("\n--- Search Results ---\n");
    while (fscanf(fp, "%s %s %s %s %s %s %s", 
                  name, email, branch, hostel, pass, gender, hostel_status) != EOF) {
        if (strstr(name, query) || strstr(email, query) || 
            strstr(branch, query) || strstr(hostel, query)) {
            found = 1;
            printf("\nName: %s\n", name);
            printf("Email: %s\n", email);
            printf("Branch: %s\n", branch);
            printf("Hostel: %s\n", hostel);
            printf("-------------------\n");
        }
    }

    fclose(fp);

    if (!found) {
        printf("No users found matching your search.\n");
    }
}