#include <stdio.h>
#include <stdlib.h>
#define MAX_COLOR 255
#define BRIGHTNESS_FACTOR 150

int main()
{  int i;
    FILE *fin=fopen("images/lena512.bmp","rb");
    FILE *fout=fopen("images/lena_bright3.bmp","wb");
    unsigned char header[54];
    unsigned char colortable[1024];
    if(fin==NULL)
    {
        printf("FILE NOT FOUND\n");
    }
    for(i=0;i<54;i++)
    {
        header[i]=getc(fin);
    }
    fwrite(header,sizeof(unsigned char),54,fout);
    int height=*(int*)&header[22];
    int width=*(int*)&header[18];
    int depth=*(int*)&header[28];
    if(depth<=8)
    {
        fread(colortable,sizeof(unsigned char),1024,fin);
        fwrite(colortable,sizeof(unsigned char),1024,fout);
    }
    int imgsize=height*width;
    unsigned char buffer[imgsize];
    fread(buffer,sizeof(unsigned char),imgsize,fin);
    for(i=0;i<imgsize;i++)
    {
        int temp;
        temp=buffer[i] + BRIGHTNESS_FACTOR ;
        buffer[i]=(temp>MAX_COLOR)?MAX_COLOR:temp;
    }
    fwrite(buffer,sizeof(unsigned char),imgsize,fout);
    fclose(fin);
    fclose(fout);
    return 0;
}
