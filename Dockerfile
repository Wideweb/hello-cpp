# Сборка ---------------------------------------

# В качестве базового образа для сборки используем gcc:latest
FROM gcc:latest as build

WORKDIR /sdl_build

ARG SDL_VERSION=2.0.12
ARG SDL_DIR=SDL2-${SDL_VERSION}
ARG SDL_TAR=${SDL_DIR}.tar.gz
ARG SDL_URL=https://www.libsdl.org/release/${SDL_TAR}

ARG CMAKE_VERSION=3.17.0
ARG CMAKE_DIR=cmake-${CMAKE_VERSION}
ARG CMAKE_TAR=${CMAKE_DIR}.tar.gz
ARG CMAKE_URL=https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/${CMAKE_TAR}

RUN apt-get update && \
    apt-get install -y \
    cmake \
    && \
    mkdir -p tmp && \
    # CMAKE BEGIN
    cd tmp && \
    wget ${CMAKE_URL} && \
    tar -xzf ${CMAKE_TAR} && \
    cd ${CMAKE_DIR} && \
    ./bootstrap && \
    make && \
    make install && \
    cd / && \
    # CMAKE END
    # SDL BEGIN
    cd tmp && \
    wget ${SDL_URL} && \
    tar -xzvf ${SDL_TAR} && \
    cd ${SDL_DIR} && \
    mkdir -p build && \
    cd build && \
    ../configure && \
    make && \
    make install && \
    cd / && \
    # SDL END
    rm -rf tmp

# Скопируем директорию в контейнер
ADD . /app/src

# Установим рабочую директорию для сборки проекта
WORKDIR /app/build

# Выполним сборку нашего проекта
RUN cmake ../src && \
    cmake --build .

# Запуск ---------------------------------------

# В качестве базового образа используем ubuntu:latest
FROM ubuntu:latest

# Скопируем приложение со сборочного контейнера в рабочую директорию
COPY --from=build /app/build/hello-sdl .

# Установим точку входа
ENTRYPOINT ["./hello"]