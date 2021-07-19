#include <iostream>
using namespace std;

struct Elem
{
    int data; 
    Elem* next,
        * prev;
};

class List
{       
    Elem* Head,
        * Tail;
    // Количество элементов:
    int Count;

public:
    List(); 
    List(const List&); // Конструктор копирования.
    ~List(); 
    int   size(); // Получить количество.
    Elem* GetElem(int); // Получить элемент списка.
    void  DelAll(); // Удалить весь список.
    void  Del(int pos = 0); // Удаление элемента(без параметра запрос).
    void  Insert(int pos = 0); // Вставка элемента(без параметра запрос).
    void  AddTail(int n); // Добавление в конец списка.
    void  AddHead(int n); // Добавление в начало списка.

    void  Print(const char* mess); // Печать списка.
    void  Print(const int   pos); // Печать определенного элемента.

    List& operator = (const List&);
    List operator +  (const List&);  // Сложение двух списков (дописывание)

    // сравнение по элементам:
    bool operator == (const List&);
    bool operator != (const List&);
    bool operator <= (const List&);
    bool operator >= (const List&);
    bool operator <  (const List&);
    bool operator >  (const List&);

    // Переворачивание списка:
    List operator - ();
};

List::List()
{   // Изначально список пуст:
    Head = Tail = NULL;
    Count = 0;
}

List::List(const List& L)
{
    Head = Tail = NULL;
    Count = 0;

    // Голова списка, из которого копируем:
    Elem* temp = L.Head;
    // Пока не конец списка:
    while (temp != 0)
    {   // Передираем данные:
        AddTail(temp->data);
        temp = temp->next;
    }
}

List::~List()
{   // Удаляем все элементы:
    DelAll();
}

void List::AddHead(int n)
{   // Новый элемент:
    Elem* temp = new Elem;

    // Предыдущего нет:
    temp->prev = 0;
    // Заполняем данные:
    temp->data = n;
    // Следующий - бывшая голова:
    temp->next = Head;

    // Если элементы есть?
    if (Head != 0)
        Head->prev = temp;

    // Если элемент первый, то он одновременно и голова и хвост:
    if (Count == 0) Head = Tail = temp;
    // иначе новый элемент - головной:
    else           Head = temp;

    Count++;
}

void List::AddTail(int n)
{   // Создаем новый элемент:
    Elem* temp = new Elem;
    // Следующего нет:
    temp->next = 0;
    // Заполняем данные:
    temp->data = n;
    // Предыдущий - бывший хвост:
    temp->prev = Tail;

    // Если элементы есть?
    if (Tail != 0)
        Tail->next = temp;

    // Если элемент первый, то он одновременно и голова и хвост:
    if (Count == 0) Head = Tail = temp;
    // иначе новый элемент - хвостовой
    else           Tail = temp;
    Count++;
}

void List::Insert(int pos)
{   // Если параметр отсутствует или равен 0, то запрашиваем его:
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }

    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count + 1)
    {
        cout << "Incorrect position !!!\n";
        return;
    }

    // Если вставка в конец списка:
    if (pos == Count + 1)
    {   // Вставляемые данные:
        int data;
        cout << "Input new number: ";
        cin >> data;
        // Добавление в конец списка:
        AddTail(data);
        return;
    }
    else if (pos == 1)
    {   // Вставляемые данные:
        int data;
        cout << "Input new number: ";
        cin >> data;
        // Добавление в начало списка:
        AddHead(data);
        return;
    }

    // Отсчитываем от головы n - 1 элементов:
    Elem* Ins = Head;
    for (int i = 1; i < pos; i++)
    {   // Доходим до элемента,
        // перед которым вставляемся:
        Ins = Ins->next;
    }

    // Доходим до элемента,
    // который предшествует
    Elem* PrevIns = Ins->prev;

    // Создаем новый элемент
    Elem* temp = new Elem;

    // Вводим данные:
    cout << "Input new number: ";
    cin >> temp->data;

    // Настройка связей:
    if (PrevIns != 0 && Count != 1)
        PrevIns->next = temp;

    temp->next = Ins;
    temp->prev = PrevIns;
    Ins->prev = temp;

    Count++;
}

