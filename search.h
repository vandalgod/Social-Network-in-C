#ifndef SEARCH_H
#define SEARCH_H

void search_by_name(const char *name, const char *current_user_email);


void search_by_email(const char *email_search, const char *current_user_email);

void search_by_hostel(const char *hostel_search, const char *current_user_email);


void search_by_branch(const char *branch_search, const char *current_user_email);


void str_tolower(char *str);


void search_users(const char *query);

#endif