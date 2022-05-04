#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define dip reduced_serch_space;
#define pb push_back;
// Node of a n_arry tree
class TrieNode
{
    public:
    //helps in determining is there any string ending at this position
    bool is_end;
    //if child[i]!=NULL implies there is at least one string consisting of i+'a' character at this position
    TrieNode* child[26];
    //constructor to initialize values
    TrieNode()
    {
        for(int i=0;i<26;i++) this->child[i]=NULL;
        is_end=false;
    }
};
class Trie{
    public:
     TrieNode *root;
     //constructor of Trie 
     Trie() {
       root=new TrieNode(); 
    }
    
    void insert(string word) {
     TrieNode* curr=root;
        for(char c:word)
        {
            if(curr->child[c-'a']==NULL)
                curr->child[c-'a']=new TrieNode();
            curr=curr->child[c-'a'];
        }
        curr->is_end=true;
        
    }
    void generate_all(TrieNode *curr_node,string &temp,vector<string>& all_strings)
    {
      
        for(int i=0;i<26;i++)
        {
           if(curr_node->child[i]!=NULL)
           {
               temp.push_back(i+'a');
               if(curr_node->child[i]->is_end==true) all_strings.push_back(temp);
               generate_all(curr_node->child[i],temp,all_strings);
               temp.pop_back();
           }
        }
    }
    vector<string> all_prefix_correct(string given_prefix,TrieNode *curr)
    {
    
        vector<string> all_strings;
        string temp=given_prefix;
        for(char c:given_prefix)
        {
            if(curr->child[c-'a']==NULL) return all_strings;
              curr=curr->child[c-'a'];       
        }
        if(curr->is_end==true) all_strings.push_back(given_prefix);
        generate_all(curr,temp,all_strings);
        return all_strings;
    }
    vector<vector<string>> first_character(string &input)
    {
        TrieNode* curr=root;
        vector<vector<string>> f_missing_all_strings;
        for(int i=0;i<26;i++)
        {
            vector<string> all_strings;
            if(i+'a'!=input[0] && curr->child[i]!=NULL)
            {
                string temp=input;
                temp[0]='a'+i;
                all_strings=all_prefix_correct(temp,root);
            }
            f_missing_all_strings.push_back(all_strings);
        }
       return f_missing_all_strings;
    }
    vector<vector<string>> second_character(string &input)
    {
        vector<vector<string>> s_missing_all_strings;
        TrieNode* curr=root;
     if(curr->child[input[0]-'a']==NULL) return s_missing_all_strings;
     else curr=curr->child[input[0]-'a'];
     for(int i=0;i<26;i++)
     {
         vector<string> all_strings;
            if(i+'a'!=input[1] && curr->child[i]!=NULL)
            {
                string temp=input;
                temp[1]=i+'a';
                all_strings=all_prefix_correct(temp,root);
            }
            s_missing_all_strings.push_back(all_strings);
     }
     return s_missing_all_strings;
    }
    vector<vector<string>> third_character(string& input)
    {
        vector<vector<string>> t_missing_all_strings;
        TrieNode* curr=root;
        
        for(int i=0;i<2;i++)
        {
            if(curr->child[input[i]-'a']==NULL) return t_missing_all_strings;
            else curr=curr->child[input[i]-'a'];
        }
         for(int i=0;i<26;i++)
        {
            vector<string> all_strings;
            if(i+'a'!=input[2] && curr->child[i]!=NULL)
            {
                string temp=input;
                temp[2]=i+'a';
                all_strings=all_prefix_correct(temp,root);
            }
            t_missing_all_strings.push_back(all_strings);
        }
     return t_missing_all_strings;
    }
    
};
int LCS(string &word1, string &word2) {
        int n=word1.size();
        int m=word2.size();
       vector<vector<int>> dp(n+1,vector<int> (m+1,0));
        for(int i=0;i<=n;i++)
        {
            for(int j=0;j<=m;j++)
            {
                if(i==0)
                    dp[i][j]=j;
                else if(j==0)
                    dp[i][j]=i;
               else if(word1[i-1]==word2[j-1])
                    dp[i][j]=dp[i-1][j-1];
                else
                    dp[i][j]=1+min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]));       
            }
        }
        return dp[n][m];
    }
int32_t main()
{
    //taking input from user
    cout<<"Start Typing........ "<<endl;
    string search_word;
    cin>>search_word;
    int n=search_word.size();
    int prefix_len=min(3LL,(n+1)/2LL);

    vector<string> reduced_serch_space;
    Trie*dic=new Trie();
    string xx;
    vector<string> reduced_serch;
    ifstream file("words.txt");
   while(getline(file,xx))
   {
       reduced_serch_space.push_back(xx);
    
   }
    
   
     //considering all prefix character are correct
     string prefix_string=search_word.substr(0,prefix_len);
     reduced_serch=dic->all_prefix_correct(prefix_string,dic->root);
     
     
     
     //consider first character is not correct
     vector<vector<string>> f_strings=dic->first_character(prefix_string);
     for(auto x:f_strings)
     {
         for(string y:x) 
         {
             reduced_serch.push_back(y);
             
         }
     }
     
     
     //consider second character is not correct
     vector<vector<string>> s_strings=dic->second_character(prefix_string);
     for(auto x:s_strings)
     {
         for(string y:x)
         {
             reduced_serch.push_back(y);
         }
     }
     
    //consider third character is not correct
    if(prefix_len>2)
    {
        vector<vector<string>> t_strings=dic->third_character(prefix_string);
        for(auto x:t_strings)
       {
         for(string y:x) 
         {
             reduced_serch.push_back(y);
         }
       }
        
    }
    vector<string>  related_words;
    int close=INT_MAX;
    for(string x:reduced_serch_space)
    {
        int len=LCS(search_word,x);
        if(len<close)
        {
            related_words.clear();
            close=len;
            related_words.push_back(x);
        }
       else if(close==len)
        {
            related_words.push_back(x);
        }
    }
    for(string ans:related_words)
    {
        cout<<ans<<endl;
    }

}