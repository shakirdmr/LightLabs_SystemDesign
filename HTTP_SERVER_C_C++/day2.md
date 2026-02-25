
# Day 2 — Binding Socket to a Port

## 🎯 Goal of Today

Yesterday we created a socket.

Today we attach that socket to a **port number** so other computers can find us.

Still not accepting connections.
Just attaching to a port.

---

# 🧠 Simple Idea

Yesterday:

We bought a phone 📱

Today:

We register that phone to a number (like 5001).

So now people know where to call.

---

# 🔑 New Concepts

## 1. bind()

`bind()` attaches your socket to:

* IP address
* Port number

Without bind, your server has no address.

---

## 2. sockaddr_in

This is just a structure that holds:

* IP
* Port
* Address family

Think of it like a small form you fill before registering your phone.

---

## 3. htons()

Computers store numbers differently internally.

Network expects numbers in **big-endian format**.

`htons()` means:

Host TO Network Short

It converts your port number into correct format.

Always use it for port.

---

# 💻 Code We Write

File: `day2.c`

```c
#include <stdio.h>          // printf
#include <string.h>         // memset
#include <unistd.h>         // close
#include <sys/socket.h>     // socket
#include <netinet/in.h>     // sockaddr_in

int main() {

    // Step 1: Create socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        printf("Socket creation failed\n");
        return 1;
    }

    printf("Socket created successfully\n");

    // Step 2: Create address structure
    struct sockaddr_in server_addr;

    // Clear memory (good practice)
    memset(&server_addr, 0, sizeof(server_addr));

    // Set address family (IPv4)
    server_addr.sin_family = AF_INET;

    // Accept connections from any IP
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Set port number (convert to network format)
    server_addr.sin_port = htons(5001);

    // Step 3: Bind socket to IP + Port
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Bind failed\n");
        return 1;
    }

    printf("Bind successful. Server attached to port 5001\n");

    // Close socket (we are done for today)
    close(server_fd);

    return 0;
}
```

---

# ⚙️ Compile

```
gcc day2.c -o day2
```

---

# ▶ Run

```
./day2
```

If successful, you should see:

```
Socket created successfully
Bind successful. Server attached to port 5001
```

---

# 🔎 What Just Happened

1. We created a socket.
2. We created an address structure.
3. We filled:

   * IPv4
   * Any IP
   * Port 5001
4. We called `bind()`.
5. Linux registered our socket to port 5001.

Now:

Our program owns port 5001.

But:

It is NOT listening yet.
It is NOT accepting connections yet.

We only registered the phone number.

---

# 🧠 Mental Model

Day 1 → Bought phone
Day 2 → Got phone number (5001)

Nobody can call yet.

Tomorrow:

We make it listen using `listen()` 👂🚀
