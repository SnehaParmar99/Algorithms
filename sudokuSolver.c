#include <iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<algorithm>
#include<sys/time.h>
#define boxsize 3
#define gridsize 9
using namespace std;
int globalCounter = 0;
int blanks = 0;
int clues = 0;
class Element
{
public:
int data;
bool modify; // if this is set to 1 it can be modified. IF 0, it is part of puzzle and cannot be modified
public :
Element(){};
Element(int data1,int modify1)
{
	data = data1;
	modify = modify1;
}
};

void printGrid(int grid[][gridsize]) ;//grid should be gridsizexgridsize integer matrix;
void printGridToSolve(Element grid[][gridsize]) ;//grid should be gridsizexgridsize integer matrix;
void createPuzzle(int grid[][gridsize]) ; //creates random Sudoku puzzle;
/*bool checkRow(int grid[][gridsize], int toInsert, int row ); //check if value toInsert is already present in the same row
bool checkColumn(int grid[][gridsize], int toInsert, int column); //check if value toInsert is already present in the same column
bool checkBox(int grid[][gridsize],int toInsert,int row,int column); // check if value toInsert is already present in the same box
*/
bool create(int grid[][gridsize],int row,int column,vector<int> numbers);
//bool canCreate(int grid[][gridsize],int i,int j,int* toInsert,vector<int> numbers);
void createGridToSolve(int grid[][gridsize],Element gridtosolve[][gridsize]);
bool solve(Element gridtosolve[][gridsize],int row,int column,vector<int> numbers);

int main()
{
	int m[gridsize][gridsize] = {0};

  //  printGrid(m);
    createPuzzle(m);
   // printGrid(m);
    cout<<endl<<"overall time = "<<globalCounter<<" blanks = "<<blanks<<" clues = "<<clues;
   return 0;
}
//vector<int> numbers (gridsize);

void createPuzzle(int grid[][gridsize])
{
int row = 0;
int column = 0;
vector<int> numbers (gridsize);
for(int i = 1 ; i < gridsize+1; i++)
	numbers[i-1] = i;

srand ( time(NULL) );
create( grid,row,column,numbers);


Element gridtosolve[gridsize][gridsize];
for(int i = 0 ;i<gridsize;i++)
	for(int j = 0 ;j<gridsize;j++)
	{
		gridtosolve[i][j].data = 0;
		gridtosolve[i][j].modify = true;
	}

srand ( time(NULL) );
printGrid(grid);
cout<<"With blanks : "<<endl;

struct timeval startT, endT;
gettimeofday(&startT, NULL);

createGridToSolve (grid,gridtosolve);

gettimeofday(&endT, NULL);

cout<<"time taken in microseconds was" << ((endT.tv_sec * gridsize+100000 + endT.tv_usec)  - (startT.tv_sec * gridsize+100000 + startT.tv_usec))<<endl;


//printGridToSolve(gridtosolve);

vector<int> numbers1 (gridsize);
for(int i = 1 ; i < gridsize+1; i++)
	numbers1[i-1] = i;

srand ( time(NULL) );
Element gridtosolve2[gridsize][gridsize];

int sample[][gridsize] = {
				{3,4,1,0},{0,2,0,0},{0,0,2,0},{0,1,4,3}

};
for(int i = 0 ;i<gridsize;i++)
	for(int j = 0 ;j<gridsize;j++)
	{
		gridtosolve2[i][j].data = sample[i][j];
		gridtosolve2[i][j].modify = !(sample[i][j]);
	}
printGridToSolve(gridtosolve);

solve( gridtosolve,row,column,numbers1);
cout<<"Solved Grid = "<<endl;
printGridToSolve(gridtosolve);

}
void createGridToSolve(int grid[][gridsize],Element gridtosolve[][gridsize])
{
	for(int i = 0 ;i<gridsize;i++)
		for(int j = 0 ;j<gridsize;j++)
		{
			if((rand() % 100) > 55)
			{
				gridtosolve[i][j].data = grid[i][j];
				gridtosolve[i][j].modify = false;
				clues++;
			} else blanks++;

		}
}

