#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <cstdint>
#include <stdlib.h>
#include <time.h>

#if defined(__APPLE__)

// macOS specific definitions
// libkern/OSByteOrder.h defines htonll(x) OSSwapHostToBigInt64(x)
// libkern/OSByteOrder.h defines ntohll(x) OSSwapBigToHostInt64(x)
#include <libkern/OSByteOrder.h>

#elif defined(__linux__)

// Linux specific definitions
#include <endian.h>

#if __BYTE_ORDER == __BIG_ENDIAN
#define htonll(x) (x)
#define ntohll(x) (x)
#elif __BYTE_ORDER == __LITTLE_ENDIAN
#define htonll(x) __bswap_64(x)
#define ntohll(x) __bswap_64(x)
#endif

#else

// Generic fallback definitions (not comprehensive)
#define htonll(x) (x)
#define ntohll(x) (x)

#endif

typedef enum {
    JOIN = 1,
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

// Functions to convert message length to network byte order
uint32_t convert_message_len(uint32_t buffer_len);

// Functions to convert message length from network byte order
uint32_t convert_back_message_len(uint32_t net_message_total_len);

// Functions to convert 16-bit text data to network byte order
uint16_t convert_text_len(uint16_t message_len);

// Functions to convert 16-bit text data from network byte order
uint16_t convert_back_text_len(uint16_t net_message_len);

// Functions to convert 64-bit timestamp to network byte order
uint64_t convert_timestamp(uint64_t timestamp);

// Functions to convert 64-bit timestamp from network byte order
uint64_t convert_back_timestamp(uint64_t net_timestamp);

#endif // !_PROTOCOL_H_
