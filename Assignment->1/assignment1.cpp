#include<bits/stdc++.h>
using namespace std;
int main(){
    ifstream input_file("test.c");
    ofstream output_file("output.txt");
    string str,temp="";
    bool flag = false,flag1 = false,flag2 = false;
    if(input_file.is_open()){
        cout<<"File sucessfully opened";
    while(getline(input_file,str))
    {
        flag = false;
        flag2 = false;
        if(temp[temp.length()-2]=='*' && temp[temp.length()-1]=='/')
        {
            flag1 = false;
        }
        temp = "";
        for(int i=0;i<str.length();i++)
        {
            if((str[i] == '/' && str[i+1]=='/'))
            {
                flag = true;
                break;
            }
            else if(str[i]=='/' && str[i+1]=='*')
            {
                flag1 = true;
                temp = str;
                 break;
            }
        
              else if(str[i]=='*' && str[i+1]=='/'){
                flag2 = true;
                flag1=false;
                break;
            }
            
           
        }
       if(flag || flag1 || flag2)
       {
        continue;
       }
      
        
       output_file<<str;
      
    }
    input_file.close();
    output_file.close();

    }
    else{
      cout<<"sorry file not opened";
   
}



    return 0;
}
