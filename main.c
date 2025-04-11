#include <stdio.h>
#include "user.h"

int main() {
    int option;
    char email[50];

    while (1) {
        printf("\n--- SRM Social Network ---\n");
        printf("1. Register\n2. Login\n3. Exit\nChoose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                register_user();
                break;
            case 2:
                if (login_user(email)) {
                    user_dashboard(email);
                }
                break;
            case 3:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid option!\n");
        }
    }
}
