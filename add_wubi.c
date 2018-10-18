#include<string.h>
#include<gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>
#include "add_wubi.h"
#define _MIN 99
int delete_wubi(const char *word)
{

  char buffer[100];
  char text[100];
  int i;
  FILE * wubi =fopen("/home/carl/.config/fcitx/rime/wubi86.dict.yaml","r");
  FILE * new_wubi =fopen("/home/carl/.config/fcitx/rime/wubi.dict.yaml","w");
  int len=strlen(word);
  int flag=0;
  strcpy(text,word);
  text[18]='\0';
  if(strcmp(text,"还没有这个词")==0||strcmp(text,"已删除这个词")==0
      ||strcmp(text,"至少输两个字")==0)
  {
    gtk_main_quit();
    exit(0); 
  }
  

  for (i=0;i<_MIN&&!feof(wubi);i++)
  {
    fgets(buffer,100,wubi);
    fputs(buffer,new_wubi);
  }
//查询词语是否已经存在
    while(fgets(buffer,100,wubi)!=NULL)
    {
      if(!flag&&buffer[len]=='	')
      {
        strcpy(text,buffer);
        text[len]='\0';
        if(strcmp(word,text)==0)
        {
          flag=1;
          continue;
        }
      }
      fputs(buffer,new_wubi);

    }
    fclose(wubi);
    fclose(new_wubi);
    remove("/home/carl/.config/fcitx/rime/wubi86.dict.yaml");
    rename("/home/carl/.config/fcitx/rime/wubi.dict.yaml","/home/carl/.config/fcitx/rime/wubi86.dict.yaml");
    return flag;
}
void copy(char * a,const char * b)
{
  int i;
  for (i=0;i<3;i++)
  {
    a[i]=b[i];
  }
  a[3]='\0';
  return ;
}
int add_wubi(const char * word,char * bm)
{
  char buffer[100];
  char text[40];
  char temp_word[5];//保存单个汉字用于比较
  char temp_buffer[5];//保存单个汉字用于比较
  int i,j;
  int flag=0;
  int len=strlen(word);
  FILE * wubi =fopen("/home/carl/.config/fcitx/rime/wubi86.dict.yaml","a+,css=UTF-8");

  strcpy(text,word);
  text[18]='\0';
  if(strcmp(text,"已存在，编码")==0||strcmp(text,"已保存，编码")==0
      ||strcmp(text,"至少输两个字")==0||strcmp(text,"未查询到编码")==0)
  {
    gtk_main_quit();
    exit(0); 
  }

  //
  //
  //一个汉字占三字节 utf-8
  for (i=0;i<_MIN&&!feof(wubi);i++)
  {
    fgets(buffer,100,wubi);
  }
//查询词语是否已经存在
    while(!feof(wubi))
    {
      fgets(buffer,100,wubi);
      if(buffer[len]=='	')
      {
        buffer[len]='\0';
        if(strcmp(word,buffer)==0)
        {
          for(i=0;buffer[len+i+1]!='	';i++)
          {
            bm[i]=buffer[len+i+1];
          }
          bm[i]='\0';
          fclose(wubi);
          strcpy(text,"已存在，编码");
          strcat(text,bm);
          strcpy(bm,text);
          return 0;
        }
      }
    }

    rewind(wubi);//成功把指针移到文件开头
    
    for (i=0;i<_MIN&&!feof(wubi);i++)
    {
      fgets(buffer,100,wubi);
    }

  //从99行查起
  //
  //
  if(len==6)
  {
    copy(temp_word,word);
    while(!feof(wubi))
    {
      fgets(buffer,100,wubi);
      copy(temp_buffer,buffer);
      if(strcmp(temp_word,temp_buffer)==0&&buffer[3]=='	')
      {
        bm[0]=buffer[4];
        bm[1]=buffer[5];
        break;
      }
    }

    if(feof(wubi))
      return 1;

    rewind(wubi);//成功把指针移到文件开头
    
    for (i=0;i<_MIN&&!feof(wubi);i++)
    {
      fgets(buffer,100,wubi);
    }
    


    copy(temp_word,&word[3]);
    while(!feof(wubi))
    {
      fgets(buffer,100,wubi);
      copy(temp_buffer,buffer);
      if(strcmp(temp_word,temp_buffer)==0&&buffer[3]=='	')
      {
        bm[2]=buffer[4];
        bm[3]=buffer[5];
        bm[4]='\0';
        break;
      }
    
    }
    if(feof(wubi))
      return 1;
    strcpy(buffer,word);
    strcat(buffer,"	");
    strcat(buffer,bm);
    strcat(buffer,"	");
    strcat(buffer,"50000000000\n");
    fputs(buffer,wubi);
    
  
  }
  else if(len==9)
  {
  
    for (j=0;j<2;j++)
    {
      copy(temp_word,&word[3*j]);
      while(!feof(wubi))
      {
        fgets(buffer,100,wubi);
        copy(temp_buffer,buffer);
        if(strcmp(temp_word,temp_buffer)==0&&buffer[3]=='	')
        {
          bm[j]=buffer[4];
          break;
        }
    
      }
      if(feof(wubi))
        return 1;


      rewind(wubi);//成功把指针移到文件开头
      
      for (i=0;i<_MIN&&!feof(wubi);i++)
      {
        fgets(buffer,100,wubi);
      }
    


    }





    copy(temp_word,&word[6]);
    while(!feof(wubi))
    {
      fgets(buffer,100,wubi);
      copy(temp_buffer,buffer);
      if(strcmp(temp_word,temp_buffer)==0&&buffer[3]=='	')
      {
        bm[2]=buffer[4];
        bm[3]=buffer[5];
        bm[4]='\0';
        break;
      }
    
    }
    if(feof(wubi))
      return 1;
    strcpy(buffer,word);
    strcat(buffer,"	");
    strcat(buffer,bm);
    strcat(buffer,"	");
    strcat(buffer,"50000000000\n");

    fputs(buffer,wubi);
    
  
  
  
  }
  else if(len>9)
  {
    for (j=0;j<3;j++)
    {
      copy(temp_word,&word[3*j]);
      while(!feof(wubi))
      {
        fgets(buffer,100,wubi);
        copy(temp_buffer,buffer);
        if(strcmp(temp_word,temp_buffer)==0&&buffer[3]=='	')
        {
          bm[j]=buffer[4];
          break;
        }
    
      }

      if(feof(wubi))
        return 1;

      rewind(wubi);//成功把指针移到文件开头
      
      for (i=0;i<_MIN&&!feof(wubi);i++)
      {
        fgets(buffer,100,wubi);
      }
    
      


    }




    copy(temp_word,&word[len-3]);
    while(!feof(wubi))
    {
      fgets(buffer,100,wubi);
      copy(temp_buffer,buffer);
      if(strcmp(temp_word,temp_buffer)==0&&buffer[3]=='	')//注意是最后一个字
      {
        bm[3]=buffer[4];
        bm[4]='\0';
        break;
      }
    
    }
    if(feof(wubi))
      return 1;
    strcpy(buffer,word);
    strcat(buffer,"	");
    strcat(buffer,bm);
    strcat(buffer,"	");
    strcat(buffer,"50000000000\n");

    fputs(buffer,wubi);
  
  
  }

  fclose(wubi);

  strcpy(text,"已保存，编码");
  strcat(text,bm);
  strcpy(bm,text);
  return 0 ;
}
