#include <functional>
#include <optional>

#include "Request.h"
#include "Response.h"

#include "Utils/Logger.h"

namespace WebCore {

class App {
public:
    virtual void handle_request(Request& req, Response& res) = 0;

    int start(const int port);

    void set_logger(Utils::Logger& logger) { m_logger.emplace(logger); }

private:
    std::optional<std::reference_wrapper<Utils::Logger>> m_logger = {};

#if defined(linux)
    int start_linux(const int port);
#endif
#if defined(_WIN32) || defined(WIN32)
    int start_windows(const int port);
#endif
};

}
