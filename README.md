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
Repo includes a folder, `/dirs`, to use as a working example.  

The command takes two arguments: the directory to search and the name of the output file you want to create.
``` bash
./defrag dirs <your_output_file.mp3>
```
### 4. Enjoy the music
Listen to the .mp3 in any media player!  
♪┏(・o･)┛♪