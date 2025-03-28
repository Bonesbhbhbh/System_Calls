#include <stdio.h>
#include <stdbool.h>
#include  <ctype.h>

#define BUF_SIZE 1024

bool is_vowel(char c) {
	/*
	 * Returns true if c is a vowel (upper or lower case), and
	 * false otherwise.
	 */
	c = tolower(c);
	bool isVowel = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ); //gonna ignore y here
	return isVowel;
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
	/*
	 * Copy all the non-vowels from in_buf to out_buf.
	 * num_chars indicates how many characters are in in_buf,
	 * and this function should return the number of non-vowels that
	 * that were copied over.
	 */
	//printf("in copy_non_vowels!\n");
	int count = 0;
	for(int i = 0 ; i < num_chars; i++) {
		if(!is_vowel(in_buf[i])) {
            out_buf[count] = in_buf[i]; // take the non-vowel and add it to the out_buf
            count++;
		}
	}
	//printf("leaving copy_non_vowels\n");
	return count;
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
	/*
	 * Copy all the non-vowels from inputFile to outputFile.
	 * Create input and output buffers, and use fread() to repeatedly read
	 * in a buffer of data, copy the non-vowels to the output buffer, and
	 * use fwrite to write that out.
	 */
    size_t num_chars;
    
    char in_buff[BUF_SIZE];
	char out_buff[BUF_SIZE];

	while((num_chars = fread(in_buff, sizeof(char), BUF_SIZE, inputFile)) > 0) {  //copilot suggestion... treat with skepticism ...
		//printf("in while loop, disemvowel - size of num_chars is: %d\n",num_chars);
		int consonants = copy_non_vowels(num_chars, in_buff, out_buff);
		size_t written = 0;
		//printf("size of consonants is:%d\n size of written is: %d\n",consonants,written);
		while(written < consonants){
			written += fwrite(out_buff + written, sizeof(char), consonants - written, outputFile);
			//printf("size of consonants is:%d\n size of written is: %d\n",consonants,written);
		}
		//printf("out of internal while-loop haven't left fread() purgatory\n");
	}
	//printf("out of while-loop, disemvowel\n");
	return;
}



int main(int argc, char *argv[]) {
	// This sets these to `stdin` and `stdout` by default.
	// You then need to set them to user specified files when the user
	// provides files names as command line arguments.

	/*
	printf("opened main with %d arguments \n",(argc -1));
	for(int i = 1 ; i < argc; i++) {
		printf("argv[%d]: %s\n",i,argv[i]);
	}
	*/
	FILE* inputFile = stdin;
	FILE* outputFile = stdout;

	// Code that processes the command line arguments
	// and sets up inputFile and outputFile.
	if(argc >= 2) {
	    inputFile = fopen(argv[1], "r");
	    if (inputFile == NULL) {
	        printf("error opening input file\n");
	        return 0;
	    }
	}
	if(argc >= 3) {
		outputFile = fopen(argv[2], "w");
		if(outputFile == NULL) {
			printf("could not open output file\n");
			return 0;
		}
	}
	//printf("input and output initialized\n");
	disemvowel(inputFile, outputFile);
	//printf("done disemvowel-ing\n");
	fclose(outputFile);
	fclose(inputFile);
	//printf("closed files\n");
	return 0;
}
