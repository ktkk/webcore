#include <WebCore/Request.h>

#include <iostream>

using namespace WebCore;

Request Request::parse_request(char buffer[])
{
    std::cout << buffer;

    Request req;
    return req;
}
