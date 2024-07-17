#include "server_utils.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <mutex>
#include <ostream>
#include <unistd.h>
#include <vector>

std::atomic<unsigned int> cli_count = 0;
std::atomic<int> uid = 10;

std::vector<std::unique_ptr<Client>> clients;
std::mutex clients_mutex;

void Client::sendmsg(Message &msg, int socket_fd) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    for (const auto &client : clients) {
        if (client->uid == uid) {
            Proto::send_msg(socket_fd, msg);
        }
    }
}

void add_client(std::unique_ptr<Client> &client) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    clients.push_back(std::move(client));
}

void remove_client(uint32_t uid) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    clients.erase(std::remove_if(clients.begin(), clients.end(), [uid](const std::unique_ptr<Client> &client) {
        return client->uid == uid;
    }), clients.end());
}

void handle_client(std::unique_ptr<Client> client) {
    cli_count.fetch_add(1);
    // auto cli = client.get();

    std::cout << "<< accept ";
    print_addr_port(client->addr);
    std::cout << " referenced by " << client->uid << std::endl;

    while (true) {
        std::unique_ptr<Message> data = Proto::recv_msg(client->connfd);

        if (data->command == REGISTER) {
            std::cout << "-> received register message" << std::endl;
        } else if (data->command == JOIN) {
            std::cout << "-> received join message" << std::endl;
        } else if (data->command == LEAVE) {
            std::cout << "-> received leave message" << std::endl;
        } else if (data->command == TEXT) {
            std::cout << "-> received text message" << std::endl;
        } else {
            break;
        }
    }

    close(client->connfd);
    remove_client(client->uid);

    std::cout << "<< disconnect client ";
    print_addr_port(client->addr);
    std::cout << " referenced by " << client->uid << std::endl;
    cli_count.fetch_sub(1);
}

void print_addr_port(const sockaddr_in &addr) {
    std::cout << (addr.sin_addr.s_addr & 0xff) << "."
        << ((addr.sin_addr.s_addr & 0xff00) >> 8) << "."
        << ((addr.sin_addr.s_addr & 0xff0000) >> 16) << "."
        << ((addr.sin_addr.s_addr & 0xff000000) >> 24) << ":"
        << addr.sin_port << std::endl;
}
