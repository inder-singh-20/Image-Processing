#include <stdio.h>
#include <stdlib.h>
#include "mask.h"

#define BMP_READER 54
#define BMP_COLORTABLE 1024
#define CUSTOM_IMGSIZE 512*512

void imgreader(const char* imgname,int *height,int *width,int *depth,unsigned char* header,unsigned char* colortable,unsigned char* buf);
void imgwriter(const char* imgname,int depth,unsigned char* header,unsigned char* colortable,unsigned char* buf);
void line_detecter(unsigned char* inputdata,unsigned char* outputdata,int imgrows,int imgcols,int MASK[3][3]);

int main()
{   int imgwidth,imgheight,imgdepth;
   unsigned char header[BMP_READER];
   unsigned char colortable[BMP_COLORTABLE];
   unsigned char buf[CUSTOM_IMGSIZE];
   unsigned char buf2[CUSTOM_IMGSIZE];
   const char imgname[]="images/lena512.bmp";
   const char newimgname[]="images/cameraman_ldia.bmp";
   int VER[3][3]={{-1,2,-1},
                   {-1,2,-1},
                    {-1,2,-1}};
     int HOR[3][3]={{-1,-1,-1},
                     {2,2,2},
                     {-1,-1,-1}};
     int LDIA[3][3]={{-1,-1,2},
                    {-1,2,-1},
                    {2,-1,-1}};


    imgreader(imgname,&imgheight,&imgwidth,&imgdepth,&header[0],&colortable[0],&buf[0]);
    line_detecter(buf,buf2,imgwidth,imgheight,HOR);
//    convolve(imgheight,imgwidth,&lpmask,buf,buf2);
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
void line_detecter(unsigned char* inputdata,unsigned char* outputdata,int imgrows,int imgcols,int MASK[3][3])
{
    int x,y,i,j,sum;
    for(y=1;y<=imgrows-1;y++)
    {
        for(x=1;x<imgcols;x++)
        {
            sum=0;
            for(i=-1;i<=1;i++)
            {
                for(j=-1;j<=1;j++)
                {
                    sum=sum+ *(inputdata + x+i+ (long)(y+j)*imgcols)*MASK[i+1][j+1];
                }
            }
            if(sum>255) sum=255;
            if(sum<0) sum=0;
            *(outputdata + x + (long)y*(imgcols)) =sum;
        }
    }
}
