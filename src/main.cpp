#include <stdio.h>

#include "protocol.h"

void print_msg (Message* message) {
    if (message->type)
        printf("\n%d\n", message->type);
    else
        printf("\ntype: (null)\n");

    if (message->channel)
        printf("%s\n", message->channel);
    else
        printf("channel: (null)\n");

    if (message->user)
        printf("%s\n", message->user);
    else
        printf("user: (null)\n");

    if (message->message)
        printf("%s\n", message->message);
    else
        printf("message: (null)\n");

    if (message->timestamp)
        printf("%s\n", asctime(localtime(&message->timestamp)));
    else
        printf("timestamp: (null)\n\n");
}

int main (void) {
    Message* join_msg = create_join_message("test_channel");
    Message* leave_msg = create_leave_message("test_channel");
    Message* register_msg = create_register_message("test_user");
    Message* text_msg = create_text_message("Hello, world!", "test_channel");

    uint16_t msg_len = 0;
    int i = 0;

    printf("Join message channel: ");
    char* string = serialize_message(join_msg, &msg_len);
    for (i = 0; i < msg_len; i++) {
        printf("%#X ", string[i]);
    }
    Message* message = deserialize_message(string);
    print_msg(message);
    free(message);
    free(string);

    msg_len = 0;
    printf("Leave message channel: ");
    string = serialize_message(leave_msg, &msg_len);
    for (i = 0; i < msg_len; i++) {
        printf("%#X ", string[i]);
    }
    message = deserialize_message(string);
    print_msg(message);
    free(string);
    free(message);

    msg_len = 0;
    printf("Register message user: ");
    string = serialize_message(register_msg, &msg_len);
    for (i = 0; i < msg_len; i++) {
        printf("%#X ", string[i]);
    }
    message = deserialize_message(string);
    print_msg(message);
    free(string);
    free(message);

    msg_len = 0;
    printf("Text message content: ");
    string = serialize_message(text_msg, &msg_len);
    for (i = 0; i < msg_len; i++) {
        printf("%#X ", string[i]);
    }
    message = deserialize_message(string);
    print_msg(message);
    free(string);
    free(message);

    // Free the allocated memory
    free_message(join_msg);
    free_message(leave_msg);
    free_message(register_msg);
    free_message(text_msg);

    return 0;
}
