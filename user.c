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
        str[i] = tolower((unsigned char)str[i]);
    }
}

int name_exists(const char *name) {
    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) {
        printf("Error: Unable to open users file for checking name.\n");
        return 0;
    }

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

    if (strcmp(email + email_len - domain_len, domain) != 0) return 0;

    if (email[0] == '@') return 0;

    return 1;
}

int email_exists(const char *email) {
    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) return 0;
    
    char name[50], file_email[50], branch[50], hostel[50], pass[20], gender[10], hostel_status[5];
    char email_lower[50], file_email_lower[50];
    
    // Convert input email to lowercase
    strcpy(email_lower, email);
    to_lowercase(email_lower);
    
    while (fscanf(fp, "%s %s %s %s %s %s %s", name, file_email, branch, hostel, pass, gender, hostel_status) != EOF) {
        // Convert stored email to lowercase for comparison
        strcpy(file_email_lower, file_email);
        to_lowercase(file_email_lower);
        
        if (strcmp(email_lower, file_email_lower) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int validate_gender(const char *gender) {
    char gender_lower[10];
    strncpy(gender_lower, gender, sizeof(gender_lower) - 1);
    gender_lower[sizeof(gender_lower) - 1] = '\0';
    to_lowercase(gender_lower);

    return (strcmp(gender_lower, "male") == 0 ||
            strcmp(gender_lower, "female") == 0 ||
            strcmp(gender_lower, "other") == 0);
}

int validate_hostel_status(const char *status) {
    char status_lower[5];
    strncpy(status_lower, status, sizeof(status_lower) - 1);
    status_lower[sizeof(status_lower) - 1] = '\0';
    to_lowercase(status_lower);

    return (strcmp(status_lower, "yes") == 0 || strcmp(status_lower, "no") == 0);
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void register_user() {
    char name[50], email[50], branch[50], hostel[50] = "N/A", password[20], gender[10], hostel_status[5];
    int valid_input = 0;

    printf("\n--- User Registration ---\n");

    do {
        printf("Enter Name: ");
        if (fgets(name, sizeof(name), stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        }

        size_t len = strlen(name);
        if (len > 0 && name[len-1] == '\n') {
            name[len-1] = '\0';
        }

        if (strlen(name) == 0) {
            printf("Name cannot be empty.\n");
            continue;
        }

        if (name_exists(name)) {
            printf("This name is already taken. Please choose a different name.\n");
            continue;
        }
        valid_input = 1;
    } while (!valid_input);

    valid_input = 0;
    do {
        printf("Enter Email (must end with @srmap.edu.in): ");
        if (fgets(email, sizeof(email), stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        }

        size_t len = strlen(email);
        if (len > 0 && email[len-1] == '\n') {
            email[len-1] = '\0';
        }

        to_lowercase(email);  // ✅ Normalize email

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

    valid_input = 0;
    do {
        printf("Enter Gender (Male/Female/Other - any case accepted): ");
        if (fgets(gender, sizeof(gender), stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        }

        size_t len = strlen(gender);
        if (len > 0 && gender[len-1] == '\n') {
            gender[len-1] = '\0';
        }

        if (!validate_gender(gender)) {
            printf("Invalid gender! Please enter Male, Female, or Other.\n");
            continue;
        }

        gender[0] = toupper(gender[0]);
        for (int i = 1; gender[i]; i++) {
            gender[i] = tolower(gender[i]);
        }
        valid_input = 1;
    } while (!valid_input);

    valid_input = 0;
    do {
        printf("Do you stay in hostel? (Yes/No): ");
        if (fgets(hostel_status, sizeof(hostel_status), stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        }

        size_t len = strlen(hostel_status);
        if (len > 0 && hostel_status[len-1] == '\n') {
            hostel_status[len-1] = '\0';
        }

        if (!validate_hostel_status(hostel_status)) {
            printf("Invalid input! Please enter Yes or No.\n");
            continue;
        }

        hostel_status[0] = toupper(hostel_status[0]);
        for (int i = 1; hostel_status[i]; i++) {
            hostel_status[i] = tolower(hostel_status[i]);
        }
        valid_input = 1;
    } while (!valid_input);

    if (strcasecmp(hostel_status, "Yes") == 0) {
        printf("Enter Hostel Name: ");
        if (fgets(hostel, sizeof(hostel), stdin) == NULL) {
            printf("Error reading input.\n");
            strcpy(hostel, "N/A");
        } else {
            size_t len = strlen(hostel);
            if (len > 0 && hostel[len-1] == '\n') {
                hostel[len-1] = '\0';
            }

            if (strlen(hostel) == 0) {
                strcpy(hostel, "N/A");
            }
        }
    }

    printf("Enter Branch: ");
    if (fgets(branch, sizeof(branch), stdin) == NULL) {
        printf("Error reading input.\n");
        strcpy(branch, "Not_Specified");
    } else {
        size_t len = strlen(branch);
        if (len > 0 && branch[len-1] == '\n') {
            branch[len-1] = '\0';
        }

        if (strlen(branch) == 0) {
            strcpy(branch, "Not_Specified");
        }
    }

    printf("Enter Password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        printf("Error reading input.\n");
        return;
    }

    size_t len = strlen(password);
    if (len > 0 && password[len-1] == '\n') {
        password[len-1] = '\0';
    }

    if (strlen(password) == 0) {
        printf("Password cannot be empty.\n");
        return;
    }

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
    clear_input_buffer();

    if (confirm == 'y' || confirm == 'Y') {
        FILE *fp = fopen("data/users.txt", "a");
        if (!fp) {
            printf("Error: Unable to open users file for registration.\n");
            return;
        }

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
    char email_lower[50], file_email_lower[50];
    int found = 0;

    printf("\n--- User Login ---\n");
    printf("Enter Email: ");
    scanf("%s", email);
    printf("Enter Password: ");
    scanf("%s", password);

    // Convert input email to lowercase
    strcpy(email_lower, email);
    to_lowercase(email_lower);

    FILE *fp = fopen("data/users.txt", "r");
    while (fscanf(fp, "%s %s %s %s %s %s %s", 
                  file_name, file_email, file_branch, file_hostel, 
                  file_pass, file_gender, file_hostel_status) != EOF) {
        // Convert stored email to lowercase for comparison
        strcpy(file_email_lower, file_email);
        to_lowercase(file_email_lower);
        
        if (strcmp(email_lower, file_email_lower) == 0 && strcmp(password, file_pass) == 0) {
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
    int choice;
    char friend_name[50];
    char search_query[50],search_name[50], search_email[50], search_hostel[50], search_branch[50];
    
    while (1) {
        printf("\n--- %s's Dashboard ---\n", global_user_name);
        printf("1. View Profile\n");
        printf("2. Send Friend Request (by name)\n");
        printf("3. Accept Friend Request\n");
        printf("4. Post a Message\n");
        printf("5. View My Messages\n");
        printf("6. View Friends' Messages\n");
        printf("7. Search Users\n");
        printf("8. View Friends\n");
        printf("9. Logout\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer(); // Clear input buffer
            continue;
        }
        clear_input_buffer(); // Clear input buffer

        switch (choice) {
            case 1:
                view_profile(email);
                break;
            case 2:
                printf("Enter friend's name: ");
                if (scanf("%s", friend_name) != 1) {
                    printf("Error reading input.\n");
                    clear_input_buffer();
                    continue;
                }
                clear_input_buffer();
                send_request(global_user_name, friend_name);
                break;
            case 3:
                show_and_accept_requests(global_user_name);
                break;
            case 4:
                post_message(global_user_name);
                break;
            case 5:
                view_messages(global_user_name);
                break;
            case 6:
                view_friend_messages(global_user_name);
                break;
            case 7:
                printf("\n--- Search Users ---\n");
                printf("1. Search by Name\n");
                printf("2. Search by Email\n");
                printf("3. Search by Hostel\n");
                printf("4. Search by Branch\n");
                printf("Choose search type (1-4): ");
                
                int search_choice;
                if (scanf("%d", &search_choice) != 1) {
                    printf("Invalid input! Please enter a number between 1 and 4.\n");
                    clear_input_buffer();
                    continue;
                }
                clear_input_buffer();
                
                if (search_choice < 1 || search_choice > 4) {
                    printf("Invalid option! Please enter a number between 1 and 4.\n");
                    continue;
                }
                
                switch (search_choice) {
                    case 1:
                        printf("Enter name to search: ");
                        if (scanf("%s", search_name) != 1) {
                            printf("Error reading input.\n");
                            clear_input_buffer();
                            continue;
                        }
                        clear_input_buffer();
                        search_by_name(search_name, email);
                        break;
                    case 2:
                        printf("Enter email to search: ");
                        if (scanf("%s", search_email) != 1) {
                            printf("Error reading input.\n");
                            clear_input_buffer();
                            continue;
                        }
                        clear_input_buffer();
                        search_by_email(search_email, email);
                        break;
                    case 3:
                        printf("Enter hostel to search: ");
                        if (scanf("%s", search_hostel) != 1) {
                            printf("Error reading input.\n");
                            clear_input_buffer();
                            continue;
                        }
                        clear_input_buffer();
                        search_by_hostel(search_hostel, email);
                        break;
                    case 4:
                        printf("Enter branch to search: ");
                        if (scanf("%s", search_branch) != 1) {
                            printf("Error reading input.\n");
                            clear_input_buffer();
                            continue;
                        }
                        clear_input_buffer();
                        search_by_branch(search_branch, email);
                        break;
                }
                break;
            case 8:
                view_friends(global_user_name);
                break;
            case 9:
                printf("Logging out...\n");
                log_event(email, "Logged out");
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void view_profile(char email[]) {
    FILE *fp = fopen("data/users.txt", "r");
    if (!fp) {
        printf("Error: Cannot open users file.\n");
        return;
    }

    char name[50], file_email[50], branch[50], hostel[50], pass[20], gender[10], hostel_status[5];
    int found = 0;

    while (fscanf(fp, "%s %s %s %s %s %s %s", 
                  name, file_email, branch, hostel, pass, gender, hostel_status) != EOF) {
        if (strcmp(email, file_email) == 0) {
            found = 1;
            printf("\n--- Your Profile ---\n");
            printf("Name: %s\n", name);
            printf("Email: %s\n", file_email);
            printf("Branch: %s\n", branch);
            printf("Hostel: %s\n", hostel);
            printf("Gender: %s\n", gender);
            printf("Hostel Status: %s\n", hostel_status);
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Error: Profile not found.\n");
    }
}
