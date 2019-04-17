# Get_next_line

| get_next_line     |                                            |
| ------------- | ----------------------------------------- |
| Prototype        | int get_next_line(const int fd, char **line);    |
| Description    | Get_next_line is a function that return a line (succession of
character that end with '\n') read from a file descriptor. The strind is
returned without the '\n'. Calling the function get_next_line in a loop will
then allow you to read the text available on a file descriptor one line at the
end of the text, no matter the size of either the text or ones of it's lines.
Multi file descriptor are manage. |
| Param #1        | The file descriptor |
| Param #2        | The address of the image that will be used yo save the line
read from the file decriptor |
| Return value    | can be 1, 0 or -1 depending on whether a line has been read,
when the reading has been completed, or if an error has happened respectively |
| Libc functions| malloc(3) |

## Use

Get_next_line is part of the library [libft](https://github.com/tcollard/libft)

## Project instruction

[get_next_line.pdf](https://github.com/tcollard/get_next_line/tree/master/PDF)

## Author

Thibault Collard : tcollard@student.42.fr
