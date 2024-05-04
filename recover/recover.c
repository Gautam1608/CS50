#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    unsigned char buffer[512];
    char outfile[9] = "000.jpg";
    char jpegopen = 0;
    FILE *outptr;
    while (fread(buffer, 1, 512, inptr))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            if (jpegopen)
            {
                fclose(outptr);
                if (outfile[1] == '9' && outfile[2] == '9')
                {
                    outfile[0]++;
                    outfile[1] = '0';
                    outfile[2] = '0';
                }
                else if (outfile[1] != '9' && outfile[2] == '9')
                {
                    outfile[1]++;
                    outfile[2] = '0';
                }
                else
                {
                    outfile[2] = (char) (outfile[2] + 1);
                }
            }
            outptr = fopen(outfile, "w");
            jpegopen = 1;
        }
        if (jpegopen)
        {
            fwrite(buffer, 1, 512, outptr);
        }
    }
    fclose(outptr);
    fclose(inptr);
}
