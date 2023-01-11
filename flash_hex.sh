#!/bin/bash

# Set up the ESP-IDF
export IDF_PATH=/path/to/esp-idf

# Create a new project
idf.py new my_project

# Copy the provided code into the project
cp /path/to/flash_hex.c my_project/main

# Build the project
idf.py build
