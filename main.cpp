#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>

using namespace std;
map<char,int> ops;


vector<string> postFijo(string ecuacion)
{
    stack<char> stk;
    vector <string> ecuacion_postfijo;
    string num;
    for(auto i : ecuacion)
    {
        if(isdigit(i)||(i >= 'a' && i<='z')||(i>='A' && i<='Z'))
        {
            if(isdigit(i))
                num+=i;
            else
                ecuacion_postfijo.push_back(string(1,i));
        } else
        {
            if(!num.empty())
            {
                ecuacion_postfijo.push_back(num);
                num.clear();
            }
            if(i=='(')
            {
                stk.push(i);
            } else
            {
                if(i==')')
                {
                    while(stk.top()!='(')
                    {
                        ecuacion_postfijo.push_back(string(1, stk.top()));
                        stk.pop();
                    }
                    stk.pop();
                }
                else
                    {
                    if(!stk.empty())
                    {
                        if(ops[stk.top()]==ops[i])
                        {
                            ecuacion_postfijo.push_back(string(1,stk.top()));
                            stk.pop();
                            stk.push(i);
                        }
                        else if (ops[stk.top()] < ops[i])
                        {
                            stk.push(i);
                        }
                        else if (ops[stk.top()] > ops[i])
                        {
                            while(!stk.empty() && stk.top()!='(')
                            {
                                ecuacion_postfijo.push_back(string(1,stk.top()));
                                stk.pop();
                            }
                            stk.push(i);
                        }
                    } else
                    {
                        stk.push(i);
                    }
                }
            }
        }
    }
    if(!num.empty()){
        ecuacion_postfijo.push_back(num);
        num.clear();
    }
    while(!stk.empty()){
        if(stk.top()!='('&&stk.top()!=')') {
            ecuacion_postfijo.push_back(string (1,stk.top()));
        }
        stk.pop();
    }
    return ecuacion_postfijo;
}

float operate(vector<string> pf)
{
    vector<string>variables;
    map<string,int> valores;
    stack<float> stk;
    float aux;
    for(auto i:pf) {
        if(i=="+"){
            aux=stk.top();
            stk.pop();
            stk.top()+=aux;
        }
        else if(i=="-"){
            aux=stk.top();
            stk.pop();
            stk.top()-=aux;
        }
        else if(i=="*"){
            aux=stk.top();
            stk.pop();
            stk.top()*=aux;
        }
        else if(i=="/"){
            aux=stk.top();
            stk.pop();
            stk.top()/=aux;
        }
        else if(i=="^"){
            aux=stk.top();
            stk.pop();
            stk.top()=pow(stk.top(),aux);
        }
        else if((i >= "a" && i <= "z" ) || (i >= "A" && i <= "Z" )){
            if ( find(variables.begin(), variables.end(), i) == variables.end() )
            {
                int valor;
                cout<<"Inserte el valor de "<<i<<endl;
                cin>>valor;
                valores[i]=valor;
                variables.push_back(i);
            }
            stk.push(valores[i]);

        }
        else{
            stk.push(stof(i));
        }
    }
    return stk.top();
}

int main() {
    ops['+']=1;
    ops['-']=1;
    ops['*']=2;
    ops['/']=2;
    ops['^']=3;
    string ecuacion;
    cin>>ecuacion;
    cout<<operate(postFijo(ecuacion));


}