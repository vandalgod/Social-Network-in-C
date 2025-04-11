#ifndef USER_H
#define USER_H

extern char global_user_name[50];  // <-- Add this line
void register_user();
int login_user(char email[]);
void user_dashboard(char email[]);

#endif
