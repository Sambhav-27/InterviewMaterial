/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

int carry =0;
int c=0;
class Solution {
public:
    
    ListNode* push_front(ListNode* h, int val) {
        ListNode* temp = new ListNode(val);
        temp->next = h;
        h = temp;
        return h;
    }

    ListNode* add(ListNode* h1, ListNode* h2, int l1, int l2) {
        if(!h1 && !h2) return NULL;
        if(h1) {
            h1 = h1->next;
            l1++;
        }
        if(h2) {
            h2 = h2->next;
            l2++;
        }
        
        ListNode* head = add(h1, h2, l1, l2);
        int tot = c;
        if(h1) {
            tot+= h1->val;
            cout<<h1->val<<" ";
        }
        if(h2) {
            tot+= h2->val;
            cout<<h2->val<<" ";
        }
        // cout<<tot<<" ";
        head = push_front(head, tot%10);
        c = tot/10; 
        return head;
    }
    
    ListNode* recur(ListNode *h1, ListNode* h2, int l1, int l2) {
        
        if(l1 ==0 && l2 ==0) return NULL;
        
        int n1=0,n2=0;
        if(l1>l2) {
            n1 = h1->val;
            h1= h1->next;
            l1--;
        }

        else if(l1 == l2) {
            n1 = h1->val;
            n2 = h2->val;
            h1 = h1->next; h2 = h2->next;
            l1--; l2--;
        }
        

        ListNode* head = recur(h1, h2, l1,l2);
        int sum = n1+n2+carry;
        head = push_front(head, sum%10);
        carry = sum/10;
        return head;
    }
    
    int len(ListNode* h1) {
        int s=0;
        ListNode* temp = h1;
        while(temp) {
            s++;
            temp = temp->next;
        }
        return s;
    }
    
    
    ListNode* addTwoNumbers(ListNode* h1, ListNode* h2) {
        // /pre = NULL;
        carry = 0;
        int l1 = len(h1);
        int l2 = len(h2);
        
        // l1 will always be larger
        if(l2 > l1) {
            swap(l1, l2);
            swap(h1, h2);
        }
        
        ListNode* ans = recur(h1, h2, l1, l2);
        if(carry !=0) {
            ans = push_front(ans, carry);
        }

        
        // check for less than 1 node

        
        return ans;
    }
};
