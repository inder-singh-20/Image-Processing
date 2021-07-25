#include <stdio.h>
#include <stdlib.h>

int main()
{       int i;
        FILE* fin=fopen("images/lena_color.bmp","rb");
        FILE* fout=fopen("images/lena_grey.bmp","wb");
        unsigned char header[54];
        unsigned char colortable[1024];
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
        int img_size=height*width;
        unsigned char buffer[img_size][3];
      //  fread(buffer,sizeof(unsigned char),img_size,fin);
        for(i=0;i<img_size;i++)
        {   buffer[i][0]=getc(fin);
            buffer[i][1]=getc(fin);
            buffer[i][2]=getc(fin);
            int temp=0;
            temp=(buffer[i][0]*0.3) + (buffer[i][1]*0.59) + (buffer[i][2]*0.11);
            putc(temp,fout);
            putc(temp,fout);
            putc(temp,fout);

        }
        fwrite(buffer,sizeof(unsigned char),img_size,fin);
    fclose(fin);
    fclose(fout);
    return 0;
}
