# DirScout (C)

A lightweight directory brute-forcing tool written in C for web reconnaissance.

## Features
- Fast directory enumeration
- Uses HTTP HEAD requests
- Detects common response codes (200, 301, 302, 403)
- Minimal dependencies (libcurl)

## Usage
```bash
make
./dirscout https://example.com wordlists/common.txt
