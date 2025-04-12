#ifndef USER_H
#define USER_H

void register_user();
int login_user(char email[]);
void user_dashboard(char email[]);
int validate_email_format(const char *email);
int email_exists(const char *email);
int name_exists(const char *name);
int validate_gender(const char *gender);
int validate_hostel_status(const char *status);

#endif
