// [2-2.2] Insert => Open Address 방법
/***********************************************************/
 
#if 1
 
int Insert_Data(SCORE * d)
{
    int pos, key;
    pos= key = Get_Hash_Key(d->id);// key는 백업용 , pos 는 추가할 데이터의 아이디 
    for (;;) {
        //빈방이면 저장하고 방 번호 리턴
        if (Hash_table[pos].id == -1) {
            Hash_table[pos] = *d; //자료 넣어주기 
            return pos;
        }
        else {
            //아니면 STEP만큼 증가
            pos =pos + STEP;
 
            // 1순회 하였따면 빈방이 없으므로 -1 리턴 
            if (pos == key) return -1;
 
            //방끝까지 도달하면 다시 방시작으로
            if (pos >= MAX_ST) pos = 0;
        }
    }
 
    /* 내가 처음 생각햇던거랑 비교하자.
    if (Hash_table[HASH_KEY]) Hash_table[HASH_KEY]= Get_Hash_Key(&d);
    else {
        if (Hash_table[]) {
         
        }
            Hash_table[HASH_KEY + STEP] = Get_Hash_Key(&d);
    }
 
    */
 
}
 
/***********************************************************/
// [2-2.3] Search
/***********************************************************/
 
#if 0
 
SCORE * Search_Data(int id)
{
    int pos, key;
    pos = key = Get_Hash_Key(id);// key는 백업용 , pos 는 추가할 데이터의 아이디 
    for (;;) {
        //해당 KEY자리에 같은 사번이면 1리턴
        if (Hash_table[pos].id == id) return &Hash_table[pos];
 
        //해당 KEY방이 빈방이면 없는 자료이므로 NULL 리턴
        if (Hash_table[pos].id == -1) return NULL;
 
        //아니면 STEP만큼 증가
        pos = pos + STEP;
 
        // 1순회 하였따면 빈방이 없으므로 -1 리턴 
        if (pos == key) return NULL;
        //방끝까지 도달하면 다시 방시작으로
        if (pos >= MAX_ST) pos = 0;
    }
}
/***********************************************************/
// [2-3-1.2] Heap Push (Min Heap)
/***********************************************************/
#if 1
int Heap_Push_Minheap(int *heap, int size, int *lastnode, int d)
{
    int temp, n, p;
 
    //풀체크
    if (*lastnode == size) return 0; 
 
    //마지막노드에 데이터추가 
    ++(*lastnode);
    heap[*lastnode] = d;
    n = *lastnode;
 
    while (n/2)//끝까지 다올라가도 종료. 만약 나누기 2안하면 부모가 0일떄의 판단이아니라 지가 0일때의 판단
    {
        //추가된 자식과 부모와 비교하여 재배치
        if (heap[n / 2] > heap[n]) {
            temp = heap[n / 2];
            heap[n / 2] = heap[n];
            heap[n] = temp;
            n = n / 2;
        }
        //재배치할 필요없으면 종료 
        else break;
    }
 
    /***** 강사님 방식 ***********
    i=*lastnode;
    p=i/2;
    while (p)//끝까지 다올라가도 종료 
    {
        //추가된 자식과 부모와 비교하여 재배치
        if (heap[p] < heap[n]) {
            temp = heap[p];
            heap[p] = heap[n];
            heap[n] = temp;
            n = n / 2;
            p = n / 2;
 
        }
        //재배치할 필요없으면 종료 
        else break;
    }
     
     
    */
 
 
 
    return 1;
}
/***********************************************************/
// [2-3-1.3] Heap Pop (Min Heap)
/***********************************************************/
#if 1
int Heap_Pop_Minheap(int *heap, int *lastnode, int *d)
{
    int p,c, temp;
 
    //Empty 체크
    if (*lastnode == 0) return -1;
 
    //pop을 최상위에 뽑자
    *d = heap[1];
 
    //라스트 노드가 가리키는 애를 최상위로 올리자. 라스트 노드 하나 줄이기
    heap[1] = heap[(*lastnode)--];
 
    //부모 왼쪽 자식 ,오른쪽 자식 초기화
    p = 1;
    c = p * 2;  
    // 부모와 자식 경쟁하며 내려가기
    while (c<=(*lastnode)){
    //자식이 한명인지 두명인지 판단하기 
 
        //자식 한개인경우
        if (heap[c + 1] == 0) {
            if (heap[p]>heap[c]) {
                temp = heap[p];
                heap[p] = heap[c];
                heap[c] = temp;
                p = c;
                c = c * 2;
            }
            else break;
        }
 
        //자식 두개인 경우
        else {
            //두명일경우 우선순위가 높은쪽과 비교하기 
            if (heap[c] < heap[c + 1]) {
                if (heap[p]>heap[c]) {
                    temp = heap[p];
                    heap[p] = heap[c];
                    heap[c] = temp;
                    p =c;
                    c = c * 2;
                }
                else break;
            }
            else {
                if (heap[p]>heap[c+1]) {
                    temp = heap[p];
                    heap[p] = heap[c+1];
                    heap[c+1] = temp;
                    p = c + 1;
                    c = (c+1) * 2;
                }
                else break;
            }   
        }
    }
    return 1;
 
    /*
    int l, r, c, p, temp;
        //Empty 체크
        if(heap[*lastnode]==0) return 0;
 
        //최상위노드 전달후 lastnode 조정
        *d=heap[1];
        heap[1]=heap[(*lastnode)--];
 
        //부모, 왼쪽 자식, 오른쪽 자식위치 초기화
        p=1;l=2;r=3;
 
        //왼쪽 자식이 lastnode일떄까지 하위노드로이동
        while(l<=(*lastnode)){   //왼쪽은 항상 있기때문에 ㅁ노ㅓㅏㅁㄴ오리ㅕㅑㅁㅈ돌
            //부모와 비교할 자식후보자 선택
            //자식이 하나이면 왼쪽노드가후보자
            if(l == *lastnode) c=1; //완전이진트리라서 자식이 하나일려면 l이 lastnode의 값과 같아야함.
 
            //자식이 둘이면 둘중 우선순위높은 후보자 선택
            else if(heap[l]<heap[r]) c=1;
            else c=r;
 
            //부모와 자식후보자와 비교하여 재배치후 부모, 자식위치 조정
            if (heap[p]>heap[c]) {
                temp = heap[p];
                heap[p] = heap[c];
                heap[c] = temp;
                p = c;
                l = 2*p;
                r = 2*p+1;
            }   
            //재배치 필요 없으면 종료
            else break;
        }
 
     
    */
     
}
/***********************************************************/
// [2-3-1.4] Heap Push (Max Heap)
/***********************************************************/
#if 1
int Heap_Push_Maxheap(int *heap, int size, int *lastnode, int d)
{
    int temp, n, p;
 
    //풀체크
    if (*lastnode == size) return 0;
 
    //마지막노드에 데이터추가 
    ++(*lastnode);
    heap[*lastnode] = d;
    n = *lastnode;
 
    while (n / 2)//끝까지 다올라가도 종료. 만약 나누기 2안하면 부모가 0일떄의 판단이아니라 지가 0일때의 판단
    {
        //추가된 자식과 부모와 비교하여 재배치
        if (heap[n / 2] < heap[n]) {
            temp = heap[n / 2];
            heap[n / 2] = heap[n];
            heap[n] = temp;
            n = n / 2;
        }
        //재배치할 필요없으면 종료 
        else break;
    }
    return 1;
 
}
/***********************************************************/
// [2-3-1.5] Heap Pop (Max Heap)
/***********************************************************/
#if 1
int Heap_Pop_Maxheap(int *heap, int *lastnode, int *d)
{
 
    int l, r, c, p, temp;
    //Empty 체크
    if (heap[*lastnode] == 0) return 0;
 
    //최상위노드 전달후 lastnode 조정
    *d = heap[1];
    heap[1] = heap[(*lastnode)--];
 
    //부모, 왼쪽 자식, 오른쪽 자식위치 초기화
    p = 1; l = 2; r = 3;
 
    //왼쪽 자식이 lastnode일떄까지 하위노드로이동
    while (l <= (*lastnode)) {   //왼쪽은 항상 있기때문에 ㅁ노ㅓㅏㅁㄴ오리ㅕㅑㅁㅈ돌
                                //부모와 비교할 자식후보자 선택
                                //자식이 하나이면 왼쪽노드가후보자
        if (l == *lastnode) c = 1;  //완전이진트리라서 자식이 하나일려면 l이 lastnode의 값과 같아야함.
 
                                    //자식이 둘이면 둘중 우선순위높은 후보자 선택
        else if (heap[l]>heap[r]) c = 1;
        else c = r;
 
        //부모와 자식후보자와 비교하여 재배치후 부모, 자식위치 조정
        if (heap[p]<heap[c]) {
            temp = heap[p];
            heap[p] = heap[c];
            heap[c] = temp;
            p = c;
            l = 2 * p;
            r = 2 * p + 1;
        }
        //재배치 필요 없으면 종료
        else break;
    }
    return 1;
 
}
/***********************************************************/
// [2-3-1.6] Heap Sort 
/***********************************************************/
#if 1
typedef int(*HEAP_PUSH)(int*, int, int*, int);
typedef int(*HEAP_POP)(int*, int*, int*);
 
