#include <stdio.h>
#include <ctype.h>
#include "smallFun.h"
int getline(char *line, int lim, FILE *fp){
  int i;
  int c;
  for(i = 0; i < lim - 1 && (c = getc(fp)) != EOF && c != '\n'; i++)
    line[i] = c;
  if(c == '\n')
    line[i++] = c;
  line[i] = '\0';
  return i;
}
int endOfLine(char line[]){
  int i, rt;
  i = 0;
  while(1){
    switch(line[i]){
      case '/':
        switch(line[i+1]){
          case '/':
            return i - 1;
          case '*':
            rt = i;
            i += 2;
            Pre:
            while(line[i] != '\0' && line[i] != '*')
              i++;
            if(line[i] == '\0')
              return rt - 1;
            i++;
            while(line[i] == '*')
              i++;
            if(line[i] == '\0')
              return rt - 1;
            if(line[i] == '/'){
              i++;
              break;				
            }
            else{
              i++;
              goto Pre;
            }
          default:
            i++;
            break;
        }
        break;
      case '\'': 
        rt = i;
        i++;
        while(line[i] != '\0' && line[i] != '\''){
          if(line[i] == '\\')
            i++;
          i++;
        }
        if(line[i] == '\0')
          return rt;
        i++;
        break;
      case '\"':
        rt = i;
        i++;
        while(line[i] != '\0' && line[i] != '\"'){
          if(line[i] == '\\')
            i++;
          i++;
        }
        if(line[i] == '\0')
          return rt;
        i++;
        break;
      case '\0':
        return i - 1;
      default:
        i++;
        break;
    }
  }
}
bool lastCharEnd(char *line){
  int i = endOfLine(line);
  if(i == -1)
    return 0; 
  while(i >= 0 && isspace(line[i]))
    i--;
  if(i == -1)
    return 0; 
  return (line[i] == '}' || line[i] == ';') ?  1 : 0;
}
/*
char* trimFrontSpace(char *line){//去除前导空白
	int i, j;
	for(j = 0; (line[j] == ' ' || line[j] == '\t') ; j++)
		;
	for(i = 0; line[j] != '\n'; i++, j++)
		line[i] = line[j];
	line[i] = line[j];
	line[i+1] = '\0';
	return line;
}*/
void noFrontSpacePrint(char *line){
  char *p = line; 
  while(*p == ' ' || *p == '\t')
    p++; 
  printf("%s", p); 
}
bool lastLeftBigBrace(char *line){//最右边是不是'{'
  char last = ' ';
  int i = 0;
  while(1){
    switch(line[i]){
      case '/':
        switch(line[i+1]){
          case '/':
            goto L1;
          case '*':
            i += 2;
            Pre:
            while(line[i] != '\0' && line[i] != '*')
              i++;
            if(line[i] == '\0')
              goto L1;
            i++;
            while(line[i] == '*')
              i++;
            if(line[i] == '\0')
              goto L1;
            if(line[i] == '/'){
              i++;
              break;
            }
            else{
              i++;
              goto Pre;
            }				
          default:
            i++;
            break;
        }
        break;
      case '\'': 
        i++;
        while(line[i] != '\0' && line[i] != '\''){
          if(line[i] == '\\')
            i++;
          i++;
        }
        if(line[i] == '\0')
          goto L1;
        i++;
        break;
      case '\"':
        i++;
        while(line[i] != '\0' && line[i] != '\"'){
          if(line[i] == '\\')
            i++;
          i++;
        }
        if(line[i] == '\0')
          goto L1;
        i++;
        break;
      case '}':case '{':
        last = line[i];
        i++;
        break;
      case '\0':
        goto L1;
      default:
        i++;
        break;
    }
  }
  L1: 
  return last == '{' ? 1 : 0; 
}
bool firstRightBigBrace(char *line){//右大括号
  int i = 0;
  int match = 0;
  while(1){
    switch(line[i]){
      case '/':
        switch(line[i+1]){
          case '/':
            return 0;
          case '*':
            i += 2;
            Pre:
            while(line[i] != '\0' && line[i] != '*')
              i++;
            if(line[i] == '\0')
              return 0;
            i++;
            while(line[i] == '*')
              i++;
            if(line[i] == '\0')
              return 0;
            if(line[i] == '/'){
              i++;
              break;
            }
            else{
              i++;
              goto Pre;
            }				
          default:
            i++;
            break;
        }
        break;
      case '\'': 
        i++;
        while(line[i] != '\0' && line[i] != '\''){
          if(line[i] == '\\')
            i++;
          i++;
        }
        if(line[i] == '\0')
          return 0;
        i++;
        break;
      case '\"':
        i++;
        while(line[i] != '\0' && line[i] != '\"'){
          if(line[i] == '\\')
            i++;
          i++;
        }
        if(line[i] == '\0')
          return 0;
        i++;
        break;
      case '}':
        if(match == 0)
          return 1;
        else{
          match--;
          i++;
        }
        break;
      case '{':
        match++;
        i++;
        break;
      case '\0':
        return 0;
      default:
        i++;
        break;
    }
  }
}

