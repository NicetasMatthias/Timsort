#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

struct run
{
    int start;
    int length;
    run(int st,int len):start(st),length(len){}
};
int minRunLength(int n);


int main()
{
    int N=0,minrun=0,tmp_start=0,current_index=0,*tmp_arr=nullptr,first_ind=0,second_ind=0;
    int *arr=nullptr;
    run tmp_run(0,0);
    vector <run> runs;
    cout << "input number of elements:";
    cin >> N; //считываем сколько элементов должно быть в массиве
    arr = new int [N]; //выделяем память под нужное количество элементов
    srand(static_cast<unsigned int>(time(nullptr))); //сбрасываем рандом временем
    cout << "Unsorted array:" << endl;
    for (int i = 0; i < N; i++)
    {
        arr[i]=rand()%10000; //заполняем рандомом
        cout << arr[i] << "\t";
    }
    minrun=minRunLength(N);
    //тут начинаем работать с массивом
    while (current_index<N) //тут мы разбиваем массив на подмассивы
    {
        if (current_index==N-1)
        {
            runs.end()->length++;
            break;
        }
        tmp_start=current_index;

        if (arr[tmp_start]>arr[tmp_start+1])
        {
            swap(arr[tmp_start],arr[tmp_start]);
        }
        current_index+=2;
        while (arr[current_index]>=arr[current_index-1])
        {
            current_index++;
        }
        if (current_index-tmp_start<minrun)
        {
            if (tmp_start+minrun>N)
                current_index=N-1;
            else
                current_index=tmp_start+minrun;
        }
        runs.push_back(run(tmp_start,current_index-tmp_start+1));

        for (int i = tmp_start+1; i <= current_index; i++) // сортируем подмассив вставками
        {
            for (int j=i;(j>tmp_start)&&(arr[j-1]>arr[j]);j--)
            {
                swap(arr[j],arr[j-1]);
            }
        }

        if (current_index==N-1) break;
        current_index++;

    }

    cout << "\n\nArray with sorted runs:" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << arr[i] << "\t";
    }

    //начинаем сливать подмассивы
    while (runs.size()>1)
    {
        tmp_run=runs[(runs.size()-2)];
        tmp_arr=new int [tmp_run.length];
        for (int i=tmp_run.start; i<tmp_run.start+tmp_run.length; i++)
        {
            tmp_arr[i-tmp_run.start]=arr[i];
        }
        current_index=tmp_run.start;
        first_ind=0;
        second_ind=runs.back().start;
        while (current_index!=runs.back().start+runs.back().length-1)
        {
            if (first_ind==tmp_run.length)
            {
                arr[current_index]=arr[second_ind];
                current_index++;
                second_ind++;
                continue;
            }

            if (second_ind==(runs.back().start+runs.back().length))
            {
                arr[current_index]=tmp_arr[first_ind];
                current_index++;
                first_ind++;
                continue;
            }


            if ((tmp_arr[first_ind]<arr[second_ind]))
            {
                arr[current_index]=tmp_arr[first_ind];
                current_index++;
                first_ind++;
            }
            else
            {
                arr[current_index]=arr[second_ind];
                current_index++;
                second_ind++;
            }
        }
        runs[(runs.size()-2)].length+=runs.end()->length;
        runs.pop_back();
    }

    cout << "\n\nSorted array:" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << arr[i] << "\t";
    }


    return 0;
}

int minRunLength(int n)
{
    int flag = 0;
    while (n >= 64)
    {
        flag |= n & 1;
        n >>= 1;
    }
    return n + flag;
}
