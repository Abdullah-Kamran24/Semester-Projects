#include <iostream>
#include <ctime>
#include<conio.h>
#include <fstream>
//#include <cstdlib>
//#include<stdlib.h>
#include <windows.h>


#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26   //height of the screen in characters.
#define WIN_WIDTH 70       //width of the main gameplay window.
#define MENU_WIDTH 20       //width reserved for the side menu
#define GAP_SIZE 7          //gap size between obstacles(Flappy Bird)
#define PIPE_DIF 45         //set the horizontal difference (distance) between two pipes 

using namespace std;

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

class hangman
{
private:
    // Node class for linked list (incorrect guesses)
    class Node
    {
    public:
        char letter;
        Node *next;
        Node(char l)
        {
            letter = l;
            next = nullptr;
        }
    };

    // Stack class for previous guesses
    class Stack
    {
    private:
        static const int SIZE = 50;
        char data[SIZE];
        int top;

    public:
        Stack()
        {
            top = -1;
        }

        void push(char ch)
        {
            if (!isFull())
            {
                data[++top] = ch;
            }
        }

        char pop()
        {
            if (!isEmpty())
            {
                return data[top--];
            }
            return '\0';
        }

        bool isEmpty()
        {
            return top == -1;
        }

        bool isFull()
        {
            return top == SIZE - 1;
        }

        void display()
        {
            for (int i = top; i >= 0; --i)
            {
                cout << data[i] << " ";
            }
            cout << "\n";
        }
    };

    // Word and game variables
    string word;
    string hint;
    string guessedWord;
    int lives;
    Stack previousGuesses;
    Node *incorrectGuessesHead;

    // Word list
    struct WordEntry
    {
        string word;
        string hint;
    };

    WordEntry wordLibrary[23] = {
        {"red", "Color"}, {"blue", "Color"}, {"green", "Color"}, {"orange", "Color"}, {"white", "Color"},   //FOr color
        {"lust", "Deadly Sin"}, {"envy", "Deadly Sin"}, {"wrath", "Deadly Sin"}, {"greed", "Deadly Sin"},   //Deadly sins
        {"sloth", "Deadly Sin"}, {"pride", "Deadly Sin"}, {"gluttony", "Deadly Sin"},  
        {"happiness", "Emotion"}, {"sadness", "Emotion"}, {"fear", "Emotion"}, {"disgust", "Emotion"}, {"anger", "Emotion"},  //for emotions
        {"orange", "Fruit"}, {"apple", "Fruit"}, {"banana", "Fruit"},   //fruits
        {"toyota", "Car Brand"}, {"suzuki", "Car Brand"}, {"ford", "Car Brand"}}; //for cars

    // Random word selector
    int randomIndex()
    {
        srand(time(0));
        return rand() % 23;
    }

    // Add incorrect guess to linked list
    void addIncorrectGuess(char guess)
    {
        Node *newNode = new Node(guess);
        newNode->next = incorrectGuessesHead;
        incorrectGuessesHead = newNode;
    }

    // Clear incorrect guess list
    void clearIncorrectGuesses()
    {
        while (incorrectGuessesHead)
        {
            Node *temp = incorrectGuessesHead;
            incorrectGuessesHead = incorrectGuessesHead->next;
            delete temp;
        }
    }

    // Show hangman stages
    void displayHangman()
    {
        const string stages[] = {
            "  +---+\n      |\n      |\n      |\n      |\n      |\n",
            "  +---+\n  |   |\n      |\n      |\n      |\n      |\n",
            "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n",
            "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n",
            "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n",
            "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n",
            "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n",
            "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n"};

        int stageIndex = 7 - lives;
        if (stageIndex < 0)
            stageIndex = 0;
        else if (stageIndex > 7)
            stageIndex = 7;

        cout << stages[stageIndex] << "\n";
    }

    // Check if game is over
    bool isGameOver()
    {
        return lives == 0 || guessedWord == word;
    }

