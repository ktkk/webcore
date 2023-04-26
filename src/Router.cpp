#include <sstream>

#include <WebCore/Router.h>

using namespace WebCore;

void Router::add_route(HttpMethod method, std::string path,
    std::function<void(Request&, Response&)> callback)
{
    m_routes.push_back({ method, path, callback });
}

void Router::handle_request(Request& req, Response& res)
{
    for (auto& route : m_routes) {
        if (route.method == req.get_method() && route.path == req.get_path()) {
            if (m_logger.has_value()) {
                std::stringstream log;
                log << "Serving request ";
                log << route.method << ", " << route.path;
                m_logger->get().info(log.str());
            }

            route.callback(req, res);

            return;
        }
    }

    res.set_status(HttpStatus::NotFound);
    res.write("WebCore v0.1\nPage not found :(");
}
