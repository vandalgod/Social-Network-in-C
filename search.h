#ifndef SEARCH_H
#define SEARCH_H

// Search functions
void search_by_name(const char *name, const char *current_user);
void search_by_email(const char *email, const char *current_user);
void search_by_hostel(const char *hostel, const char *current_user);
void search_by_branch(const char *branch, const char *current_user);

// Validation functions
int validate_search_input(const char *input);
int is_valid_email_format(const char *email);

// Display functions
void display_search_results(const char *name, const char *email, const char *branch, 
                          const char *hostel, const char *gender, const char *hostel_status,
                          const char *current_user);

#endif