void getFirstKeyWord(char line[], char word[]){//判断一行语句的第一个关键词
  int i = 0;
  int j = 0;
  char c;
  Pre:
  while(line[i] == ' ' || line[i] == '\t')
    i++;
  if(isalpha(line[i]) || line[i] == '_'){
    word[j++] = line[i++];
    while(isalnum(line[i]) || line[i] == '_')
      word[j++] = line[i++];
    word[j] = '\0';
  } 
  else{
    switch(line[i]){
      case '/':
        switch(line[i+1]){
          case '/':
            goto End;
          case '*':
            i += 2;
            L1:
            while(line[i] != '\0' && line[i] != '*')
              i++;
            if(line[i] == '\0')
              goto End;
            i++;
            while(line[i] == '*')
              i++;
            if(line[i] == '\0')
              goto End;
            if(line[i] == '/'){
              i++;
              goto Pre;
            }
            else{
              i++;
              goto L1;
            }
          default:
            word[j++] = line[i];
            goto End;
        }
        break;
      case '\0':
        goto End;
      default:
        word[j++] = line[i];
        goto End;
    }
    
    
  }
  End: 
  word[j] = '\0';
}
int countLeftBrace(char line[]){
  int match = 0;
  int i = 0;
  while(1){
    switch(line[i]){
      case '/':
        switch(line[i+1]){
          case '/':
            return match;
          case '*':
            i += 2;
            Pre:
            while(line[i] != '\0' && line[i] != '*')
              i++;
            if(line[i] == '\0')
              return match;
            i++;
            while(line[i] == '*')
              i++;
            if(line[i] == '\0')
              return match;
            if(line[i] == '/'){
              i++;
              break;
            }
            else{
              i++;
              goto Pre;
            }				
          default:
            i++;
            break;
        }
        break;
      case '\'': 
        i++;
        while(line[i] != '\0' && line[i] != '\''){
          if(line[i] == '\\')
            i++;
          i++;
        }
        if(line[i] == '\0')
          return match;
        i++;
        break;
      case '\"':
        i++;
        while(line[i] != '\0' && line[i] != '\"'){
          if(line[i] == '\\')
            i++;
          i++;
        }
        if(line[i] == '\0')
          return match;
        i++;
        break;
      case '(':
        match++;
        i++;
        break;
      case ')':
        match--;
        i++;
        break;
      case '\0':
        return match;
      default:
        i++;
        break;
    }
  }
}
bool anotherComment(char line[]){
  int i;
  for(i = 0; line[i] != '\0'; i++){
    if(line[i] == '*'){
      i++;
      while(line[i] == '*')
        i++;
      if(line[i] == '/')
        return 1;
      if(line[i] == '\0')
        return 0;	
    }
  }
  return 0;
}

void printTabs(int n){//打印n个tab，实则以空格代替
  for(int i = 0; i < n; i++){
    putchar(' ');
    putchar(' ');
  }
}