    // Display current game status
    void displayStatus()
    {
        cout << "Word: " << guessedWord << "\n";
        cout << "Lives: " << lives << "\n";
        cout << "Incorrect guesses: ";

        Node *temp = incorrectGuessesHead;
        while (temp)
        {
            cout << temp->letter << " ";
            temp = temp->next;
        }
        cout << "\n";

        cout << "Previous guesses (stack): ";
        Stack tempStack = previousGuesses;
        while (!tempStack.isEmpty())
        {
            cout << tempStack.pop() << " ";
        }
        cout << "\n";
    }

    // Show welcome message and rules
    void displayMessage()
    {
        cout << GREEN;
        cout <<endl<<endl<< "RULES:\n";
        cout << "- You start with some lives which are displayed.\n";
        cout << "- The computer will choose a random word.\n";
        cout << "- Guess one letter at a time.\n";
        cout << "- Correct guesses reveal the letters in the word.\n";
        cout << "- Incorrect guesses cost a life.\n";
        cout << "- Try to guess the word before running out of lives!\n\n";
        cout << RESET;

        char start_end;
        while (true)
        {
            cout << "\n\tPress 'E'/'e' to Continue: \n";
            cout << "\t\tOR  \n\t'Q'/'q' to Quit: \n";
            cout << "Enter your choice: ";
            cin >> start_end;
            start_end = tolower(start_end);

            if (start_end == 'e' || start_end == 'q')
                break;

            cout << "Invalid input! Please press 'E' to continue or 'Q' to quit.\n";
        }

        if (start_end == 'q')
        {
            cout << "QUITTING......\n";
            exit(0);
        }

        cout << "Hint: " << hint << "\n";
    }

    // Process the player's guess
    bool makeGuess(char guess)
    {
        previousGuesses.push(guess);
        bool correct = false;

        for (size_t i = 0; i < word.length(); i++)
        {   //t will place it in all positions where word exists 
            if (word[i] == guess && guessedWord[i] == '_')
            {
                guessedWord[i] = guess;
                correct = true;
            }
        }

        if (!correct)
        {
            lives--;
            addIncorrectGuess(guess);
        }

        return correct;
    }

    // Check win
    bool didWin()
    {
        return guessedWord == word;
    }

public:
    // Main gameplay function
    void play()
    {
        while (true)
        {
            int index = randomIndex();
            //We set the secret word and its hint based on the random index.
            word = wordLibrary[index].word;
            hint = wordLibrary[index].hint;
            lives = word.length() / 2 + 1;
            incorrectGuessesHead = nullptr;
            guessedWord = string(word.length(), '_');
            previousGuesses = Stack();

            displayMessage();

            while (!isGameOver())
            {
                displayHangman();
                displayStatus();    //show the current word, remaining lives, wrong guesses, and previous guesses.

                char guess;
                cout << "Enter your guess: ";
                cin >> guess;
                makeGuess(tolower(guess));    //make the guess after converting it to lowercase
            }

            displayHangman();
            if (didWin())
            {
                cout << "Congratulations! You guessed the word!\n";
            }
            else
            {
                cout << "Game Over! The correct word was: " << word << "\n";
            }

            char replay;
            cout << "Do you want to play again? (y/n): ";
            cin >> replay;
            if (tolower(replay) != 'y')
                break;

            clearIncorrectGuesses();
        }

        cout << "===================================\n";
        cout << "       Thanks for playing!       \n";
        cout << "===================================\n";
    }
};

class flappyBird {
    public:
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        HANDLE buffer[2];
        int activeBuffer = 0;
        COORD CursorPosition;
    
        int pipePos[3];
        int gapPos[3];
        int pipeFlag[3];
    
        char bird[2][6] = {
            '/','-','-','o','\\',' ',
            '|','_','_','_',' ','>'
        };
    
        int birdPos = 6;
        int score = 0;
        int highScore = 0;
    
        flappyBird() {
            buffer[0] = GetStdHandle(STD_OUTPUT_HANDLE);
            buffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
            SetConsoleActiveScreenBuffer(buffer[activeBuffer]);
            console = buffer[activeBuffer];
            setcursor(0, 0);
            loadHighScore();
        }
    
        void gotoxy(int x, int y) {
            CursorPosition.X = x;
            CursorPosition.Y = y;
            SetConsoleCursorPosition(console, CursorPosition);
        }
    
