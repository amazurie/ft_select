# ft_select

The purpose for this project is to learn more about screen oriented programs using termcap/terminfo libraries in the C programming language.

Requirements (latest tested):
- GNU make (v3.81) <br />
- GCC (v4.2.1)

Features:
- If you pass a list of arguments to the program it gets displayed in your terminal. <br />
- arrows to move through the list. <br />
- One or more choices can be selected or un-selected with the space key. <br />
- Validate the selection with the return key, the list of choices will be sent back to the shell. <br />
- Re-organizes the display on window resize or displays an error if the list cannot fit the in window. <br />
- ESC key exits. <br />
- Pressing the delete or backspace keys removes an element from the list. <br />
- Press 'a' to select all and 'u' to unselect all. <br />
- Confirmation mode can be changed pressing '<' or '>' (shift if not caps lock required) <br />
- Searching by pressing '/', un/selection required ctrl during search <br />
- Colored output based on some supported file extensions. <br />
- Saving current state and restore 's' and 'r' <br />
- Restores the screen to what it was before clearing it. <br />
- No memory leaks
