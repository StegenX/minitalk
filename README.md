# minitalk

A tiny client/server IPC project using only Unix signals. The server prints any string sent by the client, which encodes characters bit-by-bit via `SIGUSR1`/`SIGUSR2`.

> Part of the 42 curriculum. Focuses on low-level signaling, bitwise encoding, and robust synchronization.

## Features

- Server prints its PID and receives messages from clients
- Client sends an arbitrary string to a server PID via signals
- Bitwise character transfer (1 bit per signal)
- Graceful end-of-message handling (NUL terminator)
- Robust signal handling and minimal timing to avoid lost signals
- Clean, norm-compliant code organization (42 style)

## Build

Typical Makefile targets:

```sh
make         # build server and client
make clean   # remove objects
make fclean  # remove objects and binaries
make re      # rebuild from scratch
make bonus   # build bonus (ack / Unicode / faster tx if implemented)
```

Expected binaries (common naming):
- `server`
- `client`

Bonus builds may reuse the same names or produce `server_bonus` / `client_bonus` depending on your Makefile.

## Run

1) Start the server (it prints its PID):

```sh
./server
```

Example output:
```
Server PID: 42421
```

2) From another terminal, run the client with the server PID and your message:

```sh
./client 42421 "Hello from minitalk!"
```

Server prints:
```
Hello from minitalk!
```

Notes:
- The client argument order is: `./client <server_pid> <message>`.
- Messages usually end with a `\n` printed by the server after receiving the string terminator (implementation-dependent).

## Protocol overview

- Each character (8 bits) is sent LSB→MSB or MSB→LSB (choose one consistently):
  - One signal encodes bit=0 (e.g., `SIGUSR1`)
  - The other encodes bit=1 (e.g., `SIGUSR2`)
- The client iterates bits of each char and sends the corresponding signal.
- The server’s signal handler rebuilds the byte and writes it to stdout when a full character is assembled.
- The client also sends the `\0` terminator; when the server receives it, it can print a newline and/or acknowledge completion.

Timing and reliability:
- Insert a short delay after each signal (e.g., `usleep(50-150)` microseconds) unless using acknowledgments.
- With bonus acknowledgments, the client waits for a reply (e.g., `SIGUSR1`) before sending the next bit/char.

## Implementation notes

- Use `sigaction` with `SA_SIGINFO` to retrieve sender PID if needed (bonus ack).
- Keep the signal handlers async-signal-safe; avoid non-reentrant functions. Typical pattern: accumulate bit state in `static` vars and write with `write(1, &c, 1)` once a byte completes.
- Convert `PID` from string with validation; reject invalid PIDs before sending.
- Use bitwise ops to set/read bits efficiently.

## Bonus ideas (commonly accepted)

- Acknowledgment: server signals the client for each received bit/char, allowing near-zero sleeps on client side.
- Unicode (UTF-8) safety: bytestream works transparently; just ensure you don’t split multi-byte sequences incorrectly during printing (raw bytes are fine for UTF-8).
- Error feedback: client prints an error if the server is unreachable (e.g., `kill` fails), or if it times out waiting for an ack.

## Testing

- Basic:
  - Short messages: `./client <PID> "Hi"`
  - Empty message: `./client <PID> ""` (server should at least handle terminator)
- Long strings:
  - `./client <PID> "$(printf 'A%.0s' {1..2000})"`
- Stress timing:
  - Reduce/increase `usleep` to see if characters are lost without ack; verify with ack the stream stays correct.
- Nonexistent PID:
  - `./client 999999 "test"` → Should report an error.

## Troubleshooting

- Client prints: `Error: invalid PID` → Ensure you copied the correct number from the server output.
- Server shows garbled text → Increase per-bit `usleep` or implement acknowledgments.
- Nothing is printed → Check signal masks/handlers and that you send the NUL terminator.

## Authors

- StegenX — https://github.com/StegenX
