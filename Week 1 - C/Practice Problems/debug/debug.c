// There are two kinds of errors that can occur when writing a program. The first errors you are likely to encounter are syntactical errors.
// In addition to syntactical errors, there can also be logical errors, which we’ll take a look at soon.

// In computer science, syntax is important for a computer to understand what you are telling it to do.
// Each programming language has its own syntactical rules, which include the combination of both words and punctuation.

// This lab starts with distribution code which has several syntactical errors. The idea is for you to try to compile (make)
// the program, learn to interpret the rather cryptic error messages output by the compiler, and debug the program.

#include <cs50.h>
#include <stdio.h>

        int
        main(void)
{
    // Ask for your name and where live
    string name = get_string("What is your name? ");
    string location = get_string("Where do you live? ");

    // Say hello
    printf("Hello, %s, from %s! \n", name, location);
}
