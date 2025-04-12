#include <stdio.h>
#include <string.h>
#include "search.h"

void search_user(const char *key) {
    FILE *fp = fopen("data/users.txt", "r");
    char name[50], email[50], branch[50], hostel[50], password[20], gender[10], hostel_status[5];
    int found = 0;
    
    while (fscanf(fp, "%s %s %s %s %s %s %s", 
                  name, email, branch, hostel, password, gender, hostel_status) != EOF) {
        if (strstr(name, key) || strstr(email, key) || strstr(branch, key)) {
            printf("\nFound User:\n");
            printf("Name: %s\n", name);
            printf("Email: %s\n", email);
            printf("Branch: %s\n", branch);
            printf("Gender: %s\n", gender);
            printf("Hostel Status: %s\n", hostel_status);
            if (strcasecmp(hostel_status, "Yes") == 0) {
                printf("Hostel: %s\n", hostel);
            }
            printf("-------------------\n");
            found = 1;
        }
    }
    
    if (!found) {
        printf("No user found matching '%s'.\n", key);
    }
    
    fclose(fp);
}
