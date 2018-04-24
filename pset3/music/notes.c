// Prints frequencies of and outputs WAV file with all notes in an octave

#include <cs50.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"
#include "wav.h"

// Notes in an octave
const string NOTES[] = {"C", "C#", "D", "D#", "E", "F",
                        "F#", "G", "G#", "A", "A#", "B"
                       };

// Default octave
#define OCTAVE 4

int main(int argc, string argv[])
{
    // Override default octave if specified at command line
    int octave = OCTAVE;
    if (argc == 2)
    {
        octave = atoi(argv[1]);
        if (octave < 0 || octave > 8)
        {   //function called fprintf to print error messages to stderr (standard error)
            fprintf(stderr, "Invalid octave\n");
            return 1; // main returns 1 in case of error
        }
    }
    else if (argc > 2)
    {
        fprintf(stderr, "Usage: notes [OCTAVE]\n");
        return 1;
    }

    // Open file for writing
    song s = song_open("notes.wav");

    // Add each semitone
    for (int i = 0, n = sizeof(NOTES) / sizeof(string); i < n; i++)
    {
        // Append octave to note
        char note[4]; // allocate space for a (short) string by declaring an array for 4 chars

        // stores its output in a string, create a string from two placeholders, %s and %i
        // use sprintf to store a NOTES[i] (a string, ergo the %s) in that memory followed by octave (an int, ergo the %i).
        sprintf(note, "%s%i", NOTES[i], octave);
        // take values like "A" and 4 and, effectively,
        // concatenate them in order to create a new string,
        // the value of which is, for instance, A4.

        // Calculate frequency of note
        int f = frequency(note);

        // Print note to screen
        printf("%3s: %i\n", note, f);

        // Write (eighth) note to file
        note_write(s, f, 1);
    }

    // Close file
    song_close(s);
}
