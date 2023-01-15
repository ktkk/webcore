#pragma once

#include <functional>
#include <string>
#include <vector>

#include "HttpStatus.h"
#include "Request.h"
#include "Response.h"

class Router {
public:
  void add_route(std::string method, std::string path,
                 std::function<void(Request &, Response &)> callback);
  void handle_request(Request &req, Response &res);

private:
  struct Route {
    std::string method;
    std::string path;
    std::function<void(Request &, Response &)> callback;
  };
  std::vector<Route> m_routes;
};
