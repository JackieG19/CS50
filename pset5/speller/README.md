# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

A lung disease caused by the inhalation of very fine silica dust, causing inflammation in the lungs.

## According to its man page, what does `getrusage` do?

It returns resource usage measures for a process(es), like CPU time and memory used.

## Per that same man page, how many members are in a variable of type `struct rusage`?

There are 16 members in a structure.

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

If we pass them by value, whole two structures will be copied into 'calculate' - that's a waisting of time and resources.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The text file is specified in the command line as the 2nd or 3rd argument. A file pointer is set to a file that is opened in "readmode". If the pointer is pointed at a null character then an error is thrown.
Then variables are set up before the loop. "index" tracks the position in the word, "misspellings" tracks the amount of words misspelt, "words" tracks the amount of words scanned for misspellings, "word" is
the character set that is hopefully building a word that is set to the maximum size of a word plus the end of string character.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fgetc reads the file character by character, discriminating vs anything that isn't alphabetical or an apostrophe proceeded by a character. fscanf reads until white space and stores the array in a buffer, the array may contain commas etc which
would cause problems for the misspelling function.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?
Those parameters are never intented to be modified in the functions, so we wrote an other layer of ensuring this behavior.

