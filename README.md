# C Gist Creator

**WIP**

Create a Gist from command-line.

Written in C with [libcurl](https://curl.se/libcurl/) and [jansson](https://jansson.readthedocs.io/en/latest/tutorial.html)

## Pre-requisites

This applies to Ubuntu...

Install [libjansson](https://packages.ubuntu.com/fr/focal/libjansson-dev) and [libcurl-dev](https://packages.ubuntu.com/fr/focal/libcurl-dev). We went for "OpenSSL flavour".

```
sudo apt install libcurl4-openssl-dev libjansson-dev
```

## Usage

1. Create a [GitHub personal access token](https://github.com/settings/tokens), with "Create gists" scope
2. Create a `token` file containing the personal access token (without spaces or newlines)
3. Build: `gcc -o main main.c -lcurl -ljansson`
4. Invoke: `./main sample-files/hello.js`
