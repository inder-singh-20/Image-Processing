#include <stdio.h>
#include <stdlib.h>
#define BMP_READER 54
#define BMP_COLORTABLE 1024
#define CUSTOM_IMGSIZE 512*512

void correct_brightness(unsigned char* inputdata,unsigned char* outputdata,int imgrows,int imgcols,int brightness);
void imgwriter(const char* imgname,int depth,unsigned char* header,unsigned char* colortable,unsigned char* buf);
void imgreader(const char* imgname,int* height,int* width,int* depth,unsigned char* header,unsigned char* colortable,unsigned char* buf);

void imgreader(const char* imgname,int* height,int* width,int* depth,unsigned char* header,unsigned char* colortable,unsigned char* buf)
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
    * width=*(int*)&header[18];
    * height=*(int*)&header[22];
    * depth=*(int*)&header[28];
    if(* depth<=8)
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

void correct_brightness(unsigned char* inputdata,unsigned char* outputdata,int imgrows,int imgcols,int brightness)
{
    int x,y,i;
    for(y=0;y<imgrows;y++)
    {
        for(x=0;x<imgcols;x++)
        {
           i =*(inputdata + x + y*imgcols) + brightness;
        if(i>255)
         {i=255;}
        if(i<0)
            {i=0;}

        *(outputdata + x + y*imgcols)=i;
    }
    }
}
int main()
{
   int imgwidth,imgheight,imgdepth;
   unsigned char header[BMP_READER];
   unsigned char colortable[BMP_COLORTABLE];
   unsigned char buf[CUSTOM_IMGSIZE];
   unsigned char buf2[CUSTOM_IMGSIZE];
   const char imgname[]="images/girlface.bmp";
   const char newimgname[]="images/girlface_bright.bmp";
   imgreader(imgname,&imgheight,&imgwidth,&imgdepth,&header[0],&colortable[0],&buf[0]);
   correct_brightness(buf,buf2,imgheight,imgwidth,100);
   imgwriter(newimgname,imgdepth,header,colortable,buf2);
   return 0;
}
