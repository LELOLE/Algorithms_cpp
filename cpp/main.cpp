//
//  main.cpp
//  cpp
//
//  Created by zhujunli on 2020/11/10.
//****************    关于链表的笔记     *******************/
/*
 链表的创建，依次定义结点并赋值
 */
//****************         *******************/
#include <iostream>
#include <set>
//*****************    Definition of ListNode   *******************/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {
    }
};
//******************************************************************/

//*****************         SOULUTIONS         *********************/

class Solution {
public:
    ListNode * reverseList(ListNode * head);
    ListNode * reverseBetween(ListNode *head, int m, int n);
    ListNode * getIntersectionNode(ListNode * headA, ListNode * headB);
};

//*****************         DECLARATION         *********************/
void testReverseList();
void testReverseBetween();
int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
//    testReverseList();w
    testReverseBetween();
    
    return 0;
}


#pragma mark 将整个链表逆序(206)
ListNode * Solution::reverseList(ListNode * head) {
    ListNode *new_head = NULL;
    while (head) {
        ListNode *next = head->next;
        head->next = new_head;
        new_head = head;
        head = next;
    }
    return new_head;
}
void testReverseList() {
    ListNode a(1), b(2), c(3), d(4), e(5);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    Solution Solve;
    ListNode *head = &a;
    printf("Before reverse:\n");
    while (head) {
        printf("%d\n",head->val);
        head = head->next;
    }
    head = Solve.reverseList(&a);
    printf("After reverse:\n");
    while (head) {
        printf("%d\n",head->val);
        head = head->next;
    }
}
#pragma mark 将链表m到n之间的元素逆序(92)
ListNode * Solution::reverseBetween(ListNode *head, int m, int n) {
    int change_len = n - m + 1;//计算需要逆置的结点个数
    ListNode *pre_head = NULL;//初始化开始逆置的结点前驱
    ListNode *result = head;//最终转换后的链表头结点，非特殊情况即为head
    while (head && --m) {//将head向前移动m-1个位置
        pre_head = head;//记录head的前驱
        head = head->next;
    }
    ListNode *modify_list_tail = head;//将modify_list_tail指向当前的head，即逆置后的链表尾
    ListNode *new_head = NULL;
    while (head && change_len) {//逆置change_len个结点
        ListNode *next = head->next;
        head->next = new_head;
        new_head = head;
        head = next;
        change_len--;//每完成一个结点逆置，change_len--
    }
    modify_list_tail->next = head;//连接逆置后的链表尾与逆置段的最后一个结点
    if (pre_head) {//如果pre_head不空，说明不是从第一个结点开始逆置的m>1
        pre_head->next = new_head;//将逆置链表开始的结点前驱与逆置后的头结点链接
    }
    else {
        result = new_head;//如果pre_head为空，说明 m==1 从第一个结点开始逆置结果即为逆置后的头结点
    }
    return result;
}
void testReverseBetween() {
    ListNode a(1), b(2), c(3), d(4), e(5);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    Solution Solve;
    ListNode *head = &a;
    printf("Before reverse:\n");
    while (head) {
        printf("%d\n",head->val);
        head = head->next;
    }
    head = Solve.reverseBetween(&a, 2, 4);
    printf("After reverse:\n");
    while (head) {
        printf("%d\n",head->val);
        head = head->next;
    }
}

#pragma mark 求两个链表的交点(160)
ListNode * getIntersectionNode(ListNode * headA, ListNode * headB) {
    ListNode *node = NULL;
    return node;
}

//准备知识C++ Set
void testSet() {
    std::set<int> test_set;
    const int A_LEN = 7;
    const int B_LEN = 8;
    
}



