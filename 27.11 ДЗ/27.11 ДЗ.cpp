﻿#include <iostream>
#include <string>
using namespace std;
class DateTime
{
    int day;
    int month;
    int year;

public:
    void SetDay(int day)
    {
        if (day > 0 && day <= 31) // TO DO: february 28-29, april june 30
        {
            this->day = day;
        }
        else
        {
            cout << "Invalid value!" << endl;
            throw "ERROR!\n";
        }
    }

    int GetDay() const
    {
        return day;
    }

    void SetMonth(int month)
    {
        if (month >= 1 && month <= 12)
        {
            this->month = month;
        }
        else
        {
            cout << "Invalid value!" << endl;
            throw "ERROR!\n";
        }
    }

    int GetMonth() const
    {
        return month;
    }

    void SetYear(int year)
    {
        this->year = year;
    }

    int GetYear() const
    {
        return year;
    }

    DateTime() {
        //cout << "DateTime c-tor without parameters\n";
        SetDay(11);
        SetMonth(10);
        SetYear(2023);
    }

    DateTime(int day, int month) {
        //cout << "DateTime c-tor with 2 parameters\n";
        SetDay(day);
        SetMonth(month);
        SetYear(2023);
    }

    DateTime(int day, int month, int year)
    {
        //cout << "DateTime main c-tor with 3 parameters\n";
        SetDay(day);
        SetMonth(month);
        SetYear(year);
    }

    DateTime(const DateTime& original)
    {
        //cout << "DateTime copy constructor\n";
        this->day = original.day;
        this->month = original.month;
        this->year = original.year;
    }

    ~DateTime() {
        //cout << "DateTime destructor\n";
    }

    void Print() const
    {
        cout << "Date: " << day << "." << month << "." << year << endl;
    }
    string date_to_string() {
        string s;
        s += to_string(day);
        s += '.';
        s += to_string(month);
        s += '.';
        s += to_string(year);
        return s;
    }

    int& operator [] (unsigned int index) {
        if (index == 0)return day;
        if (index == 1)return month;
        if (index == 2)return year;
        throw"Incorrect index\n";
    }

};

istream& operator>>(istream& cin, DateTime& obj)
{
    int day, month, year;
    cout << "Type a year:" << endl;
    cin >> year;
    obj.SetYear(year);
    cout << "Type a month:" << endl;
    cin >> month;
    obj.SetMonth(month);
    cout << "Type a day:" << endl;
    cin >> day;
    obj.SetDay(day);
    return cin;
}

ostream& operator<<(ostream& cout, DateTime& obj)
{
    obj.Print();
    return cout;
}

class Student
{
    string name;
    string surname;
    DateTime birthday;
    DateTime study_start;
    int* hometask_rates = nullptr; // ПОЛЕ-ПОКАЖЧИК
    int hometask_rates_count = 0;
    int* practice_rates = nullptr;
    int practice_rates_count = 0;
    int* exam_rates = nullptr;
    int exam_rates_count = 0;
public:

    Student()
    {
        SetName("Veronika");
        SetSurname("Geyna");
        SetBirthday({ 1,2,2005 });
        SetStudyStart({ 1,2,2022 });
    }

    void PrintStudent()
    {
        cout << "Name: " << name << endl;
        cout << "Surname: " << surname << endl;
        cout << "Birthday: ";
        birthday.Print();
        cout << "Study start date";
        study_start.Print();
    }
    // тiло КК для класу, яке створюе компiлятор за замовчуванням
    // поверхневе копiювання

    // якщо в складi класу е поле-покажчик,
    // то потрiбно ОБОВ'ЯЗКОВО зробити ЯВНИЙ конструктор копiювання
    // в якому пiд усi поля-покажчики буде видiлена ОКРЕМА НОВА ДIЛЯНКА ПАМ'ЯТI
    Student(const Student& original)
    {
        this->name = original.name;
        this->surname = original.surname;
        this->birthday = original.birthday;
        this->study_start = original.study_start;

        // приклад ГЛИБОКОГО КОПIЮВАННЯ
        this->hometask_rates_count = original.hometask_rates_count;

        // для полiв-покажчикiв буде окремий код, який видiляе нову пам'ять!!!!
        this->hometask_rates = new int[this->hometask_rates_count];
        // мало видiлити пам'ть, ii потрiбно ще й проiнiцiалiзувати!!!
        for (int i = 0; i < this->hometask_rates_count; i++)
        {
            this->hometask_rates[i] = original.hometask_rates[i];
        }
    }

