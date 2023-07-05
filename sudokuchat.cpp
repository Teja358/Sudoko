#include <iostream>
#include <vector>
#include <random>

// Size of the Sudoku grid
const int GRID_SIZE = 9;

// Function to print the Sudoku grid
void printGrid(const std::vector<std::vector<int>>& grid) {
    std::cout << "+-------+-------+-------+" << std::endl;
    for (int i = 0; i < GRID_SIZE; i++) {
        if (i % 3 == 0 && i != 0) {
            std::cout << "|-------+-------+-------|" << std::endl;
        }
        for (int j = 0; j < GRID_SIZE; j++) {
            if (j % 3 == 0 && j != 0) {
                std::cout << "| ";
            }
            if (grid[i][j] == 0) {
                std::cout << ". ";
            } else {
                std::cout << grid[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "+-------+-------+-------+" << std::endl;
}

// Function to check if a number can be placed at the given position in the grid
bool isValid(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
    // Check if the number exists in the same row
    for (int c = 0; c < GRID_SIZE; c++) {
        if (grid[row][c] == num) {
            return false;
        }
    }

    // Check if the number exists in the same column
    for (int r = 0; r < GRID_SIZE; r++) {
        if (grid[r][col] == num) {
            return false;
        }
    }

    // Check if the number exists in the same 3x3 grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (grid[startRow + r][startCol + c] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to generate a random Sudoku grid
std::vector<std::vector<int>> generateRandomGrid() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 9);

    std::vector<std::vector<int>> grid(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));

    // Fill the grid with random numbers
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            // Generate a random number between 1 and 9
            int num = dis(gen);

            // Check if the number is valid at the current position
            if (isValid(grid, row, col, num)) {
                grid[row][col] = num;
            }
        }
    }

    return grid;
}

// Function to check if the Sudoku grid is completely filled
bool isGridFilled(const std::vector<std::vector<int>>& grid) {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] == 0) {
                return false;
            }
        }
    }
    return true;
}

// Function to get user input for filling a cell
void getUserInput(int& row, int& col, int& num) {
    std::cout << "Enter the row (1-9), column (1-9), and number (1-9) to fill (space-separated): ";
    std::cin >> row >> col >> num;
    row--;
    col--;
}

int main() {
    std::cout << "Welcome to Sudoku!" << std::endl;

    // Generate a random Sudoku grid
    std::vector<std::vector<int>> grid = generateRandomGrid();

    // Game loop
    while (true) {
        // Print the Sudoku grid
        std::cout << std::endl;
        printGrid(grid);

        // Get user input
        int row, col, num;
        getUserInput(row, col, num);

        // Check if the input is valid
        if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE && num >= 1 && num <= 9) {
            // Check if the cell is empty
            if (grid[row][col] == 0) {
                // Check if the number can be placed in the cell
                if (isValid(grid, row, col, num)) {
                    // Fill the cell with the number
                    grid[row][col] = num;

                    // Check if the grid is completely filled
                    if (isGridFilled(grid)) {
                        std::cout << std::endl;
                        std::cout << "Congratulations! You solved the Sudoku puzzle!" << std::endl;
                        break;
                    }
                } else {
                    std::cout << "Invalid number! Please try again." << std::endl;
                }
            } else {
                std::cout << "The cell is already filled! Please try again." << std::endl;
            }
        } else {
            std::cout << "Invalid input! Please try again." << std::endl;
        }
    }

    return 0;
}
