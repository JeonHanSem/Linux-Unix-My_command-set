#include "header.h"

int fileCheck(char *file_name){
	struct stat finfo;	//파일의 정보를 담고있는 구조체
	mode_t file_mode;
	int i,flag=0;

	//링크할 파일이 없으면 종료한다
	if ((stat(file_name, &finfo)) == -1){
   		printf("ln: %s: No such file or directory\n", file_name);
   		exit(1);
   	}
   	file_mode = finfo.st_mode;

   	//링크할 파일이 디렉토리면 종료한다
   	if (S_ISDIR(file_mode)){
		printf("Error: It is a directory\n");
		exit(1);
	}
	return flag;
}

int fileCheck2(char *file_name){
	struct stat finfo;	//파일의 정보를 담고있는 구조체
	mode_t file_mode;
	int i,flag=0;

	//링크한것을 저장한 파일이 이미 존재하면 종료한다
	if ((stat(file_name, &finfo)) == 0){
   		printf("ln: %s: File exists\n", file_name);
		exit(1);
   	}

	return flag;
}

int main(int argc, char **argv){
	int flag;
	
    if(argc != 1 && strcmp(argv[1],"-s")==0){
    	if(argc < 4){
			printf("please input filename\n");
			exit(1);
		}
		else if(argc > 4){
			printf("ln: %s: No such file or directory\n", argv[2]);
			exit(1);
		}
    	if(fileCheck2(argv[3])==0)
      	 	symlink(argv[2],argv[3]);
    }
	else{
		if(argc < 3){
			printf("please input filename\n");
			exit(1);
		}
		else if(argc > 3){
			printf("ln: %s: No such file or directory\n", argv[2]);
			exit(1);
		}
		if(fileCheck(argv[1])==fileCheck2(argv[2]))
			link(argv[1],argv[2]);
	}
	return 0;
}
