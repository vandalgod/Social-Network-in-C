#ifndef SEARCH_H
#define SEARCH_H

/**
 * Search users by name
 * @param name The name to search for
 * @param current_user_email Email of the current user (to exclude from results)
 */
void search_by_name(const char *name, const char *current_user_email);

/**
 * Search users by email
 * @param email_search The email pattern to search for
 * @param current_user_email Email of the current user (to exclude from results)
 */
void search_by_email(const char *email_search, const char *current_user_email);

/**
 * Search users by hostel
 * @param hostel_search The hostel name to search for
 * @param current_user_email Email of the current user (to exclude from results)
 */
void search_by_hostel(const char *hostel_search, const char *current_user_email);

/**
 * Search users by branch
 * @param branch_search The branch name to search for
 * @param current_user_email Email of the current user (to exclude from results)
 */
void search_by_branch(const char *branch_search, const char *current_user_email);

/**
 * Helper function to convert string to lowercase
 * @param str The string to convert
 */
void str_tolower(char *str);

/**
 * Search users by any criteria
 * @param query The search query
 */
void search_users(const char *query);

#endif