#pragma once

#include <functional>
#include <optional>
#include <string>
#include <vector>
#include <iostream>

#include "HttpMethod.h"
#include "HttpStatus.h"
#include "Request.h"
#include "Response.h"

namespace WebCore {

class Router {
public:
    using Callback = std::function<void(const Request&, Response&)>;

    void add_route(Route&);
    void add_route(HttpMethod method, std::string path, Callback callback);
    
    void handle_request(const Request& req, Response& res);

    void set_logger(Logger& logger) { m_logger.emplace(logger); }

private:
    struct Route {
        HttpMethod method;
        std::string path;
        Callback callback;
    };
    std::vector<Route> m_routes;

    std::optional<std::reference_wrapper<Logger>> m_logger = {};
};

}
