// Prompts user for a sequence of notes with which to synthesize a song

#include <cs50.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"
#include "wav.h"

int main(int argc, string argv[])
{
    // Check command line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: synthesize FILE\n");
        return 1;
    }
    string filename = argv[1];

    // Open file for writing
    song s = song_open(filename);

    // Expect notes from user until EOF
    while (true)
    {
        // Expect note from a user one at a time
        string line = get_string("");

        // Check for EOF
        if (line == NULL)
        {
            break;
        }

        // Check if line is rest
        if (is_rest(line))
        {
            rest_write(s, 1);
        }
        // Else it proceeds to "tokenize" the user’s input into two tokens:
        // a note which is left of the @ in the user’s input, and
        // a fraction, which can be found to the right of the @ in the user’s input
        else
        {
            // Parse line into note and duration
            string note = strtok(line, "@"); // program uses a function called strtok to facilitate such....
            string fraction = strtok(NULL, "@"); //...it then writes that note (or rest) to a file.

            // Write note to song
            note_write(s, frequency(note), duration(fraction));
        }
    }

    // Close file
    song_close(s);
}
