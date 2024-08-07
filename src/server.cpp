#include "server_utils.h"

#include <arpa/inet.h>
#include <chrono>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

#define MAX_CLIENTS 100
#define BACKLOG 5
#define PROTOCOL "TPC"
#define IP_ADDRESS "127.0.0.1"
#define PORT 5000

int main (void) {
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Failed when creating an endpoint for communication. Error code: " << errno << " (" << strerror(errno) << ")" << std::endl;
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    serv_addr.sin_port = PORT;

    signal(SIGPIPE, SIG_IGN);

    if (bind(listenfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
        std::cerr << "Failed to bind a name to a socket. Error code: " << errno << " (" << strerror(errno) << ")" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (listen(listenfd, BACKLOG) == -1) {
        std::cerr << "Failed to listen for socket connections and limit the queue of incoming connections. Error code: " << errno << " (" << strerror(errno) << ")" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "+==================================+" << std::endl;
    std::cout << "|           SERVER INFO            |" << std::endl;
    std::cout << "+-----------------+----------------+" << std::endl;
    std::cout << "|    Protocol     | " << std::setw(14) << PROTOCOL << " |" << std::endl;
    std::cout << "+-----------------+----------------+" << std::endl;
    std::cout << "|   Ip Address    | " << std::setw(14) << IP_ADDRESS << " |" << std::endl;
    std::cout << "+-----------------+----------------+" << std::endl;
    std::cout << "|      Port       | " << std::setw(14) << PORT << " |" << std::endl;
    std::cout << "+-----------------+----------------+" << std::endl;
    std::cout << "|     Backlog     | " << std::setw(14) << BACKLOG << " |" << std::endl;
    std::cout << "+-----------------+----------------+" << std::endl;
    std::cout << "|  Max. Clients   | " << std::setw(14) << MAX_CLIENTS << " |" << std::endl;
    std::cout << "+==================================+\n" << std::endl;

    while (true) {
        if ((connfd = accept(listenfd, (struct sockaddr*) &cli_addr, &clilen)) == -1) {
            std::cerr << "Failed to listen for socket connections and limit the queue of incoming connections. Error code: " << errno << " (" << strerror(errno) << ")" << std::endl;
            exit(EXIT_FAILURE);
        }

        if (cli_count.load() + 1 == MAX_CLIENTS) {
            std::cout << "<< max clients reached\n";
            std::cout << "<< reject client ";
            print_addr_port(cli_addr);
            close(connfd);
            continue;
        }

        std::unique_ptr<Client> client = std::make_unique<Client>(connfd, cli_addr, uid.fetch_add(1));
        std::thread(handle_client, std::move(client)).detach();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    close(listenfd);

    return EXIT_SUCCESS;
}
