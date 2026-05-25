# A TCP Server and Client Written in C.
A locally hosted server/client pair written in C utilizing the POSIX socket API, created as part of my first foray into network programming. The server listens on 127.0.0.1:8080. This project is POSIX compliant, and should run on most Linux/UNIX-based machines, as well as WSL on Windows. 

## Compilation
A Makefile has been included to make this process as easy as possible. Simply ensure that GCC and Make are installed, and then cd into the project's directory and type make to build the binaries, which will be placed in the bins directory.

## Usage
Run both the server (./bins/server) and the client (./bins/client) in seperate terminal windows on the same machine. The client will connect to the server, receive and display a message, and disconnect.

