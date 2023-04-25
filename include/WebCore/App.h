#include <functional>
#include <optional>

#include "Request.h"
#include "Response.h"

#include "Utils/Logger.h"

namespace WebCore {

class App {
public:
    virtual void handle_request(Request& req, Response& res) = 0;

    int start(int port);

    void set_logger(Utils::Logger& logger) { m_logger.emplace(logger); }

private:
    std::optional<std::reference_wrapper<Utils::Logger>> m_logger = {};
};

}
