/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *left;
 *     struct Node *right;
 *     struct Node *next;
 * };
 */
void DO(struct Node *curr)
{
    struct Node *head=curr;
    struct Node *copyhead=NULL;
    
    while (head->left  != NULL)
    {
        copyhead=head;
        while (head != NULL)
        {
            head->left->next=head->right;
            if (head->next != NULL)
                head->right->next=head->next->left;
            head=head->next;
        }
        head=copyhead->left;
    }
    
}

struct Node* connect(struct Node* root) {
    if (root == NULL)
        return root;
    DO(root);
    return root;
}