    Student(string value) {
        name = value;
    }

    ~Student()
    {
        if (hometask_rates != nullptr)
        {
            delete[] hometask_rates;
            hometask_rates = nullptr;
        }
    }

    void SetName(string name)
    {
        this->name = name;
    }

    string GetName() const
    {
        return name;
    }

private:

    void SetBirthday(const DateTime& birthday)
    {
        this->birthday = birthday;
    }

public:

    DateTime GetBirthday() const
    {
        return birthday;
    }

    void SetStudyStart(const DateTime& study_start)
    {
        this->study_start = study_start;
    }
    DateTime GetStudyStart() const
    {
        return study_start;
    }

    void SetSurname(string surname)
    {
        this->surname = surname;
    }

    string GetSurname() const
    {
        return surname;
    }

    void AddHometaskRate(unsigned int rate)
    {
        if (rate < 1 || rate > 12)
        {
            cout << "Incorrect value for parameter rate. Value must be from 1 to 12\n";
            throw "ERROR!";
        }

        if (hometask_rates_count == 0)
        {
            hometask_rates = new int[1];
            hometask_rates[0] = rate;
        }
        else
        {
            int* temp = new int[hometask_rates_count + 1];
            for (int i = 0; i < hometask_rates_count; i++)
                temp[i] = hometask_rates[i];
            temp[hometask_rates_count] = rate;
            delete[] hometask_rates;
            hometask_rates = temp;
        }
        hometask_rates_count++;
    }

    void PrintHometaskRates() const
    {
        cout << "Hometasks rates: ";
        for (int i = 0; i < hometask_rates_count; i++)
        {
            cout << hometask_rates[i] << ", ";
        }
        cout << "\n";
    }

    int GetHometaskRateByIndex(unsigned int index)
    {
        if (index >= hometask_rates_count)
        {
            cout << "Incorrect index when accessing the evaluation array\n";
            throw "ERROR!";
        }
        return hometask_rates[index];
    }

    int GetHometasksRatesCount() const
    {
        return hometask_rates_count;
    }

    void AddPracticRate(int rate)
    {
        if (rate < 1 || rate > 12)
        {
            cout << "Incorrect value for parameter rate. Value must be from 1 to 12" << endl;
            throw "ERROR!";
        }

        if (practice_rates_count == 0)
        {
            cout << "Add first rate!" << endl;
            practice_rates = new int[1];
            practice_rates[0] = rate;
        }
        else
        {
            cout << "Add yet another rate" << endl;
            int* temp = new int[practice_rates_count + 1];
            for (int i = 0; i < practice_rates_count; i++)
            {
                temp[i] = practice_rates[i];
                temp[i + 1] = rate;
            }
            delete[] practice_rates;
            practice_rates = temp;
        }

        practice_rates_count++;
    }

    int GetPracticeRateByIndex(unsigned int index)
    {
        if (index >= practice_rates_count)
        {
            cout << "Incorrect index when accessing the evaluation array\n";
            throw "ERROR!";
        }
        return practice_rates[index];
    }

    int GetPracticetasksRatesCount() const
    {
        return practice_rates_count;
    }

    void AddExamRate(int rate)
    {
        if (rate < 1 || rate > 12)
        {
            cout << "Incorrect value for parameter rate. Value must be from 1 to 12" << endl;
            throw "ERROR!";
        }

        if (exam_rates_count == 0)
        {
            cout << "Add first rate!" << endl;
            exam_rates = new int[1];
            exam_rates[0] = rate;
        }
        else
        {
            cout << "Add yet another rate" << endl;
            int* temp = new int[exam_rates_count + 1];
            for (int i = 0; i < exam_rates_count; i++)
            {
                temp[i] = exam_rates[i];
                temp[i + 1] = rate;
            }
            delete[] exam_rates;
            exam_rates = temp;
        }

        exam_rates_count++;
    }

