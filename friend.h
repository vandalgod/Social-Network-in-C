#ifndef FRIEND_H
#define FRIEND_H

void ensure_data_directory();
void send_request(const char *sender_name, const char *receiver_name);
void show_and_accept_requests(const char *receiver_name);
void view_friends(const char *user_name);
int are_friends(const char *u1, const char *u2);
int is_request_already_sent(const char *sender, const char *receiver);
int user_exists_by_name(const char *name);
void add_friend(const char *user1, const char *user2);

#endif