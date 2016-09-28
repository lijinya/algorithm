    //һ�������������  
    /*----------------------------------------------------------- 
    |   node           right 
    |   / /    ==>     / / 
    |   a  right     node  y 
    |       / /       / /     
    |       b  y     a   b    //���� 
    -----------------------------------------------------------*/  
    static rb_node_t* rb_rotate_left(rb_node_t* node, rb_node_t* root)  
    {  
        rb_node_t* right = node->right;    //ָ��ָ��ָ�� right<--node->right  
       
        if ((node->right = right->left))    
        {  
            right->left->parent = node;  //�ñ������ע��ͼ��node��Ϊb�ĸ�ĸ  
        }  
        right->left = node;   //node��Ϊright������  
       
        if ((right->parent = node->parent))  
        {  
            if (node == node->parent->right)  
            {  
                node->parent->right = right;  
            }  
            else  
            {  
                node->parent->left = right;  
            }  
        }  
        else  
        {  
            root = right;  
        }  
        node->parent = right;  //right��Ϊnode�ĸ�ĸ  
       
        return root;  
    }  
      
      
    //��������  
    /*----------------------------------------------------------- 
    |       node            left 
    |       / /             / / 
    |    left  y   ==>    a    node 
    |   / /                    / / 
    |  a   b                  b   y  //������������࣬�����Թ� 
    -----------------------------------------------------------*/  
    static rb_node_t* rb_rotate_right(rb_node_t* node, rb_node_t* root)  
    {  
        rb_node_t* left = node->left;  
       
        if ((node->left = left->right))  
        {  
            left->right->parent = node;  
        }  
        left->right = node;  
       
        if ((left->parent = node->parent))  
        {  
            if (node == node->parent->right)  
            {  
                node->parent->right = left;  
            }  
            else  
            {  
                node->parent->left = left;  
            }  
        }  
        else  
        {  
            root = left;  
        }  
        node->parent = left;  
       
        return root;  
    }  
      
      
    //������������ҽ��  
    //----------------------------------------------------  
    //rb_search_auxiliary������  
    //rb_node_t* rb_search�������ҵ��Ľ��  
    //----------------------------------------------------  
    static rb_node_t* rb_search_auxiliary(key_t key, rb_node_t* root, rb_node_t** save)  
    {  
        rb_node_t *node = root, *parent = NULL;  
        int ret;  
       
        while (node)  
        {  
            parent = node;  
            ret = node->key - key;  
            if (0 < ret)  
            {  
                node = node->left;  
            }  
            else if (0 > ret)  
            {  
                node = node->right;  
            }  
            else  
            {  
                return node;  
            }  
        }  
       
        if (save)  
        {  
            *save = parent;  
        }  
       
        return NULL;  
    }  
      
    //��������rb_search_auxiliary���ҽ��  
    rb_node_t* rb_search(key_t key, rb_node_t* root)  
    {  
        return rb_search_auxiliary(key, root, NULL);  
    }  
      
      
    //�ġ�������Ĳ���  
    //---------------------------------------------------------  
    //������Ĳ�����  
    rb_node_t* rb_insert(key_t key, data_t data, rb_node_t* root)  
    {  
        rb_node_t *parent = NULL, *node;  
       
        parent = NULL;  
        if ((node = rb_search_auxiliary(key, root, &parent)))  //����rb_search_auxiliary�ҵ������  
      
    ��ĵط�  
        {  
            return root;  
        }  
       
        node = rb_new_node(key, data);  //������  
        node->parent = parent;     
        node->left = node->right = NULL;  
        node->color = RED;  
       
        if (parent)  
        {  
            if (parent->key > key)  
            {  
                parent->left = node;  
            }  
            else  
            {  
                parent->right = node;  
            }  
        }  
        else  
        {  
            root = node;  
        }  
       
        return rb_insert_rebalance(node, root);   //������󣬵���rb_insert_rebalance�޸������  
      
    ������  
    }  
      
      
    //�塢�������3�ֲ������  
    //�������������ص������Ժ���������3������������е��޸�������  
    //--------------------------------------------------------------  
    //������޸������3�����  
    //Ϊ���������ע���б�ʾ���㣬ҲΪ���������������ҵĂzƪ�������Ӧ��  
    //��z��ʾ��ǰ��㣬p[z]��ʾ��ĸ��p[p[z]]��ʾ�游��y��ʾ���塣  
    //--------------------------------------------------------------  
    static rb_node_t* rb_insert_rebalance(rb_node_t *node, rb_node_t *root)  
    {  
        rb_node_t *parent, *gparent, *uncle, *tmp;  //��ĸp[z]���游p[p[z]]������y����ʱ���*tmp  
       
        while ((parent = node->parent) && parent->color == RED)  
        {     //parent Ϊnode�ĸ�ĸ���ҵ���ĸ����ɫΪ��ʱ  
            gparent = parent->parent;   //gparentΪ�游  
        
            if (parent == gparent->left)  //���游�����Ӽ�Ϊ��ĸʱ��  
                                     //��ʵ����������䣬�޷Ǿ�����˳���ӡ���ĸ���游�Ĺ�ϵ��:D��  
            {  
                uncle = gparent->right;  //��������ĸ������y���Ǹ�ĸ���Һ��ӡ�  
      
                if (uncle && uncle->color == RED) //���1��z������y�Ǻ�ɫ��  
                {  
                    uncle->color = BLACK;   //��������y��Ϊ��ɫ  
                    parent->color = BLACK;  //z�ĸ�ĸp[z]Ҳ��Ϊ��ɫ�����z��p[z]���Ǻ�ɫ�����⡣  
                    gparent->color = RED;    
                    node = gparent;     //���游�����������z��ָ��z�������㣬����Ϊ��ɫ��  
                //�������1�У�ֻ������z��Ϊ��ĸ���Һ��ӵ������  
                }  
                else                     //���2��z������y�Ǻ�ɫ�ģ�  
                {     
                    if (parent->right == node)  //��zΪ�Һ���  
                    {  
                        root = rb_rotate_left(parent, root); //����[���z���븸ĸ���]  
                        tmp = parent;  
                        parent = node;  
                        node = tmp;     //parent��node ������ɫ  
                    }  
                                 //���3��z������y�Ǻ�ɫ�ģ���ʱz��Ϊ�����ӡ�  
                                        //ע�⣬1�����3�����������2�仯�����ġ�  
                                        //......2��z���������Ǻ�ɫ�ģ�����������1�ˡ�  
                    parent->color = BLACK;   //z�ĸ�ĸp[z]��Ϊ��ɫ  
                    gparent->color = RED;    //ԭ�游�����Ϊ��ɫ  
                    root = rb_rotate_right(gparent, root); //����[���z�����游���]  
                }  
            }   
       
            else   
            {       
            // if (parent == gparent->right) ���游���Һ��Ӽ�Ϊ��ĸʱ���������뿴���������µ�23¥��ͬʱ����лSupremeHoverָ������  
                uncle = gparent->left;  //�游��������Ϊ�����㡣[ԭ���������ϲ���һ����]  
                if (uncle && uncle->color == RED)  //���1��z������y�Ǻ�ɫ��  
                {  
                    uncle->color = BLACK;  
                    parent->color = BLACK;  
                    gparent->color = RED;  
                    node = gparent;           //ͬ�ϡ�  
                }  
                else                               //���2��z������y�Ǻ�ɫ�ģ�  
                {  
                    if (parent->left == node)  //��zΪ����  
                    {  
                        root = rb_rotate_right(parent, root);  //�Խ��parent��root����  
                        tmp = parent;  
                        parent = node;  
                        node = tmp;       //parent��node ������ɫ  
                    }   
                      //�������2�ı仯����Ϊ�����3.  
                    parent->color = BLACK;  
                    gparent->color = RED;  
                    root = rb_rotate_left(gparent, root);   //�Խ��gparent��root����  
                }  
            }  
        }  
       
        root->color = BLACK; //����㣬����������������Ϊ��ɫ��  
        return root;      //���ظ���㡣  
    }  
      
      
    //�����������ɾ��  
    //------------------------------------------------------------  
    //�������ɾ�����  
    rb_node_t* rb_erase(key_t key, rb_node_t *root)  
    {  
        rb_node_t *child, *parent, *old, *left, *node;  
        color_t color;  
       
        if (!(node = rb_search_auxiliary(key, root, NULL)))  //����rb_search_auxiliary����Ҫɾ����  
      
    ���  
        {  
            printf("key %d is not exist!/n");  
            return root;  
        }  
       
        old = node;  
       
        if (node->left && node->right)  
        {  
            node = node->right;  
            while ((left = node->left) != NULL)  
            {  
                node = left;  
            }  
            child = node->right;  
            parent = node->parent;  
            color = node->color;  
        
            if (child)  
            {  
                child->parent = parent;  
            }  
            if (parent)  
            {  
                if (parent->left == node)  
                {  
                    parent->left = child;  
                }  
                else  
                {  
                    parent->right = child;  
                }  
            }  
            else  
            {  
                root = child;  
            }  
        
            if (node->parent == old)  
            {  
                parent = node;  
            }  
        
            node->parent = old->parent;  
            node->color = old->color;  
            node->right = old->right;  
            node->left = old->left;  
        
            if (old->parent)  
            {  
                if (old->parent->left == old)  
                {  
                    old->parent->left = node;  
                }  
                else  
                {  
                    old->parent->right = node;  
                }  
            }   
            else  
            {  
                root = node;  
            }  
        
            old->left->parent = node;  
            if (old->right)  
            {  
                old->right->parent = node;  
            }  
        }  
        else  
        {  
            if (!node->left)  
            {  
                child = node->right;  
            }  
            else if (!node->right)  
            {  
                child = node->left;  
            }  
            parent = node->parent;  
            color = node->color;  
        
            if (child)  
            {  
                child->parent = parent;  
            }  
            if (parent)  
            {  
                if (parent->left == node)  
                {  
                    parent->left = child;  
                }  
                else  
                {  
                    parent->right = child;  
                }  
            }  
            else  
            {  
                root = child;  
            }  
        }  
       
        free(old);  
       
        if (color == BLACK)  
        {  
            root = rb_erase_rebalance(child, parent, root); //����rb_erase_rebalance���ָ��������  
      
    ��  
        }  
       
        return root;  
    }  
      
      
    //�ߡ��������4��ɾ�����  
    //----------------------------------------------------------------  
    //������޸�ɾ����4�����  
    //Ϊ�˱�ʾ����ע�͵ķ��㣬ҲΪ���������������ҵĂzƪ�������Ӧ��  
    //x��ʾҪɾ���Ľ�㣬*other��w��ʾ�ֵܽ�㣬  
    //----------------------------------------------------------------  
    static rb_node_t* rb_erase_rebalance(rb_node_t *node, rb_node_t *parent, rb_node_t *root)  
    {  
        rb_node_t *other, *o_left, *o_right;   //x���ֵ�*other���ֵ�����*o_left,*o_right  
       
        while ((!node || node->color == BLACK) && node != root)   
        {  
            if (parent->left == node)  
            {  
                other = parent->right;  
                if (other->color == RED)   //���1��x���ֵ�w�Ǻ�ɫ��  
                {  
                    other->color = BLACK;    
                    parent->color = RED;   //�����У��ı���ɫ��w->�ڡ�p[x]->�졣  
                    root = rb_rotate_left(parent, root);  //�ٶ�p[x]��һ������  
                    other = parent->right;  //x�����ֵ�new w ����ת֮ǰw��ĳ�����ӡ���ʵ����������  
      
    ��Ч����  
                }  
                if ((!other->left || other->left->color == BLACK) &&  
                    (!other->right || other->right->color == BLACK))    
                              //���2��x���ֵ�w�Ǻ�ɫ����w����������Ҳ  
      
    ���Ǻ�ɫ��  
      
                {                         //����w��w���������Ӷ��Ǻ�ɫ�ģ�����x��w�ϵ�ȥ��һ��ɫ��  
                    other->color = RED;   //���ǣ��ֵ�w��Ϊ��ɫ��  
                    node = parent;    //p[x]Ϊ�½��x  
                    parent = node->parent;  //x<-p[x]  
                }  
                else                       //���3��x���ֵ�w�Ǻ�ɫ�ģ�  
                {                          //�ң�w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
                    if (!other->right || other->right->color == BLACK)  
                    {  
                        if ((o_left = other->left))   //w��������left[w]����ɫ������  
                        {  
                            o_left->color = BLACK;    //w�����ӱ�Ϊ�ɺ�->��ɫ  
                        }   
                        other->color = RED;           //w�ɺ�->��  
                        root = rb_rotate_right(other, root);  //�ٶ�w�����������Ӷ�������ʻָ���  
                        other = parent->right;        //�仯��ģ��������Һ��ӣ���Ϊ�µ��ֵܽ��  
      
    w��  
                    }  
                                //���4��x���ֵ�w�Ǻ�ɫ��  
          
                    other->color = parent->color;  //���ֵܽڵ�Ⱦ�ɵ�ǰ�ڵ㸸�ڵ����ɫ��  
                    parent->color = BLACK;  //�ѵ�ǰ�ڵ㸸�ڵ�Ⱦ�ɺ�ɫ  
                    if (other->right)      //��w���Һ����Ǻ�  
                    {  
                        other->right->color = BLACK;  //�ֵܽڵ�w�Һ���Ⱦ�ɺ�ɫ  
                    }  
                    root = rb_rotate_left(parent, root);  //������һ������  
                    node = root;   //����x��Ϊ����  
                    break;  
                }  
            }  
            //������������������ԭ��һ�¡������ԡ�  
            else  
            {  
                other = parent->left;  
                if (other->color == RED)  
                {  
                    other->color = BLACK;  
                    parent->color = RED;  
                    root = rb_rotate_right(parent, root);  
                    other = parent->left;  
                }  
                if ((!other->left || other->left->color == BLACK) &&  
                    (!other->right || other->right->color == BLACK))  
                {  
                    other->color = RED;  
                    node = parent;  
                    parent = node->parent;  
                }  
                else  
                {  
                    if (!other->left || other->left->color == BLACK)  
                    {  
                        if ((o_right = other->right))  
                        {  
                            o_right->color = BLACK;  
                        }  
                        other->color = RED;  
                        root = rb_rotate_left(other, root);  
                        other = parent->left;  
                    }  
                    other->color = parent->color;  
                    parent->color = BLACK;  
                    if (other->left)  
                    {  
                        other->left->color = BLACK;  
                    }  
                    root = rb_rotate_right(parent, root);  
                    node = root;  
                    break;  
                }  
            }  
        }  
       
        if (node)  
        {  
            node->color = BLACK;  //���node[����������Ϊ�˸����]����Ϊ��ɫ��  
        }    
        return root;  //����root  
    }  
      
      
    //�ˡ���������  
    //������  
    int main()  
    {  
        int i, count = 100;  
        key_t key;  
        rb_node_t* root = NULL, *node = NULL;  
          
        srand(time(NULL));  
        for (i = 1; i < count; ++i)  
        {  
            key = rand() % count;  
            if ((root = rb_insert(key, i, root)))  
            {  
                printf("[i = %d] insert key %d success!/n", i, key);  
            }  
            else  
            {  
                printf("[i = %d] insert key %d error!/n", i, key);  
                exit(-1);  
            }  
        
            if ((node = rb_search(key, root)))  
            {  
                printf("[i = %d] search key %d success!/n", i, key);  
            }  
            else  
            {  
                printf("[i = %d] search key %d error!/n", i, key);  
                exit(-1);  
            }  
            if (!(i % 10))  
            {  
                if ((root = rb_erase(key, root)))  
                {  
                    printf("[i = %d] erase key %d success/n", i, key);  
                }  
                else  
                {  
                    printf("[i = %d] erase key %d error/n", i, key);  
                }  
            }  
        }  
       
        return 0;  
    }  