    int GetExamtasksRatesCount() const
    {
        return exam_rates_count;
    }

    int GetExamRateByIndex(unsigned int index)
    {
        if (index >= exam_rates_count)
        {
            cout << "Incorrect index when accessing the evaluation array\n";
            throw "ERROR!";
        }
        return exam_rates[index];
    }

    void PrintPracticeTaskRates() const
    {
        for (int i = 0; i < practice_rates_count; i++)
        {
            cout << practice_rates_count << ")" << practice_rates[i] << endl;
        }
    }
    int GetAverageHometaskRate()const {
        int average = 0;
        for (int i = 0; i < hometask_rates_count; i++)
            average += hometask_rates[i];
        average = average / hometask_rates_count;
        return average;
    }

    Student& operator=(const Student& original)
    {
        if (this == &original)
            return *this;
        name = original.name;
        surname = original.surname;
        birthday = original.birthday;
        study_start = original.study_start;

        if (hometask_rates != nullptr)
            delete[] hometask_rates;

        if (exam_rates != nullptr)
            delete[]exam_rates;

        if (practice_rates != nullptr)
            delete[]practice_rates;

        hometask_rates_count = original.hometask_rates_count;
        exam_rates_count = original.exam_rates_count;
        practice_rates_count = original.practice_rates_count;

        if (hometask_rates_count > 0)
        {
            hometask_rates = new int[hometask_rates_count];
            for (int i = 0; i < hometask_rates_count; i++)
                hometask_rates[i] = original.hometask_rates[i];
        }

        if (exam_rates_count > 0)
        {
            exam_rates = new int[exam_rates_count];
            for (int i = 0; i < exam_rates_count; i++)
                exam_rates[i] = original.exam_rates[i];
        }

        if (practice_rates_count > 0)
        {
            practice_rates = new int[practice_rates_count];
            for (int i = 0; i < practice_rates_count; i++)
                practice_rates[i] = original.practice_rates[i];
        }

        return *this;
    }
};


bool operator==(const Student& left, const Student& right)
{
    return left.GetAverageHometaskRate() == right.GetAverageHometaskRate();
}

bool operator!=(const Student& left, const Student& right)
{
    return left.GetAverageHometaskRate() != right.GetAverageHometaskRate();
}

bool operator>(const Student& left, const Student& right)
{
    return left.GetAverageHometaskRate() > right.GetAverageHometaskRate();
}

bool operator<(const Student& left, const Student& right)
{
    return left.GetAverageHometaskRate() < right.GetAverageHometaskRate();
}


class Group
{
    Student* group;
    int groupSize, courseN;
    string groupName, specialty;
    void SetGroupSize(int groupSize)
    {
        this->groupSize = groupSize;
    }
public:
    friend istream& operator>>(istream& cin, Group& obj);
    friend ostream& operator<<(ostream& cout, Group& obj);
    Group() : Group(0) {}

    Group(int groupSize)
    {
        this->groupSize = groupSize;
        courseN = 1;
        groupName = "KN-0";
        specialty = "Designer";
        group = new Student[groupSize];
    }

    Group(int groupSize, int courseN, string groupName, string specialty)
    {
        this->groupSize = groupSize;
        this->courseN = courseN;
        this->groupName = groupName;
        this->specialty = specialty;
        group = new Student[groupSize];
    }

    Group(const Group& obj)
    {
        this->group = new Student[obj.groupSize];
        this->groupSize = obj.groupSize;
        this->courseN = obj.courseN;
        this->groupName = obj.groupName;
        this->specialty = obj.specialty;
        for (int i = 0; i < obj.groupSize; i++)
            this->group[i] = obj.group[i];
    }

    Group& operator=(const Group& original)
    {
        if (this == &original)
        {
            return *this;
        }

        if (group != nullptr)
            delete[] group;

        groupSize = original.groupSize;
        courseN = original.courseN;
        groupName = original.groupName;
        specialty = original.specialty;

        group = new Student[groupSize];
        for (int i = 0; i < this->groupSize; i++)
            group[i] = original.group[i];

        return *this;
    }

