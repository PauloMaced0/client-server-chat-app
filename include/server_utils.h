#ifndef _server_utils_H_
#define _server_utils_H_

#include "protocol.h"

#include <cstdint>
#include <memory>
#include <netinet/in.h>

#define MAX_CLIENTS 100
#define BACKLOG 5

extern std::atomic<unsigned int> cli_count;
extern std::atomic<int> uid;

class Client {
public:
    struct sockaddr_in addr;    // Client remote address
    int connfd;                 // Connection file descriptor
    uint32_t uid;               // Client unique identifier
    string name;                // Client name 

    Client(int socket_fd, sockaddr_in client_addr, uint32_t client_uid)
    : connfd(socket_fd), addr(client_addr), uid(client_uid), name("") {}

    void sendmsg(Message &msg, int sock_fd);
};

extern void add_client(std::unique_ptr<Client> &client);
extern void remove_client(uint32_t uid);
extern void handle_client(std::unique_ptr<Client> client);
extern void print_addr_port(const sockaddr_in &addr);

#endif // !_server_utils_H_
