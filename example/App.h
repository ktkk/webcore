#pragma once

#include <string>

#include <WebCore/WebCore.h>

class App final : public WebCore::App {
public:
    App();

    void register_routes();
    void handle_request(WebCore::Request& req, WebCore::Response& res) override;

private:
    WebCore::Router m_router;
};
