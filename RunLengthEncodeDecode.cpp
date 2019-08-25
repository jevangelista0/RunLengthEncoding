#include <iostream>
#include <fstream>
using namespace std;

int numR = 0, numC = 0, minVal = 0, maxVal = 0;
// LAST TEXT LINE: methodType, numRuns, total bytes

void eMethodOne(ifstream& in, ofstream& encode){ // 0 no w
	int curr = 0, next = -1, r = 0, c = 0, count = 0, numRuns = 0;

	in >> curr;
	while(!in.eof()){
		encode << r << " " << c  << " " << curr << " ";
		count++;

		for(int i=0; i<numC-1; i++){ // traverse columns
			in >> next;
			c++;

			if(curr == next){
				count++;
			}else{
				encode << count << "\n";
				numRuns++;
				curr = next;
				count = 1;
				encode << r << " " << c  << " " << curr << " ";
			}
		}
		encode << count << "\n";
		numRuns++;

		in >> next; // causing bugs (this and numC-1 ... probably something with how we read)
		count = 0;
		c = 0;
		r++;
	}

//	encode << "methodType: 1 numRuns: " << numRuns << " total bytes: " << numRuns * 4;
	in.close();
	encode.close();
}

void eMethodTwo(ifstream& in, ofstream& encode){ // no 0 no w
	int curr = 0, next = -1, r = 0, c = 0, count = 0, numRuns = 0;

	in >> curr;
	while(!in.eof()){

		if(curr != 0){
			encode << r << " " << c  << " " << curr << " ";
		}
		count++;

		for(int i=0; i<numC-1; i++){ // traverse columns
			in >> next;
			c++;

			if(curr == next){
				count++;
			}else{
				if(curr != 0){
					encode << count << "\n";
					numRuns++;
				}
				curr = next;
				count = 1;
				if(curr != 0){
					encode << r << " " << c  << " " << curr << " ";
				}
			}
		}
		if(curr != 0){
			encode << count << "\n";
			numRuns++;
		}

		in >> next; // causing bugs (this and numC-1 ... probably something with how we read)
		count = 0;
		c = 0;
		r++;
	}

//	encode << "methodType: 2 numRuns: " << numRuns << " total bytes: " << numRuns * 4;
	in.close();
	encode.close();
}

void eMethodThree(ifstream& in, ofstream& encode){ // 0 w
	int curr = 0, next = -1, r = 0, c = 0, count = 0, numRuns = 0;

	in >> curr;
	encode << r << " " << c  << " " << curr << " ";
	count++;
	while(in >> next){
		c++; // traverse columns

		if(curr == next){
			count++;
		}else{
			encode << count << "\n";
			numRuns++;
			curr = next;
			count = 1;
			encode << r << " " << c  << " " << curr << " ";
		}

		if(c == numC){
			c = 0;
			r++;
		}
	}
	encode << count << "\n";

//	encode << "methodType: 3 numRuns: " << numRuns << " total bytes: " << numRuns * 4;
	in.close();
	encode.close();
}

void eMethodFour(ifstream& in, ofstream& encode){ // no 0 w
	int curr = 0, next = -1, r = 0, c = 0, count = 0, numRuns = 0;

	in >> curr;
	if(curr != 0){
		encode << r << " " << c  << " " << curr << " ";
	}
	count++;
	while(in >> next){
		c++; // traverse columns

		if(curr == next){
			count++;
		}else{
			if(curr != 0){
				encode << count << "\n";
				numRuns++;
			}
			curr = next;
			count = 1;
			if(curr != 0){
				encode << r << " " << c  << " " << curr << " ";
			}
		}

		if(c == numC){
			c = 0;
			r++;
		}
	}
	if(curr != 0){
		encode << count << "\n";
	}

//	encode << "methodType: 4 numRuns: " << numRuns << " total bytes: " << numRuns * 4;
	in.close();
	encode.close();
}

