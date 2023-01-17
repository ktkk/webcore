#include "App.h"

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
