#include <stdio.h>
#include <stdlib.h>
#define BMP_READER 54
#define BMP_COLORTABLE 1024
#define CUSTOM_IMGSIZE 1024*1024

void imgreader(const char* imgname,int *height,int *width,int *depth,unsigned char* header,unsigned char* colortable,unsigned char* buf)
{
    int i;
    FILE *ptr;
    ptr=fopen(imgname,"rb");
    if(ptr==NULL)
    {
        printf("FILE NOT FOUND\n");
    }
    for(i=0;i<54;i++)
    {
        header[i]=getc(ptr);
    }

     *width=*(int*)&header[18];
     *height=*(int*)&header[22];
     *depth=*(int*)&header[28];
    if(*depth<=8)
    {
        fread(colortable,sizeof(unsigned char),1024,ptr);
    }
    fread(buf,sizeof(unsigned char),CUSTOM_IMGSIZE,ptr);
    fclose(ptr);
}
void imgwriter(const char* imgname,int depth,unsigned char* header,unsigned char* colortable,unsigned char* buf)
{
    FILE *fo=fopen(imgname,"wb");
    fwrite(header,sizeof(unsigned char),54,fo);

      if(depth<=8)
    {
        fwrite(colortable,sizeof(unsigned char ),1024,fo);
    }
    fwrite(buf,sizeof(unsigned char),CUSTOM_IMGSIZE,fo);
    fclose(fo);
}
int main()
{
   int imgwidth,imgheight,imgdepth;
   unsigned char header[BMP_READER];
   unsigned char colortable[BMP_COLORTABLE];
   unsigned char buf[CUSTOM_IMGSIZE];
   const char imgname[]="images/cameraman.bmp";
   const char newimgname[]="images/cameraman_copy.bmp";
   imgreader(imgname,&imgheight,&imgwidth,&imgdepth,&header[0],&colortable[0],&buf[0]);
   imgwriter(newimgname,imgdepth,header,colortable,buf);
   printf("SUCCESS\n");
    return 0;
}
