#include "header.h"

#define MAXSIZE 100

void cat(char *file){
	char buf[MAXSIZE],str[MAXSIZE];
	int fd,nread;
	
	if((fd = open(file,O_RDONLY))<0){
		perror("error");
		exit(1);
	}
	//file 이름 출력
	sprintf(buf,"file name : %s\n",file);
	write(1,buf,strlen(buf));	
	//str를 MAXSIZE 바이트씩 읽고 모니터(1번)에 출력
	while(nread=read(fd,str,MAXSIZE))
		write(1,str,nread);	
	close(fd);
}

int fileCheck(char *file_name){
	struct stat finfo;	//파일의 정보를 담고있는 구조체
	mode_t file_mode;
	int i,flag=0;

	if ((stat(file_name, &finfo)) == -1){
   		perror("Error : ");
   		return 1;
   	}
   	file_mode = finfo.st_mode;

   	if (S_ISDIR(file_mode)){	//디렉토리면 에러
		printf("Error: It is a directory\n");
		return 1;
	}
	return flag;
}

//파일입력이 없을시에는 stdin에서 읽어서 stdout으로 출력한다
void stdCat(){
	int nread;
	char str[MAXSIZE];

	while(nread=read(0,str,MAXSIZE)){
		write(1,str,nread);
	}
}

int main(int argc, char **argv){
	int i;
	int flag;

	if(argc < 2){
		stdCat();
	}
	else{
		for(i=1;i<argc;i++){
			flag=fileCheck(argv[i]);
			if(flag==0)
				cat(argv[i]);
		}
	}
	return 0;
}