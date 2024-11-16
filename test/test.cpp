#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Функция для выбора случайного слова
string chooseWord(const vector<string>& words) {
    srand(time(0)); // Инициализация генератора случайных чисел
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

// Функция для отображения состояния игры
void displayGame(const string& word, const string& guessedLetters, int wrongGuesses) {
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
    int maxWrongGuesses = 6; // Максимальное количество ошибок

    // Игровой цикл
    while (wrongGuesses < maxWrongGuesses) {
        displayGame(wordToGuess, guessedLetters, wrongGuesses);

        char guess;
        cout << "Введите букву: ";
        cin >> guess;
        guess = tolower(guess); // Приведение к нижнему регистру

        if (guessedLetters.find(guess) != string::npos) {
            cout << "Вы уже угадали эту букву!" << endl;
            continue;
        }

        guessedLetters += guess;

        if (wordToGuess.find(guess) != string::npos) {
            // Буква угадана
            bool wordGuessed = true;
            for (char c : wordToGuess) {
                if (guessedLetters.find(c) == string::npos) {
                    wordGuessed = false;
                    break;
                }
            }
            if (wordGuessed) {
                cout << "Поздравляем! Вы угадали слово: " << wordToGuess << endl;
                break;
            }
        }
        else {
            // Буква не угадана
            wrongGuesses++;
        }
    }

    if (wrongGuesses == maxWrongGuesses) {
        cout << "Вы проиграли! Слово было: " << wordToGuess << endl;
    }

    return 0;
}