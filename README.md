# c-multithreaded-defragger
A high-performance C program that reassembles binary files from a complex directory tree. This program makes use of **pthreads** for parallel searching, and a **blocking mutex** to synchronize data, and ensure **thread-safe reassembly**.

## Features
* Multithreading
* Blocking Mutex
* Dynamic Memory Management
* POSIX directory traversal

## Requirements

### Software
* GNU C Compiler (`gcc`)
* GNU Make (`make`)

### Dependencies
* POSIX-compliant Environment
* `pthreads` library

## Setup & Installation
### 1. Clone the repository:
``` bash
git clone https://github.com/your-username/c-multithreaded-defragger.git
cd c-multithreaded-defragger
```
### 2. Build the executable:
``` bash
make
```
This creates the `defrag` executable from `main.c`
### 3. Run the application:
The command takes two arguments: the path to the directory to search and the name for the reassembled output file.
``` bash
./defrag <path_to_directory> <your_output_file>
```
#### Example:
Repo includes a folder, `/dirs`, to use as a working example.
``` bash
./defrag dirs music.mp3
```
You can now listen to the reassembled `music.mp3` in any media player!  
♪┏(・o･)┛♪