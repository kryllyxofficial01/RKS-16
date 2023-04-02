# Preprocessor Directives
These are not instructions, but rather single lines of code that expand into assembly.

<br>

## Define
This directive declares a global integer "variable" (meant in the loosest sense of the word).

You use the directive like this:
```
#define test 10
```
Here the variable `test` is created with the value 10.

<br>

To access the contents later, use the prefix "$". Here's an example:
```
#define test 10

ldi @a $test
```
This will store the value of `test` into register A.