    void printGroup()
    {
        cout << "Group name: " << groupName << endl;
        cout << "Specialty: " << specialty << endl;
        int f;
        Student temp;
        for (int i = 1; i < groupSize; i++)
        {
            f = 0;
            for (int r = 0; r < groupSize - i; r++)
            {
                if (group[r].GetSurname() > group[r + 1].GetSurname())
                {
                    temp = group[r];
                    group[r] = group[r + 1];
                    group[r + 1] = temp;
                    f = 1;
                }
            }
            if (f == 0)
            {
                break;
            }
        }
        for (int i = 0; i < groupSize; i++)
        {
            cout << i + 1 << ' ' << group[i].GetSurname() << ' ' << group[i].GetName();
            cout << endl;
        }
    }

    int getGroupSize() const
    {
        return groupSize;
    }

    Student getStudentByIndex(int index)const
    {
        return group[index];
    }

    void AddStudent(const Student& new_student)
    {
        Student* tmp = new Student[groupSize + 1];
        for (int i = 0; i < groupSize; i++)
            tmp[i] = group[i];

        tmp[groupSize] = new_student;

        delete[] group;
        group = tmp;
        groupSize++;
    }


    void MergeWithGroup(Group& another_group)
    {
        for (int i = 0; i < another_group.getGroupSize(); i++)
        {
            this->AddStudent(another_group.getStudentByIndex(i));
        }

        int k = another_group.getGroupSize();
        for (int i = 0; i < k; i++)
        {
            another_group.DeleteTheWorstStudent();
        }
    }

    void TransferStudent(Group& other, int index)
    {
        if (index >= 0 && index < groupSize)
        {
            other.AddStudent(group[index]);
            for (int i = index; i < groupSize - 1; i++)
                group[i] = group[i + 1];
            groupSize--;
        }
    }

    void DeleteFailedStudents()
    {
        int failedExams = 0, newSize = 0;
        for (int i = 0; i < groupSize; i++)
        {
            if (!(group[i].GetExamRateByIndex(i) > 4))//pass-grade is 4
                failedExams++;
        }
        newSize = failedExams;
        Student* tmp = new Student[groupSize + 1];
        for (int i = 0, j = 0; i < groupSize; i++)
        {
            if (group[i].GetExamRateByIndex(i))
            {
                tmp[j] = group[i];
                j++;
            }
        }
        delete[]group;
        group = tmp;
        groupSize -= failedExams;
    }
    void DeleteTheWorstStudent()
    {
        int worst = 0, tmp1 = 0, first = 0, index = 0;
        Student* tmp = new Student[groupSize - 1];
        for (int i = 0; i < groupSize; i++)
        {
            int gradesCount = group[i].GetHometasksRatesCount();
            for (int j = 0; j < gradesCount; i++)
                tmp1 = group[i].GetHometaskRateByIndex(j);
            if (gradesCount > 0 && first == 0)
            {
                worst = tmp1 / gradesCount;
                index = i;
            }
            else if (gradesCount > 0 && first > 0)
            {
                worst = (tmp1 / gradesCount) < worst ? (tmp1 / gradesCount) : worst;
                index = i;
            }
            tmp1 = 0;
            first++;
        }
        for (int i = 0; i < groupSize; i++)
        {
            if (i < index)
                tmp[i] = group[i];
            else if (i == index)
                continue;
            else
                tmp[i - 1] = group[i];
        }
        delete[]group;
        group = tmp;
    }
    operator string() {
        string info;
        info += "Group name: ";
        info += groupName;
        info += "\n";
        info += "Specialty: ";
        info += specialty;
        info += "\n\n";
        for (int i = 0; i < groupSize; i++)
        {
            info += "Student # ";
            info += to_string(i + 1);
            info += '\n';
            info += "Name: ";
            info += group[i].GetName();
            info += '\n';
            info += group[i].GetSurname();
            info += "Study start: ";
            info += group[i].GetStudyStart().date_to_string();
        }
        info += "\n\n\n";
        return info;
    }
};
bool operator == (const Group& left, const Group& right)
{
    return left.getGroupSize() == right.getGroupSize();
}

