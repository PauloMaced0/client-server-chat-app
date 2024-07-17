#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <ctime>
#include <string>
#include <memory>

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

using string = std::string;

typedef enum {
    JOIN = 1,
    LEAVE,
    REGISTER,
    TEXT
} MessageType;

class Message {
public:
    int command;

    Message(const int& cmd) : command(cmd) {}

    virtual ~Message() = default;

    virtual string to_string() const = 0;

    static std::unique_ptr<Message> from_string(const string& data);
};

class JoinMessage : public Message {
public:
    string channel;

    JoinMessage(const string& ch) : Message(JOIN), channel(ch) {}

    string to_string() const override;

    static std::unique_ptr<JoinMessage> from_string(const string& data);
};


class LeaveMessage : public Message {
public:
    string channel;

    LeaveMessage(const string& ch) : Message(LEAVE), channel(ch) {}

    string to_string() const override;

    static std::unique_ptr<LeaveMessage> from_string(const string& data);
};

class RegisterMessage : public Message {
public:
    string user;

    RegisterMessage(const string& usr) : Message(REGISTER), user(usr) {}

    string to_string() const override;

    static std::unique_ptr<RegisterMessage> from_string(const string& data);
};

class TextMessage : public Message {
public:
    string message;
    string channel;
    time_t ts;

    TextMessage(const string& msg, const string& ch, time_t timestamp = time(NULL))
        : Message(TEXT), message(msg), channel(ch), ts(timestamp) {}

    string to_string() const override;

    static std::unique_ptr<TextMessage> from_string(const string& data);
};

class Proto {
public:
    static RegisterMessage register_user(const string& username);

    static JoinMessage join(const string& channel);

    static LeaveMessage leave(const string& channel);

    static TextMessage message(const string& message, const string& channel = "");

    static void send_msg(int socket_fd, const Message& msg);

    static std::unique_ptr<Message> recv_msg(int socket_fd);
};

class ProtoBadFormat : public std::runtime_error {
public:
    ProtoBadFormat(const string& original_msg)
        : std::runtime_error("Bad message format"), original_msg_(original_msg) {}

    const string& original_msg() const;

private:
    string original_msg_;
};

#endif // !_PROTOCOL_H_
