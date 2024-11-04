# pipex - 42 Project


# pipex - 42 Project

**pipex** is a program that simulates the Unix shell's ability to pipe commands (`|`), allowing the output of one command to serve as the input to the next. The project also supports multiple intermediate commands and handles here-documents for flexible input processing.

## Usage

```bash
./pipex <infile> <cmd1> <cmd2> <outfile>

Bonus
The bonus version includes:

Multiple Commands: Allows for chaining multiple intermediate commands in the form ./pipex <infile> <cmd1> <cmd2> ... <cmdN> <outfile>.
Here-Documents: Supports here-documents with ./pipex here_doc LIMITER <cmd1> <cmd2> ... <outfile>, where the input is fed directly until a specified delimiter.
Features
Command Piping: Replicates the shell’s piping functionality, connecting multiple commands in a sequence.
Intermediate Commands: Supports multiple intermediate commands to create complex pipelines.
Here-Documents: Implements here-documents (<<) to allow flexible custom input directly into the pipeline.

