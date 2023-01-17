#include <WebCore/Request.h>

#include <cstring>
#include <iostream>
#include <sstream>

using namespace WebCore;

Request Request::parse_request(char buffer[], long buffer_length)
{
    Request req;

    std::string request_string { buffer, (size_t)buffer_length };
    std::istringstream input_stream { request_string };

    std::string method_string;
    input_stream >> method_string;
    req.set_method(HttpMethod::from_method_string(method_string));

    std::string path_string;
    input_stream >> path_string;
    req.set_path(path_string);

    return req;
}
