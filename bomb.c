#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define ARRAYLENGTH  30000

void runInstruction (char instruction);

int bfData[ARRAYLENGTH], pointer = 0;
FILE *fp;
char currChar;

int main(int argc, char*argv[]) {
	if (argc != 2) {
		printf("One argument expected.\n");
		return -1;
	}

	// Check if file exists and if user has permission to read it
	if (access(argv[1], F_OK) == -1) {
		printf("File does not exist.\n");
		return -1;
	}

	if (access(argv[1], R_OK) == -1) {
		printf("User does not have permission to read the file.\n");
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

void runInstruction(char instruction) {
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
					} else {
						runInstruction(currChar);
						currChar = fgetc(fp);
					}
				}
			} else {
				int cLoops = 1;

				do {
					currChar = fgetc(fp);

					if (currChar == EOF)
						exit(fclose(fp));
					else if (currChar == '[')
						cLoops++;
					else if (currChar == ']')
						cLoops--;
				} while (currChar != ']' || cLoops > 0);
			}
			break;

		case EOF:
			// Kill Bomb
			exit(fclose(fp));
	}

}
