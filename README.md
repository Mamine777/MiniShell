# Minishell 

### was done by :
Mokariou && isall

**As beautiful as a shell**  

## Summary  
This project involves creating a simple shell—**your very own bash**.  
By undertaking this, you'll delve into processes and file descriptors, learning about key systems programming concepts while building a fully functional shell.  

---

## Version  
**7.1**  

---

## Contents  
1. [Introduction](#introduction)  
2. [Common Instructions](#common-instructions)  
3. [Mandatory Part](#mandatory-part)  
4. [Bonus Part](#bonus-part)  
5. [Submission and Peer-evaluation](#submission-and-peer-evaluation)  

---

## I. Introduction  
Shells have existed since the beginning of IT, evolving from tedious switch-aligned programming to a more user-friendly command-line interface.  
With Minishell, you can travel back in time and tackle the challenges faced by developers before GUI-based systems like Windows.  

---

## II. Common Instructions  

- **Programming Language**: C, adhering to the **Norm**.  
- **Stability**:  
  - Functions must not crash unexpectedly (e.g., segmentation fault).  
  - No memory leaks are tolerated; heap-allocated memory must be properly freed.  
- **Makefile**:  
  - Compile with flags `-Wall -Wextra -Werror` using `cc`.  
  - Include the rules: `$(NAME)`, `all`, `clean`, `fclean`, `re`, and optionally `bonus`.  
- **Libft**: If allowed, include its sources in a `libft` folder. Your Makefile must compile it correctly.  
- **Testing**: Create test programs to validate your work; these will assist during defense.  

---

## III. Mandatory Part  

### Program Details  
- **Name**: `minishell`  
- **Files to Submit**: `Makefile`, `*.h`, `*.c`  

### Shell Requirements  
1. **Prompt**: Display a prompt while awaiting input.  
2. **Command Execution**:  
   - Find and execute commands using `PATH`, absolute, or relative paths.  
3. **Built-ins**: Implement the following:  
   - `echo` (with `-n` option)  
   - `cd` (relative/absolute paths only)  
   - `pwd` (print working directory)  
   - `export` (no options)  
   - `unset` (no options)  
   - `env` (no options/arguments)  
   - `exit` (no options)  
4. **Redirections**:  
   - `<` Redirect input.  
   - `>` Redirect output.  
   - `<<` Read until a delimiter (doesn't affect history).  
   - `>>` Append output.  
5. **Pipes (`|`)**: Link commands together using a pipeline.  
6. **Environment Variables**: Expand `$` variables and handle `$?` for the last exit status.  
7. **Interactive Mode**:  
   - `ctrl-C`: Display a new prompt.  
   - `ctrl-D`: Exit shell.  
   - `ctrl-\`: Ignore.  
8. **Quotes**:  
   - Single (`'`): Treat enclosed content literally.  
   - Double (`"`): Interpret `$` while keeping other characters literal.  
9. **Signal Handling**: Use a **single global variable** to handle received signals.  

### External Functions Allowed  
`readline`, `add_history`, `fork`, `execve`, `pipe`, `dup`, `signal`, `getenv`, and more.  

---

## IV. Bonus Part  

The following features can be implemented if the **mandatory part is perfect**:  
1. Logical operators: `&&` and `||` with parenthesis for priorities.  
2. Wildcards (`*`): Match files in the current directory.  

---

## V. Submission and Peer-evaluation  

- **Repository**: Submit to your assigned Git repository. Ensure all file names and structure are correct.  
- **Evaluation**: Peer reviews will precede automated testing (Deepthought). A single failure will halt the automated evaluation.  

