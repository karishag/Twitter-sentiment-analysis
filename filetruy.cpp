#include <iostream>
#include <windows.h>
#include <string.h>
#include <mysql.h>
#include <fstream>
using namespace std;
int main()
{
    fstream file;
    string word, t, q, filename,filename1;

    // filename of the file
    filename = "dictionary.txt";

    // opening file
    file.open(filename.c_str());
    int tmp, p;
    float v;
    // extracting words form the file
    fstream file1;
        file1.open ("example.txt", ios::out | ios::in );

    while (file >> word)
    {
        // displaying content
            cout<<word<<"  ";
            file1<<word<<" ";
            if(file >> p)
            {
                cout<<p<<endl;
                fstream file3;
                filename1="sentiment_labels.txt";
                file3.open(filename1.c_str());
                while(file3 >> tmp)
                {
                    //cout<<tmp<<endl;
                    if(tmp == p)
                    {
                        //cout<<"Hello"<<endl;
                        if(file3 >> v)
                        {
                            cout<<tmp<<"   "<<v<<endl;
                            file1<<v<<endl;;
                            file3 >> v;
                            break;
                            //cout<<v<<endl;
                        }
                    }
                    file3 >> v;
                    //file3 >> tmp;
                }
                //file >> word;
            }
            //cout<<word<<endl;
            //file >> word;
        }

    return 0;
}
