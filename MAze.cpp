#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to check if the current position is within the bounds of the maze and not a dead end
bool isValid(vector<vector<int>>& maze, vector<vector<int>>& visited, int x, int y) {
    int N = maze.size();
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] > 0 && visited[x][y] == 0);
}

// Utility function to print the solution matrix
void printSolution(vector<vector<int>>& solution) {
    for (int i = 0; i < solution.size(); i++) {
        for (int j = 0; j < solution[i].size(); j++) {
            cout << solution[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Recursive function to explore the maze
void exploreMaze(vector<vector<int>>& maze, vector<vector<int>>& solution, vector<vector<int>>& visited, int x, int y, int& maxLength, int length) {
    int N = maze.size();

    // Check if the current position is out of the matrix or is a dead-end
    if (!isValid(maze, visited, x, y)) return;

    // If the destination is reached
    if (x == N - 1 && y == N - 1) {
        solution[x][y] = 1;
        if (length > maxLength) {
            maxLength = length;
            printSolution(solution);
        }
        solution[x][y] = 0;
        return;
    }

    // Mark the current position as part of the solution path
    solution[x][y] = 1;
    visited[x][y] = 1;

    // Explore all four possible moves based on the jump value
    for (int jump = 1; jump <= maze[x][y]; jump++) {
        // Move right
        if (isValid(maze, visited, x, y + jump)) {
            exploreMaze(maze, solution, visited, x, y + jump, maxLength, length + 1);
        }
        // Move down
        if (isValid(maze, visited, x + jump, y)) {
            exploreMaze(maze, solution, visited, x + jump, y, maxLength, length + 1);
        }
        // Move left
        if (isValid(maze, visited, x, y - jump)) {
            exploreMaze(maze, solution, visited, x, y - jump, maxLength, length + 1);
        }
        // Move up
        if (isValid(maze, visited, x - jump, y)) {
            exploreMaze(maze, solution, visited, x - jump, y, maxLength, length + 1);
        }
    }

    // Unmark the current position (backtrack)
    solution[x][y] = 0;
    visited[x][y] = 0;
}

int main() {
    vector<vector<int>> maze = {
        {1, 1, 0, 1, 0},
        {1, 1, 1, 0, 0},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 1, 0},
        {1, 1, 1, 1, 1}
    };

    int N = maze.size();
    vector<vector<int>> solution(N, vector<int>(N, 0));
    vector<vector<int>> visited(N, vector<int>(N, 0));
    int maxLength = 0;

    exploreMaze(maze, solution, visited, 0, 0, maxLength, 0);

    if (maxLength == 0) {
        cout << "No path found from source to destination." << endl;
    }
    else {
        cout << "Length of longest path is " << maxLength << endl;
    }

    return 0;
}