        void setcursor(bool visible, DWORD size) {
            if (size == 0) size = 20;
            CONSOLE_CURSOR_INFO lpCursor;
            lpCursor.bVisible = visible;
            lpCursor.dwSize = size;
            SetConsoleCursorInfo(console, &lpCursor);
        }
    
        void drawBorder() {
            for (int i = 0; i < SCREEN_WIDTH; i++) {
                gotoxy(i, 0); cout << CYAN << "#" << RESET;
                gotoxy(i, SCREEN_HEIGHT); cout << CYAN << "#" << RESET;
            }
            for (int i = 0; i < SCREEN_HEIGHT; i++) {
                gotoxy(0, i); cout << CYAN << "#" << RESET;
                gotoxy(SCREEN_WIDTH, i); cout << CYAN << "#" << RESET;
                gotoxy(WIN_WIDTH, i); cout << CYAN << "#" << RESET;
            }
        }
    
        void genPipe(int ind) {
            gapPos[ind] = 3 + rand() % 14;
        }
    
        void drawPipe(int ind) {
            if (pipeFlag[ind]) {
                for (int i = 0; i < gapPos[ind]; i++) {
                    gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << GREEN << "***" << RESET;
                }
                for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {
                    gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << GREEN << "***" << RESET;
                }
            }
        }
    
        void erasePipe(int ind) {
            if (pipeFlag[ind]) {
                for (int i = 0; i < gapPos[ind]; i++) {
                    gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
                }
                for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {
                    gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
                }
            }
        }
    
        void drawBird() {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 6; j++) {
                    gotoxy(j + 2, i + birdPos);
                    cout << YELLOW << bird[i][j] << RESET;
                }
            }
        }
    
        void eraseBird() {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 6; j++) {
                    gotoxy(j + 2, i + birdPos);
                    cout << " ";
                }
            }
        }
    
        int collision() {
            if (pipePos[0] >= 61) {
                if (birdPos < gapPos[0] || birdPos > gapPos[0] + GAP_SIZE) {
                    return 1;
                }
            }
            return 0;
        }
    
        void updateScore() {
            gotoxy(WIN_WIDTH + 7, 5); cout << MAGENTA << "Score: " << score << RESET;
            gotoxy(WIN_WIDTH + 7, 6); cout << MAGENTA << "High: " << highScore << RESET;
        }
    
        void gameover() {
            saveHighScore();
            SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
            system("cls");
            cout << "\n\n\t\t" << RED << "--- Game Over ---" << RESET << "\n\n";
            cout << "\t\tYour Score: " << YELLOW << score << RESET << "\n";
            cout << "\t\tHigh Score: " << GREEN << highScore << RESET << "\n\n";
            cout << "\t\tPress any key to return to menu.\n";
            getch();
        }
    
        void instructions() {
            system("cls");
            cout << CYAN << "Instructions\n";
            cout << "----------------\n" << RESET;
            cout << "Press SPACE to jump\n";
            cout << "Press ESC to exit\n";
            cout << "\nPress any key to return to menu.";
            getch();
        }
    
        void loadHighScore() {
            ifstream file("highscore.txt");
            if (file.is_open()) {
                file >> highScore;
                file.close();
            }
        }
    
        void saveHighScore() {
            if (score > highScore) {
                highScore = score;
                ofstream file("highscore.txt");
                if (file.is_open()) {
                    file << highScore;
                    file.close();
                }
            }
        }
    
        void play() {
            birdPos = 6;
            score = 0;
            pipeFlag[0] = 1; pipeFlag[1] = 0;
            pipePos[0] = pipePos[1] = 4;
    
            console = buffer[activeBuffer];
            SetConsoleActiveScreenBuffer(console);
            system("cls");
    
            drawBorder();
            genPipe(0);
            updateScore();
    
            gotoxy(WIN_WIDTH + 5, 2); cout << BLUE << "FLAPPY BIRD" << RESET;
            gotoxy(WIN_WIDTH + 7, 12); cout << "Controls";
            gotoxy(WIN_WIDTH + 2, 14); cout << "Spacebar = Jump";
    
            gotoxy(10, 5); cout << "Press any key to start";
            getch();
            gotoxy(10, 5); cout << "                      ";
    
            while (1) {
                if (kbhit()) {
                    char ch = getch();
                    if (ch == 32) {
                        if (birdPos > 3) birdPos -= 3;
                    }
                    if (ch == 27) return;
                }
    
                drawBird();
                drawPipe(0);
                drawPipe(1);
    
                if (collision()) {
                    gameover();
                    return;
                }
    
                Sleep(90);
                eraseBird();
                erasePipe(0);
                erasePipe(1);
    
                birdPos += 1;
    
                if (birdPos > SCREEN_HEIGHT - 2) {
                    gameover();
                    return;
                }
    
                if (pipeFlag[0]) pipePos[0] += 2;
                if (pipeFlag[1]) pipePos[1] += 2;
    
                if (pipePos[0] >= 40 && pipePos[0] < 42) {
                    pipeFlag[1] = 1;
                    pipePos[1] = 4;
                    genPipe(1);
                }
    
                if (pipePos[0] > 68) {
                    score++;
                    updateScore();
                    pipeFlag[1] = 0;
                    pipePos[0] = pipePos[1];
                    gapPos[0] = gapPos[1];
                }
            }
        }
    };

