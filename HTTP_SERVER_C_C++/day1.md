# HTTP Server in C/C++ — From Scratch

Building an HTTP server from the ground up, one day at a time.

---

## Day 1 — Understanding Sockets

### Goal

Understand what happens when we create a socket in C.

> We are **NOT** building a server yet.
> We are only creating the communication tool.

---

### Core Concepts

**1. IP Address**

An IP address is like a house address — it tells where a computer lives on the network.

```
192.168.1.10
```

**2. Port**

A port is like a door of that house. One computer can have many ports.

| Port | Protocol |
|------|----------|
| 80   | HTTP     |
| 443  | HTTPS    |
| 22   | SSH      |

> IP = House, Port = Door

**3. TCP**

TCP is a reliable connection protocol. It ensures:
- Data is not lost
- Data arrives in the correct order
- Both sides are properly connected (via a handshake)

**4. Socket**

A socket is a communication endpoint. In Linux, everything is treated like a file — including network connections.

When we create a socket, Linux gives us back a small number called a **file descriptor** (e.g. `3`, `4`, `5`). That number is our handle to the network channel.

---

### Code

**[day1.c](day1.c)**

```c
#include <stdio.h>          // For printf
#include <sys/socket.h>     // For socket()
#include <unistd.h>         // For close()

int main() {

    // socket(domain, type, protocol)
    // AF_INET     = IPv4
    // SOCK_STREAM = TCP (reliable connection)
    // 0           = OS chooses the protocol automatically
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // socket() returns -1 if it fails
    if (sockfd == -1) {
        printf("Socket creation failed\n");
        return 1;
    }

    // On success, Linux returns a file descriptor number
    printf("Socket created successfully\n");
    printf("Socket file descriptor number is: %d\n", sockfd);

    // Done — close the socket
    close(sockfd);

    return 0;
}
```

---

### Compile & Run

```bash
gcc day1.c -o day1
./day1
```

**Output:**
```
Socket created successfully
Socket file descriptor number is: 3
```

---

### What Actually Happened

1. Our C program called `socket()`
2. That triggered a **system call** to the Linux kernel
3. The kernel created an internal TCP structure
4. The kernel returned a file descriptor number
5. We printed it, then closed the socket

**What we did NOT do:**
- Connect to the internet
- Send any data
- Open any port

We only created the communication tool.

---

### Mental Model

> Calling `socket()` is like buying a phone.
> You haven't called anyone yet — you just got the phone.

---

### What We Learned

- What is an IP address
- What is a Port
- What is TCP
- What is a Socket
- What is a File Descriptor
- How to create a socket in C
