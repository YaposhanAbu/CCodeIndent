/******************************************************************************
*******************************我的第一个中小程序******************************
*******************************************************************************
************************************************************2021年3月1日*******
****************************************************************自家书房*****/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "smallFun.h"
FILE *fp;
char s[1000], word[30];

void commentHandle();
void normalHandle(int ntab);
void specialHandle(int ntab);
void switchHandle(int ntab);
void incompleteHandle(int ntab, int match);

void commentHandle(){
	while(getline(s, 1000, fp) > 0){
		printf("%s", s);
		if(anotherComment(s))
			return;
	}
}
void incompleteHandle(int ntab, int match){
	while(getline(s, 1000, fp) > 0){
		printTabs(ntab+2);
		noFrontSpacePrint(s);
		if((match += countLeftBrace(s)) == 0){
			if(lastLeftBigBrace(s))
				normalHandle(ntab+1);
			else if(( strcmp(word, "while") == 0
						|| strcmp(word, "if") == 0 
						|| strcmp(word, "for") == 0
						|| strcmp(word, "else") == 0) && !lastCharEnd(s))
				specialHandle(ntab+1);
			return;	
		}		
	}
}
void switchHandle(int ntab){
	int match;
	int end;
	while(getline(s, 1000, fp) > 0){
		end = endOfLine(s);
		getFirstKeyWord(s, word);
		if(s[end + 1] == '/' && s[end + 2] == '*'){
			printf("%s", s);
			commentHandle();
		}
		else{
			if((match = countLeftBrace(s)) > 0){
				printTabs(ntab);
				noFrontSpacePrint(s);
				incompleteHandle(ntab, match);
			}
			else{
				if(lastLeftBigBrace(s)){
					printTabs(ntab+1);
					noFrontSpacePrint(s);
					if(strcmp(word, "switch") == 0)
						switchHandle(ntab+2);
					else
						normalHandle(ntab+2);
				}
				else if(firstRightBigBrace(s)){
					printTabs(ntab - 1);
					noFrontSpacePrint(s);
					return;
				}
				else if((        strcmp(word, "while") == 0
											|| strcmp(word, "if") == 0 
											|| strcmp(word, "for") == 0
											|| strcmp(word, "else") == 0) &&  !lastCharEnd(s)
											){
					printTabs(ntab+1);
					noFrontSpacePrint(s);
					
					specialHandle(ntab+2);
				}
				else{
					if((strcmp(word, "case") == 0 || strcmp(word, "default") == 0))
						printTabs(ntab);
					else
						printTabs(ntab+1);
					noFrontSpacePrint(s);
				}
			}
		}
	}
}
void normalHandle(int ntab){
	int match;
	int end;
	while(getline(s, 1000, fp) > 0){
		getFirstKeyWord(s, word);
		end = endOfLine(s);
		if(s[end + 1] == '/' && s[end + 2] == '*'){
			printf("%s", s);
			commentHandle();
		}
		else{
			if((match = countLeftBrace(s)) > 0){
				printTabs(ntab);
			  noFrontSpacePrint(s);
				incompleteHandle(ntab,  match);
			}
			else{
				if(firstRightBigBrace(s)){
						printTabs(ntab - 1);
						noFrontSpacePrint(s);
						if(lastLeftBigBrace(s)){
							if(strcmp(word, "switch") == 0)
								switchHandle(ntab);
							else
								normalHandle(ntab);
						}
						else if((strcmp(word, "while") == 0
									|| strcmp(word, "if") == 0 
									|| strcmp(word, "for") == 0
									|| strcmp(word, "else") == 0) && !lastCharEnd(s)
									){
							specialHandle(ntab);
						}
						return;
				}
				else{
					if(lastLeftBigBrace(s)){
						printTabs(ntab);
						noFrontSpacePrint(s);
						if(strcmp(word, "switch") == 0)
							switchHandle(ntab+1);
						else
							normalHandle(ntab+1);
					}
		      else if( (strcmp(word, "while") == 0
									|| strcmp(word, "if") == 0 
									|| strcmp(word, "for") == 0
									|| strcmp(word, "else") == 0)  && !lastCharEnd(s)
																	){
						printTabs(ntab);
						noFrontSpacePrint(s);
						
						specialHandle(ntab+1);
					}
					else{
						printTabs(ntab);
						noFrontSpacePrint(s);
					}
				}
			}
		}
	}
}
void specialHandle(int ntab){
	int match;
	int end;
	if(getline(s, 1000, fp) > 0){
		getFirstKeyWord(s, word);
		end = endOfLine(s);
		if(s[end+1] == '/' && s[end+2] == '*'){
			printf("%s", s);
			commentHandle();
		}
		else{
			if((match = countLeftBrace(s)) > 0){
				printTabs(ntab);
				noFrontSpacePrint(s);
				incompleteHandle(ntab,  match);
			}
			else{
				if(lastLeftBigBrace(s)){
				
					if(strcmp(word, "{") == 0){
						printTabs(ntab - 1);
						noFrontSpacePrint(s);
						normalHandle(ntab);
					}
					else{
						printTabs(ntab);	
						noFrontSpacePrint(s);
						if(strcmp(word, "switch") == 0)
							switchHandle(ntab+1);
						else
							normalHandle(ntab+1);
					}
				}
				else if( (strcmp(word, "while") == 0
									|| strcmp(word, "if") == 0 
									|| strcmp(word, "for") == 0
									|| strcmp(word, "else") == 0) && !lastCharEnd(s)
																			){
					printTabs(ntab);
					noFrontSpacePrint(s);
					
					specialHandle(ntab+1);
				}
				else{
					printTabs(ntab);
					noFrontSpacePrint(s);
				}
			}
		}
	}
}
/*
这个400多行的代码花了好长时间啊
不过最后也还算成功，嘻嘻
*/

int main(int argc, char**argv){
	fp = fopen(argv[1], "r");
	int ntab = 0;
	int match;
	int end;
	while(getline(s, 1000, fp) > 0){
		/*
		首先得读取头单词
		你懂的
		*/
		getFirstKeyWord(s, word);
		end = endOfLine(s);
		if(s[end+1] == '/' && s[end+2] == '*'){
			printTabs(ntab);
			noFrontSpacePrint(s);
			commentHandle();
		}
		else{
			if((match = countLeftBrace(s)) > 0){//handle the incpmplete line
				printTabs(ntab);
				noFrontSpacePrint(s);
				incompleteHandle(ntab,  match);
			}
			else{//handle the complete line
				if(lastLeftBigBrace(s)){
					printTabs(ntab);
					noFrontSpacePrint(s);
					if( strcmp(word, "switch") == 0)
						switchHandle(ntab+1);
					else
						normalHandle(ntab+1);
				}
				else if( (strcmp(word, "while") == 0
								|| strcmp(word, "if") == 0 
								|| strcmp(word, "for") == 0
								|| strcmp(word, "else") == 0) && !lastCharEnd(s)
																			){
					printTabs(ntab);
					noFrontSpacePrint(s);
					specialHandle(ntab+1);
				}
				else{
					printTabs(ntab);
					noFrontSpacePrint(s);
				}
			}
		}
	}
	fclose(fp);
	return 0;
}