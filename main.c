#include <stdio.h>
#include "user.h"

int main() {
    int choice;
    char email[50];

    while (1) {
        printf("\n=== SRM Social Network ===\n");
        printf("1. Register\n2. Login\n3. Exit\nChoose option: ");
        scanf("%d", &choice);
        if (choice == 1) {
            register_user();
        } else if (choice == 2) {
            if (login_user(email)) {
                user_dashboard(email);
            }
        } else {
            break;
        }
    }

    return 0;
}
