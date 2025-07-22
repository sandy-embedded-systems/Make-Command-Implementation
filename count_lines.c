/* This file will return How many lines are there in Makefile/makefile */

#ifndef _LINES
#define _LINES
unsigned long int find_lines(char *file_name)
{
	FILE *fp=NULL;
	fp=fopen(file_name,"r");
	unsigned long int cnt=0;
	char ch;
	while((ch=fgetc(fp))!=EOF){
		if(ch=='\n') cnt++;
	}
	return cnt;
}
#endif
