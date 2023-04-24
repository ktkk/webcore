#include <asm-generic/socket.h>
#include <functional>
#include <netdb.h>
#include <netinet/in.h>
#include <optional>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

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
