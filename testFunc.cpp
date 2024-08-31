#include <bits/stdc++.h>
using namespace std;

class Classroom
{
private:
    string *name_arr;
    int *score_arr;
    int count;

public:
    Classroom()
    {
        name_arr = new string[99999];
        score_arr = new int[99999];
        count = 0;
    }
    ~Classroom(){
        delete []name_arr;
        delete []score_arr;
    }
    void add(string n, int s)
    {
        name_arr[count] = n;
        score_arr[count] = s;
        count++;
    }

    void displayall()
    {
        for (int i = 0; i < count; i++)
        {
            cout << "Name: " << name_arr[i] << endl
                 << "Score: " << score_arr[i] << endl;
        }
    }
    void displaybest()
    {
        int max = score_arr[0];
        for (int i = 0; i < count; i++)
        {
            if (max < score_arr[i])
                max = score_arr[i];
        }
        for (int i = 0; i < count; i++)
        {
            if (score_arr[i] == max)
                cout << "Name: " << name_arr[i] << endl
                     << "Score: " << score_arr[i] << endl;
        }
    }
};

void quickSort(dataList<node> *l){
    int pivot = l->get(0).distance;
    dataList<node> *leftBound;
    dataList<node> *middleBound;
    dataList<node> *rightBound;
    for (int i = 0; i < l->length(); i++){
        node newNode = l->get(i);
        if (l->get(i).distance < pivot)
            leftBound->push_back(newNode);
        else if (l->get(i).distance == pivot)
            middleBound->push_back(newNode);
        else
            rightBound->push_back(newNode);
    }
}

struct node{
public:
    int distance;
    int Label;
    node operator=(node other){
        node newNode;
        newNode.distance = other.distance;
        newNode.Label = other.Label;
        return newNode;
    }
};

int main()
{
    ifstream file("mnist.csv");
    string line;
    stringstream ss;
    getline(file,line);
    ss << line;
    while (getline(ss,line,','))
        cout << line << " ";
}