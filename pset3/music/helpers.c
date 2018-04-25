#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
// Helper functions for music
#include "helpers.h"


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)   // Fraction (numerator--->1/4<---denominator)
{
    if(fraction[0] == '1')  // if numerator[top number of the fraction] equals to 1
    {
        if(fraction[2] == '8')  // if denominator[bottom number of the fraction] equals to a 8
        {
            return 1;
        }
        else if(fraction[2] == '4')
        {
            return 2;
        }
        else if(fraction[2] == '2')
        {
            return 4;
        }
        else if(fraction[2] == '1')
        {
            return 8;
        }
    }
    else if(fraction[0] == '3' && fraction[2] == '8')   // 3/8 fraction
    {
        return 3;
    }
    else
    {
        return 0;
    }
    return 0;
}

int frequency(string note) // Calculates frequency (in Hz) of a note
{
    int octave = note[strlen(note) - 1];
    octave -= 48; // adjusting to an ascii into an int value

    double freq = 0.0;  // determine the frequency of note in the given octave

    switch(note[0]) // determine note letter
    {
        case 'C' :
            freq = 440.0 / (pow(2.0, (9.0 / 12.0)));
            break;
        case 'D' :
            freq = 440.0 / (pow(2.0, (7.0 / 12.0)));
            break;
        case 'E' :
            freq = 440.0 / (pow(2.0, (5.0 / 12.0)));
            break;
        case 'F' :
            freq = 440.0 / (pow(2.0, (4.0 / 12.0)));
            break;
        case 'G' :
            freq = 440.0 / (pow(2.0, (2.0 / 12.0)));
            break;
        case 'A' :
            freq = 440.0; // using the frequency of A4 - 440 hertz as a default to divide 2 1/12
            break;
        case 'B' :
            freq = 440.0 * (pow(2.0, (2.0 / 12.0)));
            break;
        default :
            return 0;
    }

    if(octave > 4)  // if octave num is greater than the 4th octave
    {
        for(int i = 0; i < octave - 4; i++)
        {
            freq *= 2.0;
        }
    }
    else if(octave < 4) // if octave num is lesser than the 4th octave
    {
        for(int i = 0; i < 4 - octave; i++)
        {
            freq /= 2.0;
        }
    }


    if(note[1] == 'b')  // if the note is a flat
    {
        freq /= (pow(2.0, (1.0 / 12.0)));   // divide from 2 1/12
    }
    else if(note[1] == '#') // if the note is a sharp
    {
        freq *= (pow(2.0, (1.0 / 12.0)));   // multiply from 2 1/12
    }

    int ret = round(freq);  // return frequency value as an integer
    return ret;

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
     if (strlen(s) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


