#include <iostream>
using namespace std;

class str // упрощенный аналог класса string
{
private:
    char* s; // указатель на строку символов (без завершающего символа '\0')
    int n;   // размер строки символов
public:
    str() : s(nullptr), n(0) {} // конструктор по умолчанию
    str(const char *st) // конструктор, принимающий постоянную строку текста
    {
        int i = 0;
        for (i = 0; st[i] != '\0'; i++); // вычисляем длину входной строки
        n = i; 
        s = new char[n];
        for (i = 0; i < n; i++) s[i] = st[i]; // копируем строку st, исключая нулевой символ
    }
    str(str& T) // конструктор копирования
    {
        n = T.n;
        s = new char[n];
        for (int i = 0; i < n; i++) s[i] = T.s[i];
    }
    ~str() { delete[] s;}
    operator char* ()  // преобразование типа str в строку char*
    {
        char* p = new char[n+1];
        for (int i = 0; i < n; i++) p[i] = s[i];
        p[n] = '\0';
        return p;
    } 
    str& operator = (str& st) // перегрузка оператора присваивания
    {
        if (&st == this) return *this; // Проверка на самоприсваивание
        if (s) delete[] s; // Удаление старого содержимого
        n = st.n;
        s = new char[n]; 
        for (int i = 0; i < n; i++) s[i] = st.s[i];
        return *this;
    }
    void print() // печать строки
    {
        /*char* p = new char[n + 1];  // сформируем строку с символом '\0' в конце
        for (int i = 0; i < n; i++) p[i] = s[i];
        p[n] = '\0';
        cout << p << endl;
        delete[] p;*/
        for (int i = 0; i < n; i++) cout << s[i];
    }
    int length() { return n; }
    char at(int k) // извлечение символа с индексом k
    {
        return (k >= 0 && k < n) ? s[k] : '\0';
    }
    void setchar(char ch, int k) // установить символ ch в позицию с индексом k
    {
        if (k >= 0 && k < n) s[k] = ch;
    }
};

int main()
{
    setlocale(LC_ALL, "russian");
    str s1, s2("wqeqrwe"), s3(s2), s4("ddddd");
    printf("Привет\n");
    s1 = s2;
    char* p = s4;
    s1.print();
    s2.print(); 
    cout << endl << p << endl;
    cout << s2.length() << "   "<< s2.at(2) << endl;
    s3.setchar('z', 2);
    s3.print();
}