class CarGame {
    public:
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD CursorPosition;

        int enemyY[3];
        int enemyX[3];
        int enemyFlag[3];

        char car[4][4] = {
            {' ', '#', '#', ' '},
            {'#', '#', '#', '#'},
            {' ', '#', '#', ' '},
            {'#', '#', '#', '#'}
        };

        int carPos = WIN_WIDTH / 2;
        int score = 0;
        int highScore = 0;

        void gotoxy(int x, int y) {
            CursorPosition.X = x;
            CursorPosition.Y = y;
            SetConsoleCursorPosition(console, CursorPosition);
        }

        void setcursor(bool visible, DWORD size) {
            if (size == 0)
                size = 20;

            CONSOLE_CURSOR_INFO lpCursor;
            lpCursor.bVisible = visible;
            lpCursor.dwSize = size;
            SetConsoleCursorInfo(console, &lpCursor);
        }

        void setColor(int color) {
            SetConsoleTextAttribute(console, color);
        }

        void drawBorder() {
            setColor(14);
            for (int i = 0; i < SCREEN_HEIGHT; i++) {
                gotoxy(0, i); cout << "|";
                gotoxy(WIN_WIDTH, i); cout << "|";
            }

            for (int i = 0; i <= WIN_WIDTH; i++) {
                gotoxy(i, 0); cout << "-";
                gotoxy(i, SCREEN_HEIGHT); cout << "-";
            }
        }

        void genEnemy(int ind) {
            enemyX[ind] = 17 + rand() % 33;
        }

        void drawEnemy(int ind) {
            if (enemyFlag[ind] == true) {
                setColor(12);
                gotoxy(enemyX[ind], enemyY[ind]);     cout << "****";
                gotoxy(enemyX[ind], enemyY[ind] + 1); cout << " ** ";
                gotoxy(enemyX[ind], enemyY[ind] + 2); cout << "****";
                gotoxy(enemyX[ind], enemyY[ind] + 3); cout << " ** ";
            }
        }

        void eraseEnemy(int ind) {
            if (enemyFlag[ind] == true) {
                setColor(0);
                gotoxy(enemyX[ind], enemyY[ind]);     cout << "    ";
                gotoxy(enemyX[ind], enemyY[ind] + 1); cout << "    ";
                gotoxy(enemyX[ind], enemyY[ind] + 2); cout << "    ";
                gotoxy(enemyX[ind], enemyY[ind] + 3); cout << "    ";
            }
        }

        void resetEnemy(int ind) {
            eraseEnemy(ind);
            enemyY[ind] = 1;
            genEnemy(ind);
        }

