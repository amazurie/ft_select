# ft_select

The goal for this project is to learn more about screen oriented programs using termcap/terminfo libraries in the C programming language.

If you pass a list of arguments to the program it gets displayed in your terminal.
arrows to move through the list.
One or more choices can be selected or un-selected with the space key.
Validate the selection with the return key, the list of choices will be sent back to the shell.
Re-organizes the display on window resize or displays an error if the list cannot fit the in window.
ESC key exits.
Pressing the delete or backspace keys removes an element from the list.
Press 'a' to select all and 'u' to unselect all.
Confirmation mode can be changed pressing '<' or '>' (shift if not caps lock required)
Searching by pressing '/', un/selection required ctrl during search
Colored output based on some supported file extensions.
Saving current state and restore 's' and 'r'
Restores the screen to what it was before clearing it.
No memory leaks
