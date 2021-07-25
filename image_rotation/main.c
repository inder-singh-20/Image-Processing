#include <stdio.h>
#include <stdlib.h>

int main()
{   int i,ch,j;
    FILE* fin=fopen("images/cameraman.bmp","rb");
    FILE* fout=fopen("images/cameraman_7.bmp","wb");
    //FILE* fout=fopen("images/cameraman_rotate2.bmp","wb");
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
    unsigned char buffer[width][height];
    unsigned char buffer2[width][height];
    fread(buffer,sizeof(unsigned char),img_size,fin);
    printf("ENTER ROTATION DIRECTIONS\n");

    printf("1 : ROTATE RIGHT\n");
    printf("2 : ROTATE LEFT\n");
    printf("3 : ROTATE 180\n");
    printf("4 : QUIT\n\n");
    printf("ENTER YOUR CHOICE\n");
    scanf("%d",&ch);
    switch(ch)
    {
    case 1:
        for(i=0;i<width;i++)
        {
            for(j=0;j<height;j++)
            {
                buffer2[j][height-1-i]=buffer[i][j];
            }
        }
        break;
    case 2:
       for(i=0;i<width;i++)
        {
            for(j=0;j<height;j++)
            {
                buffer2[j][i]=buffer[i][j];
            }
        }
        break;
    case 3:
          for(i=0;i<width;i++)
        {
            for(j=0;j<height;j++)
            {
                buffer2[width-i][j]=buffer[i][j];
            }
        }
        break;
    case 4:exit(1);
    default:printf("INVALID INPUT\n");
    }
    fwrite(buffer2,sizeof(unsigned char),img_size,fout);
    printf("ROTATED SUCCESSFULLY\n");
    fclose(fin);
    fclose(fout);

}
