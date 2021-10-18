# minishell

A very simply sh-like unix shell written in C using recursive descent parser technique.

# Brief summary

There is a main loop which would frequently scan for commands, parse it into token,
check the grammar and syntax and either produce an error or an output the resulting command, it's also handeling signals (Ctrl-Z, Ctrl-C and Ctrl-\)


# The lexical analyser

It will simply break the string input into a serie of tokens. They will be use for our shell language grammer.

# The Syntax Tree Parser

The shell language grammer is defined as follows in Backus–Naur form:

  cmd_line::| <job> '||' <cmd_line>
            | <job> '&&' <cmd_line>
            | <job>
  
  job::     | <cmd> '|' <job>
            | <cmd>
  
  cmd::     | <builtin> '>' <filename>
            | <builtin> '<' <filename>
            | <builtin> '>>' <filename>
            | <builtin> '<<' <filename>
  
  builtin:: | <pathname> <args>
  
  args::    | <word> <args>
            | <word>
 
 A recursive descent parser are use for build our execution tree (Abstract syntax tree).
 If the parser does not parse all the input string , that means that the input isn't part of the shell grammair, and it will stop where it doesn't found a match with his syntax.
 
 
# Execution

After we build our syntax tree, it is quite easy to traverse through out the tokens in order and make executions if necessary.
We are certain that our syntax tree works because the parser would throw an error in the first place if it wasn't