void dMethodOne(ifstream& encode, ofstream& decode){ // 0 no w
	// read first few numbers before the first actual line
	// decode by just printing the instructions per line
	// if max column then print new line
	// repeat till before the last line

	int r = 0, c = 0, pixel = 0, length = 0;
	decode << numR << " " << numC << " " << minVal << " " << maxVal << "\n";

	while(!encode.eof()){
		encode >> r;
		encode >> c;
		encode >> pixel;
		encode >> length;

		for(int i=0; i<length && !encode.eof(); i++){
			decode << pixel << " ";
		}
		if(c+length == numC){ // getting offset and checking if out of bounds
			decode << "\n";
		}
	}

}

void dMethodTwo(ifstream& encode, ofstream& decode){ // no 0 no w
	// read first few numbers before the first actual line
	// get line and check if == current row and column
	// if not print 0s till equal rows and columns (or just columns)
	// then print the instruction and check offset like previous decode

	int r = 0, c = 0, currR = 0, currC = 0, pixel = 0, length = 0, runIndex = 0;
	decode << numR << " " << numC << " " << minVal << " " << maxVal << "\n";

	while(!encode.eof()){
		encode >> currR;
		encode >> currC;
		encode >> pixel;
		encode >> length;

		for(; r<numR && !encode.eof(); r++){
			for(c = 0; c<numC && !encode.eof(); c++){
				if(runIndex == length){ // run finished and read update
					encode >> currR;
					encode >> currC;
					encode >> pixel;
					encode >> length;

					runIndex = 0;
				}

				if(r < currR || c < currC){
					decode << "0 ";
				}else{
					runIndex++;
					decode << pixel << " ";
				}

			}
			if(c == numC){
				decode << "\n";
			}
		}
	}

	if(r < numR || c < numC){ // is there are still missing 0s after the last line
		for(; r<numR+1; r++){
			for(; c<numC; c++){
				decode << "0 ";
			}
			c = 0;
			decode << "\n";
		}
	}

	encode.close();
	decode.close();
}

void dMethodThree(ifstream& encode, ofstream& decode){ // 0 w
	// read headers
	// follow instructions till before out of bounds then print next line
	// if cut off continue till finished length then read again

	int r = 0, c = 0, currR = 0, currC = 0, pixel = 0, length = 0, runIndex = 0;
	decode << numR << " " << numC << " " << minVal << " " << maxVal << "\n";

	encode >> currR;
	encode >> currC;
	encode >> pixel;
	encode >> length;

	for(; r<numR; r++){
		for(c=0; c<numC; c++){
			if(runIndex < length){
				runIndex++;
				decode << pixel << " ";
			}else{
				encode >> currR;
				encode >> currC;
				encode >> pixel;
				encode >> length;
				runIndex = 1;

				decode << pixel << " ";
			}
		}
		decode << "\n";
	}

	encode.close();
	decode.close();
}

void dMethodFour(ifstream& encode, ofstream& decode){ // no 0 w
	// read header stuff
	// fill in 0s till we match the row and column of the given input from file
	// follow instructions until before out of bounds and cut off to new line
	// continue until the length is filled
	// check for missing 0s after till we match total row and column
	cout << "https://github.com/jevangelista0\n";
	int r = 0, c = 0, currR = 0, currC = 0, pixel = 0, length = 0, runIndex = 0;
	decode << numR << " " << numC << " " << minVal << " " << maxVal << "\n";

	encode >> currR;
	encode >> currC;
	encode >> pixel;
	encode >> length;

	for(; r<numR && !encode.eof(); r++){
		for(c=0; c<numC && !encode.eof(); c++){
			if(runIndex < length){
				if((c < currC || r < currR) && !(runIndex > 1)){
					decode << "0 ";
				}else{
					runIndex++;
					decode << pixel << " ";
				}
			}else{
				runIndex = 1;

				encode >> currR;
				encode >> currC;
				encode >> pixel;
				encode >> length;

				if((c < currC || r < currR) && !(runIndex > 1)){
					decode << "0 ";
				}else{
					decode << pixel << " ";
				}
			}
		}
		if(c == numC){
			decode << "\n";
		}
	}

	if(r < numR || c < numC){ // is there are still missing 0s after the last line
		for(; r<numR+1; r++){
			for(; c<numC; c++){
				decode << "0 ";
			}
			c = 0;
			decode << "\n";
		}
	}

	encode.close();
	decode.close();
}

