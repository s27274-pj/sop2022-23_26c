#include <stdio.h>
#include <stdlib.h>

int countOfLines(FILE *filePtr) {
	char prevChar;
	int count = 0;
	char readChar;
	fseek(filePtr, 0, SEEK_SET); /*ensures the pointer is at the beginning of the file*/	
	readChar = getc(filePtr); /*getc reads single char from file*/
	while (readChar != EOF) { /*EOF - End Of File, this is returned when end of file is reached*/
		if (readChar == '\n') { /*count is increased if a newline is encountered*/
			count++;
		}
		prevChar = readChar;
		readChar = getc(filePtr);
		if (prevChar != '\n' && readChar == EOF) { /*safety measure in case there is no newline at the end of file*/
			count++;
		}
	}
	return count;
}

int * getNumbers(FILE *filePtr, int count) {
	int i;
	int * numbers = (int*)calloc(count, sizeof(int)); /*allocating memory for count*sizeof(int) bytes 
	                                                  (will be freed later when no longer needed)*/
	if (numbers == NULL) {   /*checking if memory was successfully allocated*/
		printf("Memory allocation failed");
		return 1;
	}
	fseek(filePtr, 0, SEEK_SET);								  
	for (i = 0; i < count; i++) {
		fscanf(filePtr, "%d\r\n", &numbers[i]);   /*reads integers from file and assigns each to a position in numbers array*/
	}
	return numbers;
}

void printReverse(int *numbers, int size) {
	int i;
	for (i = size - 1; i >= 0; i--) {
		printf("%d\n", numbers[i]);
	}
}

int main(int argc, char** argv) {
	char fileName[255];
	FILE * filePtr;
	int count;
	int * numbers;

	if (argc == 1) { /*if there is only 1 argument (the first argument is the path to the program) we ask the user to input the filename*/
		printf("Please input name of file: ");
		scanf("%254s", fileName); /*%254s protects us from buffer overflow (more data than allocated for our array being read)
									this is important because the surplus data can overwrite other data causing unforeseen effects*/
		filePtr = fopen(fileName, "r");  
	} else {
		filePtr = fopen(argv[1], "r"); 
	}
	if (filePtr == NULL) { /*if the pointer is NULL that means the file wasn't opened*/
		printf("Couldn't open file\n");
		return -1;
	}
	count = countOfLines(filePtr);
	numbers = getNumbers(filePtr, count);
	fclose(filePtr); /*it's important to close the file to ensure resources are released*/

	printReverse(numbers, count);
	free(numbers); /*the memory that was previously allocated is freed here (since the data is no longer needed)*/
	return 0;
}
