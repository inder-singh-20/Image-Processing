#include <stdio.h>
#include <stdlib.h>
#define BMP_READER 54
#define BMP_COLORTABLE 1024
#define CUSTOM_IMGSIZE 512*512
void imghistogram(unsigned char * imgdata,int imgrows,int imgcols,float hist[]);
void imgreader(const char* imgname,int* height,int* width,int* depth,unsigned char* header,unsigned char* colortable,unsigned char* buf);
void imgwriter(const char* imgname,int depth,unsigned char* header,unsigned char* colortable,unsigned char* buf);
void imghistogramequalization(unsigned char* inputdata,unsigned char * outputdata,int imgrows,int imgcols);

float IMG_HIST[255];
int main()
{
   int imgwidth,imgheight,imgdepth;
   unsigned char imgheader[BMP_READER];
   unsigned char colortable[BMP_COLORTABLE];
   unsigned char buf[CUSTOM_IMGSIZE];
   unsigned char buf2[CUSTOM_IMGSIZE];
   const char imgname[]="images/lena_dark.bmp";
   const char newimgname[]="images/lena_equalized.bmp";

   imgreader(imgname,&imgheight,&imgwidth,&imgdepth,&imgheader[0],&colortable[0],&buf[0]);
   //imghistogram(&buf[0],imgheight,imgwidth,&IMG_HIST[0]);
   imghistogramequalization(&buf[0],&buf2[0],imgheight,imgwidth);
   imgwriter(newimgname,imgdepth,imgheader,colortable, buf2);

    return 0;
}
void imghistogram(unsigned char * imgdata,int imgrows,int imgcols,float hist[])
{  FILE* ptr=fopen("image_hist.txt","w");
   int x,y,i,j;
   long int ihist[255];
   long int sum;
    for(i=0;i<255;i++)
    {
        ihist[i]=0;
    }
    sum=0;
    for(y=0;y<imgrows;y++)
    {
        for(x=0;x<imgcols;x++)
        {
            j=*(imgdata+x+ y*imgcols);
            ihist[j]=ihist[j] + 1;
            sum=sum+1;
        }
    }
    for(i=0;i<255;i++)
    {
        hist[i]=(float)ihist[i]/(float)sum;
    }
    for(i=0;i<255;i++)
    {
        fprintf(ptr,"\n%f",hist[i]);
    }
    fclose(ptr);
}
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
        fwrite(colortable,sizeof(unsigned char ),CUSTOM_IMGSIZE,fo);
    }
    fwrite(buf,sizeof(unsigned char),CUSTOM_IMGSIZE,fo);
    fclose(fo);
}
void imghistogramequalization(unsigned char* inputdata,unsigned char * outputdata,int imgrows,int imgcols)
{
    int x,y,i,j;
    float histeq[256];
    float hist[256];
    float sum;
    imghistogram(&inputdata[0],imgrows,imgcols,&hist[0]);

    for(i=0;i<255;i++)
    {
        sum=0.0;
    for(j=0;j<i;j++)
    {
        sum=sum+ hist[j];
    }
    histeq[i]=(int)(255*sum +0.5);
}
for(y=0;y<imgrows;y++)
{
    for(x=0;x<imgcols;x++)
    {
        *(outputdata + x + y*imgcols)=histeq[*(inputdata + x + y*imgcols)];
    }
}
}
