#!/usr/bin/env bash

set -e

echo "Adding ShellSweeper repository..."

sudo mkdir -p /etc/apt/keyrings

curl -fsSL https://srblank.github.io/shellsweeper/shellsweeper.asc | \
    sudo gpg --dearmor -o /etc/apt/keyrings/shellsweeper.gpg

echo \
"deb [signed-by=/etc/apt/keyrings/shellsweeper.gpg] https://srblank.github.io/shellsweeper stable main" \
| sudo tee /etc/apt/sources.list.d/shellsweeper.list

sudo apt update

echo "Installing ShellSweeper..."

sudo apt install shellsweeper