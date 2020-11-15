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
    ListNode * getIntersectionNode1(ListNode * headA, ListNode * headB);
    ListNode * getIntersectionNode2(ListNode * headA, ListNode * headB);
    ListNode * detectCycle1(ListNode *head);
    ListNode * detectCycle2(ListNode *head);
};

//*****************         DECLARATION         *********************/
void testReverseList();
void testReverseBetween();
void testSet();
void testIntersection();
void testDetectCycle();
int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
//    testReverseList();w
//    testReverseBetween();
//    testSet();
    testIntersection();
    testDetectCycle();
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
//solution 1
ListNode * Solution::getIntersectionNode1(ListNode * headA, ListNode * headB) {
    std::set<ListNode *>node_set;
    while (headA) {
        node_set.insert(headA);
        headA = headA->next;
    }
    while (headB) {
        if (node_set.find(headB) != node_set.end()) {
            return headB;
        }
        headB = headB->next;
    }
    return NULL;
}
//Solution 2 空间复杂度
int get_list_length(ListNode *head) {
    int len = 0;
    while(head) {//遍历链表，计算链表长度
        len++;
        head = head->next;
    }
    return len;
}

ListNode *forward_long_list(int long_len, int short_len, ListNode *head) {
    int delta = long_len - short_len;
    while (head && delta) {
        head = head->next;//将指针向前移动至多出节点个数后面的位置
        delta--;
        
    }
    return head;
}

ListNode *Solution::getIntersectionNode2(ListNode * headA, ListNode * headB) {
    int list_A_len = get_list_length(headA);
    int list_B_len = get_list_length(headB);//求A,B两个链表的长度
    if (list_A_len > list_B_len) {
        headA = forward_long_list(list_A_len, list_B_len, headA);//如果链表A长，移动headA到对应位置
    } else {
        headB = forward_long_list(list_B_len, list_A_len, headB);//如果链表B长，移动headB到对应位置
    }
    
    while (headA && headB) {
        if (headA == headB) {//当两个指针指向同一节点时，说明找到了
            return headA;
        }
        headA = headA->next;
        headB = headB->next;
    }
    return NULL;
}

//准备知识C++ Set

void testSet() {
    std::set<int> test_set;
    const int A_LEN = 7;
    const int B_LEN = 8;
    
    int a[A_LEN] = {5, 1, 4, 8, 10, 1, 3};
    int b[B_LEN] = {2, 7, 6, 3, 1, 6, 0, 1};
    for (int i = 0; i < A_LEN; i++) {
        test_set.insert(a[i]);
    }
    for (int i = 0; i < B_LEN; i++) {
        if (test_set.find(b[i]) != test_set.end()) {
            printf("b[%d] = %d in array A.\n", i, b[i]);
        }
    }
}

void testIntersection() {
    ListNode a1(1), a2(2), b1(3), b2(4), b3(5), c1(6), c2(7), c3(8);
    a1.next = &a2;
    a2.next = &c1;
    c1.next = &c2;
    c2.next = &c3;
    b1.next = &b2;
    b2.next = &b3;
    b3.next = &c1;
    Solution solve;
    ListNode *result1 = solve.getIntersectionNode1(&a1, &b1);
    ListNode *result2 = solve.getIntersectionNode2(&a1, &b1);
    printf("result_1_val = %d, result_2_val = %d \n", result1->val, result2->val);
}


#pragma mark 链表求环(141)
// Solution 1 使用set求环起始节点
ListNode *Solution::detectCycle1(ListNode *head) {
    std::set<ListNode *>node_set;
    while (head) {
        if (node_set.find(head) != node_set.end()) {
            return head;
        }
        node_set.insert(head);
        head = head->next;
    }
    return NULL;
}

//Solution 2 快慢指针赛跑
ListNode * Solution::detectCycle2(ListNode *head) {
    ListNode *fast = head;
    ListNode *slow = head;
    ListNode *meet = NULL;
    while (fast) {
        slow = slow->next;
        fast = fast->next;
        if (!fast) {
            return NULL;
        }
        fast = fast->next;
        if (fast == slow) {
            meet = fast;
            break;
        }
    }
    if (meet == NULL) {
        return NULL;
    }
    while (head && meet) {
        if (head == meet) {
            return head;
        }
        head = head->next;
        meet = meet->next;
    }
    return NULL;
}
//test detectCycle
void testDetectCycle() {
    ListNode a(1), b(2), c(3), d(4), e(5), f(6), g(7);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = &f;
    f.next = &g;
    g.next = &c;
    Solution solve;
    ListNode *result_1 = solve.detectCycle1(&a);
    ListNode *result_2 = solve.detectCycle2(&a);
    if (result_1 && result_2) {
        printf("result_1_val = %d, result_2_val = %d \n", result_1->val, result_2->val);
    } else {
        printf("NULL \n");
    }
}
