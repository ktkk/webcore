#include "Request.h"
#include "Response.h"

namespace WebCore {

class App {
public:
    virtual void handle_request(Request& req, Response& res) = 0;

    int start();
};

}