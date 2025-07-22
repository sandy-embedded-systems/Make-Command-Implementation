#ifndef _MAKE_MULTI_LINE
#define _MAKE_MULTI_LINE
void make_target(void){
	struct stat o_file,c_file;     /* cc -c -o main.c main.o*/
	int fd,flag=1,flag2=1,i,found,run=0;
	char *p=arg[0],name[20],cc[10]="cc -c -o ",cmd[30],*q=NULL,temp[20];
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
			if(status_file(name)){
				found=0;
				for(i=2;i<lines;i+=2){
					if(strstr(arg[i],p)){
						found=1;
						break;
					}
				}
				if(found){
					if(status_file(p)){
						stat(p,&o_file);
						stat(name,&c_file);
						if(c_file.st_mtime>o_file.st_mtime){
							printf("%s\n",arg[i+1]+1);
							if(system(arg[i+1])!=0){
								printf("makefile:%d: recipe for target '%s' failed\n",i+2,p);
								printf("make: *** [fun.o] Error 1\n");
								exit(0);
							}
							run=1;
							flag=0;
						}
					}
					else{
						run=1;
						printf("%s\n",arg[i+1]+1);
						if(system(arg[i+1])!=0){
							 printf("makefile:%d: recipe for target '%s' failed\n",i+2,p);
               printf("make: *** [%s] Error 1\n",p);
               exit(0);
						}
						flag=0;
					}
				}
				else{
					if(status_file(p)){
						stat(p,&o_file);
						stat(name,&c_file);
						if(c_file.st_mtime>o_file.st_mtime){
							strcpy(cmd,cc);
							strcat(cmd,p);
							strcat(cmd," ");
							strcat(cmd,name);
							printf("%s\n",cmd);
							if(system(cmd)!=0){
								printf("makefile:%d: recipe for target '%s' failed\n",i+2,p);
                printf("make: *** [%s] Error 1\n",p);
                exit(0);
							}
							flag=0;
						}
					}
					else{
						run=1;
						strcpy(cmd,cc);
						strcat(cmd,p);
						strcat(cmd," ");
						strcat(cmd,name);
						printf("%s\n",cmd);
						if(system(cmd)!=0){
							 printf("makefile:%d: recipe for target '%s' failed\n",i+1,p);
               printf("make: *** [%s] Error 1\n",p);
               exit(0);
						}
						flag=0;
					}
				}
			}
			else{
				printf("make: *** No rule to make target '%s', needed by 'a.out'.  Stop.\n",p);
				exit(0);
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
	else if(flag) printf("make: 'a.out' is up to date.\n");
	if(run&&flag2){
		strcpy(cmd,arg[1]);
		printf("%s\n",cmd+1);
		system(cmd);
	}
}
#endif
