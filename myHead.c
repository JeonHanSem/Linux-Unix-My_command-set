#include "header.h"

void Head(char *file,int n){
	char buf[BUFSIZ];
	int j=0;
	FILE *fd;

	if((fd = fopen(file,"r"))==NULL){
		perror("fopen error");
		exit(1);
	}
	//file 이름 출력
	printf("file name : %s\n",file);	
	//end of file 까지 읽으면서 조건에 맞는 라인까지 출력한다
	while(!feof(fd)){
		fgets(buf,sizeof(buf),fd);
		printf("%s", buf);
		if((++j)==n)
			break;
	}
	fclose(fd);
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
void stdHead(int n){
	int nread,cnt=0;
	char str[BUFSIZ];

	while(fgets(str,sizeof(str),stdin)){
		printf("%s", str);
		if((++cnt)==n)
			break;
	}
	exit(1);
}
int main(int argc, char **argv){
	int i,n,p=0;
	int flag;

	////////파일을 입력하지 않았을 경우/////////////////
	if(argc == 1){
		stdHead(10);
	}
	else if(argc < 4){
		if(strcmp(argv[1],"-n")==0){
			if(argc == 2){
				printf("usage: head [-n lines | -c bytes] [file ...]\n");
				exit(1);
			}
			n = atoi(argv[2]);	//출력할 라인 수
			stdHead(n);
		}
	}
	/////////////////////////////////////////////////////

	if(strcmp(argv[1],"-n")==0){
		n = atoi(argv[2]);	//출력할 라인 수
		p = 2;	//옵션부분은 제외해준다
	}
	else{
		n=10;	//옵션없을때는 라인 10줄을 출력하도록 하는 변수
	}
	for(i=p+1;i<argc;i++){
		flag=fileCheck(argv[i]);
		if(flag==0)
			Head(argv[i],n);
	}
	return 0;
}
