#include <stdio.h>
#include <unistd.h>
int main(){
	char exit[] = ":q";
	char buffer[2] = "00";
	int counter = 0;
//	FILE *fptr;

//	fptr = fopen("debug","w");
	char c;
	while(read(STDIN_FILENO, &c, 1) == 1){
	//	buffer[counter % 2] = c;
		buffer[1] = c;
	//	fprintf(fptr,"%c",buffer[0]);
	//	fprintf(fptr, " ");
	//	fprintf(fptr, "%c\n",buffer[1]);
		if(buffer[0] == exit[0] && buffer[1] == exit[1]){
			break;
		}
		buffer[0] = c;
		counter++;
	}
//	fclose(fptr);
	printf("%d",counter);
	return 0;
}
