#include "header.h"

#define PERMS 0644
void fmake(char *file){
	int fd;

	fd = open(file,O_WRONLY | O_CREAT, PERMS);
	close(fd);
}

void Touch(char *file_name){
	struct stat finfo;	//파일의 정보를 담고있는 구조체

	//파일이 존재하지 않으면 생성한다
	if ((stat(file_name, &finfo)) == -1){
   		fmake(file_name);
   	}
	//파일 최종 수정시간 변경
	utime(file_name,NULL);
}

int main(int argc, char **argv){
	int i;
	//struct stat finfo;

	if(argc < 2){
		printf("please input filename\n");
		exit(1);
	}
	else{
		for(i=1;i<argc;i++){
			Touch(argv[i]);
		}
	}
	
	return 0;
}
