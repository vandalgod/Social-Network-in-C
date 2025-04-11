#include <stdio.h>
#include <string.h>
#include "search.h"

void search_user(const char *key) {
    FILE *fp = fopen("data/users.txt", "r");
    char name[50], email[50], password[50];
    int found = 0;
    while (fscanf(fp, "%s %s %s", name, email, password) != EOF) {
        if (strstr(name, key) || strstr(email, key)) {
            printf("Found: %s (%s)\n", name, email);
            found = 1;
        }
    }
    if (!found) printf("No user found.\n");
    fclose(fp);
}
