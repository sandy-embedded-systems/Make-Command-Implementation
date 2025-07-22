/* This is the file inplementation file */

#include"header.h"
void creat_target(void);
int main(){
	char *_file=NULL;
	int fd,i=0;
	_file=search_file();
	if(_file==NULL){
		printf("make: *** No targets specified and no makefile found.  Stop.\n");
		exit(0);
	}
	lines=find_lines(_file);
	fd=open(_file,O_RDONLY);
	while(i<lines){
		getlines(fd,i);
		if(i%2==0) check_seperator(i);
		else if(i%2!=0) check_syntax(i);
		i++;
	}
	creat_target();
	if(lines==1){
		make_target_1line(0);
	}
	else if(lines==2){
		make_target_1line(1);
	}
	else make_target();
	return 0;
}
void check_syntax(int i){
	if(arg[i][0]!='\t'){
		printf("makefile:%d: *** missing separator.  Stop.\n",i+1);
		exit(0);
	}
}
void check_seperator(int l){
	char ch;
	if(strchr(arg[l],':')==NULL){
		printf("makefile:%d: *** missing separator.  Stop.\n",l+1);
		exit(0);
	}
}
void getlines(int fd,int i)
{
	char str[100],ch,j=0;
	do{
		read(fd,&ch,1);
		str[j++]=ch;
	}while(ch!='\n');
	str[j-1]='\0';
	arg[i]=calloc(strlen(str)+1,1);
	strcpy(arg[i],str);
}
void creat_target(void){
	int j=0;
	char ch;
	while((ch=arg[0][j])!=':'){
		target_file[j++]=ch;
	}
}
