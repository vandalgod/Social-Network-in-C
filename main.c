#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "user.h"
#include "friend.h"
#include "post.h"
#include "search.h"
#include "log.h"

int main() {
    // Ensure data directory exists at program start
    ensure_data_directory();
     // Ensure data directory exists at startup
    #ifdef _WIN32
        system("if not exist data mkdir data");
    #else
        system("mkdir -p data");
    #endif

    
    int option;
    char email[50];

    while (1) {
        printf("\n--- SRM Social Network ---\n");
        printf("1. Register\n2. Login\n3. Exit\nChoose an option: ");
        
        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        while (getchar() != '\n'); // Clear input buffer

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
                printf("Invalid option! Please choose 1-3.\n");
        }
    }
}