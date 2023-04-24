#include <WebCore/App.h>

using namespace WebCore;

using SocketAddress = struct sockaddr;
using SocketAddressIPv4 = struct sockaddr_in;
using InAddress = in_addr;

int App::start(int port)
{
    int socket_file_descriptor { socket(AF_INET, SOCK_STREAM, 0) };

    if (socket_file_descriptor < 0) {
        return 1;
    }

    int opt { 1 };
    if (setsockopt(
            socket_file_descriptor,
            SOL_SOCKET,
            SO_REUSEADDR,
            &opt,
            sizeof(opt))
        < 0) {
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
        return 1;
    }

    if (listen(socket_file_descriptor, 5) != 0) {
        return 1;
    }

    m_logger->get().info("Listening on port %d");

    // Main connection loop
    while (true) {
        SocketAddressIPv4 peer_address;
        unsigned int peer_address_length { sizeof(peer_address) };

        int client_file_descriptor { accept(
            socket_file_descriptor,
            (SocketAddress*)&peer_address,
            &peer_address_length) };

        if (client_file_descriptor < 0) {
            return 1;
        }

        char buffer[4096];
        long buffer_length { read(
            client_file_descriptor,
            buffer,
            sizeof(buffer)) };

        buffer[buffer_length] = '\0';

        Request req { Request::parse_request(buffer, buffer_length) };
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