        void drawCar() {
            setColor(9);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    gotoxy(j + carPos, i + 22); cout << car[i][j];
                }
            }
        }

        void eraseCar() {
            setColor(0);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    gotoxy(j + carPos, i + 22); cout << " ";
                }
            }
        }

        int collision() {
            for (int i = 0; i < 2; i++) {
                if (enemyFlag[i] == 1) {
                    if (enemyY[i] + 4 >= 22 && enemyY[i] <= 26) {
                        if (enemyX[i] + 4 >= carPos && enemyX[i] <= carPos + 3) {
                            return 1;
                        }
                    }
                }
            }
            return 0;
        }

        void loadHighScore() {
            ifstream file("highscore.txt");
            if (file.is_open()) {
                file >> highScore;
                file.close();
            }
        }

        void saveHighScore() {
            ofstream file("highscore.txt");
            if (file.is_open()) {
                file << highScore;
                file.close();
            }
        }

        void gameover() {
            system("cls");
            setColor(12);
            cout << endl;
            cout << "\t\t--------------------------" << endl;
            cout << "\t\t-------- Game Over -------" << endl;
            cout << "\t\t--------------------------" << endl << endl;
            cout << "\t\tYour Score: " << score << endl;

            if (score > highScore) {
                highScore = score;
                saveHighScore();
                cout << "\t\tNew High Score!" << endl;
            } else {
                cout << "\t\tHigh Score: " << highScore << endl;
            }

            setColor(15);
            cout << "\t\tPress any key to go back to menu.";
            getch();
        }

        void updateScore() {
            setColor(10);
            gotoxy(WIN_WIDTH + 7, 5); cout << "Score: " << score << " ";
        }

        void instructions() {
            system("cls");
            setColor(11);
            cout << "Instructions";
            cout << "\n----------------";
            cout << "\n Avoid Cars by moving left or right. ";
            cout << "\n\n Press 'A' to move left";
            cout << "\n Press 'D' to move right";
            cout << "\n Press 'ESC' to exit";
            cout << "\n\nPress any key to go back to menu...";
            setColor(15);
            getch();
        }

        void play() {
            loadHighScore();
            carPos = WIN_WIDTH / 2;
            score = 0;
            enemyFlag[0] = 1;
            enemyFlag[1] = 0;
            enemyY[0] = enemyY[1] = 1;

            system("cls");
            drawBorder();
            updateScore();

            genEnemy(0);
            genEnemy(1);

            setColor(15);
            gotoxy(WIN_WIDTH + 7, 2); cout << "Car Game";
            gotoxy(WIN_WIDTH + 6, 4); cout << "----------";
            gotoxy(WIN_WIDTH + 6, 6); cout << "----------";
            gotoxy(WIN_WIDTH + 7, 8); cout << "High Score:";
            gotoxy(WIN_WIDTH + 7, 9); cout << highScore;
            gotoxy(WIN_WIDTH + 7, 12); cout << "Controls";
            gotoxy(WIN_WIDTH + 7, 13); cout << "--------";
            gotoxy(WIN_WIDTH + 2, 14); cout << " A Key - Left";
            gotoxy(WIN_WIDTH + 2, 15); cout << " D Key - Right";

            gotoxy(18, 5); cout << "Press any key to start";
            getch();
            gotoxy(18, 5); cout << "                      ";

            while (1) {
                if (_kbhit()) {
                    char ch = _getch();
                    if (ch == 'a' || ch == 'A') {
                        if (carPos > 18)
                            carPos -= 4;
                    }
                    if (ch == 'd' || ch == 'D') {
                        if (carPos < 50)
                            carPos += 4;
                    }
                    if (ch == 27) {
                        break;
                    }
                }

                drawCar();
                drawEnemy(0);
                drawEnemy(1);

                if (collision()) {
                    gameover();
                    return;
                }

                Sleep(50);

                eraseCar();
                eraseEnemy(0);
                eraseEnemy(1);

                if (enemyY[0] == 10) {
                    if (enemyFlag[1] == 0)
                        enemyFlag[1] = 1;
                }

                if (enemyFlag[0] == 1) {
                    enemyY[0] += 1;
                }

                if (enemyFlag[1] == 1) {
                    enemyY[1] += 1;
                }

                if (enemyY[0] > SCREEN_HEIGHT - 4) {
                    resetEnemy(0);
                    score++;
                    updateScore();
                }

                if (enemyY[1] > SCREEN_HEIGHT - 4) {
                    resetEnemy(1);
                    score++;
                    updateScore();
                }
            }
        }
};


