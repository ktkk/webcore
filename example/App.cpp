#include "App.h"

#include <filesystem>
#include <fstream>
#include <iostream>

App::App()
    : m_router()
    , m_logger()
{
    register_routes();

    set_logger(m_logger);
}

void App::register_routes()
{
    using WebCore::HttpMethod;
    using WebCore::HttpStatus;

    using WebCore::Utils::Logger;

    m_router.set_logger(m_logger);

    m_router.add_route(HttpMethod::Get, "/", [this](auto& req, auto& res) {
        m_logger.info("Made a GET request to the '/' endpoint.");

        // Assume we're running inside the build/ directory
        std::string path = "../example/index.html";

        res.add_headers({
            { "Content-Type", "text/html" },
        });

        std::ifstream file_stream { path };
        std::string body { std::istreambuf_iterator<char> { file_stream }, std::istreambuf_iterator<char> {} };

        res.write(body);
    });

    m_router.add_route(HttpMethod::Get, "/users/:id", [this](auto& req, auto& res) {
        m_logger.warn("Query paramters aren't properly implemented yet.");

        auto params = req.get_params();
        std::string id = params["id"];

        res.write("User ID: " + id);
    });
}

void App::handle_request(const WebCore::Request& req, WebCore::Response& res)
{
    m_router.handle_request(req, res);
}
