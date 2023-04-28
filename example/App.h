#pragma once

#include "WebCore/Utils/Logger.h"
#include <string>

#include <WebCore/WebCore.h>

class App final : public WebCore::App {
public:
    App();

    void register_routes();
    void handle_request(const WebCore::Request& req, WebCore::Response& res) override;

private:
    WebCore::Router m_router;
    WebCore::Utils::Logger m_logger;
};
