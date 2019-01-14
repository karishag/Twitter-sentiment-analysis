#include <iostream>
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
        tree[i].pos = (tree[i<<1].pos + tree[i<<1 | 1].pos)/2;
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
    int mean = 0;
    for(int i=0;i<n;i++){
        mean = mean + tmp[i].pos;
    }
    mean = mean/n;
    cout<<"Sentiment value is: "<<mean<<endl;
}
void getTweet(string s,int q)
{
    int c=0, n=0;
    float p;
    struct node tmp[100];
    //s="So happy I am to see u";
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
        if(file.eof())
        {
            break;
        }
            if(strcmp(word.c_str(),tmp[n].word.c_str())==0)
            {
            //cout<<word<<endl;
                if(file >> p)
                tmp[n].pos=p;
            //if(file >> p)
              //  tmp[n].neu=p;
            //if(file >> p)
                //tmp[n].neg=p;
            }
        }
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
            while(row=mysql_fetch_row(res))
            {
                getTweet(row[1], q);
            }
            //getTweet("I am sad");
        }
        else
        {
            cout<<"query error: "<<mysql_error(conn)<<endl;
        }
    return 0;
}
