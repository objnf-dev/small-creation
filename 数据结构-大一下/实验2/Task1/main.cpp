#include "chainlist.h"

void SkimAndOutput(Node *chain){
    cout<<"当前链表长度为："<<ListLength(chain)<<"\n"<<"列表中的元素为：";
    for(int i=1;i<=ListLength(chain);i++){
        DataType tmp;
        Find_pos(chain, i, &tmp);
        cout<<tmp<<" ";
    }
    cout<<endl;
}

int main(){
    struct Node *chain;
    if(InitList(chain))
        cout<<"链表初始化成功"<<endl;
    DataType dataInsert[5] = {'a', 'b', 'c', 'd', 'e'};
    for(int i=0;i<5;i++)
    ListInsert(chain, 1, dataInsert[i]);
    SkimAndOutput(chain);
    DataType insert_f = 'f';
    ListInsert(chain, 3, insert_f);
    SkimAndOutput(chain);
    cout<<"请输入要删除的元素：";
    DataType del_ele;
    cin>>del_ele;
    ListDelete(chain, del_ele);
    SkimAndOutput(chain);
    DestroyList(chain);
    cout<<"链表销毁成功。"<<endl;
    return 0;

}
