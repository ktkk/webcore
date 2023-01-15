#pragma once

#include <string>

#include <WebCore/WebCore.h>

class App {
public:
    App();

    void register_routes();
    void handle_request(Request& req, Response& res);

private:
    Router m_router;
};
