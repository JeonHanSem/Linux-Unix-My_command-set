#include "header.h"

#define MAXSIZE 100

void Chmod(char *file,int mode){
	if(chmod(file,mode)<0){ //입력받은 모드로 파일의 권한을 변경한다
		perror("chmod error");
		exit(1);
	}
}

int main(int argc, char **argv){
	int i;
	int mode;

	if(argc < 3){
		printf("please input filename or mode number\n");
		exit(1);
	}
	else{
		mode = strtol(argv[1],0,8); //모드를 8진수로 받는다
		for(i=2;i<argc;i++){
			Chmod(argv[i],mode);
		}
	}
	return 0;
}
