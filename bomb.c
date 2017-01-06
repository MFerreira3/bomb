#include <stdio.h>
#define ARRAYLENGTH  30000

int runInstruction (char instruction);

char bfData[ARRAYLENGTH], pointer = 0;
FILE *fp;
char currChar;

int main(int argc, char*argv[]) {
	if (argc != 2) {
		printf("One argument expected.\n");
		return -1;
	}

	for (int i = 0; i < ARRAYLENGTH; i++) {
		bfData[i] = 0;
	}

	// Open the given file for reading
	fp = fopen(argv[1], "r");
	// Store the first character
	currChar = fgetc(fp);

	// Read and interpret all characters until the end of file is reached
	while (currChar != EOF) {
		runInstruction(currChar);
		currChar = fgetc(fp);
	}

	return fclose(fp);
}

int runInstruction(char instruction) {
	// Define where the current loop starts
	int loopBeginning = 0;

	switch (instruction) {
		case '>':
			++pointer;
			break;

		case '<':
			--pointer;
			break;

		case '+':
			++bfData[pointer];
			break;

		case '-':
			--bfData[pointer];
			break;

		case '.':
			putchar(bfData[pointer]);
			break;

		case ',':
			bfData[pointer] = getchar();
			break;

		case '[':
			// Check if it even needs to iterate through the loop instructions
			if (bfData[pointer] != 0) {
				// Keep reading and interpreting
				currChar = fgetc(fp);
				loopBeginning = ftello(fp);

				// Loop until a closing bracket is found
				while (1) {
					// Check whether the current character is a closing bracket
					if (currChar == ']') {
						// Check whether the current bfData is 0
						if (bfData[pointer] != 0) {
							// Get back to the beginning of iteration
							fseeko(fp, loopBeginning - 1, SEEK_SET);
							currChar = fgetc(fp);
						} else {
							// Break the current loop
							break;
						}
					} else if (currChar == EOF) {
						// TODO We need an EOF verification here pls and ty
					} else {
						runInstruction(currChar);
						currChar = fgetc(fp);
					}
				}
			} else {
				// Jump to the next closing bracket
				while (currChar != ']') {
					currChar = fgetc(fp);
				}
			}
			break;
	}

}
