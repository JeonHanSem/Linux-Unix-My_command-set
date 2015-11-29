#include "header.h"

#define MAXSIZE 100

void Tail(char *file,int n){
	char buf[MAXSIZE][MAXSIZE];
	int j=0,k;
	FILE *fd;

	if((fd = fopen(file,"r"))==NULL){
		perror("fopen error");
		exit(1);
	}
	//file 이름 출력
	sprintf(buf[0],"file name : %s\n",file);
	printf("%s",buf[0]);	
	//end of file까지 읽으면서 라인수를 세어놓는다
	while(fgets(buf[j++],sizeof(buf[j]),fd)!=NULL){}
	//파일의 끝에서부터 주어진 조건인 라인까지 출력한다
	//파일의 전체길이가 주어진 조건보다 짧은경우 전체를 다 출력하도록 하였다
	if(j<n+1)	
		k=1;
	else
		k=j-n;
	for(;k<j+1;k++)
		printf("%s", buf[k-1]);
	fclose(fd);
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

//파일입력이 없을시에는 stdin에서 읽어서 stdout으로 출력한다
void stdTail(int n){
	int k,cnt=0;
	int i;
	int flag;
	char str[MAXSIZE];
	char buf[MAXSIZE][MAXSIZE];

	while(fgets(buf[cnt],sizeof(buf[cnt]),stdin)!=NULL){cnt++;}
	//파일의 끝에서부터 주어진 조건인 라인까지 출력한다
	//파일의 전체길이가 주어진 조건보다 짧은경우 전체를 다 출력하도록 하였다
	if(cnt<n+1)	
		k=1;
	else
		k=cnt-n;
	for(;k<cnt;k++){
		printf("%s", buf[k-1]);
	}
	exit(1);
}

int main(int argc, char **argv){
	char buf[MAXSIZE][MAXSIZE];
	char str[MAXSIZE];
	int i,j=0,n,p=0,flag;
	FILE *fd;

	////////파일을 입력하지 않았을 경우/////////////////
	if(argc == 1){
		stdTail(10);
	}
	else if(argc < 4){
		if(strcmp(argv[1],"-n")==0){
			if(argc == 2){
				printf("usage: head [-n lines | -c bytes] [file ...]\n");
				exit(1);
			}
			n = atoi(argv[2]);	//출력할 라인 수
			stdTail(n);
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
			Tail(argv[i],n);
	}
	return 0;
}