void gotoxy(int x, int y) 
{   //helper function to move the cursor to a specific (x, y) position in the console.
     COORD pos = { (SHORT)x, (SHORT)y };  //(SHORT)x and (SHORT)y cast the int values to SHORT, as COORD expects SHORT.
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);  //sets the console cursor position using a handle to the console and the position struct.
}

class Game {
        private:
            int x, y1;   //(x is horizontal, y1 is vertical for laser movement).
            const int y = 20;  //(playerâ€™s position)
            char c;  // user input key
            char character = '^';
            int x2, y2;   // Position of the ball
            int count1, count2;  //control horizontal and vertical ball movement
            int count;   
            char character2 = 79;    // ball's symbol (O).
            int score;
            int check;   //used for losing condition
        
        public:
            Game() 
            {
                resetGame(); // Initialize values
            }
        
            void resetGame() 
            { //Resets all values to start or restart the game.
                x = 46;
                y1 = y;
                x2 = 3;
                y2 = 10;
                count1 = 0;
                count2 = 0;
                count = 0;
                score = 0;
                check = 0;
            }
        
            void displayInstructions() 
            {
                cout << "\n\n\t\t" << GREEN
                     << "YOU MUST SCORE 5 POINTS TO WIN THE GAME! SHOOT LASER WRONGLY FIVE TIMES AND YOU LOSE!"
                     << RESET;
                cout << "\n\t\t\t\t\t\t" << YELLOW << "GOOD LUCK!" << RESET;
                getch();
            }
        
            void playGame() 
            {
                resetGame(); // Reset game state before each play
        
                while (check != 5 && score < 5) 
                { //loop continues until player wins (score == 5) or loses (check == 5).
                    system("cls");
        
                    gotoxy(40, 5);
                    cout << WHITE << "SCORE:\t" << score;
        //Displays the ball and the player at their respective positions with different colors.
                    gotoxy(x2, y2);
                    cout << MAGENTA << character2;
        
                    gotoxy(x, y);
                    cout << CYAN << character;
        
                    //getch() waits for a key press.
                    c = getch();
        
                    if (c == 'd')   //'d': move right by increasing x.
                    {
                        x += 2;
                    }

                    if (c == 'a')    //'a': move left by decreasing x.
                    {
                         x -= 2;
                    }
        
                    if (c == 'w')   //When 'w' is pressed, shoot a laser/arrow.
                    {
                        count--;
                        if (count <= 0)
                        {
                         system("cls");   
                        }
        
                        while (y1 >= 5) 
                        { //Moves the laser/arrow upward one step at a time
                            gotoxy(x, y1);
                            cout << "|";
                            y1--;
                            if (y1 == y2 && x == x2 + 1)
                            { //If laser/arrow coordinates match enemy's, it counts as a hit and increases score.
                                cout << "\a" << GREEN << "YOU GOT IT!" << RESET; //\a triggers beep sound.
                                score++;
                                break;
                            }
                            Sleep(20);
                        }
        
                        if (y1 != y2 || x != x2 + 1) 
                        { //(wrong shots counter
                            check++;
                            gotoxy(100, 5);   //Display "lives lost" at position (100, 5).
                            cout << RED << check << " LIVE(S) LOST " << (char)3 << RESET;
                        }
        
                        y1 = y;  //Reset laser to player's level for next shot.
                    }
        
                    if (c == ' ')   //If spacebar is pressed, exit the game early.
                    {
                        return;
                    }
        
                    // Move enemy//ball  Horizontal Movement
                    if (x2 < 116 && count1 < 50) 
                    {  // rightward movement of the enemy
                        x2++;       // Move the enemy one position to the right.
                        count1++;   // Increase count to limit how far it moves in one direction.
                        if (count1 == 49)
                        { //resets count1 to 0 to allow for possible change in direction
                             count1 = 0;
                        }
                    } 
                    else 
                    {
                        x2--; // If not moving right, move left.
                    }
                    
                    //Reset ball Position When It Reaches Far Right
                    if (x2 == 115) 
                    { //t jumps back to the left side (x2 = 3) and its vertical position y2 is reset to 10.
                        x2 = 3;
                        y2 = 10;
                    }
        
                    if (y2 < 20 && count2 <= 10) 
                    { //Moves the enemy down one step
                        y2++;
                        count2++;  //increments count2 to limit how far it moves downward.
                    } 
                    else 
                    {
                        y2--;  // Otherwise move up.
                        count2++;    // Keep counting to eventually reset
                        if (count2 == 21) 
                        {
                            count2 = 0;
                            y2 = 10;     // Reset to starting vertical position.
                        }
                    }
        
                    Sleep(50);  //r 50 milliseconds to control the speed of movement
                }
        
                system("cls");
                if (check == 5) 
                {
                    cout << "\n\n\n\n\n\t\t" << RED << "YOU LOST THE GAME. BETTER LUCK NEXT TIME! :(" << RESET;
                } 
                else 
                {
                    cout << "\n\n\n\n\n\n\t\t" << GREEN << "YOU WON THE GAME! CONGRATULATIONS!! :))" << RESET;
                }
                getch();
            }
};

