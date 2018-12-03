
# coding: utf-8

# In[21]:


def anagram(s, t):
    s = s.replace(" ","")
    t = t.replace(" ","")
    
    s_len = len(s)
    t_len = len(t)
    if(s_len!= t_len):
        return False
    
    s_dict = {}
    for i in range(s_len):
        if(s[i] in s_dict.keys()):
            s_dict[s[i]]+=1
        else:
            s_dict[s[i]]=1
            
    t_dict = {}
    for i in range(t_len):
        if(t[i] in t_dict.keys()):
            t_dict[t[i]]+=1
        else:
            t_dict[t[i]]=1
            
    if(t_dict==s_dict):
        return True
    else:
        return False
            
    
    


# In[22]:


s = "public rel1ations"
t = "crap built on lies"

if(anagram(s, t)):
    print("is anagram")
else:
    print("not anagram")

