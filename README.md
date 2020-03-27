# Hello, man [![Build Status](https://travis-ci.com/Wideweb/hello-cpp.svg?branch=master)](https://travis-ci.com/github/Wideweb/hello-cpp)

## Build

- mkdir build
- cd build
- cmake .. -DCMAKE_BUILD_TYPE=$BUILD_CONFIGURATION -DTARGET_CPU=$TARGET_CPU
- cmake --build .

Use DBUILD_SHARED_LIBS flag to build hello-lib as shared or static library

## Dockerize

- docker build -t hello-cpp .
- docker run hello-cpp

## Connect to docker hub

- docker login -u $DOCKER_USER -p $DOCKER_PASS
- docker pull alkevich/hello-cpp
- docker run alkevich/hello-cpp
