#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <locale>

using namespace std;

// Функция для отображения виселицы
void drawHangman(int wrongGuesses) {
    cout << "-------------" << endl;
    cout << "|           |" << endl;
    cout << "|";
    if (wrongGuesses >= 1) cout << "           |"; // Верёвка - вертикальная черта
    cout << endl;
    cout << "|";
    if (wrongGuesses >= 2) cout << "           O"; // Голова
    cout << endl;
    cout << "|";
    if (wrongGuesses >= 3) cout << "          /"; // Туловище
    if (wrongGuesses >= 4) cout << "|"; // Левая рука
    if (wrongGuesses >= 5) cout << "\\"; // Правая рука
    cout << endl;
    if (wrongGuesses >= 6) cout << "|          / \\" << endl; // Ноги
    else cout << "|           " << endl;
    cout << "-------------" << endl;
}

string chooseWord(const vector<string>& words) {
    srand(time(0));
    return words[rand() % words.size()];
}

void displayGame(const string& word, const string& guessedLetters, int wrongGuesses) {
    system("cls"); //Для Windows.  Для Linux/macOS используйте system("clear");
    drawHangman(wrongGuesses);
    cout << "Слово: ";
    for (char c : word) {
        if (guessedLetters.find(c) != string::npos) {
            cout << c << " ";
        }
        else {
            cout << "_ ";
        }
    }
    cout << endl;
    cout << "Ошибки: " << wrongGuesses << endl;
    cout << "Угаданые буквы: " << guessedLetters << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<string> words = { "apple", "banana", "orange", "grape", "watermelon" };
    string wordToGuess = chooseWord(words);
    string guessedLetters = "";
    int wrongGuesses = 0;
    int maxWrongGuesses = 6;

    while (wrongGuesses < maxWrongGuesses) {
        displayGame(wordToGuess, guessedLetters, wrongGuesses);

        char guess;
        cout << "Введите букву: ";
        cin >> guess;
        guess = tolower(guess);

        if (guessedLetters.find(guess) != string::npos) {
            cout << "Вы уже угадали эту букву!" << endl;
            system("pause");
            continue;
        }

        guessedLetters += guess;

        if (wordToGuess.find(guess) == string::npos) {
            wrongGuesses++;
        }

        bool wordGuessed = true;
        for (char c : wordToGuess) {
            if (guessedLetters.find(c) == string::npos) {
                wordGuessed = false;
                break;
            }
        }
        if (wordGuessed) {
            system("cls");
            displayGame(wordToGuess, guessedLetters, wrongGuesses);
            cout << "Поздравляем! Вы угадали слово: " << wordToGuess << endl;
            break;
        }
        system("pause");
    }

    if (wrongGuesses == maxWrongGuesses) {
        system("cls");
        displayGame(wordToGuess, guessedLetters, wrongGuesses);
        cout << "Вы проиграли! Слово было: " << wordToGuess << endl;
    }

    return 0;
}