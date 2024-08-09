#include "protocol.h"

#include <arpa/inet.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <cstring>
#include <sys/_endian.h>
#include <unistd.h>

string JoinMessage::to_string() const {
    std::ostringstream oss;
    oss << command << '\0' << channel;
    return oss.str();
}

std::unique_ptr<JoinMessage> JoinMessage::from_string(const string &data) {
    std::istringstream strStream(data);
    string cmd, ch;
    std::getline(strStream, cmd, '\0');
    std::getline(strStream, ch, '\0');
    return std::make_unique<JoinMessage>(ch);
}

string LeaveMessage::to_string() const {
    std::ostringstream oss;
    oss << command << '\0' << channel;
    return oss.str();
}

std::unique_ptr<LeaveMessage> LeaveMessage::from_string(const string &data) {
    std::istringstream strStream(data);
    string cmd, ch;
    std::getline(strStream, cmd, '\0');
    std::getline(strStream, ch, '\0');
    return std::make_unique<LeaveMessage>(ch);
}

string RegisterMessage::to_string() const {
    std::ostringstream oss;
    oss << command << '\0' << user;
    return oss.str();
}

std::unique_ptr<RegisterMessage> RegisterMessage::from_string(const string &data) {
    std::istringstream strStream(data);
    string cmd, usr;
    std::getline(strStream, cmd, '\0');
    std::getline(strStream, usr, '\0');
    return std::make_unique<RegisterMessage>(usr);
}

string TextMessage::to_string() const {
    std::ostringstream oss;
    oss << command << '\0' << message << '\0' << channel << '\0' << ts;
    return oss.str();
}

std::unique_ptr<TextMessage> TextMessage::from_string(const string &data) {
    std::istringstream strStream(data);
    string cmd, msg, ch;
    time_t timestamp;
    std::getline(strStream, cmd, '\0');
    std::getline(strStream, msg, '\0');
    std::getline(strStream, ch, '\0');
    strStream >> timestamp;
    return std::make_unique<TextMessage>(msg, ch, timestamp);
}

RegisterMessage Proto::register_user(const string &username) {
    return RegisterMessage(username);
}

JoinMessage Proto::join(const string &channel) {
    return JoinMessage(channel);
}
LeaveMessage Proto::leave(const string &channel) {
    return LeaveMessage(channel);
}

TextMessage Proto::message(const string &message, const string& channel) {
    return TextMessage(message, channel, static_cast<time_t>(std::time(nullptr)));
}

void Proto::send_msg(int socket_fd, const Message &msg) {
    int sent;
    string msg_str = msg.to_string();
    uint32_t len = msg_str.size();

    uint32_t len_network_order = htonl(len);

    char len_bytes[sizeof(uint32_t)];
    memcpy(len_bytes, &len_network_order, sizeof(uint32_t));

    string full_frame(len_bytes, sizeof(uint32_t));

    full_frame += msg_str;

    sent = send(socket_fd, &full_frame, full_frame.size(), 0); 

    if (sent == -1) {
        std::cerr << "Failed to send message data. Error code: " << errno << " (" << strerror(errno) << ")" << std::endl;
        exit(EXIT_FAILURE);
    } else if ((uint32_t) sent == msg_str.size()) {
        throw std::runtime_error("Failed to send message data");
    }
}

std::unique_ptr<Message> Proto::recv_msg(int socket_fd) {
    int received;
    char len_arr[sizeof(uint32_t)];
    uint32_t len;

    received = recv(socket_fd, &len_arr, sizeof(len_arr)/sizeof(len_arr[0]), 0);

    memcpy(&len, len_arr, sizeof(len));

    len = ntohl(len);

    if (received == 0) {
        std::cerr << "Connection is closed!" << std::endl;
        return NULL;
    } else if (received == -1) {
        std::cerr << "Failed to receive message length. Error code: " << errno << " (" << strerror(errno) << ")" << std::endl;
        return NULL;
    } else if ((uint32_t) received != sizeof(len_arr)/sizeof(len_arr[0])) { 
        std::cerr << "Failed to receive message data" << std::endl;
        return NULL;
    }

    char buffer[len];

    received = recv(socket_fd, &buffer, len, 0);
    if (received == 0) {
        std::cerr << "Connection is closed!" << std::endl;
        return NULL;
    } else if (received == -1) {
        std::cerr << "Failed to receive message length. Error code: " << errno << " (" << strerror(errno) << ")" << std::endl;
        return NULL;
    } else if ((uint32_t) received != len) {
        std::cerr << "Failed to receive message data" << std::endl;
        return NULL;
    }

    buffer[len] = '\0';

    return Message::from_string(string(buffer, len));
}

std::unique_ptr<Message> Message::from_string(const string& data) {
    std::istringstream strStream(data);
    string command;
    std::getline(strStream, command, '\0');
    int cmd = std::stoi(command);

    if (cmd == REGISTER) {
        return RegisterMessage::from_string(data);
    } else if (cmd == JOIN) {
        return JoinMessage::from_string(data);
    } else if (cmd == LEAVE) {
        return LeaveMessage::from_string(data);
    } else if (cmd == TEXT) {
        return TextMessage::from_string(data);
    } else {
        throw ProtoBadFormat(data);
    }
}

const string& ProtoBadFormat::original_msg() const {
    return original_msg_;
}

