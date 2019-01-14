#include <bits/stdc++.h>
#include <windows.h>
#include <string.h>
#include <mysql.h>
#include <fstream>
using namespace std;

struct node
{
    string word;
    float pos;
    int neu;
    int neg;
};

void build(struct node tmp[],int n,struct node tree[]){

    for(int i = 0;i<n;i++){
        tree[n+i] = tmp[i];
        //memcpy(tree[n+i], tmp[i]);
    }
    for(int i = n-1;i>0;--i){
        tree[i].word= tree[i<<1].word + " " + std::string(tree[i<<1 | 1].word);

        if((tree[i<<1].pos == 0 || tree[i<<1|1].pos == 0))
        {
            tree[i].pos = tree[i<<1].pos?tree[i<<1].pos:tree[i<<1|1].pos;
        }
        else if((tree[i<<1].pos < 0.5 || tree[i<<1].pos > -0.5) && (tree[i<<1|1].pos< 0.5 || tree[i<<1|1].pos > -0.5))
        {
            tree[i].pos = (1*tree[i<<1].pos + 1*tree[i<<1 | 1].pos)/2;
        }
        else if((tree[i<<1].pos < 0.5 || tree[i<<1].pos > -0.5) && (tree[i<<1|1].pos>0.5 || tree[i<<1|1].pos < -0.5))
        {
            tree[i].pos = (1*tree[i<<1].pos + 2*tree[i<<1 | 1].pos)/3;
        }
        else if((tree[i<<1].pos > 0.5 || tree[i<<1].pos < -0.5) && (tree[i<<1|1].pos<0.5 || tree[i<<1|1].pos > -0.5))
        {
            tree[i].pos = (2*tree[i<<1].pos + 1*tree[i<<1 | 1].pos)/3;
        }
        else if((tree[i<<1].pos > 0.5 || tree[i<<1].pos < -0.5) && (tree[i<<1|1].pos> 0.5 || tree[i<<1|1].pos < -0.5))
        {
            tree[i].pos = (2*tree[i<<1].pos + 2*tree[i<<1 | 1].pos)/4;
        }
        //tree[i].neu = (tree[i<<1].neu + tree[i<<1 | 1].neu)/2;
        //tree[i].neg = (tree[i<<1].neg + tree[i<<1 | 1].neg)/2;

    }
}

void segment(struct node tmp[],int n)
{
    struct node tree[2*n];
    build(tmp,n,tree);
    cout<<tree[1].word<<endl;
    cout<<"Sentimental Value = ";
    cout<<tree[1].pos<<endl<<endl;
    //cout<<tree[1].neu<<endl;
    //cout<<tree[1].neg<<endl;
}
void normalMethod(struct node tmp[],int n){
    float mean = 0;
    for(int i=0;i<n;i++){
        mean = mean + tmp[i].pos;
    }
    float an = (float )mean/n;
    cout<<"Sentiment value is: "<<an<<endl;
}
void getTweet(string s,int q)
{
    int c=0, n=0;
    float p;
    struct node tmp[100];
    //s="So happy I am to see u";
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    cout<<s<<endl;
    for (int i=0; i<=s.length(); i++)
    {
        if (s[i]==' ' || i==s.length())
        {
        tmp[n].word = s.substr(i-c, c);
        //cout<<tmp[n].word<<endl;
        ifstream file;
        string word, t, q, filename;

    // filename of the file
        filename = "SentiWords_1.1.txt";

    // opening file
        file.open(filename.c_str(),ios::in);

    // extracting words form the file
        while (file >> word && !file.eof())
        {
        // displaying content
            if(strcmp(word.c_str(),tmp[n].word.c_str())==0)
            {
            //cout<<word<<endl;
                if(file >> p)
                   tmp[n].pos=p;
            //if(file >> p)
              //  tmp[n].neu=p;
            //if(file >> p)
                //tmp[n].neg=p;
                break;
            }
        }
        if(file.eof())
        {
            tmp[n].pos=0;
        }
        cout<<tmp[n].pos<<endl;
        c=0;
        n++;
        }
        else
        {
            c++;
        }
    }
    if(q == 2){
        segment(tmp,n);
    }
    else{
        normalMethod(tmp,n);
    }
}

int main()
{
    int q;
    cout<<"Press 1 for normal method and 2 for Effecient method!"<<endl;
    cin>>q;
    if(q==2){
        cout<<"Effecient method - Segment Tree"<<endl;
    }
    else if(q == 1){
        cout<<"Normal method"<<endl;
    }
    else{
        cout<<"Invalid Option"<<endl;
        exit(0);
    }
     MYSQL* conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
     conn = mysql_init(0);

     conn = mysql_real_connect(conn,"localhost","root","root","twitter",0,NULL,0);

     if(conn)
        cout<<"connection to mca databse successful "<<endl;
     else
        cout<<"connection problem: "<<mysql_error(conn)<<endl;
    int qstate = mysql_query(conn,"select * from tweets");
    if(!qstate)
        {
            res = mysql_store_result(conn);
            /*while(row=mysql_fetch_row(res))
            {
                getTweet(row[1], q);
            }*/
            //getTweet("zyrian",q);
            //getTweet("This is a very brilliant idea to go for a nightout",q);
            getTweet("Extremely sad and happy",q);
            //getTweet("He is a very good politician and an awakened personality of the nation",q);
        }
        else
        {
            cout<<"query error: "<<mysql_error(conn)<<endl;
        }
    return 0;
}
