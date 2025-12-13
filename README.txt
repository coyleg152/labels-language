Labels Programming Language
Author: theth/coyleg152


Introduction:

"Labels" is an esoteric programming language heavily inspired by Urban Müller's
"Brainf**k" language. The goal was to create a language with LESS symbols than
Brainf**k's eight, which led to Labels being designed with just seven.

Because I cheated.

Labels does indeed have seven core operators, but it also has goto-style labels
which can be formed with any combination of A-Z, a-z, 0-9, and underscores.
This means Labels actually has 70 recognized characters, not counting decorative
characters like spaces and newlines which can be used to separate labels.


How it works:

The Labels interpreter (compiled from "labels.c") implements a Turing Machine
with each cell holding a single byte value. There is initially only one cell,
but a new cell is automatically created each time the TM pointer moves beyond
its current boundaries, and every cell initially has a value of 0.

Labels code is traversed character by character, starting from the very first
character and stopping at the end of the code. Each operation is performed as
soon as its operator is read, and labels can be used to jump forwards or
backwards in the code. The '?' operator can also be used to conditionally skip
the next operator/label. Below are descriptions of each operator.


Operators originally from Brainf**k:

+ (Increment the current cell value by 1)
- (Decrement the current cell value by 1)
< (Move left by 1 cell)
> (Move right by 1 cell)
. (Print the current cell value as an ascii character)


New operators found in Labels:

? (Skip the next operation or label if the current cell value is 0)
: (Marks a position in the code that can be travelled to via label)


How to use labels in Labels:

The implementation of labels is similar to the goto keyword in C. When a label
without an ending ':' is read, the reader jumps to the first instance of that
label WITH an ending ':' and continues from there. If no corresponding label
with a ':' is found in the code, the program stops.

Below are examples of label functionality.


Using labels to travel backwards:

############    ############
| ex1: ex1 | => | ex1: ex1 |
|     (^)  |    |   (^)    |
############    ############


Using labels to travel forwards:

#################    #################
| ex2 j ex2: j: | => | ex2 j ex2: j: |
|(^)            |    |         (^)   |
#################    #################


When multiple ':' labels share a name, only the earliest one matters:

#################    #################
| ex3: ex3 ex3: | => | ex3: ex3 ex3: |
|     (^)       |    |   (^)         |
#################    #################


If a matching ':' label cannot be found, the program will end:

##################    ##################
| loop: ex4 loop | => | loop: ex4 loop |
|      (^)       |    |              ()|
##################    ##################


How to compile and run Labels on Linux:

Step 1 - Ensure "labels.c", "linked_list.c", and "dynamic_string.c" are all
in your current working directory

Step 2 - Compile labels.c by running
$ gcc labels.c -o labels.out

Step 3 - Run labels.out with one or more code files like so
$ ./labels.out (file1) (file2) ...


Simple example program:

++++++++ ++++++++ ++++++++ ++++++++
++++++++ ++++++++ ++++++++ ++++++++
++++++++ ++++++++ ++++++++ ++++++++

++++++++.
+.

>

++++++++++.

$ ./labels.out basic_hi
hi


Shorter "hi" program using '?' and labels:

+++++++++++++a:>++++++++<-?a>.+.>++++++++++.

$ ./labels.out labels_hi
hi


Additional notes:

- More example code can be found in the Labels GitHub repository
- Avoid adding new cells in an infinite loop as this will cause errors
- To kill an active labels.out process, use "^C" or "kill" to avoid leaks
