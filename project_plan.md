# Project/Learning Plan: Toy Shell
## Core Features and Stretch Goals
### Minimum Viable Shell (Core Features)

#### Internal/Built-in Commands:
- exit: Terminate the shell.
- cd: Change the current working directory.
- help: Display shell usage and available commands.

#### External Commands:
- ls: List directory contents.
- echo: Print arguments to stdout.
- cat: Concatenate and print files.
- pwd: Print the current working directory.
- grep: Search text using patterns.
- Stretch Goals (Advanced Features)

#### Internal/Built-in Commands:
- history: Display command history.
- alias: Create command aliases.
- unset: Remove shell variables or functions.
- export: Set environment variables.
- jobs: List background jobs.
- fg: Bring a background job to the foreground.
- kill: Send signals to processes.

#### External Commands:
- mkdir: Create directories.
- rm: Remove files or directories.
- cp: Copy files and directories.
- mv: Move or rename files.
- ps: Display process status.
- man: Display manual pages.
- find: Search for files in a directory hierarchy.
- sort: Sort lines of text files.
- wc: Print newline, word, and byte counts for files.

## Week-by-Week Plan

### Week 1: Foundations and Basic Shell Structure
__Theme__: C Basics, Shell Skeleton, and Simple I/O

__C Version__: K&R C (C89)

__Shell Commands__: None (focus on infrastructure)

#### Concepts:
__C Basics__: Review pointers, arrays, strings, and structs.
__Shell Skeleton__: Implement a loop to display a prompt (>) and read input (fixed buffer: char input[256]).
__System Calls__: Introduce printf, fgets, and stdin.
__Error Handling__: Check for fgets failures.

#### Deliverables:
A shell that prints a prompt and echoes input.
Code organized in main.c with a read_input() function.

#### Resources:
K&R, Chapters 1-5.
Linux man pages for fgets.

### Week 2: Parsing and Built-in Commands
__Theme__: Input Parsing and Basic Command Execution

__C Version__: K&R C (C89)

__Shell Commands__: exit, help

#### Concepts:

__Parsing__: Use strtok to split input into tokens (command + arguments).
__Built-ins__: Implement exit (terminate shell) and help (display usage).
__Processes__: Introduce fork and wait (but don’t execute external commands yet).
__Modularity__: Separate parsing logic into parse_input() and built-ins into execute_built_in().

#### Deliverables:
Shell parses input and handles exit/help.
Code split into parse.c and builtins.c.

#### Resources:
K&R, Chapter 7 (Input/Output).
Linux man pages for strtok.

### Week 3: Executing External Commands
__Theme__: Process Management and System Calls

__C Version__: K&R C (C89)

__Shell Commands__: ls, echo, cat, pwd, grep

#### Concepts:

__Process Creation__: Use fork, execvp, and waitpid to run external commands.
__Error Handling__: Check return values of fork/execvp and print errors to stderr.
__Path Resolution__: Use which or hardcode /bin/ for simplicity.

#### Deliverables:
Shell executes external commands (e.g., ls -l).
Error messages for failed commands.

#### Resources:
Advanced Programming in the UNIX Environment, Chapter 8 (Process Control).
Linux man pages for execvp.

### Week 4: Dynamic Input and Memory Management
__Theme__: Upgrading to Dynamic Buffers

__C Version__: C99 (for getline)

__Shell Commands__: None (infrastructure upgrade)

#### Concepts:
__Dynamic Memory__: Replace fixed buffer with getline (POSIX) or custom realloc loop.
__Memory Safety__: Check for malloc/realloc failures; use valgrind to debug leaks.
__Buffer Overflow __Protection: Ensure input cannot exceed allocated memory.

#### Deliverables:
Shell reads input dynamically (no fixed limit).
Memory leaks checked with valgrind.

#### Resources:
Modern C by Gustedt, Chapter 10 (Dynamic Memory).
GNU getline documentation.

### Week 5: Pipes and Redirection
__Theme__: Advanced I/O and Process Communication

__C Version__: C99

__Shell Commands__: | (pipes), > (output redirection)

#### Concepts:

__Pipes__: Use pipe, dup2, and fork to connect processes (e.g., ls | grep).
__File Descriptors__: Redirect stdout/stdin using dup2 and open.
__Error Handling__: Close unused file descriptors; check for pipe failures.

#### Deliverables:
Shell supports cmd1 | cmd2 and cmd > file.
Code split into io_redirection.c.

#### Resources:
Advanced Programming in the UNIX Environment, Chapter 15 (IPC).
Linux man pages for pipe.

### Week 6: Signals, Job Control, and Polish
__Theme__: Robustness and User Experience

__C Version__: C11 (for _Generic or stdatomic.h if needed)

__Shell Commands__: & (background processes), Ctrl+C handling

#### Concepts:

__Signals__: Use signal or sigaction to handle SIGINT (Ctrl+C) and SIGCHLD (zombie processes).
__Job Control__: Track background processes with a job table (array of pid_t).
__Environment Variables__: Use getenv/setenv for shell configuration.

#### Deliverables:
Shell handles Ctrl+C gracefully and supports cmd &.
Job table tracks background processes.

#### Resources:
Advanced Programming in the UNIX Environment, Chapter 10 (Signals).
Linux man pages for sigaction.

### Week 7: Security, Sanitization, and Memory Safety
__Theme__: Hardening the Shell

__C Version__: C11

__Shell Commands__: None (focus on security)

#### Concepts:

__Input Sanitization__: Prevent command injection (e.g., avoid system(); sanitize arguments).
__Memory Safety__: Use valgrind to detect leaks; replace unsafe functions (strcpy → strncpy).
__Buffer Overflow Protection__: Implement stack canaries or use compiler flags (-fstack-protector).
__Privilege Escalation__: Avoid running shell as root; drop privileges if necessary.
__Secure Coding Practices__: Use snprintf instead of sprintf; validate all inputs.

#### Deliverables:
Shell resists basic injection attempts and has no memory leaks.
Documentation of security measures and testing results.

#### Resources:
OWASP Command Injection Guide
Valgrind Quick Start
GCC Security Options

Connection Between Commands and Concepts

  
    
      Shell Command/Feature
      Connected Concepts
      C Version
    
  
  
    
      Prompt/Input
      printf, fgets, buffers
      C89
    
    
      exit/help
      Parsing, modular functions
      C89
    
    
      External commands
      fork, execvp, process lifecycle
      C89
    
    
      Dynamic input
      getline, malloc/realloc, memory safety
      C99
    
    
      Pipes (`
      `)
      pipe, dup2, file descriptors, IPC
    
    
      Redirection (>)
      open, dup2, file descriptors
      C99
    
    
      Background processes (&)
      signal, job control, process groups
      C11
    
    
      Security
      Input sanitization, memory safety, canaries
      C11
    
  


