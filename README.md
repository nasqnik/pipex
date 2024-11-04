# pipex - 42 Project


**Pipex** is a program that simulates the Unix shell's ability to pipe commands (|), allowing the output of one command to serve as the input to another. 
The project also supports multiple intermediate commands and handles here-documents for flexible input processing.

`./pipex <infile> <cmd1> <cmd2> <outfile>`

Bonus handles:
- multiple commands
'./pipex <infile> <cmd1> <cmd2> <cmd3> ... <outfile>'
- supports here-documents
'./pipex here_doc <limiter> <cmd1> <cmd2> <cmd3> ... <outfile>'



## Features
- `Command Piping`: Replicates the shell’s piping functionality, connecting multiple commands in a sequence.
- `Intermediate Commands`: Allows for multiple intermediate commands, creating a complex pipeline.
- `Here-Documents`: Supports here-documents (<<) to feed custom input directly into the pipeline.
