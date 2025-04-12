#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "search.h"
#include "user.h"
#include "friend.h"
#include "log.h"

#define MAX_RESULTS 50
#define MAX_LINE_LENGTH 256

// Helper function to validate email format
int is_valid_email_format(const char *email) {
    int at_count = 0;
    int dot_count = 0;
    int len = strlen(email);
    
    // Check minimum length
    if (len < 5) return 0;
    
    // Check for @ and . symbols
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') at_count++;
        if (email[i] == '.') dot_count++;
        
        // Check for invalid characters
        if (!isalnum(email[i]) && email[i] != '@' && email[i] != '.' && email[i] != '_' && email[i] != '-')
            return 0;
    }
    
    // Must have exactly one @ and at least one .
    if (at_count != 1 || dot_count < 1) return 0;
    
    // @ cannot be first or last character
    if (email[0] == '@' || email[len-1] == '@') return 0;
    
    // . cannot be first or last character
    if (email[0] == '.' || email[len-1] == '.') return 0;
    
    return 1;
}

// Helper function to validate search input
int validate_search_input(const char *input) {
    if (input == NULL || strlen(input) == 0) return 0;
    return 1;
}

// Search by name
void search_by_name(const char *name, const char *current_user) {
    if (!validate_search_input(name)) {
        printf("Invalid name input.\n");
        return;
    }

    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) {
        printf("Error opening users file.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        char file_name[50], email[50], branch[50], hostel[50], gender[10], hostel_status[5];
        if (sscanf(line, "%s %s %s %s %*s %s %s", 
                  file_name, email, branch, hostel, gender, hostel_status) == 6) {
            if (strstr(file_name, name) && strcmp(email, current_user) != 0) {
                display_search_results(file_name, email, branch, hostel, gender, hostel_status, current_user);
                found = 1;
            }
        }
    }
    fclose(fp);

    if (!found) {
        printf("No users found with name containing '%s'.\n", name);
    }
    log_event(current_user, "Searched users by name");
}

// Search by email
void search_by_email(const char *email, const char *current_user) {
    if (!validate_search_input(email) || !is_valid_email_format(email)) {
        printf("Invalid email input.\n");
        return;
    }

    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) {
        printf("Error opening users file.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        char name[50], file_email[50], branch[50], hostel[50], gender[10], hostel_status[5];
        if (sscanf(line, "%s %s %s %s %*s %s %s", 
                  name, file_email, branch, hostel, gender, hostel_status) == 6) {
            if (strstr(file_email, email) && strcmp(file_email, current_user) != 0) {
                display_search_results(name, file_email, branch, hostel, gender, hostel_status, current_user);
                found = 1;
            }
        }
    }
    fclose(fp);

    if (!found) {
        printf("No users found with email containing '%s'.\n", email);
    }
    log_event(current_user, "Searched users by email");
}

// Search by hostel
void search_by_hostel(const char *hostel, const char *current_user) {
    if (!validate_search_input(hostel)) {
        printf("Invalid hostel input.\n");
        return;
    }

    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) {
        printf("Error opening users file.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        char name[50], email[50], branch[50], file_hostel[50], gender[10], hostel_status[5];
        if (sscanf(line, "%s %s %s %s %*s %s %s", 
                  name, email, branch, file_hostel, gender, hostel_status) == 6) {
            if (strcasecmp(hostel_status, "Yes") == 0 && 
                strstr(file_hostel, hostel) && 
                strcmp(email, current_user) != 0) {
                display_search_results(name, email, branch, file_hostel, gender, hostel_status, current_user);
                found = 1;
            }
        }
    }
    fclose(fp);

    if (!found) {
        printf("No users found in hostel '%s'.\n", hostel);
    }
    log_event(current_user, "Searched users by hostel");
}

// Search by branch
void search_by_branch(const char *branch, const char *current_user) {
    if (!validate_search_input(branch)) {
        printf("Invalid branch input.\n");
        return;
    }

    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) {
        printf("Error opening users file.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        char name[50], email[50], file_branch[50], hostel[50], gender[10], hostel_status[5];
        if (sscanf(line, "%s %s %s %s %*s %s %s", 
                  name, email, file_branch, hostel, gender, hostel_status) == 6) {
            if (strstr(file_branch, branch) && strcmp(email, current_user) != 0) {
                display_search_results(name, email, file_branch, hostel, gender, hostel_status, current_user);
                found = 1;
            }
        }
    }
    fclose(fp);

    if (!found) {
        printf("No users found in branch '%s'.\n", branch);
    }
    log_event(current_user, "Searched users by branch");
}

// Display search results with friend request option
void display_search_results(const char *name, const char *email, const char *branch, 
                          const char *hostel, const char *gender, const char *hostel_status,
                          const char *current_user) {
    printf("\nFound User:\n");
    printf("Name: %s\n", name);
    printf("Email: %s\n", email);
    printf("Branch: %s\n", branch);
    printf("Gender: %s\n", gender);
    printf("Hostel Status: %s\n", hostel_status);
    if (strcasecmp(hostel_status, "Yes") == 0) {
        printf("Hostel: %s\n", hostel);
    }
    
    // Check if already friends
    if (are_friends(current_user, name)) {
        printf("Status: Already friends\n");
    } else if (is_request_already_sent(current_user, name)) {
        printf("Status: Friend request pending\n");
    } else {
        printf("\nSend friend request to %s? (y/n): ", name);
        char choice;
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            send_request(current_user, name);
        }
    }
    printf("-------------------\n");
}
