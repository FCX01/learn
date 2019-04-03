#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <cstdlib>

using namespace std;

int splitword(vector<string>  &words,int n)
{
    ifstream in;
    if(n==1)
      in.open("input1.txt");
    if(n==2)
      in.open("input2.txt");
    if(n==3)
      in.open("input3.txt");
    if(n==4)
      in.open("input4.txt");
    if(n==5)
      in.open("input5.txt");
    if(!in){
        cout << "打开文件出错！" <<endl;
        return -1;
    }
	string s;
	string temp;
    while(getline(in,s))
    {
		int i=0;
		int flag=0;///标志位
		while(s[i] != 0){
			if(isalpha(s[i])){ ///是否为字母
				if(s[i] >= 'A' && s[i] <= 'Z' )  ///大写字母转小写
                    s[i] -= -32;
				if(flag != 1 && flag != 2) 	{ ///未记录
					words.push_back(temp);
					temp = "";
				}
				temp += s[i];
				flag = 1;
			}
			else if(isdigit(s[i])){///是否为数字
				if(flag != 1 && flag != 2){
					words.push_back(temp);
					temp = "";
				}
				temp += s[i];
				flag = 2;
			}
			else if(s[i] == ' ' || s[i] == '\t'){///是否为空
				flag = 0;
			}
			else {
				if(flag != 3 || s[i] != '='){
					words.push_back(temp);
					temp = "";
				}
				temp += s[i];
				flag = 3;
			}
			i++;
		}
    }
	in.close();
	return 0;
}

int main()
{
	vector<string> reserved_word;
	reserved_word.push_back("begin");
	reserved_word.push_back("call");
	reserved_word.push_back("const");
	reserved_word.push_back("do");
	reserved_word.push_back("end");
	reserved_word.push_back("if");
	reserved_word.push_back("odd");
	reserved_word.push_back("procedure");
	reserved_word.push_back("read");
	reserved_word.push_back("then");
	reserved_word.push_back("var");
	reserved_word.push_back("while");
	reserved_word.push_back("write");

	vector<string> words;
	int choice;
	cout<<"请输入文件名:（1-5）"<<endl;
	cin>>choice;
	splitword(words,choice);

	vector<string> result_word;   ///提取标识符及出现次数
	vector<int> times;
	int n=0,i,j,k;
	for(i=0;i<words.size();i++){
		if(isalpha(words[i][0])){  ///如果words是字母串
			for(k=0;k<13;k++){///判断是否是保留字
				if( words[i] == reserved_word[k] ) 	break;
			}
			if(k==13){
				if(n==0){///判断是否已经记录过
					result_word.push_back(words[i]);
					times.push_back(1);
					n++;
				}
				else{
					for(j=n-1;j>=0;j--){ ///是否出现过
						if(words[i] == result_word[j]) {
							times[j] ++;
							break;
						}
					}
					if(j<0){ ///未出现过，加入记录
						result_word.push_back(words[i]);
						times.push_back(1);
						n++;
					}
				}
			}
		}
	}


	ofstream out;
	if(choice==1)
	   out.open("result1.txt");
    if(choice==2)
	   out.open("result2.txt");
    if(choice==3)
	   out.open("result3.txt");
    if(choice==4)
	   out.open("result4.txt");
    if(choice==5)
	   out.open("result5.txt");
	for(i=0;i<result_word.size();i++){
		out << "(" << result_word[i] << ": "<<times[i]<<")"<<endl;
	}
	out.close();
	cout << "结果已存入result"<<choice<<".txt"<<endl;
	return 0;
}
