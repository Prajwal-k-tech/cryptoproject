# Encoding and Obfuscation Exercise

An early C++ team project exploring a layered string transformation. The encoder applies Base64, inserts characters at fixed positions, converts to hexadecimal, and inserts additional characters at prime-related positions. The decoder reverses the pipeline.

Base64 and hexadecimal are encodings. The fixed-position insertion scheme has no secret key and is not secure encryption.

## Source layout

- `encrypt.cpp`: encoder entry point.
- `decrypt.cpp`: decoder entry point.
- `base64.cpp`, `hex.cpp`: encoding helpers.
- `thunder.cpp`, `prime.cpp`: insertion/removal helpers.

## Build from source

```bash
g++ -std=c++17 encrypt.cpp -o encode
g++ -std=c++17 decrypt.cpp -o decode
```

Each executable reads one line from standard input and prints its output. Build the entry points separately: they include the helper `.cpp` files directly. Old committed Windows binaries are historical artifacts; build the source for your own environment.

## Verification

With Python 3 and a GCC toolchain supporting sanitizers:

```sh
python3 check_roundtrip.py
```

The check compiles both CLIs with undefined-behavior and bounds sanitizers. It covers 607 round trips, including empty input, Unicode, byte values, lengths around insertion positions and a 10,000-byte input, plus malformed-input rejection. CLI input is one line; embedded newline bytes are outside that interface.

The source fixes insertion alphabet and position-array bounds, final-position removal, and malformed hexadecimal/unknown Base64 characters. This remains an encoding/obfuscation exercise with no secret key.

Original team attribution: Shura and oGhostyyy. Prajwal contributed the hexadecimal conversion code according to the original project README.