bool operator != (const Group& left, const Group& right)
{
    return left.getGroupSize() != right.getGroupSize();
}

istream& operator>>(istream& cin, Group& obj)
{
    cout << "Type a group size:" << endl;
    cin >> obj.groupSize;
    cout << "Type a group course:" << endl;
    cin >> obj.courseN;
    cout << "Type a group-name:" << endl;
    cin >> obj.groupName;
    cout << "Type a group specialty:" << endl;
    cin >> obj.specialty;

    obj.group = new Student[obj.groupSize];

    return cin;
}

ostream& operator<<(ostream& cout, Group& obj)
{
    cout << "Group name: " << obj.groupName << endl;
    cout << "Specialty: " << obj.specialty << endl;

    for (int i = 0; i < obj.groupSize; i++)
    {
        cout << "Student " << i + 1 << ":" << endl;
        cout << "Name: " << obj.group[i].GetName() << endl;
        cout << "Surname: " << obj.group[i].GetSurname() << endl;
        cout << "Birthday: ";
        obj.group[i].GetBirthday().Print();
        cout << "Study start date: ";
        obj.group[i].GetStudyStart().Print();
    }

    return cout;
}

class Fraction
{
    int numerator; // числитель
    int denominator; // знаменатель

public:
    Fraction();
    Fraction(int numerator, int denominator);

    // конструктор преобразования
    /*explicit*/ Fraction(int value)
    {
        numerator = value;
        denominator = 1;
    }

    double GetDecimal() const;
    void Print() const;
    void PrintDecimal() const;

    static Fraction Sum(const Fraction& left, const Fraction& right);
    bool GreaterThan(const Fraction& another) const;
    bool IsEquals(const Fraction& another) const;
    bool LessThan(const Fraction& another) const;

    int GetNumerator() const;
    int GetDenominator() const;
    void SetNumerator(int numerator);
    void SetDenominator(int denominator);
};

/////////////////////////////////////////////////////////////////////////////////////
// прототипы глобальных функций
Fraction operator + (const Fraction& f1, const Fraction& f2);
void F1(Fraction a);
Fraction F2();

/////////////////////////////////////////////////////////////////////////////////////
// пример тестовых вызовов функций для проверки работы конструктора преобразования
// F1(3);
// F2();

// явный конструктор без параметров с делегированием
Fraction::Fraction() : Fraction(0, 1)
{
    // благодаря делегированию в теле этого метода делать уже нечего
}

// "главный" конструктор
Fraction::Fraction(int numerator, int denominator)
{
    SetNumerator(numerator);
    SetDenominator(denominator);
}

// получение дроби в десятичном формате
double Fraction::GetDecimal() const
{
    return (double)numerator / denominator;
}

// распечатка обычной дроби
void Fraction::Print() const
{
    cout << numerator << "/" << denominator << "\n";
}

// распечатка десятичной дроби
void Fraction::PrintDecimal() const
{
    cout << GetDecimal() << "\n";
}

// геттер числителя
int Fraction::GetNumerator() const
{
    return numerator;
}

// геттер знаменателя
int Fraction::GetDenominator() const
{
    return denominator;
}

// сеттер числителя (без проверок)
void Fraction::SetNumerator(int numerator)
{
    this->numerator = numerator;
}

// сеттер знаменателя (знаменатель не должен быть равен 0!)
void Fraction::SetDenominator(int denominator)
{
    if (denominator != 0)
    {
        this->denominator = denominator;
    }
    else
    {
        throw "ERROR!";
    }
}

// сравнение двух дробей (левая дробь сравнивает себя с правой)
bool Fraction::LessThan(const Fraction& right) const
{
    return this->GetDecimal() < right.GetDecimal();
}

// сравнение двух дробей (левая дробь сравнивает себя с правой)
bool Fraction::GreaterThan(const Fraction& right) const
{
    return this->GetDecimal() > right.GetDecimal();
}