int main()
{
    hangman hm;
    flappyBird fb;
    CarGame cg;
    Game gobj;
    int choice;
    char option;

    while (true) 
    {
        system("cls");
        cout<<MAGENTA;
        cout<<endl<<endl<<"\n\t\t\t========================================================"<<endl;
        cout << " \t\t\t\t\tWELCOME TO THE GAME BOX " << endl;
        cout <<"\t\t\t========================================================"<<endl;
        cout<<RESET;
        cout <<endl<<YELLOW<< "\n\t\t~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.  | MAIN MENU |  ~.~.~.~.~.~.~.~.~.~.~.~.~.~.~. "<<RESET<<endl;
        cout <<endl;;
        cout<<GREEN;
        cout << "\t\t\t1. Hangman Game" << endl;
        cout << "\t\t\t2. Flappy Bird Game" << endl;
        cout << "\t\t\t3. Car Game" << endl;
        cout << "\t\t\t4. Bubble Shooter Game" << endl;
        cout << "\t\t\t5. Exit" << endl;
        cout<<RESET;

        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                // hm.play();
                // break;
                    srand((unsigned)time(NULL));
                    while (true) 
                    {
                        system("cls");
                        
                        cout << MAGENTA << endl<<"\n\n\t\t\t----------------------------- " << RESET << endl;
                        cout << MAGENTA << " \t\t\t|   Welcome to Hangman Game  | " << RESET << endl;
                        cout << MAGENTA << "\t\t\t ----------------------------- " << RESET << endl<<endl;
                        cout << CYAN << "\t\t\t1. Start Game" << RESET << endl;
                        cout << CYAN << "\t\t\t2. Back to Main Menu" << RESET << endl;
                        cout << YELLOW << "\t\t\tSelect option: " << RESET;
                        char op = getche();
                        cout<<endl;
                        cout << YELLOW <<endl<<"\n\n\t\t\t********************************************\n" << RESET;
                        cout << YELLOW << "\t\t\t*          Welcome to Hangman Game!        *\n" << RESET;
                        cout << YELLOW << "\t\t\t********************************************\n\n" << RESET;

                        cout << BLUE;
                        cout <<endl<< "\t\tHangman is a classic word-guessing game. The computer will randomly\n";
                        cout << "\t\tselect a word, and your task is to guess the letters in that word.\n";
                        cout << "\t\tYou have a limited number of lives, so be careful with your guesses!\n\n";
                        cout << RESET;

                        switch (op) 
                        {
                            case '1': 
                                hm.play(); 
                                break;

                            case '2': 
                                goto endHangman;

                            default: 
                                cout << "\nInvalid option!\n"; 
                                Sleep(1000);
                        }
                    }
                        endHangman:
                            break;

            case 2:
                    fb.setcursor(0, 0);
                    srand((unsigned)time(NULL));
                    while (true) 
                    {
                        system("cls");
                        fb.gotoxy(10, 5); cout << MAGENTA << " -------------------------- " << RESET;
                        fb.gotoxy(10, 6); cout << MAGENTA << " |      Flappy Bird       | " << RESET;
                        fb.gotoxy(10, 7); cout << MAGENTA << " --------------------------" << RESET;
                        fb.gotoxy(10, 9); cout << CYAN << "1. Start Game" << RESET;
                        fb.gotoxy(10, 10); cout << CYAN << "2. Instructions" << RESET;
                        fb.gotoxy(10, 11); cout << CYAN << "3. Back to Main Menu" << RESET;
                        fb.gotoxy(10, 13); cout << YELLOW << "Select option: " << RESET;
                        char op = getche();

                        switch (op) 
                        {
                            case '1': 
                                fb.play(); 
                                break;

                            case '2': 
                                fb.instructions(); 
                                break;

                            case '3': 
                                goto endFlappy;

                            default: 
                                cout << "\nInvalid option!\n"; 
                                Sleep(1000);
                        }
                    }
                    endFlappy:
                    break;

            case 3:
                cg.setcursor(0, 0);
                srand((unsigned)time(NULL));
                while (true) 
                {
                    system("cls");
                    cg.setColor(15);
                    cg.gotoxy(10, 5); cout <<MAGENTA<< " -------------------------- "<<RESET;
                    cg.gotoxy(10, 6); cout <<MAGENTA<< " |        Car Game        | "<<RESET;
                    cg.gotoxy(10, 7); cout <<MAGENTA<< " --------------------------"<<RESET;
                    cg.gotoxy(10, 9); cout << CYAN<<"1. Start Game"<<RESET;
                    cg.gotoxy(10, 10); cout <<CYAN<< "2. Instructions"<<RESET;
                    cg.gotoxy(10, 11); cout << CYAN<<"3. Back to Main Menu"<<RESET;
                    cg.gotoxy(10, 13); cout <<YELLOW<< "Select option: "<<RESET;
                    char op = getche();

                    switch (op) 
                    {
                        case '1':
                            cout<<endl; 
                            cg.play(); 
                            break;

                        case '2': 
                            cg.instructions(); 
                            break;
                        case '3': 
                            goto endCar;

                        default: 
                            cout << "\nInvalid option!\n"; 
                            Sleep(1000);
                    }
                }
                endCar:
                break;

            case 4:
                while (true) 
                {
                    system("cls");
                    gotoxy(10, 5);
                    cout << MAGENTA << " ------------------------------------" << RESET;
                    gotoxy(10, 6);
                    cout << MAGENTA << " |      Bubble Shooting Game        |" << RESET;
                    gotoxy(10, 7);
                    cout << MAGENTA << " ------------------------------------" << RESET;
                    gotoxy(10, 9);
                    cout << CYAN << "1. Start Game" << RESET;
                    gotoxy(10, 10);
                    cout << CYAN << "2. Instructions" << RESET;
                    gotoxy(10, 11);
                    cout << CYAN << "3. Back to Main Menu" << RESET;
                    gotoxy(10, 13);
                    cout << YELLOW << "Select option: " << RESET;

                    option = getche();

                    switch (option) 
                    {
                        case '1':
                            //gobj = playGame(); // Re-initialize the game object to reset internal state
                            gobj.playGame();
                            break;

                        case '2':
                            system("cls");
                            cout<<endl<<endl<<BLUE<<"\t\t\tpress (d): move right."<<RESET<<endl;
                            cout<<BLUE<<"\t\t\tpress(a): move left."<<RESET<<endl;
                            cout<<BLUE<<"\t\t\tpress(w): shoot a laser."<<RESET<<endl;
                            cout<<BLUE<<"\t\t\tpress(Spacebar): exit the game."<<RESET<<endl;
                            gobj.displayInstructions();
                            break;

                        case '3':
                            goto endBubble;
                            
                        default:
                            cout << "\nInvalid option. Try again.\n";
                            Sleep(1000);
                    }
                }
                endBubble:
                break;

            case 5:
                cout << "\nThanks for playing!" << endl;
                exit(0);
                break;

            default:
                cout << "\nInvalid choice. Try again.\n";
                Sleep(1000);
        }
    }

    return 0;
}
