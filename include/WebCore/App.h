#include <functional>
#include <optional>

#include "Request.h"
#include "Response.h"

#include "Utils/Logger.h"

namespace WebCore {

class App {
public:
    virtual void handle_request(const Request& req, Response& res) = 0;

    int start(const unsigned short port);

    void set_logger(Utils::Logger& logger) { m_logger.emplace(logger); }

private:
#if defined(linux)
    int start_linux(const unsigned short port);
#endif
#if defined(_WIN32) || defined(WIN32)
    int start_windows(const unsigned short port);
#endif

private:
    std::optional<std::reference_wrapper<Utils::Logger>> m_logger = {};
};

}
