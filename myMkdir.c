#include "header.h"

#define MAXSIZE 100
#define PERMS 0755

int fileCheck(char *file_name){
	struct stat finfo;	//파일의 정보를 담고있는 구조체
	mode_t file_mode;
	int i,flag=0;

	stat(file_name, &finfo);
   	file_mode = finfo.st_mode;
   	if (S_ISREG(file_mode)){
   		perror("Error");
   		return 1;
   	}
   	else if (S_ISDIR(file_mode)){	//디렉토리면 에러
		flag = 0;
	}
	return flag;
}

void pMkdir(char *path, char *cur){
	int flag=0;
	int cnt=0,i;

	if((path=strtok(path,"/"))!=NULL){
		while(path!=NULL){
			if(mkdir(path,PERMS)){	//이미 디렉토리가 존재할경우 chdir을 통해 들어간다
				cur=path;
				path=strtok(NULL,"/");
				chdir(cur);
				if(mkdir(path,PERMS)==0)
					flag=1;
				cnt++;
			}
			else{	//디렉토리가 없으면 만들고 그 디렉토리를 chdir을 통해 들어간다
				cur=path;
				path=strtok(NULL,"/");
				chdir(cur);
				flag=1;
				cnt++;
			}
		}
	}
	for(i=0;i<cnt;i++)	//현재 디렉토리를 원래대로 되돌려놓는다
		chdir("..");	
	if(flag==0){	//mkdir에 실패한경우는 이미 디렉토리가 존재하는 경우이다
		printf("mkdir error: already exist\n");
        exit(1);
	}
}

void Mkdir(char *path, char *cur){
	char *tmp=path;
	int check;
	int flag=0;
	int cnt=0,i;

	if((path=strtok(path,"/"))!=NULL){
		check=fileCheck(path);
		if(check==0){
			if(mkdir(path,PERMS)){	//이미 디렉토리가 존재할경우 chdir을 통해 들어간다
				cur=path;
				while(path=strtok(NULL,"/")){	//계속해서 디렉토리를 들어가는 상황
					chdir(cur);
					if(mkdir(path,PERMS)==0)	//mkdir에 성공했으면 flag를 1로 바꿔준다
						flag=1;
					cur=path;
					cnt++;
				}
			}
		}
		else{
			if(strcmp(tmp,path)!=0)				
				flag=0;
			else
				flag=1;
		}
	}
	for(i=0;i<cnt;i++)
		chdir("..");
	if(flag==0){	//mkdir에 실패한경우는 이미 디렉토리가 존재하는 경우이다
		perror("mkdir error");
        exit(1);
	}
}

int main(int argc, char **argv){
	int i;

	if(argc < 2){
		perror("please input directoryname");
		exit(1);
	}
	//옵션 p가 들어왔을경우
	if(strcmp(argv[1],"-p")==0){
		for(i=2;i<argc;i++)
			pMkdir(argv[i],NULL);
	}
   	else{
   		for(i=1;i<argc;i++)
   			Mkdir(argv[i],NULL);
   	}
    
    return 0;
}