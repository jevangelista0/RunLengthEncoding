#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/*todo:
 * 	fix max min initial values
 * 	figure out how to know when you are reading next line from text file (step 4)
 * 	step 2 and step 5?
 */

	int main(int argc, char** argv){
		ifstream file0(argv[1]);
		ofstream file1(argv[2]);

		if(file0.is_open() && file1.is_open()){
			int i = 0, trackHeader = 0;
			int nR = 0, nC = 0, min = -1, max = -1; // nR = numRow, nC = numCol;
			int r = 0, c = 0, count = 0, curr = -1, next = -1;

			while(file0 >> i){
				if(trackHeader < 4){ // takes note of the header
					trackHeader++;
					if(trackHeader == 1){
						nR = i;
					}else if(trackHeader == 2){
						nC = i;
					}else if(trackHeader == 3){
						min = i;
					}else{
						max = i;
						file1 << "row: " << nR << " col: " << nC << " min: " << min << " max: " << max << endl << endl;
					}
				}else{ // where we really start doing business
					c = 0;
					count = 0;
					curr = i;
					file1 << "row: " << r << " col: " << c << " curr: " << curr;
					count++;

					for(int j=0; j<nC-1; j++){
						c++;
						file0 >> next;

						if(curr == next){
							count++;
						}else{
							file1 << " count: " << count << "\n";
							curr = next;
							count = 1;
							file1 << "row: " << r << " col " << c << " curr: " << curr;
						}
					}
					file1 << " count: " << count << endl;
					r++;
				}
			}
			cout << "it worked." << endl;

			file0.close();
			file1.close();
		}

		return 0;
	}
//	INCLUDE 0 WRAP AROUND
//	bool firstRun = true;
//
//	while (file0 >> i){
//		if(trackHeader < 4){ // takes note of the header
//			trackHeader++;
//			if(trackHeader == 1){
//				nR = i;
//			}else if(trackHeader == 2){
//				nC = i;
//			}else if(trackHeader == 3){
//				min = i;
//			}else{
//				max = i;
//				file1 << "row: " << nR << " col: " << nC << " min: " << min << " max: " << max << endl << endl;
//			}
//		}else{
//			next = i;
//
//			if(firstRun){
//				curr = next;
//				firstRun = false;
//			}
//
//			if(count == 1){
//				curr = next;
//				file1 << "r: " << r << " c: " << c-1 << " curr: " << curr;
//			}
//
//			if(curr == next){
//				count++;
//			}else{
//				file1 << " count: " << count << endl;
//				count = 1;
//				curr = next;
//			}
//
//			if(c == nC){
//				c = 0;
//				r++;
//			}
//			c++;
//		}
//	}
//	file1 << " count: " << count << endl;
