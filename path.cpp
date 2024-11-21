#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Path 
{
    private:
        int rows, cols; // Rows and columns of the grid
        int *grid; // Grid representing the path

    public:
        Path(const char *fname, int m, int n); // Constructor function
        ~Path(); // Destructor
        void lowestfind(int &lowR, int &lowC); // Find the lowest point
        void Highestfind(int &highR, int &highC); // Find the highest point
    bool findPaths(int lowR, int lowC, int highR, int highC, int startRow, int startCol,int preheight); // Find a path between lowest and highest points
};

Path::Path(const char *fname, int m, int n) 
{
    rows = m;
    cols = n;

    grid = new int[rows * cols];

    ifstream infile(fname);

    for (int i = 0; i < rows; i++) // gets thing from file
    {
        int base = i * cols;
        for (int offset = 0; offset < cols; offset++) 
        {
            infile >> grid[base + offset];
        }
    }

    infile.close();
}

Path::~Path()
 {
    delete[] grid; // deletes thing at the end
}

void Path::lowestfind(int &lowR, int &lowC) // finds the lowest point in the grid and output cords
{
    int lowest = grid[0];
    lowR = 0;
    lowC = 0;
    for (int i = 0; i < rows; i++) 
    {
        int base = i * cols;
        for (int offset = 0; offset < cols; offset++)
         {
            if (grid[base + offset] < lowest) 
            {
                lowest = grid[base + offset];
                lowR = i;
                lowC = offset;
            }
        }
    }
}

void Path::Highestfind(int &highR, int &highC) // finds the highest point in the grid and output cords
{
    int highest = grid[0];
    highR = 0;
    highC = 0;
    for (int i = 0; i < rows; i++)
     {
        int base = i * cols;
        for (int offset = 0; offset < cols; offset++)
         {
            if (grid[base + offset] > highest) 
            {
                highest = grid[base + offset];
                highR = i;
                highC = offset;
            }
        }
    }
}

bool Path::findPaths(int lowR, int lowC, int highR, int highC, int startRow, int startCol,int preheight) 
{
    if (startRow < 0 || startCol < 0 || startRow >= rows || startCol >= cols) 
    {
        return false;
    }

    int currentHeight = grid[startRow * cols + startCol];

    // Check if the path goes down
    if (currentHeight < preheight) 
    {
        return false;
    }

    // Check if we've reached the highest point
    if (currentHeight == grid[highR * cols + highC]) 
    {
        return true;
    }

    // Mark current cell as visited
    grid[startRow * cols + startCol] = 0;

    // Explore all four directions
    return findPaths(lowR, lowC, highR, highC, startRow + 1, startCol,currentHeight) ||
           findPaths(lowR, lowC, highR, highC, startRow - 1, startCol,currentHeight) ||
           findPaths(lowR, lowC, highR, highC, startRow, startCol + 1,currentHeight) ||
           findPaths(lowR, lowC, highR, highC, startRow, startCol - 1,currentHeight);
}

int main(int argc, char *argv[]) 
{
   

    int row = atoi(argv[2]); // number of rows in grid
    int col = atoi(argv[3]); // number of columns in grid

    // Create Path object
    Path myPath(argv[1], row, col);

    // Find lowest and highest points
    int lowR, lowC, highR, highC;
    myPath.lowestfind(lowR, lowC);
    myPath.Highestfind(highR, highC);

    // Output lowest and highest points (1-indexed)
    cout << lowR + 1 << " " << lowC + 1 << " " << highR + 1 << " " << highC + 1 << " ";

    // Find if there is a path from lowest to highest without going down
    if (myPath.findPaths(lowR, lowC, highR, highC, lowR, lowC, 0)) 
    {
        std::cout << "yes" << endl;
    } 
    else
     {
        std::cout << "no" << endl;
    }

    return 0;
}