void List::Del(int pos)
{   // Если параметр отсутствует или равен 0, то запрашиваем его:
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }
    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count)
    {   // Неверная позиция:
        cout << "Incorrect position !!!\n";
        return;
    }

    Elem* Del = Head;
    for (int i = 1; i < pos; i++)
    {   // Доходим до элемента, который удаляется:
        Del = Del->next;
    }

    // Доходим до элемента,
    // который предшествует удаляемому:
    Elem* PrevDel = Del->prev;
    // Доходим до элемента, который следует за удаляемым:
    Elem* AfterDel = Del->next;

    // Если удаляем не голову:
    if (PrevDel != 0 && Count != 1)
        PrevDel->next = AfterDel;
    // Если удаляем не хвост:
    if (AfterDel != 0 && Count != 1)
        AfterDel->prev = PrevDel;

    // Удаляются крайние?
    if (pos == 1)
        Head = AfterDel;
    if (pos == Count)
        Tail = PrevDel;

    delete Del;
    Count--;
}

void List::Print(const int pos)
{   // Позиция от 1 до Count?
    if (pos < 1 || pos > Count)
    {   // Неверная позиция:
        cout << "Incorrect position !!!\n";
        return;
    }

    Elem* temp;
    // Определяем с какой стороны
    // быстрее двигаться:
    if (pos <= Count / 2)
    {   // Отсчет с головы:
        temp = Head;
        int i = 1;

        while (i < pos)
        {   // Двигаемся до нужного элемента:
            temp = temp->next;
            i++;
        }
    }
    else
    {   // Отсчет с хвоста:
        temp = Tail;
        for (int i = 1; i <= Count - pos; i++)
        {   // Двигаемся до нужного элемента:
            temp = temp->prev;
        }
    }
    // Вывод элемента:
    cout << pos << " element: ";
    cout << temp->data << endl;
}

void List::Print(const char* mess)
{   // Если в списке присутствуют элементы, то пробегаем по нему
    // и печатаем элементы, начиная с головного.

    cout << mess << "\n";
    if (Count != 0)
    {
        Elem* temp = Head;
        cout << "( ";
        while (temp->next != 0)
        {
            cout << temp->data << ", ";
            temp = temp->next;
        }

        cout << temp->data << " )\n";
    }
    cout << endl;
}

void List::DelAll()
{   // Пока остаются элементы, удаляем по одному с головы:
    while (Count != 0)
        Del(1);
}

int List::size()
{
    return Count;
}

Elem* List::GetElem(int pos)
{
    Elem* temp = Head;

    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count)
    {
        cout << "Incorrect position !!!\n";
        return NULL;
    }

    // Ищем нужный нам элемент:
    for (int i = 1; i < pos && temp != 0; i++)
    {
        temp = temp->next;
    }

    if (temp == 0) return 0;
    else          return temp;
}

List& List::operator = (const List& L)
{   // Проверка присваивания элемента "самому себе":
    if (this == &L)
        return *this;

    // Удаление старого списка:
    this->DelAll();

    Elem* temp = L.Head;

    // Копируем элементы:
    while (temp != 0)
    {
        AddTail(temp->data);
        temp = temp->next;
    }
    return *this;
}

// Сложение двух списков:
List List::operator + (const List& L)
{   // Заносим во временный список элементы первого списка:
    List Result(*this);
    Elem* temp = L.Head;

    // Добавляем во временный список элементы второго списка:
    while (temp != 0)
    {
        Result.AddTail(temp->data);
        temp = temp->next;
    }
    return Result;
}

bool List::operator == (const List& L)
{   // Сравнение по количеству:
    if (Count != L.Count)
        return false;

    Elem* t1 = Head,
        * t2 = L.Head;

    // Сравнение по содержанию:
    while (t1 != 0)
    {   // Сверяем данные, которые
        // находятся на одинаковых позициях:
        if (t1->data != t2->data)
            return false;

        t1 = t1->next;
        t2 = t2->next;
    }
    return true;
}

bool List::operator != (const List& L)
{   // Используем предыдущую функцию сравнения:
    return !(*this == L);
}

bool List::operator >= (const List& L)
{
    if (Count > L.Count) return true; // Сравнение по количеству.
    if (*this == L) return true;      // Сравнение по содержанию.
    return false;
}

bool List::operator <= (const List& L)
{
    if (Count < L.Count) return true; // Сравнение по количеству.
    if (*this == L) return true;      // Сравнение по содержанию.
    return false;
}

bool List::operator > (const List& L)
{
    if (Count > L.Count) return true;
    return false;
}

bool List::operator < (const List& L)
{
    if (Count < L.Count) return true;
    return false;
}

// Переворот:
List List::operator - ()
{
    List Result;

    Elem* temp = Head;
    // Копируем элементы списка, начиная с головного,
    // в свой путем добавления элементов в голову,
    // таким образом временный список Result будет содержать
    // элементы в обратном порядке
    while (temp != 0)
    {
        Result.AddHead(temp->data);
        temp = temp->next;
    }
    return Result;
}

