#if defined(linux)

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <asm-generic/socket.h>

#endif

#if defined(_WIN32) || defined(WIN32)

#include <winsock2.h>
#include <ws2tcpip.h>

#endif

#include <WebCore/App.h>

using namespace WebCore;

using SocketAddress = struct sockaddr;
using SocketAddressIPv4 = struct sockaddr_in;
using InAddress = in_addr;

int App::start(const int port)
{
#if defined(linux)
    return start_linux(port);
#endif

#if defined(_WIN32) || defined(WIN32)
    return start_windows(port);
#endif
}

#if defined(linux)

int App::start_linux(const int port)
{
    int socket_file_descriptor { socket(AF_INET, SOCK_STREAM, 0) };

    if (socket_file_descriptor < 0) {
        if (m_logger) {
            m_logger->get().error("Creating socket file descriptor failed");
        }

        return 1;
    }

    int opt = 1;
    if (setsockopt(
            socket_file_descriptor,
            SOL_SOCKET,
            SO_REUSEADDR,
            &opt,
            sizeof(opt))
        < 0) {
        if (m_logger) {
            m_logger->get().error("Setting socket options failed");
        }

        return 1;
    }

    InAddress in_address { htonl(INADDR_ANY) };

    SocketAddressIPv4 server_address {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = in_address,
    };

    if (bind(
            socket_file_descriptor,
            (SocketAddress*)&server_address,
            sizeof(server_address))
        != 0) {
        if (m_logger) {
            m_logger->get().error("Binding socket failed");
        }

        return 1;
    }

    if (listen(socket_file_descriptor, 5) != 0) {
        if (m_logger) {
            m_logger->get().error("Listen failed");
        }

        return 1;
    }

    if (m_logger) {
        m_logger->get().info("Listening on port %d");
    }

    // Main connection loop
    while (true) {
        SocketAddressIPv4 peer_address;
        unsigned int peer_address_length { sizeof(peer_address) };

        int client_file_descriptor {
            accept(
                socket_file_descriptor,
                (SocketAddress*)&peer_address,
                &peer_address_length)
        };

        if (client_file_descriptor < 0) {
            if (m_logger) {
                m_logger->get().error("Accept failed");
            }

            return 1;
        }

        char buffer[4096];
        long buffer_length {
            read(
                client_file_descriptor,
                buffer,
                sizeof(buffer))
        };

        buffer[buffer_length] = '\0';

        Request req = Request::parse_request(buffer, buffer_length);
        Response res;

        handle_request(req, res);

        // std::cout << res.to_string();

        write(
            client_file_descriptor,
            res.to_string().c_str(),
            res.to_string().size());

        close(client_file_descriptor);
    }

    return 0;
}

#endif

#if defined(_WIN32) || defined(WIN32)

int App::start_windows(const int port)
{
    WSADATA wsa_data;
    int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
        if (m_logger) {
            m_logger->get().error("WSAStartup failed");
        }

        return 1;
    }

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        if (m_logger) {
            m_logger->get().error("Failed to create socket"); // WSAGetLastError();
        }

        WSACleanup();

        return 1;
    }

    InAddress in_address { htonl(INADDR_ANY) };

    SocketAddressIPv4 server_address {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = in_address,
    };

    if (bind(
        server_socket,
        (SocketAddress*)&server_address,
        sizeof(server_address))
    == SOCKET_ERROR) {
        if (m_logger) {
            m_logger->get().error("Binding socket failed"); // WSAGetLastError();
        }

        closesocket(server_socket);
        WSACleanup();

        return 1;
    }

    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
        if (m_logger) {
            m_logger->get().error("Listen failed"); // WSAGetLastError();
        }

        closesocket(server_socket);
        WSACleanup();

        return 1;
    }

    if (m_logger) {
        m_logger->get().info("Listening on port %d");
    }

    // Main connection loop
    while (true) {
        SOCKET client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == INVALID_SOCKET) {
            if (m_logger) {
                m_logger->get().error("Accept failed"); // WSAGetLastError();
            }

            closesocket(server_socket);
            WSACleanup();

            return 1;
        }

        char buffer[4096];
        long buffer_length = recv(client_socket, buffer, sizeof(buffer), 0);

        buffer[buffer_length] = '\0';

        Request req = Request::parse_request(buffer, buffer_length);
        Response res;

        handle_request(req, res);

        send(
            client_socket,
            res.to_string().c_str(),
            res.to_string().size(),
            0);

        closesocket(client_socket);
    }
}

#endif
