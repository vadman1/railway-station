#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

class Train {
    string number;
    string station;
    string departure_time;

public:
    Train() { }

    Train(string number, string station, string departure_time) {
        this->number = number;
        this->station = station;
        this->departure_time = departure_time;
    }

    string getNumber() { return number; }

    string getStation() { return station; }

    string getDeparture_time() { return departure_time; }

    void print() {
        cout << "Номер поезда:" << number << endl;
        cout << "Станция:" << " " << station << endl;
        cout << "Время отправления:" << departure_time << endl;
    }

    friend istream& operator>>(istream& s, Train& tmp);
    friend ostream& operator<<(ostream& s, Train& tmp);
    friend ofstream& operator<<(ofstream& s, Train& tmp);

};

istream& operator>> (istream& s, Train& tmp) {
    cout << "Введите номер поезда: ";
    getline(s, tmp.number);
    cout << "Введите станцию: ";
    getline(s, tmp.station);
    cout << "Введите время отправления: ";
    getline(s, tmp.departure_time);
    return s;
}

ostream& operator<<(ostream& s, Train& tmp) {
    if (tmp.getNumber().empty()) {
        s << "Элемент пуст.";
        return s;
    }
    s << "Номер поезда: " << tmp.number << endl << "Станция: " << tmp.station << endl;
    cout << "Дата отправления: " << endl;
    s << tmp.departure_time << endl;
    return s;
}

ofstream& operator<<(ofstream& s, Train& tmp) {
    s << tmp.number << endl;
    s << tmp.station << endl;
    s << tmp.departure_time << endl;
    return s;
}

template <class T>
struct DinamicArray {
    T* data;
    int size;
};


template <class Tkey, class Tvalue>
struct KeyValue
{
    Tkey key;
    Tvalue value;
};

template <class Tkey, class Tvalue>
class AssocArray
{
    KeyValue<Tkey, Tvalue>* arr;
    int current;
    int size;

public:
    AssocArray() {
        size = 10;
        current = 0;
        arr = new KeyValue<string, Train>[size];
    }

    AssocArray(int size) {
        arr = new KeyValue<string, Train>[size];
        this->size = size;
        current = 0;
    }

    ~AssocArray() { if (arr) delete[] arr; }

    void add(Tkey& key, Tvalue& value) {
        if (current == size) {
            KeyValue<string, Train>* temp = new KeyValue<string, Train>[size + 10];
            for (int i = 0; i < size; i++)
                temp[i] = arr[i];
            delete[] arr;
            arr = temp;
            size += 10;
        }

        arr[current].key = key;
        arr[current].value = value;
        current++;
    }

    /*void print()
    {
        if (!current)
        {
            cout << "Записей не найдено!" << endl;
            return;
        }
        for (int i = 0; i < current; i++)
            cout << i + 1 << ")" << endl << arr[i].value << endl;
    }*/

    void save(ofstream& s) {
        for (int i = 0; i < current; i++)
            s << arr[i].first->value;
    }

    DinamicArray<KeyValue<string, Train>> find(Tkey key) {
        int size_res = 1;
        KeyValue<string, Train>* res = new KeyValue<string, Train>[size_res];
        DinamicArray<KeyValue<string, Train>> r;
        int f = 0;

        for (int i = 0; i < current; i++) {

            if ((arr[i].key == key) && (f < size_res)) {
                res[f] = arr[i];
                f++;
            }
            else if ((arr[i].key == key) && (f == size_res)) {
                KeyValue<string, Train>* temp = new KeyValue<string, Train>[size_res + 1];
                for (int j = 0; j < size_res; j++)
                    temp[j] = res[j];
                delete[] res;
                res = temp;
                size_res += 10;
                res[f] = arr[i];
                f++;
            }
        }
        r.data = res;
        r.size = f;
        return r;

    }

    KeyValue<string, Train>* operator[](int num) {
        return &arr[num];
    }

    int getFilled() {
        return current;
    }
};

class RailwayStation {


    AssocArray<string, Train> timeTable;

public:

    RailwayStation() { }

    void add(string& str, Train& train) {
        timeTable.add(str, train);

    }

    void find(string& str) {
        DinamicArray<KeyValue<string, Train>> tmp = timeTable.find(str);
        int t_size = tmp.size;
        KeyValue<string, Train>* p = tmp.data;
        for (int i = 0; i < t_size; i++) {
            cout << p[i].value << endl;
        }
    }


    void print() {
        int current = timeTable.getFilled();
        if (!current) {
            cout << "Записей не найдено!" << endl;
            return;
        }
        for (int i = 0; i < current; i++) {
            cout << i + 1 << ")" << endl << timeTable[i]->value << endl;
        }
    }

    void printToStation(string station) {
        int current = timeTable.getFilled();
        if (!current) {
            cout << "Записей не найдено!" << endl;
            return;
        }
        for (int i = 0; i < current; i++) {
            Train A = timeTable[i]->value;
            if (A.getStation() == station) {
                cout << i + 1 << ")" << endl << timeTable[i]->value << endl;
            }
        }
    }

    void menu() {
        for (;;) {
            cout << "[1]Ввод данных в информационную систему" << endl;
            cout << "[2]Вывод информации по всем поездам" << endl;
            cout << "[3]Вывод сведений по поезду с запрошенным номером" << endl;
            cout << "[4]Вывод сведений по тем поездам, которые следуют до запрошенной станции назначения" << endl;
            cout << "[5]Выход из программы" << endl;

            int ans = 0;
            cin >> ans;
            cin.get();
            Train A;

            /*ifstream fileRead("Vokzal.txt");
            if (fileRead.is_open())
            {
                char filecount[7];
                fileRead.getline(filecount, 7);
                count = atoi(filecount);
                for (int i = 0; i < count; i++)
                {
                    char bufnumber[50];
                    char bufstation[100];
                    char bufdeparture_time[50];
                    fileRead.getline(bufnumber, 50);
                    fileRead.getline(bufstation, 100);
                    fileRead.getline(bufdeparture_time, 50);
                    Train tmp(bufnumber, bufstation, bufdeparture_time);
                    string name;
                    add(name, tmp);
                }
            }
            fileRead.close();*/

            system("cls");
            switch (ans) {

            case 1: {
                system("cls");
                string number;
                cin >> A;
                number = A.getNumber();
                add(number, A);
                system("pause");
                system("cls");
                break;
            }

            case 2: {
                print();
                system("pause");
                system("cls");
                break;
            }
            case 3: {
                cout << "Введите номер поезда" << endl;
                string number;
                cin >> number;
                system("cls");

                find(number);

                system("pause");
                system("cls");
                break;
            }
            case 4: {
                cout << "Введите станцию назначения для просмотра информации о поездах, следующих до неё:" << endl;
                string station;
                cin >> station;
                system("cls");

                printToStation(station);

                system("pause");
                system("cls");
                break;
            }
            case 5: {
                /*ofstream fileSave;
                fileSave.open("Vokzal.txt");
                fileSave << count << endl;
                list.save(fileSave);
                fileSave.close();*/
                exit(0);
                break;
            }
            }
        }
    }


};

int main() {
    setlocale(LC_ALL, "russian");
    RailwayStation example;
    example.menu();

    /*AssocArray <char , int> test;
    char a = 'A';
    int i = 4;
    test.add(a,i);
    cout << test[i]<<endl;

    a='B';
    i=8;
    test.add(a,i);
    cout << test[a]<<endl;*/

    system("pause");
}

