#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }

    char* infile = argv[1];

    // size of the block that will be read and written
    const int BLOCK_SIZE = 512;

    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    unsigned char buffer[BLOCK_SIZE];

    FILE* outptr = NULL;  // pointer to outfile

    char image[7]; // make space for jpg file name

    int n = 0; // number of image files created

    // search until jpg header is found
    while(fread(buffer, BLOCK_SIZE, 1, inptr) == 1)
    {
        // find the header of a jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            if (n > 0) // if image has been created, close file
            {
                fclose(outptr);
            }

            sprintf(image, "%03d.jpg", n);  // make name for nth image

            // open nth image file
            outptr = fopen(image, "w");
            if (outptr == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", image);
                return 3;
            }

            n++; // increment number of image files created
        }

        if (outptr != NULL) // write to image file if one exists
        {
            fwrite(buffer, BLOCK_SIZE, 1, outptr); // write to image file
        }
    }

    fclose(outptr); // close last image file

    fclose(inptr);  // close card.raw

    return 0;
}