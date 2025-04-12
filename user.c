#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "user.h"
#include "friend.h"
#include "post.h"
#include "search.h"
#include "log.h"

char global_user_name[50];

// Helper function to convert string to lowercase
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int name_exists(const char *name) {
    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) return 0;
    
    char file_name[50], email[50], branch[50], hostel[50], pass[20], gender[10], hostel_status[5];
    while (fscanf(fp, "%s %s %s %s %s %s %s", 
                  file_name, email, branch, hostel, pass, gender, hostel_status) != EOF) {
        if (strcasecmp(name, file_name) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int validate_email_format(const char *email) {
    const char *domain = "@srmap.edu.in";
    int email_len = strlen(email);
    int domain_len = strlen(domain);
    
    if (email_len <= domain_len) return 0;
    
    // Check if email ends with @srmap.edu.in
    if (strcmp(email + email_len - domain_len, domain) != 0) return 0;
    
    // Check if username part (before @) is not empty
    if (email[0] == '@') return 0;
    
    return 1;
}

int email_exists(const char *email) {
    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) return 0;
    
    char name[50], file_email[50], branch[50], hostel[50], pass[20], gender[10], hostel_status[5];
    while (fscanf(fp, "%s %s %s %s %s %s %s", name, file_email, branch, hostel, pass, gender, hostel_status) != EOF) {
        if (strcmp(email, file_email) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int validate_gender(const char *gender) {
    char gender_lower[10];
    strcpy(gender_lower, gender);
    to_lowercase(gender_lower);
    
    return (strcmp(gender_lower, "male") == 0 || 
            strcmp(gender_lower, "female") == 0 || 
            strcmp(gender_lower, "other") == 0);
}

int validate_hostel_status(const char *status) {
    char status_lower[5];
    strcpy(status_lower, status);
    to_lowercase(status_lower);
    
    return (strcmp(status_lower, "yes") == 0 || strcmp(status_lower, "no") == 0);
}

void register_user() {
    char name[50], email[50], branch[50], hostel[50] = "N/A", password[20], gender[10], hostel_status[5];
    int valid_input = 0;

    printf("\n--- User Registration ---\n");
    
    // Name input with validation
    do {
        printf("Enter Name: ");
        scanf("%s", name);
        
        if (name_exists(name)) {
            printf("This name is already taken. Please choose a different name.\n");
            continue;
        }
        valid_input = 1;
    } while (!valid_input);
    
    // Email input with validation
    valid_input = 0;
    do {
        printf("Enter Email (must end with @srmap.edu.in): ");
        scanf("%s", email);
        
        if (!validate_email_format(email)) {
            printf("Invalid email format! Email must end with @srmap.edu.in\n");
            continue;
        }
        
        if (email_exists(email)) {
            printf("This email is already registered. Please use a different email.\n");
            continue;
        }
        
        valid_input = 1;
    } while (!valid_input);
    
    // Gender input
    valid_input = 0;
    do {
        printf("Enter Gender (Male/Female/Other - any case accepted): ");
        scanf("%s", gender);
        if (!validate_gender(gender)) {
            printf("Invalid gender! Please enter Male, Female, or Other (any case accepted).\n");
            continue;
        }
        // Convert to proper case for storage
        gender[0] = toupper(gender[0]);
        for (int i = 1; gender[i]; i++) {
            gender[i] = tolower(gender[i]);
        }
        valid_input = 1;
    } while (!valid_input);
    
    // Hostel status input
    valid_input = 0;
    do {
        printf("Do you stay in hostel? (Yes/No - any case accepted): ");
        scanf("%s", hostel_status);
        if (!validate_hostel_status(hostel_status)) {
            printf("Invalid input! Please enter Yes or No (any case accepted).\n");
            continue;
        }
        // Convert to proper case for storage
        hostel_status[0] = toupper(hostel_status[0]);
        for (int i = 1; hostel_status[i]; i++) {
            hostel_status[i] = tolower(hostel_status[i]);
        }
        valid_input = 1;
    } while (!valid_input);
    
    // Hostel name input if staying in hostel
    if (strcasecmp(hostel_status, "Yes") == 0) {
        printf("Enter Hostel Name: ");
        scanf("%s", hostel);
    }
    
    printf("Enter Branch: ");
    scanf("%s", branch);
    
    printf("Enter Password: ");
    scanf("%s", password);
    
    // Display summary for confirmation
    printf("\n--- Registration Summary ---\n");
    printf("Name: %s\n", name);
    printf("Email: %s\n", email);
    printf("Gender: %s\n", gender);
    printf("Hostel Status: %s\n", hostel_status);
    if (strcasecmp(hostel_status, "Yes") == 0) {
        printf("Hostel Name: %s\n", hostel);
    }
    printf("Branch: %s\n", branch);
    
    char confirm;
    printf("\nConfirm registration? (y/n): ");
    scanf(" %c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y') {
        FILE *fp = fopen("data/users.txt", "a");
        fprintf(fp, "%s %s %s %s %s %s %s\n", 
                name, email, branch, hostel, password, gender, hostel_status);
        fclose(fp);
        printf("Registration successful!\n");
        log_event(email, "Registered successfully");
    } else {
        printf("Registration cancelled.\n");
    }
}

int login_user(char email[]) {
    char file_name[50], file_email[50], file_branch[50], file_hostel[50], file_pass[20], file_gender[10], file_hostel_status[5];
    char password[20];
    int found = 0;

    printf("\n--- User Login ---\n");
    printf("Enter Email: ");
    scanf("%s", email);
    printf("Enter Password: ");
    scanf("%s", password);

    FILE *fp = fopen("data/users.txt", "r");
    while (fscanf(fp, "%s %s %s %s %s %s %s", 
                  file_name, file_email, file_branch, file_hostel, 
                  file_pass, file_gender, file_hostel_status) != EOF) {
        if (strcmp(email, file_email) == 0 && strcmp(password, file_pass) == 0) {
            found = 1;
            strcpy(global_user_name, file_name);
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
        printf("6. Logout\nChoose an option: ");
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
