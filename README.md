# WebCore

## WARNING

This project is a concept and a work in progress!
In its current state it **DOES NOT WORK**.

## Getting started

See [example/](example/) for a simple example application using WebCore.

You can use the router to register routes like this:
```cpp
auto router = Router();

router.add_route("GET", "/", [](Response& res, Reqeust& req) {
    res.set_status(HttpStatus::Ok);
});
```
