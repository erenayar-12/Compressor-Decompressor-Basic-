# Compressor-Decompressor-Basic

## Short Description
#### A C++ implementation of the Lempel-Ziv-Welch (LZW) lossless data compression algorithm using a custom Hash Table with linear probing. (CS300 Homework)

## Overview
#### This project implements the encoding phase of the LZW (Lempel-Ziv-Welch) compression algorithm. It reads a text file, compresses the content by building a dictionary of seen string patterns, and outputs a sequence of integer codes.
#### The core of the solution is a custom Hash Table implementation used to store the dictionary of string patterns, allowing for efficient O(1) average time complexity lookups during the compression process.

## Key Features
#### LZW Encoding Logic: Reads input character by character, accumulating strings (p + c). If a pattern exists in the dictionary, it extends the current pattern; otherwise, it outputs the code for the known pattern and adds the new extended pattern to the dictionary.

#### Custom Hash Table:
#### - Implements a generic HashTable class template.
#### - Uses Linear Probing for collision resolution.
#### - Includes automatic Rehashing when the load factor exceeds 0.5 to maintain performance.
#### - Supports generic keys and values (used here mapping string patterns to int codes).

#### Dynamic Dictionary: 
#### - Automatically initializes the dictionary with the standard ASCII character set (0-255) and dynamically grows up to a limit (4096 entries).

#### File I/O: 
#### - Reads from compin.txt and writes the compressed integer codes to compout.txt.

## How It Works
#### Initialization: A hash table is initialized with the first 256 ASCII characters, mapping each character string to its ASCII integer value.
#### Compression Loop: The program reads the input file character by character. It checks if the current combined string p + c exists in the hash table using table.find(). If found: The current pattern p becomes p + c. If not found: The code for p is written to the output file. The new pattern p + c is inserted into the hash table with a new unique code (starting from 256), provided the dictionary limit (4096) hasn't been reached. p is reset to c. Completion: After the loop finishes, the code for the remaining string p is written to the output.

## Input/Output
#### Input (compin.txt): A plain text file containing the data to be compressed.
#### Output (compout.txt): A text file containing a space-separated list of integer codes representing the compressed data.
