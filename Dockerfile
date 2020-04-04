# Сборка ---------------------------------------

# В качестве базового образа для сборки используем gcc:latest
FROM gcc:latest as build

RUN apt-get update && \
    apt-get install -y \
    cmake libsdl2-dev

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
COPY --from=build /app/build .

# Установим точку входа
ENTRYPOINT ["./hello"]