#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


//Function prototypes
void printEncodedMaze(int [], unsigned char);
void printEncodedMazeWithPath(int [], int [], unsigned char);
void encode8by8Maze(char [][8], int []);
void merge8by8Mazes(int [], int [], int [], int [], int []);
char isPathInMaze(int[], int[], unsigned char);


/*
PART 1
*/
/*
This is basically the heart of the code, it calls all the functions and has all the arrays required for each
needless to say all the functions are useless without this
*/
//RETURN : 0
int main(){
	int arr[32] ={-1,-2146430423, -1109928277,-1525661045,-1602496045,-1358950569,-1451509759,
	-1927115297,-1578180479,-1354977603,-1476294999,-2084818261,-1163749757,-1964319689,-1341614619,
	-1750141691,-1256060947,-1515522751,-1204136611,-1955867371,-1190652827,-1553272339,-1100839163,
	-1999963019,-631368865,-1882138047,-1172944163,-1412279803,-1567107339,-164346691,-2138762879,-1};
	
	int path[32] = {0, 0, 0, 0, 12, 8, 56, 32, 8032, 4416, 134115648, 67354944, 67109184,
			67109312, 133169152, 1048576, 1835008, 262144, 262144, 262144, 458752,
			65536, 65536, 65536, 65536, 983040, 67633152, 67633152, 201850880,
			164102144, 259522560, 0};
			
	char blocks1[8][8] = {{1,1,1,1,1,1,1,1},
			     {1,0,0,0,1,0,0,1},
			     {1,0,1,0,1,1,0,1},
			     {1,0,1,0,0,0,0,1},
			     {1,0,1,1,1,1,0,1},
			     {1,0,0,0,0,0,0,1},
			     {1,0,1,0,1,0,1,1},
			     {1,1,1,1,1,1,1,1}};

	char blocks2[8][8] = {{1,1,1,1,1,1,1,1},
			     {1,0,0,0,0,1,0,1},
			     {1,1,1,1,0,1,0,1},
			     {1,0,0,1,0,1,1,1},
			     {1,1,0,0,0,0,0,1},
			     {1,1,1,1,0,1,1,1},
			     {1,0,0,0,0,1,0,1},
			     {1,1,1,1,1,1,1,1}};		 	
			
	char blocks3[8][8] = {{1,1,1,1,1,1,1,1},
			     {1,0,1,0,0,0,1,1},
			     {1,0,1,0,1,0,0,1},
			     {1,0,1,0,1,0,1,1},
			     {1,0,1,0,1,0,1,1},
			     {1,0,1,0,1,0,1,1},
			     {1,0,0,0,1,0,0,1},
			     {1,1,1,1,1,1,1,1}};
	
	char blocks4[8][8] = {{1,1,1,1,1,1,1,1},
			     {1,0,1,0,1,0,1,1},
			     {1,0,1,0,0,0,0,1},
			     {1,0,0,0,1,1,1,1},
			     {1,1,1,0,1,0,0,1},
			     {1,0,0,0,0,0,1,1},
			     {1,1,0,1,1,0,0,1},
			     {1,1,1,1,1,1,1,1}};
			     
	//coordinates for part 4 and part 5			     
	int topLeft[8];
	int topRight[8];
	int bottomLeft[8];
	int bottomRight[8];
	int finalMaze[14];
	int pathInMaze[14] = {0, 4096, 4096, 4096, 4096, 7936, 256, 256, 448, 112, 16, 28, 6, 0};
	//prints maze for pt 2
	printEncodedMaze(arr, 32);
	printf("\n");
	//prints path for pt3
	printEncodedMazeWithPath(arr,path, 32);	
	printf("\n");
	//prints small blocks for part 4 and 5
	encode8by8Maze(blocks1, topLeft);
	encode8by8Maze(blocks2, topRight);
	encode8by8Maze(blocks3, bottomLeft);
	encode8by8Maze(blocks4, bottomRight);
	//array with a pointer with the locations which is needed for all possible combinations in part 6
	int *combinations[4] = {topLeft, topRight, bottomLeft, bottomRight};
	//takes all small blocks merges them together aka part 5
	merge8by8Mazes(topLeft, topRight, bottomLeft, bottomRight, finalMaze);
	
	//printEncodedMaze(arr, 32);
	
	/* 
	Part 6
	*/
	//4 for loops  (very retarded to say) needed to iterate over ALL POSSIBLE combinations
	for(int i = 0; i < 4; i++){
		for(int y = 0; y < 4; y++){
			for(int z = 0; z < 4; z++){
				for(int b = 0; b < 4; b++){
					/*
					Note to Self.
					Initially I wanted to use 1 to 5 in my for loops but as I resorted to making a combinations array I had to change it to 4 or use the for loop as we would for an array
					My first approach was very long, tedious and SUPER INEFFICIENT however executed fairly quickly so i guess it was fine but had some unnecessary output so to simplify it
					I used this simple statement using a pointer as I am not sure if we are/were allowed to use pointers for this assignment.
					*/
					
					printf("%d , %d , %d , %d \n", i+1, y+1, z+1, b+1);
					merge8by8Mazes(combinations[i], combinations[y], combinations[z], combinations[b], finalMaze);	
					isPathInMaze(finalMaze, pathInMaze, 14);
					printf("\n");	
				}
			}
		}
	}
	
	
	return 0;
}
/*
PART 2
*/
//This basically goes over each row and over each bit to check if its a 1 or
//or 0 and do the desired action aka 1 = @ and 0 = well space lol
//PARAMETERS: arr, x as the size
//RETURN : NONE
void printEncodedMaze(int arr[], unsigned char x){

	for(int i = 0; i < x; i++){
		unsigned g = 1 << (x-1);
		for(int j = x-1; j>= 0; j--){
			
			if(arr[i] & g){
				
				printf("@");
			}else{
				printf(" ");
			}
			g = g/2;	
		}

		printf("\n");
	}
	printf("\n");
	return;	
	
}
/*
PART 3
*/
// takes help from part 2 with an additional if statement inside it but this just checks if the bits for the empty part of maze
// and tries to fill them in from the bits of the path array elements.
//PARAMETER: arr, path, x as the size
//RETURN : NONE
void printEncodedMazeWithPath(int arr[], int path[], unsigned char x){
	for(int i = 0; i < x; i++){
		unsigned g = 1 << (x-1);
		for(int j = x-1; j>= 0; j--){
			
			if(arr[i] & g){
				
				printf("@");
			}else if(path[i] & g){
				printf(".");
			}else{
				printf(" ");
			}
			g = g/2;	
		}
		printf("\n");
	}
	printf("\n");
	return;
}		
/*
PART 4
*/
//takes in 4 blocks prints them into @ and well space
//PARAMETERS : inputMaze, encodedMaze
//RETURN : NONE
void encode8by8Maze(char inputMaze[][8], int encodedMaze[]){
//to loop over 8 rows
	for(int x = 0; x<8; x++){
		int decimal = 0;
		int raisedToThePower = 0;
		raisedToThePower++;
		//to loop  over the bits and convert them into decimals 
		//and part 2 will do its trick to convert it into binarys and convert into the maze
		
		for(int y= 7; y>=0 ;y--){
			decimal = decimal + inputMaze[x][y] * raisedToThePower;
			raisedToThePower = raisedToThePower * 2;
			
		}
		//save the line into an integer and should have 1 ints.
		encodedMaze[x] = decimal;
	}
	//should send in an 1d array of 8 ints.
	printEncodedMaze(encodedMaze, 8);
	return;	
}
/*
PART 5
*/
//Merges the output of part 4 using all 4 blocks and its true potential is used in part 6 aka testing all possible combinations giving me ptsd from stats lol
//basically takes in first 7 lines for left side and last 7 lines aka excluding the first column of right side blocks
//and it also reduces the top most and bottom most lines.
//PARAMETERS: topLeft, topRight, bottomLeft, bottomRight
//RETURN : NONE
void merge8by8Mazes(int topLeft[], int topRight[], int bottomLeft[], int bottomRight[], int finalMaze[]){
	//have to iterate over the maze to fit in those values
	for(int e = 0; e<14; e++){
	//need these variables to store 
		char bytes;
		int decimal = 0;
		//have to iterate over the elements for the desired boxes for right/left half
		for(int x = 7; x>0; x--){
		//left
		// check if rows exceed 7 then enter these in lower half of the 14	
		//also its e-6 because we don't want it to go out of bounds for the bottomright array we can't use 8,9,10 and so on as its not that
		//arrays size so its i-6, note its note -7 because we dont want to include the first row for both the bottom blocks.
		//e-6 and e-7 can be tricky
			if(e >= 7){
			//read
				bytes = (bottomLeft[e-6]&(1<<(x))) >> (x);
			//set	
				decimal = decimal | bytes << ( 6 + x );

			}else{
			//read
				bytes = (topLeft[e]&(1<<(x))) >> (x);
			//set	
				decimal = decimal | bytes << (6+x);	
			}		
		}
		for(int x = 6; x>=0; x--){
		//right 
		// check if rows exceed 7 then enter these in lower half of the 14
			if(e >= 7){
			//read
			//also its e-6 because we don't want it to go out of bounds for the bottomright array we can't use 8,9,10 and so on as its not that
			//arrays size so its i-6, note its note -7 because we dont want to include the first row for both the bottom blocks.
			//e-6 and e-7 can be tricky
				bytes = (bottomRight[e-6]&(1<<(x))) >> (x);
			//set	
				decimal= decimal | bytes << (x);
				
				
				
			}else{
			//read
				bytes = (topRight[e]&(1<<(x))) >> (x);
			//set
				decimal = decimal | bytes << (x);
				
			}
			
		}
		//after setting the integers for lines fit them to the final maze.
		finalMaze[e] = decimal;	
	}
	//call this function to print it out lol
	printEncodedMaze(finalMaze, 14);
	return;

}
/*
feels wierd that part 6 is missing lol
PART 7
*/
//Basically part 6 checks for path bit by bit and if the path overlaps the walls of maze it basically doesnt fit hence returns a 0
//However there are 8 exceptional cases that return a 1 as the path correctly fits inside them. 
//PARAMETERS: final,pathInMaze, x as the size
//RETURN : 1 or 0 for path detected
char isPathInMaze(int final[], int pathInMaze[], unsigned char x){
	for(int j = 0; j < x; j++){
		for(int y = x-1; y >= 0; y--){
			if((final[j] & (1 << y) )>> y != 1){
				if((pathInMaze[j] & (1 << y)) >> y != 1){
					return 0;
				}
			}
		}
	}
	printf("The maze above consists the path.\n");
	return 1;

}






























