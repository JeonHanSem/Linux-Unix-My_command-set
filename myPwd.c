#include "header.h"

#define MAXSIZE 100

int main(){
	char buf[MAXSIZE];

	if(getcwd(buf,MAXSIZE)==NULL)
		perror("getcwd error");
	else{
		//printf("%s\n", buf);
		sprintf(buf,"%s\n",buf);
		write(1,&buf,strlen(buf));
	}
	return 0;
}