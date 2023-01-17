# WebCore

## WARNING

This project is a concept and a work in progress!
In its current state, only the most basic of requests work ("GET /").

## Getting started

See [example/](example/) for a simple example application using WebCore.

You can use the router to register routes like this:
```cpp
auto router = Router();

router.add_route("GET", "/", [](Response& res, Request& req) {
    res.set_status(HttpStatus::Ok);
});
```
