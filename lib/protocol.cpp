#include "../include/protocol.h"

#define MSG_TOT_LEN_PREFIX 4
#define MSG_LEN_PREFIX 2
#define LEN_CHANNEL_PREFIX 1
#define LEN_USER_PREFIX 1

Message* create_join_message(const char* channel) {
    Message* msg = (Message*)malloc(sizeof(Message));
    msg->type = JOIN;
    msg->channel = strdup(channel);
    msg->user = NULL;
    msg->message = NULL;
    time(&msg->timestamp);
    return msg;
}

Message* create_leave_message(const char* channel) {
    Message* msg = (Message*)malloc(sizeof(Message));
    msg->type = LEAVE;
    msg->channel = strdup(channel);
    msg->user = NULL;
    msg->message = NULL;
    time(&msg->timestamp);
    return msg;
}

Message* create_register_message(const char* user) {
    Message* msg = (Message*)malloc(sizeof(Message));
    msg->type = REGISTER;
    msg->channel = NULL;
    msg->user = strdup(user);
    msg->message = NULL;
    time(&msg->timestamp);
    return msg;
}

Message* create_text_message(const char* message, const char* channel) {
    Message* msg = (Message*)malloc(sizeof(Message));
    msg->type = TEXT;
    msg->channel = strdup(channel);
    msg->user = NULL;
    msg->message = strdup(message);
    time(&msg->timestamp);
    return msg;
}

void free_message(Message* msg) {
    if (msg) {
        if (msg->message)
            free(msg->channel);
        if (msg->user)
            free(msg->user);
        if (msg->message)
            free(msg->message);
        free(msg);
    }
}

char* serialize_message(const Message* msg, uint16_t* buffer_len) {
    uint8_t channel_len = msg->channel == NULL ? 0 : strlen(msg->channel);
    uint8_t user_len = msg->user == NULL ? 0 : strlen(msg->user);
    uint16_t message_len = msg->message == NULL ? 0 : strlen(msg->message);

    *buffer_len =  MSG_TOT_LEN_PREFIX + sizeof(msg->type) + LEN_CHANNEL_PREFIX + channel_len + LEN_USER_PREFIX + user_len + MSG_LEN_PREFIX + message_len + sizeof(time_t);
    char* string = (char*) malloc(*buffer_len);

    if (string == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }

    // Network byte order conversions
    uint32_t net_message_total_len = htonl((uint32_t) *buffer_len);
    uint16_t net_message_len = htons(message_len);
    time_t net_timestamp = htonll((time_t) msg->timestamp);

    char* ptr = string;

    memcpy(ptr, &net_message_total_len, sizeof(net_message_total_len));
    ptr += sizeof(net_message_total_len);

    memcpy(ptr, &(msg->type), sizeof(msg->type));
    ptr += sizeof(msg->type);
    
    memcpy(ptr, &channel_len, sizeof(channel_len));
    ptr += sizeof(channel_len);
    if (channel_len > 0) {
        memcpy(ptr, msg->channel, channel_len);
        ptr += channel_len;
    }

    memcpy(ptr, &user_len, sizeof(user_len));
    ptr += sizeof(user_len);
    if (user_len > 0) {
        memcpy(ptr, msg->user, user_len);
        ptr += user_len;
    }

    memcpy(ptr, &net_message_len, sizeof(net_message_len));
    ptr += sizeof(net_message_len);
    if (message_len > 0) {
        memcpy(ptr, msg->message, message_len);
        ptr += message_len;
    }

    memcpy(ptr, &net_timestamp, sizeof(net_timestamp));

    return string;
}

Message* deserialize_message(const char* bytes) {
    Message* msg = (Message*) malloc(sizeof(Message));
    if (msg == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }

    const char* ptr = bytes;

    ptr += MSG_TOT_LEN_PREFIX;

    // Read message type
    memcpy(&msg->type, ptr, sizeof(msg->type));
    ptr += sizeof(msg->type);

    // Read channel 
    uint8_t channel_len;
    memcpy(&channel_len, ptr, LEN_CHANNEL_PREFIX);
    ptr += LEN_CHANNEL_PREFIX;

    if (channel_len > 0) {
        msg->channel = (char*) malloc(channel_len + 1);
        if (msg->channel == NULL) {
            perror("Failed to allocate memory");
            free(msg);
            return NULL;
        }
        memcpy(msg->channel, ptr, channel_len);
        msg->channel[channel_len] = '\0';
        ptr += channel_len;
    } else {
        msg->channel = NULL; 
    }

    // Read user
    uint8_t user_len;
    memcpy(&user_len, ptr, LEN_USER_PREFIX);
    ptr += LEN_USER_PREFIX;

    if (user_len > 0) {
        msg->user = (char*) malloc(user_len + 1); 
        if (msg->user == NULL) {
            perror("Failed to allocate memory");
            free(msg->channel);
            free(msg);
            return NULL;
        }
        memcpy(msg->user, ptr, user_len);
        msg->user[user_len] = '\0';
        ptr += user_len;
    } else {
        msg->user = NULL;
    }

    // Read message
    uint16_t message_len;
    memcpy(&message_len, ptr, MSG_LEN_PREFIX);
    ptr += MSG_LEN_PREFIX;

    if (message_len > 0) {
        msg->message = (char*) malloc(message_len + 1);
        if (msg->message == NULL) {
            perror("Failed to allocate memory");
            free(msg->user);
            free(msg->channel);
            free(msg);
            return NULL;
        }
        memcpy(msg->message, ptr, message_len);
        msg->message[message_len] = '\0';
        ptr += message_len;
    } else {
        msg->message = NULL; 
    }

    // Read timestamp
    time_t timestamp;
    memcpy(&timestamp, ptr, sizeof(timestamp));
    msg->timestamp = (time_t) ntohll(timestamp);

    printf("%d\n", msg->type);
    printf("%s\n", msg->channel);
    printf("%s\n", msg->user);
    printf("%s\n", msg->message);
    printf("%s\n", asctime(localtime(&msg->timestamp)));

    return msg;
}

void send_message(int socket, const Message* msg) {
    return;
}

Message* receive_message(int socket) {
    Message* msg = NULL;
    return msg;
}
