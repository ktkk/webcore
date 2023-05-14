#pragma once

#include <functional>
#include <optional>
#include <vector>
#include <memory>

#include "HttpMethod.h"
#include "HttpStatus.h"
#include "Request.h"
#include "Response.h"

#include "Utils/Logger.h"

namespace WebCore {

using Callback = std::function<void(const Request&, Response&)>;

class Router {
public:
    void add_route(const HttpMethod& method, const std::string& path, const Callback& callback);
    void handle_request(const Request& req, Response& res);

    void set_logger(Utils::Logger& logger) { m_logger.emplace(logger); }

private:
    struct Route {
        Route(const HttpMethod& method, const std::string& path, const Callback& callback)
            : m_method(method)
            , m_path(path)
            , m_callback(callback)
        {
        }

        HttpMethod m_method;
        std::string m_path;
        Callback m_callback;
    };

private:
    std::vector<std::unique_ptr<Route>> m_routes = {};

    std::optional<std::reference_wrapper<Utils::Logger>> m_logger = {};
};

}
