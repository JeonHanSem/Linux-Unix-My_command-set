#include "header.h"

#define PERMS 0644
void Touch(char *file){
	int fd;

	fd = open(file,O_WRONLY | O_CREAT | O_APPEND, PERMS);
	utime(file, NULL);
	close(fd);
}

int fileCheck(char *file_name){
	struct stat finfo;	//파일의 정보를 담고있는 구조체
	mode_t file_mode;
	int i,flag=0;

	//파일이 존재하지 않으면 생성해야하기때문에 flag=0을 반환한
	if ((stat(file_name, &finfo)) == -1){
   		return flag;
   	}
   	file_mode = finfo.st_mode;

   	if (S_ISDIR(file_mode)){	//디렉토리면 에러
		flag=1;
		printf("Error: It is a directory\n");
	}
	return flag;
}

int main(int argc, char **argv){
	char str;
	int fd,i,f,flag;
	//struct stat finfo;

	if(argc < 2){
		printf("please input filename\n");
		exit(1);
	}
	else{
		for(i=1;i<argc;i++){
			flag=fileCheck(argv[i]);
			if(flag==0)
				Touch(argv[i]);
		}
	}
	
	
	return 0;
}