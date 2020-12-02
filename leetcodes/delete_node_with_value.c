/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* removeElements(struct ListNode* head, int val){
    if (head==NULL)
        return head;
    
    struct ListNode *curr=NULL;
    struct ListNode *prev=NULL;
    bool flag=false;
    
    while (head->val==val)
    {
        head=head->next;
        if (head==NULL)
            return head;
    }
       
    prev=head;
    curr=head->next;
    
    while (curr!=NULL && flag==false)
    {
        if (curr->val==val)
        {
            if (curr->next!=NULL)
            {
                do
                {
                    curr=curr->next;
                }while (curr->val==val && curr->next!=NULL);
                prev->next=curr;
            }
            else
            {
                prev->next=NULL;
                flag=true;
            }
        }
        else
        {
            prev=curr;
            curr=curr->next;
        }
    }
    return head;
}
