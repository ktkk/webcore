#include "App.h"

App::App()
    : m_router()
{
    register_routes();
}

void App::register_routes()
{
    m_router.add_route("GET", "/", [](Request& req, Response& res) {
        res.set_status(HttpStatus::Ok);
    });

    m_router.add_route("GET", "/users/:id", [](Request& req, Response& res) {
        auto params = req.get_params();
        std::string id = params["id"];

        res.set_body("User ID: " + id);
    });
}

void App::handle_request(Request& req, Response& res)
{
    m_router.handle_request(req, res);
}
