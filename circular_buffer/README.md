# Circular Buffer

A modern, fast, and efficient event logger implemented in C++20. This logger provides a way to log events with timestamps. It utilizes a circular buffer to store the latest N messages, ensuring a constant amount of memory usage.

## Features

- Fast logging with minimal overhead.
- Utilizes C++20 concepts for type safety and code clarity.
- Provides an easy-to-read log output with timestamps.
- Customizable buffer size to fit specific use cases.
- Circular buffer ensures fixed memory usage, oldest messages are discarded to make room for new messages.
- Extensible by using a custom event payload structure.

## Example Output

```plaintext
2023-10-16 11:40:57  SENT Signal 1.
2023-10-16 11:40:57  RECD Signal 2.
2023-10-16 11:40:57  SENT Signal 3.
2023-10-16 11:40:57  RECD Signal 5 This is a weird signal....
2023-10-16 11:40:57  SENT Signal 1.
