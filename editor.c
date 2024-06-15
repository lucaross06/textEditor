#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <ctype.h>

//potrei fare che mi salva la posizione in cui era il cursore in cui era l'ultima volta, magari con un .file

struct termios orig_termios;
//toglie la visibilita' di quello che viene scritto, tipo quello che succede
//quando si mette una password sul terminale

void disableRawMode(){
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode(){

	tcgetattr(STDIN_FILENO,&orig_termios);
	atexit(disableRawMode);
	struct termios raw = orig_termios;

//	tcgetattr(STDIN_FILENO, &raw);
	raw.c_oflag &= ~(OPOST);
	raw.c_iflag &= ~(BRKINT | IXON | ICRNL | ISTRIP | INPCK);
	raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); //~ e'  bitwise not, &= e' bitwise and
	raw.c_cflag |= (CS8); //bitwise or
	tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);
}

void saveFile(){
	printf("\nEnter file name: ");
/*	int i = 0;
	char* fileName;
	char c;
	while(read(STDIN_FILENO, &c, 1) == 1){
		*(fileName + 1) = c;
	}*/
}

int main(){

	enableRawMode();
	char quit[] = ":q";
	char save[] = ":w";
	char buffer[2] = "00";
	int charCounter = 0;
	int wordCounter = 0; //conta gli spazi
	FILE *fptr;

	fptr = fopen("debug","w");
	char c;
	while(read(STDIN_FILENO, &c, 1) == 1){
	//	buffer[counter % 2] = c;
		buffer[1] = c;
	//	fprintf(fptr,"%c",buffer[0]);
	//	fprintf(fptr, " ");
	//	fprintf(fptr, "%c\n",buffer[1]);
		if(buffer[0] == quit[0] && buffer[1] == quit[1]){
			break;
		}
		if(buffer[0] == save[0] && buffer[1] == save[1]){ 
//			saveFile();
			break;
		}


		if (iscntrl(c)) { //se tolgo sti print esotici non funzia
			printf("%d\r\n", c);
		}
		else{
			printf("%d ('%c')\r\n", c, c);
		}
		if(c == 13){
			fprintf(fptr,"\r\n");
		}
		fprintf(fptr,"%c",c);
	//	printf("%c",c);
		buffer[0] = c;
		charCounter++;
	}
//	fclose(fptr);
	printf("%d",charCounter);
	return 0;
}