// сравнение двух дробей (левая дробь сравнивает себя с правой)
bool Fraction::IsEquals(const Fraction& right) const
{
    return this->GetDecimal() == right.GetDecimal();
}

// тестовая глобальная функция преобразования инта в дробь №1
void F1(Fraction a)
{
    cout << "explicit c-tor test global function F1\n";
}

// тестовая глобальная функция преобразования инта в дробь №2
Fraction F2()
{
    cout << "explicit c-tor test global function F2\n";
    return 5;
}

// сложение двух дробей (статическим методом класса)
Fraction Fraction::Sum(const Fraction& left, const Fraction& right)
{
    Fraction result;
    result.SetNumerator(left.numerator * right.denominator + right.numerator * left.denominator);
    result.SetDenominator(left.denominator * right.denominator);
    return result;
}

///////////////////////////////////////////////////////////////////

// пример перегрузки операции +
Fraction operator + (const Fraction& left, const Fraction& right)
{
    Fraction result;
    result.SetNumerator(left.GetNumerator() * right.GetDenominator() + right.GetNumerator() * left.GetDenominator());
    result.SetDenominator(left.GetDenominator() * right.GetDenominator());
    return result;
}

Fraction operator + (const Fraction& left, int right)
{
    Fraction result;
    result.SetNumerator(left.GetNumerator() + (right * left.GetDenominator()));
    result.SetDenominator(left.GetDenominator());
    return result;
}

Fraction operator + (int left, const Fraction& right)
{
    Fraction result;
    result.SetNumerator((left * right.GetDenominator()) + right.GetDenominator());
    result.SetDenominator(right.GetDenominator());
    return result;
}

Fraction operator + (const Fraction& left, double right)
{
    Fraction result, tmp;
    tmp.SetNumerator((int)right);
    if (right - (int)right > 0)
        tmp.SetDenominator((right - (int)right) * 10);
    else
        tmp.SetDenominator(1);
    result.SetNumerator(left.GetNumerator() * tmp.GetDenominator() + tmp.GetNumerator() * left.GetDenominator());
    result.SetDenominator(left.GetDenominator() * tmp.GetDenominator());
    return result;
}

Fraction operator + (double left, const Fraction& right)
{
    Fraction result, tmp;
    tmp.SetNumerator((int)left);
    if (left - (int)left > 0)
        tmp.SetDenominator((left - (int)left) * 10);
    else
        tmp.SetDenominator(1);
    result.SetNumerator(right.GetNumerator() * tmp.GetDenominator() + tmp.GetNumerator() * right.GetDenominator());
    result.SetDenominator(right.GetDenominator() * tmp.GetDenominator());
    return result;
}

Fraction operator - (const Fraction& left, const Fraction& right)
{
    Fraction result;
    result.SetNumerator(left.GetNumerator() * right.GetDenominator() - right.GetNumerator() * left.GetDenominator());
    result.SetDenominator(left.GetDenominator() * right.GetDenominator());
    return result;
}

Fraction operator * (const Fraction& left, const Fraction& right)
{
    Fraction result;
    result.SetNumerator(left.GetNumerator() * right.GetNumerator());
    result.SetDenominator(left.GetDenominator() * right.GetDenominator());
    return result;
}

Fraction operator / (const Fraction& left, const Fraction& right)
{
    if (right.GetNumerator() == 0) {
        throw "ERROR: Division by zero.";
    }

    Fraction result;
    result.SetNumerator(left.GetNumerator() * right.GetDenominator());
    result.SetDenominator(left.GetDenominator() * right.GetNumerator());
    return result;
}

int main()
{
    /*cout << today[3]; //ERROR
    cout << today[-1]; // ERROR*/


    string name = "Veronika";
    Student s = name; // мае працювати
    Group a;
    a.AddStudent(s);
    string b = a;
    cout << b;
    //Fraction a(2, 5); // 1/2
    //double b = 6;
    //Fraction result = a + b;
    //cout << result.GetNumerator()<<'/'<<result.GetDenominator();
    //Fraction b(1, 4); // 1/4

    //Fraction result = a + b; // 1/2 + 1/4

    //result.Print(); // 6/8
}