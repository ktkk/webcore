#include "App.h"

#include <fstream>
#include <iostream>

App::App()
    : m_router()
{
    register_routes();
}

void App::register_routes()
{
    using WebCore::HttpMethod;
    using WebCore::HttpStatus;

    m_router.add_route(HttpMethod::Get, "/", [](auto& req, auto& res) {
        std::cout << "Made a GET request to the '/' endpoint." << std::endl;

        // Assume we're running inside the build/ directory
        std::ifstream file_stream { "../example/index.html" };
        std::string body { std::istreambuf_iterator<char> { file_stream }, std::istreambuf_iterator<char> {} };

        res.set_body(body);
        res.set_status(HttpStatus::Ok);
    });

    m_router.add_route(HttpMethod::Get, "/users/:id", [](auto& req, auto& res) {
        auto params = req.get_params();
        std::string id = params["id"];

        res.set_body("User ID: " + id);
    });
}

void App::handle_request(WebCore::Request& req, WebCore::Response& res)
{
    m_router.handle_request(req, res);
}
