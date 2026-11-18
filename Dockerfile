FROM gcc:13-bookworm

WORKDIR /app
COPY . .

RUN mkdir -p data && make

CMD ["./bin/triagem"]