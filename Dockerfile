# BUILDER
FROM gcc:12.2.0 as builder
WORKDIR /app
COPY . .
RUN make all

# RUNTIME
FROM debian:stable-slim
WORKDIR /app
COPY --from=builder /app/rinha_de_bots .
CMD ["./rinha_de_bots"]