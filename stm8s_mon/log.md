2019-04-22
-
* Modified command evaluation. replaced parse_line() by a recursive eval().
* added environment variable, which are evaluated when envoked.

2019-04-18
-
* added 'o' over n t -- n t n
* rename command 'd' 'm'
* added 'd' command for duplacte  n -- n n 
* changed semantic of '+' and '-'

2019-04-16
-
* added command 'r'  to repeat loop. CTRL_C to exit loop
* added 'd' for delay in milliseconds.
* added ':' to mark loop stack
* added control stack to extend loop capability.
* added '?' conditionnal repeat loop (repeat only if condition is true)
* added 'k' query uart for available char.
* added '~' to invert tos.
* added '.' to print tos
* added 'e' to emit tos as character
* added '-' tos=next-tos
* added '+' tos=next+tos
