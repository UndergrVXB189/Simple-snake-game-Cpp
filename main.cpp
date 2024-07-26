#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int width = 20;
const int height = 10;
const string fullTail = "loveyou<3 ";

class SnakeGame {
private:
    bool gameOver;
    int score;
    int snakeX, snakeY;
    int fruitX, fruitY;
    int tailX[100]{ 0 };
    int tailY[100]{ 0 };
    int tailLength;
    int currentFruitIndex;
    enum class eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    eDirection dir;

public:
    SnakeGame() {
        gameOver = false;
        score = 0;
        snakeX = width / 2;
        snakeY = height / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tailLength = 0;
        currentFruitIndex = 0;
        dir = eDirection::STOP;
    }

    void Setup() {
        gameOver = false;
        score = 0;
        snakeX = width / 2;
        snakeY = height / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tailLength = 0;
        currentFruitIndex = 0;
        dir = eDirection::STOP;
    }

    void Draw() {
        system("cls");
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    cout << "#";
                if (i == snakeY && j == snakeX)
                    cout << "I"; 
                else {
                    bool printTail = false;
                    for (int k = 0; k < tailLength; k++) {
                        if (tailX[k] == j && tailY[k] == i) {
                            cout << fullTail[k];
                            printTail = true;
                        }
                    }
                    if (!printTail) {
                        if (i == fruitY && j == fruitX)
                            cout << char('a' + currentFruitIndex); 
                        else
                            cout << " ";
                    }
                }

                if (j == width - 1)
                    cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        cout << "Score:" << score << endl;
    }

    void Input() {
        if (_kbhit()) {
            switch (_getch()) {
            case 'a':
                dir = eDirection::LEFT;
                break;
            case 'd':
                dir = eDirection::RIGHT;
                break;
            case 'w':
                dir = eDirection::UP;
                break;
            case 's':
                dir = eDirection::DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            }
        }
    }

    void Logic() {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = snakeX;
        tailY[0] = snakeY;

        for (int i = 1; i < tailLength; i++) {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        switch (dir) {
        case eDirection::LEFT:
            snakeX--;
            break;
        case eDirection::RIGHT:
            snakeX++;
            break;
        case eDirection::UP:
            snakeY--;
            break;
        case eDirection::DOWN:
            snakeY++;
            break;
        default:
            break;
        }

        if (snakeX >= width)
            snakeX = 0;
        else if (snakeX < 0)
            snakeX = width - 1;
        if (snakeY >= height)
            snakeY = 0;
        else if (snakeY < 0)
            snakeY = height - 1;

        for (int i = 0; i < tailLength; i++) {
            if (tailX[i] == snakeX && tailY[i] == snakeY)
                gameOver = true;
        }

        if (snakeX == fruitX && snakeY == fruitY) {
            score += 10;
            currentFruitIndex++;
            tailLength++;
            if (currentFruitIndex >= fullTail.length()) {
                currentFruitIndex = 0;
                gameOver = true;
            }
            fruitX = rand() % width;
            fruitY = rand() % height;
        }
    }

    void RunGame() {
        Setup();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(100);
        }
    }

    int GetScore() {
        return score;
    }
};

int main() {
    SnakeGame game;
    game.RunGame();
    cout << "Game Over!" << endl;
    if (game.GetScore() >= 100)
        cout << "You Win! Iloveyou<3" << endl;
    else
        cout << "You Lose! Try again!" << endl;
    cout << "Score: " << game.GetScore() << endl;
    cout << "Press enter to exit..." << endl;
    cin.get();
    return 0;
}
//VXB1ll