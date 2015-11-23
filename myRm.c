#include "header.h"

#define MAXSIZE 100

void Rmf(char *file){
	struct stat finfo;	//파일의 정보를 담고있는 구조체
	mode_t file_mode;

	//옵션 f는 파일이 없어서 작업실패하더라도 에러메시지를 띄우지 않는다
	if ((stat(file, &finfo)) == -1)
   		return;

   	file_mode = finfo.st_mode;

   	if (S_ISDIR(file_mode)){	//디렉토리면 에러
		printf("Error: It is a directory\n");
		return;
    }
    unlink(file);
}

void Rmi(char *file){
	char str[MAXSIZE];
	if(access(file,F_OK)<0){	//파일이 존재하지않으면 에러를 띄운다
		perror("rm error : ");
		return;
	}
	printf("rm : remove file %s?(y/n) ",file);
	scanf("%s",str);
	if(strcmp(str,"y")==0 || strcmp(str,"Y")==0){
		if(unlink(file)<0)	//link지우기 실패했을때
			perror("rm error : ");
	}
}

void Rm(char *file){
	if(unlink(file)<0)	//link지우기 실패했을때
		perror("rm error : ");
}

int fileCheck(char *file_name){
	struct stat finfo;	//파일의 정보를 담고있는 구조체
	mode_t file_mode;
	int i,flag=0;

	if ((stat(file_name, &finfo)) == -1){
   		perror("Error : ");
   		flag=1;
   	}
   	file_mode = finfo.st_mode;

   	if (S_ISDIR(file_mode)){	//디렉토리면 에러
		flag=1;
		printf("Error: It is a directory\n");
	}
	return flag;
}


int main(int argc,char **argv){
	int i;
	char str[MAXSIZE];
	int flag;

	////////파일을 입력하지 않았을 경우/////////////////
	if(argc == 1){
		printf("please input filename\n");
		return 1;
	}
	else if(argc == 2){
		if(strcmp(argv[1],"-f")==0 || strcmp(argv[1],"-i")==0){
			printf("please input filename\n");
			return 1;
		}
	}
	/////////////////////////////////////////////////////
	
	
	if(strcmp(argv[1],"-f")==0){	//-f 옵션이면 파일이 존재하지않더라도 아무 메시지를 띄우지않는다
		for(i=2;i<argc;i++){
			Rmf(argv[i]);
		}
	}
	else if(strcmp(argv[1],"-i")==0){	//-i 옵션이면 삭제하기전에 한번 더 물어본다
		for(i=2;i<argc;i++){
			flag=fileCheck(argv[i]);
			if(flag==0)
				Rmi(argv[i]);
		}
	}
	else{
		for(i=1;i<argc;i++){	//옵션이 없으면 -f과 다르게 삭제 실패시 메시지를 띄운다
			flag=fileCheck(argv[i]);
			if(flag==0)
				Rm(argv[i]);
		}
	}	
	return 0;
}