int main(int argc, char** argv){
	char yahOrNah;
	int methodType = 0;
	ifstream in(argv[1]);
	string fileName = argv[1]; // get filename
	fileName = fileName.substr(0, fileName.find('.')); // get sub string without extension

	cout << "program asks the user if he/she want to use another method to compress the file: (‘Y’ for yes, ‘N’ for no.) ";
	cin >> yahOrNah;
	yahOrNah = (char)tolower(yahOrNah);

	while(yahOrNah == 'y'){
		cout << "What type of method? (1-4) ";
		cin >> methodType;
		while(methodType < 1 || methodType > 4){
			cout << "Invalid method type, try again: ";
			cin >> methodType;
		}

		try{
			ofstream out1(fileName + "_Encode" + (char)(methodType + '0') + ".txt" ); // make encode file
			ofstream out2( fileName + "_Encode" + (char)(methodType+'0') + "_Decode.txt"); // make decode file

			switch(methodType){ // encode
				case 1: {
					in.close();
					in.open(argv[1]);

					in >> numR;
					in >> numC;
					in >> minVal;
					in >> maxVal;

					out1 << numR << " " << numC << " " << minVal << " " << maxVal << "\n" << methodType << "\n";

					eMethodOne(in, out1);

					out1.close(); // reinitialize
					ifstream encode(fileName + "_Encode" + (char)(methodType + '0') + ".txt" ); // make encode file

					encode >> numR;
					encode >> numC;
					encode >> minVal;
					encode >> maxVal;
					encode >> methodType; // why do we need if user already entered?

					dMethodOne(encode, out2);

					break;
				}case 2: {
					in.close();
					in.open(argv[1]);

					in >> numR;
					in >> numC;
					in >> minVal;
					in >> maxVal;

					out1 << numR << " " << numC << " " << minVal << " " << maxVal << "\n" << methodType << "\n";

					eMethodTwo(in, out1);

					// DECODE
					out1.close();
					ifstream encode(fileName + "_Encode" + (char)(methodType + '0') + ".txt" ); // make encode file

					encode >> numR;
					encode >> numC;
					encode >> minVal;
					encode >> maxVal;
					encode >> methodType; // why do we need if user already entered?

					dMethodTwo(encode, out2);

					break;
				}case 3: {
					in.close();
					in.open(argv[1]);

					in >> numR;
					in >> numC;
					in >> minVal;
					in >> maxVal;

					out1 << numR << " " << numC << " " << minVal << " " << maxVal << "\n" << methodType << "\n";

					eMethodThree(in, out1);

					// DECODE
					out1.close();
					ifstream encode(fileName + "_Encode" + (char)(methodType + '0') + ".txt" ); // make encode file

					encode >> numR;
					encode >> numC;
					encode >> minVal;
					encode >> maxVal;
					encode >> methodType; // why do we need if user already entered?

					dMethodThree(encode, out2);

					encode.close();
					break;
				}case 4: {
					in.close();
					in.open(argv[1]);

					in >> numR;
					in >> numC;
					in >> minVal;
					in >> maxVal;

					out1 << numR << " " << numC << " " << minVal << " " << maxVal << "\n" << methodType << "\n";

					eMethodFour(in, out1);

					// DECODE
					out1.close();
					ifstream encode(fileName + "_Encode" + (char)(methodType + '0') + ".txt" ); // make encode file

					encode >> numR;
					encode >> numC;
					encode >> minVal;
					encode >> maxVal;
					encode >> methodType; // why do we need if user already entered?

					dMethodFour(encode, out2);

					encode.close();
					break;
				}
			}

			out1.close();
			out2.close();
		}catch(int e){
			cout << e;
		}

		cout << "program asks the user if he/she want to use another method to compress the file: (‘Y’ for yes, ‘N’ for no.) ";
		cin >> yahOrNah;
		yahOrNah = (char)tolower(yahOrNah);
	}

	cout << "Write that down and put five star on it";

	in.close();
}
