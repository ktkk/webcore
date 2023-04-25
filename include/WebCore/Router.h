#pragma once

#include <functional>
#include <optional>
#include <vector>

#include "HttpMethod.h"
#include "HttpStatus.h"
#include "Request.h"
#include "Response.h"

#include "Utils/Logger.h"

namespace WebCore {

class Router {
public:
    void add_route(HttpMethod method, std::string path,
        std::function<void(Request&, Response&)> callback);
    void handle_request(Request& req, Response& res);

    void set_logger(Utils::Logger& logger) { m_logger.emplace(logger); }

private:
    struct Route {
        HttpMethod method;
        std::string path;
        std::function<void(Request&, Response&)> callback;
    };
    std::vector<Route> m_routes;

    std::optional<std::reference_wrapper<Utils::Logger>> m_logger = {};
};

}
