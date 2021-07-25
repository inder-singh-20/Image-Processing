#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fin=fopen("images/lena_color.bmp","rb");
    FILE *fout=fopen("images/lena_blur.bmp","wb");
    unsigned char header[54];
    unsigned char colortable[1024];
    int i,j;
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
    int x,y;
    unsigned char buffer[imgsize][3];
    unsigned char buffer2[imgsize][3];
    for(i=0;i<imgsize;i++)
    {
        buffer[i][2]=getc(fin);
        buffer[i][1]=getc(fin);
        buffer[i][0]=getc(fin);
    }
    float kernel[3][3]={ {1.0/9.0,1.0/9.0,1.0/9.0},
                         {1.0/9.0,1.0/9.0,1.0/9.0},
                         {1.0/9.0,1.0/9.0,1.0/9.0}
                         };
    for(x=1;x<height-1;x++)
    {
        for(y=0;y<width-1;y++)
        {
            float sum0=0.0;
            float sum1=0.0;
            float sum2=0.0;
            for(i=-1;i<=1;i++)
            {
                for(j=-1;j<=1;j++)
                {
                    sum0=sum0 + (float)kernel[i+1][j+1]*buffer[(x+i)*width + (y+j)][0];
                    sum1=sum1 + (float)kernel[i+1][j+1]*buffer[(x+i)*width + (y+j)][1];
                    sum2=sum2 + (float)kernel[i+1][j+1]*buffer[(x+i)*width + (y+j)][2];
                }
                buffer2[(x)*width + y][0]=sum0;
                buffer2[(x)*width + y][1]=sum1;
                buffer2[(x)*width + y][2]=sum2;
            }
        }
    }
  for(int i=0;i<imgsize;i++)
  {
      putc(buffer2[i][2],fout);
      putc(buffer2[i][1],fout);
      putc(buffer2[i][0],fout);
  }
  fclose(fout);
  fclose(fin);
    return 0;
}
