# A TCP Server and Client Written in C.
A locally hosted server/client pair written in C utilizing the POSIX socket API, created as part of my first foray into network programming. The server listens on 127.0.0.1:8080. This project is POSIX compliant, and should run on most Linux/UNIX-based machines, as well as WSL on Windows. 

## Installation
Ensure `make` and `gcc` are installed on your system.
1. Clone the repository:
   
   ```
   $ git clone https://github.com/lhenso04/CLI-TCP-Server-Client.git
   $ cd CLI-TCP-Server-Client
   ```
3. Build the project:
   ``` $ make ```

## Usage
Run the server first, then the client in a separate terminal window.
1. Start the server:
   ```$ ./bins/server ```
3. Start the client:
  ```$ ./bins/client ``` <br>
  
  The client will connect to the server, print the message it receives, and disconnect.
