#include <stdio.h>
#include <stdlib.h>
#include "mask.h"

#define BMP_READER 54
#define BMP_COLORTABLE 1024
#define CUSTOM_IMGSIZE 256*256

void imgreader(const char* imgname,int *height,int *width,int *depth,unsigned char* header,unsigned char* colortable,unsigned char* buf);
void imgwriter(const char* imgname,int depth,unsigned char* header,unsigned char* colortable,unsigned char* buf);
void convolve(int imrows,int imgcols,struct mask* mymask,unsigned char* inputbuf,unsigned char* outputbuf);

void convolve(int imgrows,int imgcols,struct mask *mymask,unsigned char* inputbuf,unsigned char* outputbuf)
{
    long i,j,m,n,idx,jdx;
    int ms,im,val;
    unsigned char* temp;
    for(i=0;i<imgrows;i++)
        for(j=0;j<imgcols;j++)
            {val=0;
            for(m=0;m<mymask->rows;m++)

                for(n=0;n<mymask->cols;n++)
                    {ms=(signed char)*(mymask->data + m*mymask->rows + n);
                    idx=i-m;
                    jdx=j-n;
                    if(idx>=00&&jdx>=0)
                        im=*(inputbuf + idx*imgrows + jdx);
                    val+=ms*im;
            }
            if(val>255) val=255;
            if(val<0) val =0;
            temp=outputbuf + i*imgrows +j;
            *temp=(unsigned char)val;
    }
}
int main()
{   int imgwidth,imgheight,imgdepth;
   unsigned char header[BMP_READER];
   unsigned char colortable[BMP_COLORTABLE];
   unsigned char buf[CUSTOM_IMGSIZE];
   unsigned char buf2[CUSTOM_IMGSIZE];
   const char imgname[]="images/cameraman.bmp";
   const char newimgname[]="images/cameraman_new.bmp";
   struct mask lpmask;
   signed char *tmp;
   int i;

   lpmask.cols=lpmask.rows=5;
   lpmask.data=(unsigned char*)malloc(25);

   ///set mask values to -1
   tmp=(signed char*)lpmask.data;
   for(i=0;i<25;i++)
   {
       *tmp=-1;
       tmp++;
   }
   tmp=(signed char*)lpmask.data + 13;
   *tmp=24;
    imgreader(imgname,&imgheight,&imgwidth,&imgdepth,&header[0],&colortable[0],&buf[0]);
    convolve(imgheight,imgwidth,&lpmask,buf,buf2);
    imgwriter(newimgname,imgdepth,header,colortable,buf2);
    return 0;
}
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
