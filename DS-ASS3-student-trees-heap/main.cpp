#include <bits/stdc++.h>
#include <fstream>
using namespace std;
struct student
{
    int ID;
    string name;
    float GPA;
    string department;
};
class minHeap
{
public:
    void heapify(vector<student>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && arr[left].GPA > arr[largest].GPA)
            largest = left;
        if (right < n && arr[right].GPA > arr[largest].GPA)
            largest = right;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
    void sortedheap(vector<student>& arr)
    {
        for (int i = arr.size() - 1; i >= 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
    void min_heap(vector<student>& arr) {
        int n = arr.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);
        sortedheap(arr);
    }
    void readFile(vector<student>& students)
    {
        string myText;
        ifstream MyReadFile("data.txt");
        int counter = 0;
        student s;
        while (getline(MyReadFile, myText)) {

            if (counter == 0)
            {
                s.ID = stoi(myText);
            }
            else if (counter == 1)
            {
                s.name = myText;

            }
            else if (counter == 2)
            {

                s.GPA = stof(myText);
            }
            else
            {
                s.department = myText;
                students.push_back(s);
                counter = -1;
            }
            counter += 1;
        }
        MyReadFile.close();
    }
    void printAllStudents(vector<student> students)
    {
        cout << "Print " << students.size() << " studnts." << endl;
        for (size_t i = 0; i < students.size(); i++)
        {

            cout << "[" << students[i].ID << ", " << students[i].name << ", " << students[i].GPA << ", " << students[i].department << "]" << endl;
        }
    }
    void addStudent(vector<student>& students)
    {
        student s;
        while (true)
        {
            string st;
            bool flag = true;
            cout << "ID: ";
            cin >> st;
            for (char c : st)
            {
                if (!isdigit(c))
                {
                    cout << "please entre number." << endl;
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                for (size_t i = 0; i < students.size(); i++)
                {
                    if (stoi(st) == students[i].ID)
                    {
                        cout << "ID is used please entre deffient ID." << endl;
                        flag = false;
                        break;
                    }
                }
            }


            if (flag)
            {
                s.ID = stoi(st);
                break;
            }
        }
        cout << "Name: ";
        cin >> s.name;
        while (true)
        {
            string stt;
            bool flag = true;
            cout << "GPA: ";
            cin >> stt;
            for (char cc : stt)
            {

                if (cc == '.')
                {
                    continue;
                }
                if (!isdigit(cc))
                {
                    cout << "please entre number." << endl;
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                if ((stof(stt) > 4) || (stof(stt) < 0))
                {
                    cout << "GPA must be betwen 0 and 4" << endl;
                }
                else
                {
                    s.GPA = stof(stt);
                    break;
                }
            }
        }
        while (true)
        {
            cout << "Departmwnt: ";
            cin >> s.department;
            for (char& c : s.department)
            {
                c = toupper(c);
            }
            if ((s.department == "IT") || (s.department == "CS") || (s.department == "IS") || (s.department == "AI") || (s.department == "DS"))
            {
                break;
            }
            else
            {
                cout << "please entre department in our unvirsty [CS, IT, IS, AI, DS]." << endl;
            }
        }
        students.push_back(s);
        cout << "The student is added."<<endl;
        min_heap(students);
    }
    void menu()
    {
        string option;
        vector<student> students;
        readFile(students);
        min_heap(students);
        while (true)
        {
            cout << "choose one of the following options: \n" << "1. add a student \n" << "2. print all student(sorted by gpa) \n" << "3. exit \n";
            cin >> option;
            if (option == "1")
            {
                addStudent(students);
            }
            else if (option == "2")
            {
                this->printAllStudents(students);
                
            }
            else if (option == "3")
            {
                break;
            }
            else
            {
                cout << "invalid input" << endl;
            }
        }

    }
};
class maxHeap : public minHeap
{
public:
    void printAllStudents(vector<student> students)
    {
        reverse(students.begin(), students.end());
        cout << "Print " << students.size() << " studnts." << endl;
        for (size_t i = 0; i < students.size(); i++)
        {
            cout << "[" << students[i].ID << ", " << students[i].name << ", " << students[i].GPA << ", " << students[i].department << "]" << endl;
        }
    }
    void menu()
    {
        string option;
        vector<student> students;
        readFile(students);
        min_heap(students);
        while (true)
        {
            cout << "choose one of the following options: \n" << "1. add a student \n" << "2. print all student(sorted by gpa) \n" << "3. exit \n";
            cin >> option;
            if (option == "1")
            {
                addStudent(students);
            }
            else if (option == "2")
            {
                this->printAllStudents(students);

            }
            else if (option == "3")
            {
                break;
            }
            else
            {
                cout << "invalid input" << endl;
            }
        }

    }

};
int main() 
{
    maxHeap k;
    k.menu();
}