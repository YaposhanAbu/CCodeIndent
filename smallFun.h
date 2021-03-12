#ifndef SMALLFUN_H
#define SMALLFUN_H
typedef int bool;
int getline(char*, int, FILE *);
int endOfLine(char *);
bool lastCharEnd(char *);
void noFrontSpacePrint(char *);
bool lastLeftBigBrace(char *);
bool firstRightBigBrace(char *);
void getFirstKeyWord(char line[], char word[]);
int countLeftBrace(char *);
bool anotherComment(char *);
void printTabs(int);
#endif
