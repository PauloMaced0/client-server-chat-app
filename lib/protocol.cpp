#include "protocol.h"

#include <arpa/inet.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <cstring>

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
    oss << command << '\0' << user ;
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
    string msg_str = msg.to_string();
    uint32_t len = htonl(msg_str.size());

    if (send(socket_fd, &len, sizeof(len), 0) == -1) {
        std::cerr << "Failed to send message length. Error code: " << errno << " (" << strerror(errno) << ")" << std::endl;
        exit(EXIT_FAILURE);
    } else if ((uint32_t) send(socket_fd, &len, sizeof(len), 0) != sizeof(len)) {
        throw std::runtime_error("Failed to send message length");
    }

    if (send(socket_fd, msg_str.c_str(), msg_str.size(), 0) == -1) {
        std::cerr << "Failed to send message data. Error code: " << errno << " (" << strerror(errno) << ")" << std::endl;
        exit(EXIT_FAILURE);
    } else if ((uint32_t) send(socket_fd, msg_str.c_str(), msg_str.size(), 0) == msg_str.size()) {
        throw std::runtime_error("Failed to send message data");
    }
}

std::unique_ptr<Message> Proto::recv_msg(int socket_fd) {
    uint32_t len;
    int received;

    received = recv(socket_fd, &len, sizeof(len), 0);
    if (received == 0) {
        throw std::runtime_error("Connection is closed");
    } else if (received == -1) {
        std::cerr << "Failed to receive message length. Error code: " << errno << " (" << strerror(errno) << ")" << std::endl;
        exit(EXIT_FAILURE);
    } else if ((uint32_t) received != sizeof(len)) { 
        throw std::runtime_error("Failed to receive message data");
    }

    len = ntohl(len);
    // TODO check this !!!
    char buffer[len + 1];

    received = recv(socket_fd, buffer, len, 0);
    if (received == 0) {
        throw std::runtime_error("Connection is closed");
    } else if (received == -1) {
        std::cerr << "Failed to receive message length. Error code: " << errno << " (" << strerror(errno) << ")" << std::endl;
        exit(EXIT_FAILURE);
    } else if ((uint32_t) received != sizeof(len)) {
        throw std::runtime_error("Failed to receive message data");
    }

    // TODO check this !!!
    buffer[len] = '\0';
    return Message::from_string(buffer);
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

