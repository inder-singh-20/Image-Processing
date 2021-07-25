#include <stdio.h>
#include <stdlib.h>
#define WHITE 255
#define BLACK 0
#define THRESHHOLD 150

int main()
{
    FILE* fin=fopen("images/lighthouse.bmp","rb");
    FILE* fout=fopen("images/lighthouse_bw1.bmp","wb");
    unsigned char header[54];
    unsigned char colortable[1024];
    if(fin==NULL)
    {
        printf("FILE NOT FOUND\n");
    }
    for(int i=0;i<54;i++)
    {
        header[i]=getc(fin);
    }
    fwrite(header,sizeof(unsigned char),54,fout);
    int height=*(int*)&header[22];
    int width=*(int*)&header[18];
    int depth=*(int*)&header[28];

    int imgsize=height*width;
    if(depth<=8)
    {
        fread(colortable,sizeof(unsigned char),1024,fin);
        fwrite(colortable,sizeof(unsigned char),1024,fout);
    }
    unsigned char buffer[imgsize];
    fread(buffer,sizeof(unsigned char),imgsize,fin);

    for(int i=0;i<imgsize;i++)
    {
        buffer[i]=(buffer[i]>THRESHHOLD)?WHITE:BLACK;
    }
    fwrite(buffer,sizeof(unsigned char),imgsize,fout);
    fclose(fin);
    fclose(fout);
    return 0;
}
