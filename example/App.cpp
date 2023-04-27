#include "App.h"

#include <bits/chrono.h>
#include <clocale>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>

std::string get_last_modified_time(const std::string& path)
{
    using namespace std::chrono;
    using namespace std::filesystem;

    auto last_modified_time = system_clock::to_time_t(time_point_cast<system_clock::duration>(last_write_time(path) - file_time_type::clock::now() + system_clock::now()));

    std::string time;

    std::string previous_locale = std::setlocale(LC_ALL, nullptr);

    std::setlocale(LC_TIME, "en_US.utf-8");
    time = std::asctime(std::localtime(&last_modified_time));

    std::setlocale(LC_ALL, previous_locale.c_str());

    return time;
}

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
            { "Last-Modified", get_last_modified_time(path) },
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

void App::handle_request(WebCore::Request& req, WebCore::Response& res)
{
    m_router.handle_request(req, res);
}
