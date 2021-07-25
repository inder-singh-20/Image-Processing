#include <stdio.h>
#include <stdlib.h>
#define MAX_PIXEL 255

int main()
{   int i;
    FILE *fin=fopen("images/lena_color.bmp","rb");
    FILE *fout=fopen("images/lena_sepia1.bmp","wb");
     unsigned char header[54];
        unsigned char colortable[1024];
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
         int img_size=height*width;
        unsigned char buffer[img_size][3];
        int r,g,b;
        for(i=0;i<img_size;i++)
        {
            r=g=b=0;
            buffer[i][0]=getc(fin);
            buffer[i][1]=getc(fin);
            buffer[i][2]=getc(fin);

            r=(buffer[i][0]*0.393) + (buffer[i][1]*0.769) + (buffer[i][2]*0.189);
            g=(buffer[i][0]*0.349) + (buffer[i][1]*0.686) + (buffer[i][2]*0.168);
            b=(buffer[i][0]*0.272) + (buffer[i][1]*0.534) + (buffer[i][2]*0.131);

        if(r>MAX_PIXEL)
        {
            r=MAX_PIXEL;
        }
         if(g>MAX_PIXEL)

            {g=MAX_PIXEL;
        }
         if(b>MAX_PIXEL)
        {
            b=MAX_PIXEL;
        }
        putc(b,fout);
        putc(g,fout);
        putc(r,fout);
}
 fclose(fout);
 fclose(fin);
    return 0;
}
