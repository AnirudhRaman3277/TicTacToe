#include <iostream>

enum class Player { X, O };

class TicTacToe {
public:
    TicTacToe() : currentPlayer(Player::X) {
        // Initialize the grid
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                grid[i][j] = ' ';
            }
        }
    }

    void handleInput(int position) {
        int row = (position - 1) / 3;
        int col = (position - 1) % 3;

        if (grid[row][col] == ' ' && !isGameOver()) {
            grid[row][col] = (currentPlayer == Player::X) ? 'X' : 'O';
            togglePlayer();
        }
    }

    bool isGameOver() const {
        return checkRows() || checkColumns() || checkDiagonals();
    }

    Player getCurrentPlayer() const {
        return currentPlayer;
    }

    char getSymbol(int row, int col) const {
        return grid[row][col];
    }

private:
    bool checkRows() const {
        for (int i = 0; i < 3; ++i) {
            if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
                return true;
            }
        }
        return false;
    }

    bool checkColumns() const {
        for (int j = 0; j < 3; ++j) {
            if (grid[0][j] != ' ' && grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j]) {
                return true;
            }
        }
        return false;
    }

    bool checkDiagonals() const {
        return (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) ||
               (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]);
    }

    void togglePlayer() {
        currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
    }

    char grid[3][3];
    Player currentPlayer;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(300, 300), "Tic Tac Toe");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Font not found. Exiting..." << std::endl;
        return 1;
    }

    TicTacToe game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    // Determine which cell was clicked
                    int position = (mouseY / 100) * 3 + (mouseX / 100) + 1;

                    // Handle the input and check for game over
                    game.handleInput(position);
                }
            }
        }

        window.clear();

        // Draw the grid
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                sf::RectangleShape cell(sf::Vector2f(100, 100));
                cell.setPosition(i * 100, j * 100);
                cell.setOutlineThickness(2);
                cell.setOutlineColor(sf::Color::Black);
                window.draw(cell);

                sf::Text text;
                text.setFont(font);
                text.setCharacterSize(40);
                text.setPosition(i * 100 + 30, j * 100 + 20);

                if (game.getSymbol(i, j) == 'X') {
                    text.setString("X");
                } else if (game.getSymbol(i, j) == 'O') {
                    text.setString("O");
                }

                window.draw(text);
            }
        }

        // Display the winner or current player
        sf::Text statusText;
        statusText.setFont(font);
        statusText.setCharacterSize(20);
        statusText.setPosition(10, 300);

        if (game.isGameOver()) {
            statusText.setString("Game Over! Player " +
                                 ((game.getCurrentPlayer() == Player::X) ? "O" : "X") +
                                 " wins!");
        } else {
            statusText.setString("Current Player: " +
                                 ((game.getCurrentPlayer() == Player::X) ? "X" : "O"));
        }

        window.draw(statusText);

        window.display();
    }

    return 0;
}
