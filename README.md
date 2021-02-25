# C Gist Creator

## What is it?

A little CLI tool allowing you to create a Gist from command-line, from local files.

It is written in C with [libcurl](https://curl.se/libcurl/) and [jansson](https://jansson.readthedocs.io/en/latest/tutorial.html).

## Status

This is **Work In Progress**. Basic stuff works, but there's still room for improvement:

* [ ] Parse args, so as to set `public` and `description` in POST request to GitHub API's `/gists` endpoint
* [ ] Better error handling
* [ ] Cross-OS build (only targets Linux as of now)

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
4. Invoke: `./main hello.js`
