# Image convert and resize

Read an input image, resize it to maximum dimensions, and save it as PNG.
Uses the STB image header libraries.
Compile with: 
```
$ gcc main.c -lm
```
Example usage:
```
$ ./a.out /path/to/lena.jpg /path/to/lena_conv.png 250 360
```
