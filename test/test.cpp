#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <locale>

using namespace std;

// Функция для отображения виселицы.  Рисует висельника в зависимости от количества неправильных попыток.
void drawHangman(int wrongGuesses) {
    cout << "-------------" << endl;
    cout << "|           |" << endl;
    cout << "|";
    if (wrongGuesses >= 1) cout << "           |"; // Вертикальная линия - "верёвка"
    cout << endl;
    cout << "|";
    if (wrongGuesses >= 2) cout << "           O"; // Голова
    cout << endl;
    cout << "|";
    if (wrongGuesses >= 3) cout << "          /"; // Туловище (левая часть)
    if (wrongGuesses >= 4) cout << "|"; // Левая рука
    if (wrongGuesses >= 5) cout << "\\"; // Правая рука
    cout << endl;
    if (wrongGuesses >= 6) cout << "|          / \\" << endl; // Ноги
    else cout << "|           " << endl;
    cout << "-------------" << endl;
}

// Функция для выбора случайного слова из вектора слов.
string chooseWord(const vector<string>& words) {
    srand(time(0)); // Инициализация генератора случайных чисел (только один раз в программе!)
    return words[rand() % words.size()]; // Возвращает случайное слово из вектора
}

// Функция для отображения текущего состояния игры.
void displayGame(const string& word, const string& guessedLetters, int wrongGuesses) {
    system("cls"); // Очищает консоль (для Windows).  Для Linux/macOS используйте system("clear");
    drawHangman(wrongGuesses); // Рисует висельника
    cout << "Слово: ";
    for (char c : word) { // Выводит слово, скрывая не угаданные буквы
        if (guessedLetters.find(c) != string::npos) {
            cout << c << " ";
        }
        else {
            cout << "_ ";
        }
    }
    cout << endl;
    cout << "Ошибки: " << wrongGuesses << endl; // Выводит количество ошибок
    cout << "Угаданые буквы: " << guessedLetters << endl; // Выводит список угаданных букв
}

int main() {
    setlocale(LC_ALL, "Russian"); // Устанавливает русскую локаль для корректного отображения кириллицы

    vector<string> words = { "apple", "banana", "orange", "grape", "watermelon" }; // Список слов для игры
    string wordToGuess = chooseWord(words); // Выбирает случайное слово
    string guessedLetters = ""; // Строка для хранения угаданных букв
    int wrongGuesses = 0; // Количество неправильных попыток
    int maxWrongGuesses = 6; // Максимальное количество неправильных попыток

    // Основной игровой цикл
    while (wrongGuesses < maxWrongGuesses) {
        displayGame(wordToGuess, guessedLetters, wrongGuesses); // Отображает состояние игры

        char guess;
        cout << "Введите букву: ";
        cin >> guess;
        guess = tolower(guess); // Приводит букву к нижнему регистру

        // Проверка на повторную попытку угадать уже угаданную букву
        if (guessedLetters.find(guess) != string::npos) {
            cout << "Вы уже угадали эту букву!" << endl;
            system("pause"); // Пауза для чтения сообщения
            continue; // Переход к следующей итерации цикла
        }

        guessedLetters += guess; // Добавляет угаданную букву в список

        // Проверка, угадана ли буква
        if (wordToGuess.find(guess) == string::npos) {
            wrongGuesses++; // Увеличивает счётчик ошибок, если буква не угадана
        }

        // Проверка, угадано ли слово
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
            break; // Завершение игры, если слово угадано
        }
        system("pause"); // Пауза для чтения сообщения
    }

    // Сообщение о проигрыше, если количество ошибок достигло максимума
    if (wrongGuesses == maxWrongGuesses) {
        system("cls");
        displayGame(wordToGuess, guessedLetters, wrongGuesses);
        cout << "Вы проиграли! Слово было: " << wordToGuess << endl;
    }

    return 0;
}