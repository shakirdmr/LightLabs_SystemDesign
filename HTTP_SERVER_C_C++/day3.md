# Day 3 — listen() and accept() (Server Becomes Real)

## 🎯 Goal of Today

Yesterday we:

* Created socket
* Bound it to port

Today we:

* Tell kernel to start waiting for connections
* Accept a client

Now the server becomes alive.

---

# 🧠 Very Simple Mental Model

Day 1 → Bought phone 📱
Day 2 → Got phone number 📞
Day 3 → Turned ringtone ON and answered call 👂

---

# 🔑 New Concepts

## 1️⃣ listen()

`listen()` tells Linux:

“I am ready to receive connections.”

It also creates a small waiting line (queue).

Syntax:

```
listen(socket_fd, backlog)
```

* `socket_fd` → your server socket
* `backlog` → how many people can wait in line

Example:

```
listen(server_fd, 5);
```

Means:
Maximum 5 clients can wait before being accepted.

---

## 2️⃣ accept()

`accept()` means:

“Pick the next client from waiting line.”

Important:

* It BLOCKS (waits) until someone connects.
* It returns a NEW file descriptor.
* That new FD is for talking to that specific client.

So now you have:

server_fd → for listening
client_fd → for talking

Very important concept.

---

# Headers Used

| Header | Gives You |
|---|---|
| `<stdio.h>` | `printf()`, `perror()` |
| `<string.h>` | `memset()` |
| `<sys/socket.h>` | `socket()`, `bind()`, `listen()`, `accept()`, `struct sockaddr` |
| `<netinet/in.h>` | `struct sockaddr_in`, `socklen_t`, `INADDR_ANY`, `htons()` |
| `<unistd.h>` | `close()` |

---

# 💻 Code We Write

File: `day3.c`

```c
#include <stdio.h>          // printf, perror
#include <string.h>         // memset
#include <unistd.h>         // close
#include <sys/socket.h>     // socket, bind, listen, accept, struct sockaddr
#include <netinet/in.h>     // struct sockaddr_in, socklen_t, INADDR_ANY, htons

int main() {

    // Step 1: Create socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        perror("Socket failed");
        return 1;
    }

    printf("Socket created\n");

    // Step 2: Prepare address structure
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;          // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;  // All interfaces
    server_addr.sin_port = htons(5001);        // Port 5001

    // Step 3: Bind
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    printf("Bind successful\n");

    // Step 4: Listen
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        return 1;
    }

    printf("Server is listening on port 5001...\n");

    // Step 5: Accept one client
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    printf("Waiting for a client to connect...\n");

    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

    if (client_fd < 0) {
        perror("Accept failed");
        return 1;
    }

    printf("Client connected!\n");

    // Close client socket
    close(client_fd);

    // Close server socket
    close(server_fd);

    return 0;
}
```

---

# ⚙ Compile

```
gcc day3.c -o day3
```

---

# ▶ Run

```
./day3
```

It will hang here:

```
Waiting for a client to connect...
```

This is normal.
It is blocking at `accept()`.

---

# 🧪 Test Connection

Open another terminal and run:

```
telnet localhost 5001
```

OR

Open browser:

```
http://localhost:5001
```

Now first terminal should print:

```
Client connected!
```

---

# 🔎 What Just Happened Internally

1. Browser tries to connect.
2. TCP 3-way handshake happens inside kernel.
3. Kernel puts client in waiting queue.
4. `accept()` removes client from queue.
5. Kernel gives you NEW file descriptor.
6. That FD represents that specific client.

Important:

Server socket never talks.
Client socket talks.

---

# 🧠 Critical Understanding

You now have TWO sockets:

| Socket    | Purpose         |
| --------- | --------------- |
| server_fd | Only listens    |
| client_fd | Talks to client |

This separation is extremely important.

Node.js also does same thing internally.

---

# 🧪 Brain Check Questions

1. Why does accept() return a new file descriptor?
2. What happens if we remove listen()?
3. Why does program hang before client connects?
4. Which socket should we use to send data?

Answer these before we move to Day 4 (reading HTTP request). 🚀
