#include <asm-generic/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "Request.h"
#include "Response.h"

namespace WebCore {

class App {
public:
    virtual void handle_request(Request& req, Response& res) = 0;

    int start(int port);
};

}
