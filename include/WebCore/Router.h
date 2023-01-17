#pragma once

#include <functional>
#include <string>
#include <vector>

#include "HttpMethod.h"
#include "HttpStatus.h"
#include "Request.h"
#include "Response.h"

namespace WebCore {

class Router {
public:
    void add_route(HttpMethod method, std::string path,
        std::function<void(Request&, Response&)> callback);
    void handle_request(Request& req, Response& res);

private:
    struct Route {
        HttpMethod method;
        std::string path;
        std::function<void(Request&, Response&)> callback;
    };
    std::vector<Route> m_routes;
};

}
