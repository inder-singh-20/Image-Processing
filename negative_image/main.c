#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fin=fopen("images/girlface.bmp","rb");

    unsigned char *imgdata;
    unsigned char *newimgdata;
    unsigned char header[54];
    unsigned char colortable[1024];

    fread(header,sizeof(unsigned char),54,fin);

    int i,j;
    int height=*(int*)&header[22];
    int width=*(int*)&header[18];
    int depth=*(int*)&header[28];
    int imgdatasize=width*height;

    imgdata=(unsigned char *)malloc(imgdatasize*sizeof(unsigned char));
    newimgdata=(unsigned char *)malloc(imgdatasize*sizeof(unsigned char));


    if(depth<=8)
    {
        fread(colortable,sizeof(unsigned char),1024,fin);

    }
      fread(imgdata,sizeof(unsigned char),imgdatasize,fin);

    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            newimgdata[i*width + j]=255-imgdata[i*width + j];
        }
    }
      FILE *fout=fopen("images/girlface_negative.bmp","wb");
      fwrite(header,sizeof(unsigned char),54,fout);
      if(depth<=8)
      {fwrite(colortable,sizeof(unsigned char),1024,fout);
      }
    fwrite(newimgdata,sizeof(unsigned char),imgdatasize,fout);
    printf("SUCCESS\n");
    fclose(fout);
    fclose(fin);
}

