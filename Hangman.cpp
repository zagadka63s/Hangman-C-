#include <iostream>
#include <ctime>
#include <cstdlib>
#include<string>
#include <cstring>
#include <locale.h> // Добавляем библиотеку для установки локали (locale)

using namespace std;

const int MAX_WORDS = 5;
const char* words[MAX_WORDS] = {
    "apple", "banana","orange","grape","melon"
};

const int MAX_ERRORS = 6;

// Функция для получения случайного слова из массива words
const char* getRandomWord() {
    srand(time(nullptr)); // генератор случайных чисел на основе текущего времени
    int randomIndex = rand() % MAX_WORDS; // Генерация случайного индекса в диапазоне [0, MAX_WORDS - 1]
    return words[randomIndex]; // Возвращаем случайное слово
}

// Функция для вывода текущего состояния игры ( угаданные буквы и количество ошибок)
void displayGameState(const char* wordState, int numErrors) {
    cout << "Слово : " << wordState << endl;

    // Рисуем виселицу
    cout << "   _______ " << endl;
    cout << "   |      | " << endl;
    cout << "   |      " << (numErrors >= 1 ? "O" : " ") << endl;
    cout << "   |     " << (numErrors >= 3 ? "/" : " ") << (numErrors >= 2 ? "|" : " ") << (numErrors >= 4 ? "\\" : " ") << endl;
    cout << "   |     " << (numErrors >= 5 ? "/" : " ") << " " << (numErrors >= 6 ? "\\" : " ") << endl;
    cout << "   |" << endl;
    cout << "___|___" << endl;

    cout << "Errors: " << numErrors << endl;
}

// Функция для проверки угаданной буквы
// Возвращаем true, если угаданная буква есть в слове и обновляем wordState
bool checkGuess(const char* word, char* wordState, char guess) {
    bool correctGuess = false;
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == guess) {
            wordState[i] = guess; // Обновляем состояние слова, если угаданная буква есть в слове
            correctGuess = true;
        }
    }
    return correctGuess;
}

// Функция для проверки, завершилась ли игра
bool isGameOver(const char* word, const char* wordState, int numErrors) {
    return (strcmp(word, wordState) == 0) || (numErrors >= MAX_ERRORS);
}

int main() {
    setlocale(LC_ALL, "Russian"); // Устанавливаем русскую локаль

    // Регистрируем игрока
    string playerName;
    cout << "Введите имя: ";
    std::getline(cin, playerName); // Исправлено: getline должен быть вызван из std::cin, без std:: перед cin

    // Выбор слова для игры
    cout << "Нужно выбрать слово из списка:\n";
    for (int i = 0; i < MAX_WORDS; i++) {
        cout << i + 1 << ". " << words[i] << endl;
    }
    int wordChoice;
    do {
        cout << "Введите номер слова: ";
        cin >> wordChoice; // Исправлено: getline не нужен, так как считываем целое число
    } while (wordChoice < 1 || wordChoice > MAX_WORDS);

    const char* word = words[wordChoice - 1]; // Выбранное слово
    const int wordLength = strlen(word); // Исправлено: srtlen изменено на strlen
    char* wordState = new char[wordLength + 1];
    memset(wordState, '_', wordLength);
    wordState[wordLength] = '\0';

    int numErrors = 0;
    char guess;
    bool gameOver = false;

    // Приветствуем имя игрока
    cout << "Добро пожаловать, " << playerName << "! Давайте играть в Виселицу!" << endl;
    cout << "Попробуйте угадать слово, вводя по одной букве за раз!" << endl;

    while (!gameOver) {
        displayGameState(wordState, numErrors);

        cout << "Введите ваше предположение: ";
        cin >> guess; // Игрок вводит букву

        if (!checkGuess(word, wordState, guess)) {
            numErrors++; // Увеличиваем количество ошибок, если буква не угадана
        }

        gameOver = isGameOver(word, wordState, numErrors); // Проверяем, завершилась ли игра
    }

    if (numErrors >= MAX_ERRORS) {
        cout << "Игра окончена, " << playerName << "! Слово было: " << word << endl;
    }
    else {
        cout << "Поздравляем, " << playerName << "! Вы угадали слово: " << word << endl;
    }

    delete[] wordState; // Освобождаем память, выделенную для wordState
    return 0;
}
