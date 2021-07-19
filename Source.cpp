#include <iostream>
#include"List.h"
#include <Windows.h>

using namespace std;

int main()
{

    setlocale(LC_ALL, "rus");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("color 1F");

    int a[] = { 0,1,2,3,4,5,6,7,8,9 };
    const int n = sizeof(a) / sizeof(*a);

    List L;
    // ��������� ��������, ������� �� ������ ��������, � ������,
    // �� �������� - � �����
    for (int i = 0; i < n; i++)
        if (i % 2 == 0)
            L.AddHead(a[i]);
        else
            L.AddTail(a[i]);

    // ���������� ������:
    L.Print("List L:");

    // ������� �������� � ������:
    L.Insert();
    L.Print("List L:");

    // ���������� 5-�� � 8-�� ��������� ������:
    L.Print(5);
    L.Print(8);

    List T;
 
    T = L;
    T.Print("Copying List T:");

    List my(T);
    my.Print("Copying List my:");

    // ���������� ��� ������
    List Sum = -L + T;
    Sum.Print("List Sum:");

    std::cin.get();
    std::cin.get();
}