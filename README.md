# WebCore

### WARNING

This project is a concept and a work in progress!
In its current state, only the most basic of requests work ("GET /").

## Getting started

See [example/](example/) for a simple example application using WebCore.

You can use the router to register routes like this:
```cpp
auto router = Router();

router.add_route(HttpMethod::Get, "/", [](auto& res, auto& req) {
    res.set_status(HttpStatus::Ok);
});
```

## Testing

Tests are provided in the [tests/](tests/) directory.
You can run them with ctest.

### WARNING

Tests are still a work in progress.
