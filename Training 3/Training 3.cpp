#include <iostream>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <string>
using namespace std;

int pos = 0;
string s;

void help() {
    cout << "Доступные операции: ";
    cout << "Сложение '+' \n";
    cout << "Вычитание '-' \n";
    cout << "Множитель '*' \n";
    cout << "Деление '/' \n";
    cout << "Скобки '()' \n";
    cout << "Корень 'sqrt(0)' \n";
    cout << endl;
}

//Пробелы
void Spaceskip() {
    while (pos < s.size() && isspace(s[pos])) {
        pos++;
    }
}

double addition();

double number() {
    // Корень проверка
    Spaceskip();
    if (s.size() - pos >= 4 && s.compare(pos, 4, "sqrt") == 0) {
        pos += 4;
        Spaceskip();
        if (pos >= s.size() || s[pos] != '(') 
            throw runtime_error("Ошибка! Допишите нужные скобки!\n");
            pos++;
            double v = addition();
            if (pos >= s.size() || s[pos] != ')')
                throw runtime_error("Ошибка! Допишите нужные скобки!\n");
            pos++;
            return sqrt(v);
    }

    if (pos >= s.size()) {
        throw runtime_error("Ошибка: выражение оборвалось, не хватает числа!\n");
    }
    
    

    // Проверка на наличие скобок
    if (pos < s.size() && s[pos] == '(') {
        pos++;
        double v = addition();
        if (pos >= s.size() || s[pos] != ')')
            throw runtime_error("Ошибка! Незакрытая скобка! Попробуйте снова!\n");
            pos++;
            return v;
    }
    if (!isdigit(s[pos]))
        throw runtime_error(string("Ошибка: неизвестный символ '") + s[pos] + "'! Ожидалось число.\n");

    // Проверка числа
    double whole = 0;
    while (pos < s.size() && isdigit(s[pos])) {
        whole = whole * 10 + (s[pos++] - '0');
    }
    // Проверка на наличие дробных частей
    if (pos < s.size() && s[pos] == '.') {
        pos++;
        double frac = 0, weith = 0.1;
        while (pos < s.size() && isdigit(s[pos])) {
            frac += (s[pos++] - '0') * weith;
            weith /= 10;
        }
        whole += frac;
    }
    return whole;
}

double degree();

double multiplication() {
    double v = degree();
    while (true) {
        Spaceskip();
        if (pos >= s.size() || (s[pos] != '*' && s[pos] != '/')) {
            break;
        }
        char op = s[pos++];
        double r = degree();
        if (op == '*') {
            v = v * r;
        }
        else if (op == '/') {
            if (r == 0) {
                throw runtime_error("Ошибка! Нельзя делить на ноль. Попробуйте снова!\n");
            }
            v = v / r;
        }
    }
    return v;
}

double addition() {
    double v = multiplication();
    while (true) {
        Spaceskip();
        if (pos >= s.size() || (s[pos] != '+' && s[pos] != '-'))
            break;
        char op = s[pos++];
        double r = multiplication();
        v = (op == '+') ? v + r : v - r;
    }
    return v;
}

double degree() {

    double v = number();
    Spaceskip();
    if (pos < s.size() && s[pos] == '^') {
        pos++;
        double r = degree();
        return pow(v, r);
    }
    return  v;
}
int main(void) {
    setlocale(LC_ALL, "Russian");
    while (true) {
        cout << "Если хотите выйти нажмите 'q' \n";
        cout << "\n----------Калькулятор----------\n";
        cout << "Введите 'Help' чтобы посмотреть доступные операции\n";
        cout << "Введите ваше выражение: ";
        getline(cin, s);
        if (s == "q") {
            cout << "Завершение программы....\n";
            break;
        }
        if (s.empty()) continue;
        if (s == "Help") {
            help();
            continue;
        }

        pos = 0;

        try {
            double result = addition();
            if (pos < s.size())
                throw runtime_error("Неизвестное выражение! Попробуйте снова!\n");
            cout << "Результат: " << fixed << setprecision(3) << result << "\n";
        }
        catch (runtime_error const &r) {
            cout << r.what();
        }

    }
    return 0;
}

