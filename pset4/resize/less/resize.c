#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
	if (argc != 4) // ensure proper usage
	{
		printf("Usage:resize n infile outfile\n");
		return 1;
	}

	// remember filenames
	char* infile = argv[2];
	char* outfile = argv[3];
	int resize = atoi(argv[1]); // size to enlarge the file

	if (resize < 0 || resize > 100)
	{
		printf("The resize should be a positive integer <= 100.\n");
		return 2;
	}

	// open input file
	FILE* inptr = fopen(infile, "r");
	if (inptr == NULL) // error check
	{
		fprintf(stderr, "Could not open %s.\n", infile);
		return 3;
	}

	// open output file
	FILE* outptr = fopen(outfile, "w"); // file to write
	if (outptr == NULL) // error check
	{
		fclose(inptr);
		fprintf(stderr, "Could not create %s.\n", outfile);
		return 4;
	}

	// read infile's BITMAPFILEHEADER
	BITMAPFILEHEADER bf;
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

	// read infile's BITMAPINFOHEADER
	BITMAPINFOHEADER bi;
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

	// ensure infile is likely a 24-bit uncompressed BMP 4.0
	if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
		bi.biBitCount != 24 || bi.biCompression != 0)
	{
		fclose(outptr);
		fclose(inptr);
		fprintf(stderr, "Unsupported file format.\n");
		return 4;
	}
	// determine padding for scanlines needed for SizeImage calculation
	BITMAPFILEHEADER newbf = bf;
	BITMAPINFOHEADER newbi = bi;

	int in_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; // old padding
	// newbi.biWidth = bi.biWidth;
	// newbi.biHeight = bi.biHeight;

	newbi.biWidth *= resize; // will be the new width
    newbi.biHeight *= resize; // will be the new height
	int out_padding =  (4 - (newbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; // new padding

	// Calculate file and image size, biSizeImage calculation.
    newbi.biSizeImage = ((sizeof(RGBTRIPLE) * newbi.biWidth) + out_padding) * abs(newbi.biHeight);
    newbf.bfSize = newbi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// write outfile's BITMAPFILEHEADER
	fwrite(&newbf, sizeof(BITMAPFILEHEADER), 1, outptr);

	// write outfile's BITMAPINFOHEADER
	fwrite(&newbi, sizeof(BITMAPINFOHEADER), 1, outptr);

	for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
	{
		// Write each line resize-times
		for(int n = 0; n < resize; n++)
		{
			// iterate over pixels in scanline
			for (int p = 0; p < bi.biWidth; p++)
			{
				// temporary storage
				RGBTRIPLE triple;

				// read RGB triple from infile
				fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

				// write RGB triple to outfile
				for(int m = 0; m < resize; m++)
				{
					fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
				}
			}

			fseek(inptr, in_padding, SEEK_CUR); // skip over padding in infile

			// then add it to outfile
			for (int k = 0; k < out_padding; k++)
			{
				fputc(0x00, outptr);
			}

			if (n < resize - 1)
			{
				fseek(inptr, -(bi.biWidth * 3 + in_padding), SEEK_CUR);
			}
		}
		//fseek(inptr, bi.biWidth * 3 + in_padding, SEEK_CUR);
	}
	fclose(inptr); // close infile
	fclose(outptr); // close outfile
	return 0; // that's all folks
}