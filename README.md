# minishell | 42KL

A mini recreation of Bash <img src="https://user-images.githubusercontent.com/25181517/192158606-7c2ef6bd-6e04-47cf-b5bc-da2797cb5bda.png" width="25px" alt="Bash" title="Bash">. The project has to be coded in C language and uses a lot of low level POSIX compliant C system calls such as READ/WRITE/OPEN, forks, pipes, signals to name a few.  

![minishell.gif](https://github.com/mseong123/minishell/blob/a8a6be8e979df5e5444f1bc96b438243b941a13b/minishell.gif)

## What is Bash?
A shell is a command line interface program that the user can use to interact with an operating system's services. Bash is the GNU shell, and is currently the most common shell program in Linux or MacOS (both Unix-like operating system). Windows equivalent shells are cmd.exe (command line) and PowerShell.

## Project rules
Display a prompt while waiting for a new commmand.
- Have a working history.
- Find and launch executables (using the `PATH` variable or an absolute path).
- Handle `'` (single) and `"` (double) **quotes** like in bash.
- Implement **redirections** such as:
  - `<` redirect input.
  - `>` redirect output.
  - `<<` heredoc (doesn't affect history).
  - `>>` redirect output in append mode.
- Implement `|` (**pipes**).
- Handle **environment variables**.
- Handle `$?`.
- `ctrl-C`, `ctrl-D`, and `ctrl-\` should behave like in bash.
- Recreate the following shell **builtins**:
  - `echo` with option `-n`.
  - `cd` with only a relative or absolute path.
  - `pwd` (no flags).
  - `export` (no flags).
  - `unset` (no flags).
  - `env` (no flags or arguments).
  - `exit` (no flags).

## Status

Validated 24/7/2023. Grade: 100%. Project duration: 4 weeks.

## Clone, Compile and Run

Clone the repository:

```
git clone https://github.com/mseong123/minishell.git
cd minishell
make
./minishell
```

## Notes
- This is definitely one of the most 'notorious' and challenging project so far in the 42 curriculum given that it has to handle many edge cases and success rate is highly dependent on how far the evaluator is willing to go to test that the minishell complies with every aspect of bash. Doing this project will level up your string manipulation skills significantly and you will learn many bash behaviors which you most likely won't encounter in your daily programming. 

### Some commands to try:

As this project is made to mimic bash, you can try any commands you normally would try in bash.

If you really can't think of anything try some of the following.
```
ls -la | grep a | tr 'a-z' 'A-Z'
```

```
cat << EOF > file
cat file
rm file
```

```
ls | rev > file
cat file
rev file | cat
rm file
```

*to exit the program:*
```
exit
```