bool create(int grid[][gridsize],int row,int column,vector<int> numbers)
{
	if(row == 0 && column == 1)
	{
		//for (int i = 0 ;i < numbers.size();i++)

	}
	for(int j = 0 ;j<gridsize;j++)
	{
		int element = grid[row][j];
		if(element>0 && element <gridsize+1)
		{
			numbers.erase(std::remove(numbers.begin(), numbers.end(), element), numbers.end());
		}
	}
	for(int i = 0 ;i<gridsize;i++)
		{
			int element = grid[i][column];
			if(element>0 && element <gridsize+1)
			{
				numbers.erase(std::remove(numbers.begin(), numbers.end(), element), numbers.end());
			}
		}
	int boxRow = (row/boxsize)*boxsize;
	int boxColumn = (column/boxsize)*boxsize;
	for(int i = 0 ; i < boxsize ; i++, boxRow++, boxColumn = (column/boxsize)*boxsize)
	    for(int j = 0 ; j < boxsize ; j++, boxColumn++)
	    {
	    	int element = grid[boxRow][boxColumn];
	            if(element>0 && element <gridsize+1)
	                {
	                numbers.erase(remove(numbers.begin(), numbers.end(),element), numbers.end());
	                }
	    }
	int toInsertIndex;
	if(numbers.size()==0)
		return false;
	else
		{
		toInsertIndex = rand()%(numbers.size());
		//if(column == gridsize-1){printGrid(grid);cout<<numbers.size()<<endl;}
		grid[row][column] = numbers[toInsertIndex];
		bool nextSuccess;
		if(column == gridsize-1 && row == gridsize-1)
			return true;

		vector<int> numbers1(gridsize);
		for(int i = 1 ; i < gridsize+1; i++)
			numbers1[i-1] = i;
		if(column < gridsize-1)
			nextSuccess = create(grid,row,column+1,numbers1);
		if(column == gridsize-1 && row < gridsize-1)
			nextSuccess = create(grid,row+1,0,numbers1);
		//backtrack
		if(nextSuccess == false)
			{
			numbers.erase(remove(numbers.begin(), numbers.end(),grid[row][column]), numbers.end());
			grid[row][column] = 0;
			return create(grid,row,column,numbers);
			}
		else return true;
		}

}

bool solve(Element grid[][gridsize],int row,int column,vector<int> numbers)
{
	globalCounter++;
	//cout<<"printing within "<<row<<" "<<column<<" "<<endl;
	//printGridToSolve(grid);
	//cout<<"printing within end"<<endl;
if(grid[row][column].modify)
{

	if(row == 0 && column == 1)
	{
		//for (int i = 0 ;i < numbers.size();i++)

	}
	for(int j = 0 ;j<gridsize;j++)
	{
		int element = grid[row][j].data;
		if(element>0 && element <gridsize+1)
		{
			numbers.erase(std::remove(numbers.begin(), numbers.end(), element), numbers.end());
		}
	}
	for(int i = 0 ;i<gridsize;i++)
		{
			int element = grid[i][column].data;
			if(element>0 && element <gridsize+1)
			{
				numbers.erase(std::remove(numbers.begin(), numbers.end(), element), numbers.end());
			}
		}
	int boxRow = (row/boxsize)*boxsize;
	int boxColumn = (column/boxsize)*boxsize;
	for(int i = 0 ; i < boxsize ; i++, boxRow++, boxColumn = (column/boxsize)*boxsize)
	    for(int j = 0 ; j < boxsize ; j++, boxColumn++)
	    {
	    	int element = grid[boxRow][boxColumn].data;
	            if(element>0 && element <gridsize+1)
	                {
	                numbers.erase(remove(numbers.begin(), numbers.end(),element), numbers.end());
	                }
	    }
	int toInsertIndex;
	if(numbers.size()==0)
		return false;
	else
		{
		toInsertIndex = 0;//rand()%(numbers.size());
		//if(column == gridsize-1){printGrid(grid);cout<<numbers.size()<<endl;}
		grid[row][column].data = numbers[toInsertIndex];

		bool nextSuccess;
		if(column == gridsize-1 && row == gridsize-1)
			return true;

		vector<int> numbers1(gridsize);
		for(int i = 1 ; i < gridsize+1; i++)
			numbers1[i-1] = i;
		if(column < gridsize-1)
			nextSuccess = solve(grid,row,column+1,numbers1);
		if(column == gridsize-1 && row < gridsize-1)
			nextSuccess = solve(grid,row+1,0,numbers1);

		//backtrack
		if(nextSuccess == false)
			{
			numbers.erase(remove(numbers.begin(), numbers.end(),grid[row][column].data), numbers.end());
			grid[row][column].data = 0;
			return solve(grid,row,column,numbers);
			}
		else return true;
		}
}
else
	{
	if(column == gridsize-1 && row == gridsize-1)
				return true;

			vector<int> numbers1(gridsize);
			for(int i = 1 ; i < gridsize+1; i++)
				numbers1[i-1] = i;
			if(column < gridsize-1)
				return solve(grid,row,column+1,numbers1);
			if(column == gridsize-1 && row < gridsize-1)
				return solve(grid,row+1,0,numbers1);
	}

}

void printGrid(int grid[][gridsize]) //grid should be gridsizexgridsize integer matrix
{
    for(int i = 0;i<gridsize;i++)
    {
        for(int j= 0;j<gridsize;j++)
            cout<<grid[i][j]<<(((j+1)%boxsize==0)?" ":"");
        cout<<endl<<(((i+1)%boxsize==0)?"\n":"");

    }
}
void printGridToSolve(Element grid[][gridsize])
{
	for(int i = 0;i<gridsize;i++)
	    {
	        for(int j= 0;j<gridsize;j++)
	        {
	        	int element = grid[i][j].data;
	        	if(element  == 0)
	        		cout<<"_"<<(((j+1)%boxsize==0)?"   ":" ");
	        	else
	        		cout<<element<<(((j+1)%boxsize==0)?"   ":" ");
	            //cout<<((grid[i][j].data==0)?"-":itoa(grid[i][j].data))<<(((j+1)%boxsize==0)?" ":"");
	        }
	        cout<<endl<<(((i+1)%boxsize==0)?"\n":" ");

	    }
}