void Heap_Sort(int *data, int cnt, int order)
{
    int i, re, lastnode = 0;
    HEAP_PUSH push[2] = { Heap_Push_Maxheap, Heap_Push_Minheap };
    HEAP_POP pop[2] = { Heap_Pop_Maxheap, Heap_Pop_Minheap };
 
    //cnt개수만큼 push
    //cnt개수만큼 pop하여 data배열에 뒤에서부터 저장
    for ( i = 0; i < cnt; i++){
        push[order](data - 1, MAX_DATA, &lastnode, data[i]);
    }
 
    for (i = cnt-1; i >=0; i--) {
        pop[order](data - 1, &lastnode, &re);
        data[i] = re;
    }
 
 
    /*
    int i, temp, ret;
    int temp = cnt;
    //오름 차순일 경우 MAXheap, 내림 차순일 경우 Minheap 일단 나중에 구현하자.
    //Heap_Pop_Maxheap(*heap, *lastnode, *d)
    //Heap_Push_Maxheap(*heap, size, *lastnode, d)
 
 
    //정렬할 자료의 수 만큼 정렬 
    for  (i = 0; i < cnt; i++)
    {
        //pop으로 최상위 노드 꺼낸다음에 꺼낸노드 가장 마지막에 놓기 
        Heap_Pop_Maxheap(heap, &lastnode, &ret);
        data[--temp] = ret;
    }
    */
}
/***********************************************************/
// [2-3-2.2] 새로운 데이터의 추가 및 데이터 업데이트 함수
/***********************************************************/
#if 1
void Update_New_Data(int node, int s, int e, int idx, int data)
{
    int m;
    m = (s + e) / 2;
    //leaf 노드이면 현재 노드에 데이터 저장하고 리턴
    if (s == e) {
        tree[node] = data;
        return;
    }
 
    //idx가 중간 m이하이면 왼쪽자식으로 재귀호출
    if (idx<=m)
        Update_New_Data(node*2, s, m, idx,data);
         
    //idx가 중간 m보다 크면 오른쪽 자식으로 재귀호출
    else
        Update_New_Data(node*2 + 1, m+1, e, idx, data);
     
    //리턴하여 돌아오면 현재노드의 왼, 오른자식노드의 합으로 갱신
    tree[node] = tree[node*2] + tree[node*2+1];
}
/***********************************************************/
// [2-3-2.3] 구간 정보 요청
/***********************************************************/
#if 1
int Query(int node, int s, int e, int qs, int qe)
{
    int m, l, r;
    // qs~qe 이내에 s~e가 들어가면 해를 들고 리턴
    if (qs <= s && e <= qe)   return tree[node];
    // 무관한 범위이면 0을 return
    else if(e < qs || qe < s) return 0;
    m = (s + e) / 2;
    // 왼쪽자식으로 재귀호출
    l=Query(node * 2, s, m, qs, qe);
    // 오른쪽 자식으로 재귀호출
    r=Query(node * 2 + 1, m+1, e, qs, qe);
    // 양쪽 자식으로 받은 해를 더하여 리턴
    return l+r;
}
/*************************************************************/
// [2-3-2.4] 특정 구간 데이터 변경 함수 - 데이터 증가/감소
/*************************************************************/
#if 1
void Update_Add(int node, int s, int e, int us, int ue, int add){
    int m;
 
    //us~ue범위를 벗어난 경우 리턴
    if (e<us || ue<s) return;//query처럼 end가 us보다 앞서거나 ue보다 s가 뒤에있거나.
 
    //s==e이면 현재 노드 add더하고 리턴
    if (s == e) {
        tree[node] += add;
        return;
    }
    m = (s + e) / 2;
 
    //왼쪽자식 재귀호출
    Update_Add(node*2,s,m,us,ue,add);
 
    //오른쪽자식 재귀 호출
    Update_Add(node*2+1,m+1,e,us,ue,add);
 
    //리턴하여 돌아오면 현재 노드의 자식노드의 합으로 갱신
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}
 
/***********************************************************/
// [2-3-2.6] Propagate 함수
/***********************************************************/
#if 1
 
void Propagate(int node, int s, int e)// 해당 노드의 lazy값을 반영하고 자식 노드에게 lazy 값 전파 
{
    //전파시킬 값이 있으면 Leaf노드가 아니라면
    if (lazy[node]) {
        if (s != e) {//Leaf 노드가 아니라면
            //자식노드에게 전파시키고
            lazy[node * 2] += lazy[node];
            if (node * 2 + 1 <= LAST_NODE) 
                lazy[node * 2 + 1] += lazy[node];
        }
        //현재노드의 정보를 갱신( tree[node] += (e - s + 1)*lazy[node] )
        tree[node] += (e - s + 1)*lazy[node];
        //현재 노드의 lazy값 갱신
        lazy[node] = 0;
    }
}
#endif