#include <iostream>
#include <ctime>
using namespace std;


	// Linked List for incorrect guesses
	class Node 
	{
	public:
		
	    char letter;
	    Node* next;
	
	    Node(char l) 
		{
	        letter = l;
	        next = nullptr;
	    }
	};
	
	// Stack implementation
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
	
	class Hangman
	{
	
	private:
	    string word;
	    string hint;
	    string guessedWord;
	    int lives;
	    Stack previousGuesses;
	    Node* incorrectGuessesHead;
	
	    // Function to add incorrect guesses to the linked list
	    void addIncorrectGuess(char guess) 
		{
	        Node* newNode = new Node(guess);
	        newNode->next = incorrectGuessesHead;
	        incorrectGuessesHead = newNode;
	    }
	
	    // Function to clear the linked list of incorrect guesses
	    void clearIncorrectGuesses() 
		{
	        while (incorrectGuessesHead)
			 {
	            Node* temp = incorrectGuessesHead;
	            incorrectGuessesHead = incorrectGuessesHead->next;
	            delete temp;
	        }
	    }
	
	public:
	    // Constructor
	   Hangman(string w, string h) 
		{
		    word = w;
		    hint = h;
		    lives = w.length() / 2 + 1;
		    incorrectGuessesHead = nullptr;
		    guessedWord = string(w.length(), '_');
		}
	
	    // Destructor
	    ~Hangman() 
		{
	        clearIncorrectGuesses();
	    }
	
	    // Function to display the welcome message and rules
		   void displayMessage()
		   {
		    cout << "********************************************\n";
		    cout << "*          Welcome to Hangman Game!        *\n";
		    cout << "********************************************\n\n";
		    
		    cout << "Hangman is a classic word-guessing game. The computer will randomly\n";
		    cout << "select a word, and your task is to guess the letters in that word.\n";
		    cout << "You have a limited number of lives, so be careful with your guesses!\n\n";
		
		    cout << "RULES:\n";
		    cout << "- You start with some lives which are displayed.\n";
		    cout << "- The computer will choose a random word.\n";
		    cout << "- Guess one letter at a time.\n";
		    cout << "- If you enter a word or sentence, the first letter will be considered as the guess.\n";
		    cout << "- Correct guesses reveal the letters in the word.\n";
		    cout << "- Incorrect guesses cost a life.\n";
		    cout << "- Try to guess the word before running out of lives!\n\n";
		
		    char start_end;
		    
		    // Loop until valid input (E/e to continue, Q/q to quit)
		    while (true) 
			{
		        cout << "\n\tPress 'E'/'e' to Continue: \n";
				cout<<" \t\tOR  \n\t'Q'/'q' to Quit: \n";
				cout<<"Enter your choice: ";
		        cin >> start_end;
		
		        start_end = tolower(start_end); // Convert to lowercase for uniformity
		
		        if (start_end == 'e' || start_end == 'q')
				 {
		            break;  // Exit loop on valid input
		        }
		        
		        cout << "Invalid input! Please press 'E' to continue or 'Q' to quit.\n";
		    }
		
		    if (start_end == 'q') 
			{
		        cout << "QUITTING......\n";
		        exit(0);  // Terminate the program
		    }
		    
		    cout << "Hint: " << hint << "\n";
		}
	
	
	    // Function to display the hangman based on remaining lives
		void displayHangman() 
		{
		    const string stages[] = 
		    {
		        "  +---+\n      |\n      |\n      |\n      |\n      |\n",
		        "  +---+\n  |   |\n      |\n      |\n      |\n      |\n",
		        "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n",
		        "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n",
		        "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n",
		        "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n",
		        "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n",
		        "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n"
		    };
		
		    int stageIndex = 7 - lives;
		
		    // Ensure stageIndex is within bounds
		    if (stageIndex < 0) 
		    {
		        stageIndex = 0;
		    } 
		    else if (stageIndex > 7) 
		    {
		        stageIndex = 7;
		    }
		
		    cout << stages[stageIndex] << "\n";
		}
	
	
	    // Function to process player's guess
	    bool makeGuess(char guess)  
		{
	        previousGuesses.push(guess);
	        bool correct = false;
	
	        for (size_t i = 0; i < word.length(); i++)
			 {
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
	
	    // Function to check if the game is over
	    bool isGameOver()
		 {
	        return lives == 0 || guessedWord == word;
	    }
	
	    // Function to display the current status of the game
	    void displayStatus()
		{
	        cout << "Word: " << guessedWord << "\n";
	        cout << "Lives: " << lives << "\n";
	        cout << "Incorrect guesses: ";
	
	        Node* temp = incorrectGuessesHead;
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
	
	    // Function to check if the player has won
	    bool didWin()
		{
	        return guessedWord == word;
	    }
	};
		
	class GameController {
	private:
	    // Word Library categorized with corresponding hints
	    struct WordEntry 
		{
	        string word;
	        string hint;
	    };
	
	    WordEntry wordLibrary[23] = {
	        {"red", "Color"}, {"blue", "Color"}, {"green", "Color"}, {"orange", "Color"}, {"white", "Color"},
	        {"lust", "Deadly Sin"}, {"envy", "Deadly Sin"}, {"wrath", "Deadly Sin"}, {"greed", "Deadly Sin"},
	        {"sloth", "Deadly Sin"}, {"pride", "Deadly Sin"}, {"gluttony", "Deadly Sin"},
	        {"happiness", "Emotion"}, {"sadness", "Emotion"}, {"fear", "Emotion"}, {"disgust", "Emotion"}, {"anger", "Emotion"},
	        {"orange", "Fruit"}, {"apple", "Fruit"}, {"banana", "Fruit"},
	        {"toyota", "Car Brand"}, {"suzuki", "Car Brand"}, {"ford", "Car Brand"}
	    };
	
	    // Function to generate a random index
	    int randomIndex() 
	    {
	        srand(time(0));
	        return rand() % 23;  // Picks a random word from the 23 entries
	    }
		
		public:
		    // Function to start the game
		    void startGame() 
		    {
		        while (true) 
		        {
		            int index = randomIndex();
		            Hangman game(wordLibrary[index].word, wordLibrary[index].hint);
		            game.displayMessage();
		
		            while (!game.isGameOver()) 
		            {
		                game.displayHangman();
		                game.displayStatus();
		
		                char guess;
		                cout << "Enter your guess: ";
		                cin >> guess;
		
		                game.makeGuess(tolower(guess));
		            }
		
		            // Final hangman display and result message
		            game.displayHangman();
		            if (game.didWin()) 
		            {
		                cout << "Congratulations! You guessed the word!\n";
		            } 
		            else 
		            {
		                cout << "Game Over! The correct word was: " << wordLibrary[index].word << "\n";
		            }
		            
		            // Replay prompt
		            char replay;
		            cout << "Do you want to play again? (y/n): ";
		            cin >> replay;
		            if (tolower(replay) != 'y'){
		            	break;	
				} 
	        }
	    }
	};
	
	
int main() {

    GameController controller;
    controller.startGame();

    cout << "===================================\n";
    cout << "       Thanks for playing!       \n";
    cout << "===================================\n";
    
    return 0;
}
