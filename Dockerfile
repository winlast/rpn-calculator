# Этап сборки
FROM ubuntu:22.04 AS builder

RUN apt-get update && \
    apt-get install -y cmake g++ git && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Копируем только нужные для сборки файлы
COPY CMakeLists.txt .
COPY src/ src/
COPY include/ include/
COPY tests/ tests/

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --target rpn_calculator --parallel 2

# Финальный этап
FROM ubuntu:22.04

WORKDIR /app
COPY --from=builder /app/build/rpn_calculator .

ENTRYPOINT ["./rpn_calculator"]