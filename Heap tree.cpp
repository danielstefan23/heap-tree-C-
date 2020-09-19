#include <iostream>
#include <fstream>
#include <assert.h>
 
using namespace std;
ifstream fin ("heapuri.in");
ofstream fout ("heapuri.out");
 
const int MAX_HEAP_SIZE = 200010;
int pos[MAX_HEAP_SIZE], nr_elem;
pair<int, int> heap[MAX_HEAP_SIZE];
 
inline int father(int node_index){
    return node_index / 2;
}
 
inline int left_son(int node_index){
    return 2 * node_index;
}
 
inline int right_son(int node_index){
    return 2 * node_index + 1;
}
 
void up(int index){
    bool flag = true;
 
    while(flag){
        if(index == 1 || heap[index].first > heap[father(index)].first){
            flag = false;
        }
        else{
            swap(heap[index], heap[father(index)]);
            pos[heap[index].second] = index;
            pos[heap[father(index)].second] = father(index);
            index = father(index);
        }
    }
}
 
void down(int index){
 
    int son;
 
    do{
        son = 0;
 
        if(left_son(index) <= nr_elem){
            son = left_son(index);
 
            if(right_son(index) <= nr_elem && heap[right_son(index)].first < heap[left_son(index)].first)
                son = right_son(index);
            if(heap[son].first >= heap[index].first)
                son = 0;
        }
 
        if(son){
            swap(heap[index], heap[son]);
            pos[heap[son].second] = son;
            pos[heap[index].second] = index;
            index = son;
        }
 
    }while(son);
 
}
 
 
void insert_element(int insert_elem){
    int index = nr_elem;
 
    heap[index].first = insert_elem;
 
    up(index);
}
 
void delete_element(int delete_elem){
    heap[delete_elem] = heap[nr_elem--];
    pos[heap[delete_elem].second] = delete_elem;
 
    int position = delete_elem;
 
    if(position > 1  && heap[position].first < heap[father(position)].first)
        up(position);
    else
        down(position);
}
 
 
int main()
{
    int N, i = 0, counter, track, insert_elem, delete_elem;
    fin >> N;
 
    assert(1 <= N && N <= 200000);
 
    for(counter = 1; counter <= N; counter++){
        fin >> track;
 
        assert(1 <= track && track <= 3);
 
        if(track == 1){
            fin >> insert_elem;
            assert(1 <= insert_elem && insert_elem <= 1000000000);
            pos[++i] = ++nr_elem;
            heap[nr_elem].second = i;
            insert_element(insert_elem);
        }
        else if (track == 2){
            fin >> delete_elem;
            assert(1 <= delete_elem && delete_elem <= 1000000000);
            delete_element(pos[delete_elem]);
            //cout << heap[1].first << endl;
        }
        else{
            fout << heap[1].first <<"\n";
        }
    }
 
   // for(int i = 1; i < 9999; i++)
    //    cout << heap[i].first << endl;
 
    return 0;
}