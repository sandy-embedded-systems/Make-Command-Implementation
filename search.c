#ifndef _SEARCH 
#define _SEARCH
char *search_file(void){
	static char file_name[30];
	_Bool flag=1;
	DIR *handler=NULL;
	handler=opendir(".");
	struct dirent *p=NULL;
	while(p=readdir(handler)){
		if(strcmp(p->d_name,"makefile")==0){
			strcpy(file_name,"makefile");
			flag=0;
			break;
		}
		else if(strcmp(p->d_name,"Makefile")==0){
			strcpy(file_name,"Makefile");
			flag=0;
			break;
		}
	}
	if(flag){
		return NULL;
	}
	else return file_name;
}
#endif
