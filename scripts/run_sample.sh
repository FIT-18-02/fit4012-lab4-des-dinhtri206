#!/usr/bin/env bash
set -euo pipefail

mkdir -p logs

g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des

echo "=== Run DES Program ===" > logs/run
./des >> logs/run


echo "" >> logs/run
echo "=== Round-trip Test ===" >> logs/run
echo "Input: hello" >> logs/run
echo "Expected: decrypt(encrypt(x)) = x" >> logs/run
