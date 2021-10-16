# My study plan server

## Compilation

Install the required libraries: pqxx, boost and cpprestsdk.

```bash
$ apt install libpqxx-dev libboost-dev libcpprest-dev
```

Compile with

```bash
$ make all
```

## Usage

The server executable accepts two arguments:
- address
- port

Example of usage:

```bash
$ ./server http://localhost 9999
```

An environment variable `DATABASE_URL` should be defined with the URI of the database.