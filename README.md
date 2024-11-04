# pipex - 42 Project


**pipex** is a program that simulates the Unix shell's ability to pipe commands (`|`), allowing the output of one command to serve as the input to the next. The project also supports multiple intermediate commands and handles here-documents for flexible input processing.

```./pipex <infile> <cmd1> <cmd2> <outfile>``` 

Checked for leaks with valgrind:
valgrind --leak-check=full --leak-resolution=high -s --trace-children=yes --track-fds=yes --track-origins=yes --show-leak-kinds=all

## Bonus
The bonus version includes:

- **Multiple Commands**: Allows for chaining multiple intermediate commands in the form
  ```./pipex <infile> <cmd1> <cmd2> ... <cmdN> <outfile>```
- **Here-Documents:** Supports here-documents with
  ```./pipex here_doc LIMITER <cmd1> <cmd2> ... <outfile>```,
  where the input is fed directly until a specified delimiter.
