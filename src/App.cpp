#include "Common.h"

#if defined(linux)
#include <asm-generic/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif // defined(linux)

#if defined(_WIN32) || defined(WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#endif // defined(_WIN32) || defined(WIN32)

#include <cassert>

#include <WebCore/App.h>

using namespace WebCore;

static constexpr auto BUFFER_SIZE = 4096;

using SocketAddress = struct sockaddr;
using SocketAddressIPv4 = struct sockaddr_in;
using InAddress = struct in_addr;

int App::start(const unsigned short port)
{
#if defined(linux)
    return start_linux(port);
#endif

#if defined(_WIN32) || defined(WIN32)
    return start_windows(port);
#endif
}

#if defined(linux)

int App::start_linux(const unsigned short port)
{
    const int socket_file_descriptor { socket(AF_INET, SOCK_STREAM, 0) };

    if (socket_file_descriptor < 0) {
        if (m_logger) {
            m_logger->get().error("Creating socket file descriptor failed");
        }

        return 1;
    }

    const int opt = 1;
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

    const InAddress in_address { htonl(INADDR_ANY) };

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

        const int client_file_descriptor = accept(
            socket_file_descriptor,
            (SocketAddress*)&peer_address,
            &peer_address_length);

        if (client_file_descriptor < 0) {
            if (m_logger) {
                m_logger->get().error("Accept failed");
            }

            return 1;
        }

        char buffer[BUFFER_SIZE];
        const long buffer_length = read(
            client_file_descriptor,
            buffer,
            sizeof(buffer));
        assert(buffer_length < BUFFER_SIZE);

        buffer[buffer_length] = '\0';

        const auto req = Request::parse_request(buffer, buffer_length);
        auto res = Response();

        res.set_client_socket(client_file_descriptor);

        handle_request(req, res);

        send(
            client_file_descriptor,
            res.to_string().c_str(),
            res.to_string().size(),
            0);

        close(client_file_descriptor);
    }

    return 0;
}

#endif

#if defined(_WIN32) || defined(WIN32)

int App::start_windows(const unsigned short port)
{
    WSADATA wsa_data;
    const int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
        if (m_logger) {
            m_logger->get().error("WSAStartup failed");
        }

        return 1;
    }

    const SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        if (m_logger) {
            m_logger->get().error("Failed to create socket"); // WSAGetLastError();
        }

        WSACleanup();

        return 1;
    }

    const InAddress in_address { static_cast<UCHAR>(htonl(INADDR_ANY)) };

    SocketAddressIPv4 server_address = { 0 };
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr = in_address;

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
        const SOCKET client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == INVALID_SOCKET) {
            if (m_logger) {
                m_logger->get().error("Accept failed"); // WSAGetLastError();
            }

            closesocket(server_socket);
            WSACleanup();

            return 1;
        }

        char buffer[BUFFER_SIZE];
        long buffer_length = recv(client_socket, buffer, sizeof(buffer), 0);
        assert(buffer_length < BUFFER_SIZE);

        buffer[buffer_length] = '\0';

        const auto req = Request::parse_request(buffer, buffer_length);
        auto res = Response();

        res.set_client_socket(client_socket);

        handle_request(req, res);

        send(
            client_socket,
            res.to_string().c_str(),
            static_cast<int>(res.to_string().size()),
            0);

        closesocket(client_socket);
    }
}

#endif
