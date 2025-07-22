#ifndef _MAKE_LINE
#define _MAKE_LINE
_Bool status_file(const char *file){
	struct stat f;
	if(stat(file,&f)==-1) return 0;
	else return 1;
}
void make_target_1line(int create){
	struct stat o_file,c_file;     /* cc -c -o main.c main.o*/
	int fd,flag=1,flag2=1,run=1;
	char *p=arg[0],name[20],cc[10]="cc -c -o ",cmd[30];
	p=strchr(p,':');
	p++;
	while(*p==' ') p++;
	for(;p=strtok(p," ");){
		strcpy(name,p);
		if(strstr(name,".c")){
			if(status_file(name)){
				p=NULL;
				continue;
			}
			else{
				printf("make: *** No rule to make target '%s', needed by 'a.out'.  Stop.\n",p);
				exit(0);
			}
		}
		else if(strstr(name,".o")){
			name[strlen(name)-1]='c';
			if(!status_file(name)){
				printf("make: *** No rule to make target '%s', needed by 'a.out'.  Stop.\n",p);
				exit(0);
			}
			else{
				if(!status_file(p)){
					strcpy(cmd,cc);
					strcat(cmd," ");
					strcat(cmd,p);
					strcat(cmd," ");
					strcat(cmd,name);
					printf("%s\n",cmd);
					if(system(cmd)!=0){
						printf("<builtin>: recipe for target '%s' failed\n",p);
            printf("make: *** [%s] Error 1\n",p);
            exit(0);
					}
					flag=0;
				}
				else{
					run=0;
					stat(p,&o_file);
					stat(name,&c_file);
					if(c_file.st_mtime>o_file.st_mtime){
						strcpy(cmd,cc);
        	  strcat(cmd," ");
            strcat(cmd,p);
            strcat(cmd," ");
            strcat(cmd,name);
						printf("%s\n",cmd);
            if(system(cmd)!=0){
							printf("<builtin>: recipe for target '%s' failed\n",p);
							printf("make: *** [%s] Error 1\n",p);
							exit(0);
						}
						flag=0;
						flag2=1;
					}
				}
			}
		}
		p=NULL;
	}
	if(status_file("a.out")==0){
		strcpy(cmd,arg[1]);
		printf("%s\n",cmd+1);
		system(cmd);
		flag2=0;
	}
	if(flag && create==0) printf("make: Nothing to be done for 'a.out'.\n"); 
	if(create){
		strcpy(cmd,arg[1]);
		printf("%s\n",cmd+1);
		system(cmd);
	}
	return;
}
#endif
