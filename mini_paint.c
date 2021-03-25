#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

int width;
int height;
char bg;

float x;
float y;
float rad;

char *draw;
char type;
char color;

void output()
{
    int i = -1;

    while (++i < height)
    {
        write(1, draw + i * width, width);
        write(1, "\n", 1);
    }
    free(draw);
}

int check(float xw, float yh)
{
    float distance = sqrtf(powf(xw - x, 2) + powf(yh - y, 2));
    
    if (distance <= rad)
    {
        if (distance <= rad - 1)
            return(1);
        return(2);
    }
    return(0);
}

void drawing(void)
{
    int xw = -1;
    int yh = -1;
    int hit = -1;

    while (++xw < width)
    {
        yh = -1;
        while (++yh < height)
        {
            hit = check((float)xw, (float)yh);
            if (hit == 2 || (hit == 1 && type == 'C'))
                draw[xw + yh * width] = color;
        }
    }
}

int parseo(FILE *file)
{
    int scan_ret = 0;
    int i = 0;

    if (fscanf(file, "%d %d %c\n", &width, &height, &bg) != 3)
        return(1);
    if (width > 300 || width < 1 || height > 300 || height < 1)
        return(1);
    if ((draw = malloc(width * height)) == NULL)
        return(1);
    while (i < width * height)
        draw[i++] = bg;
    while ((scan_ret = fscanf(file, "%c %f %f %f %c\n", &type, &x, &y, &rad, &color)) == 5)
    {
        if (rad <= 0 || (type != 'c' && type != 'C'))
            return(1);
        drawing();
    }
    if (scan_ret != -1)
        return(1);
    output();
    return(0);
}

int main (int argc, char **argv)
{
    FILE *file;

    if (argc != 2)
    {
        write(1, "Error: argument\n", 16);
        return(1);
    }
    if (!(file = fopen(argv[1], "r")) || parseo(file))
    {
        write(1, "Error: Operation file corrupted\n", 32);
        return(1);
    }
    fclose(file);
    return(0);
}