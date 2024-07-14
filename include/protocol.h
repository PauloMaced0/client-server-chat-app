#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
    JOIN = 0,
    LEAVE,
    REGISTER,
    TEXT
} MessageType;

typedef struct {
    MessageType type;
    char* channel;
    char* user;
    char* message;
    time_t timestamp;
} Message;

// Function prototypes
Message* create_join_message(const char* channel);
Message* create_leave_message(const char* channel);
Message* create_register_message(const char* user);
Message* create_text_message(const char* message, const char* channel);
void free_message(Message* msg);
char* message_to_json(const Message* msg);
Message* json_to_message(const char* json);
void send_message(int socket, const Message* msg);
Message* receive_message(int socket);
char* serialize_message(const Message* msg, uint16_t* buffer_len);
Message* deserialize_message(const char* bytes);
void send_message(int socket, const Message* msg);
Message* receive_message(int socket);

#endif // !_PROTOCOL_H_
