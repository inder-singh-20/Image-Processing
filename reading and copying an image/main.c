#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *ptr=fopen("images/cameraman.bmp","rb");
    FILE *fo=fopen("images/cameraman_copy.bmp","wb");
    if(ptr==(FILE*)0)
    {
        printf("FILE NOT FOUND\n");
    }
    unsigned char header[54];///IMAGE HEADER
    unsigned char colorTable[1024];

    for(int i=0;i<54;i++)
    {
        header[i]=getc(ptr);
    }
    int width=*(int*)&header[18];
    int height=*(int*)&header[22];
    int depth=*(int*)&header[28];
    if(depth<=8)
    {
        fread(colorTable,sizeof(unsigned char),1024,ptr);
    }
    fwrite(header,sizeof(unsigned char),54,fo);
    unsigned char buf[height*width];

    fread(buf,sizeof(unsigned char),(height*width),ptr);
    if (depth<=8)
    {
        fwrite(colorTable,sizeof(unsigned char),1024,fo);
    }
    fwrite(buf,sizeof(unsigned char),(height*width),fo);
    fclose(fo);
    fclose(ptr);
    printf("\nSUCCESS\n");

    printf("\nWIDTH::%d\n",width);
    printf("\nHEIGHT::%d\n",height);
    }

