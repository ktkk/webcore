# TODO

WebCore is a work in progress. There is still a ton of stuff to do, including but not limited to:

## [App.cpp](./src/App.cpp)

- Add additional configuration for HTTPS
- Proper error handling and reporting
- Use logging in as many places as possible

## [Logger.cpp](./src/Logger.cpp)

- Color configuration
- Timezone configuration
- Allow formatted messages

## [Router.cpp](./src/Router.cpp)

- Error page configuration
- Handle route parameters
- Handle query parameters

## [Request.cpp](./src/Request.cpp)

- Allow streaming requests
- Parse query parameters
- Parse body

## [Response.cpp](./src/Response.cpp)

- Allow streaming responses
- Create header setter

## [Utils](./include/WebCore/Utils)

- Add a ThreadPool and use it in the App to distribute workloads
