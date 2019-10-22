//#include"stdafx.h"
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class WC
{
private:
	string filename;             //文件名
	vector <string> text;    //全文存储器
	vector <string> order; //命令流
	int ordern;                     //命令数 
	long charn;                   //字符数
	int linen;                      //行数
	int wordn;                    //单词数
	int Sentn;                   //句子数
 	int Elinen;                  //空行数
	int Dlinen;                  //注释行数
public:
	bool Init(vector<string>& messagelist);  //wc初始化操作 返回是否初始化成功
	void Basecount();                                    //wc统计操作
	void Output();                                          //wc输出操作
};
//---------------------------------wc初始化操作-----------------------------------
bool WC::Init(vector<string>& messagelist)//n为messagelist的成员数
{
	//---------------检查程序名------------------
	if (messagelist[0] != "wc.exe")
	{
		cout << "Please enter wc.exe first if you want to use the Word_Count." << endl;
		return false;//初始化失败
	}
	//------------------------------------------------
	int n = messagelist.size();
	this->filename = messagelist[n - 1];//初始化文件名
	for (int i = 1 ; i < n - 1; i++)
		this->order.push_back( messagelist[i]) ;    //初始化命令流
	ordern = order.size();                                         //初始化命令数
	//--------------初始化数据--------------------
	charn = 0;
	wordn = 0;
	linen = 0;
	Sentn = 0;
	Elinen = 0;
	Dlinen = 0;
	//--------------打开文件-----------------------
	ifstream infile(filename, ios::ate);
	if (!infile)
	{
		cerr << "Open error! Please check the filename." << endl;
		return false;//初始化失败
	}
	//--------------------------------------------------
	charn = infile.tellg();     //文件字符数统计
	//-------------------记录全文-------------------
	infile.seekg(0);   //把读指针定于文件开头
	string line; 
	while (getline(infile, line))
	{
		text.push_back(line);
		linen++;//同时完成总行数统计
		if (line.length() == 0) Elinen++;//空行统计
	}
	//-------------------关闭文件--------------------
	infile.close();
	return true;//初始化成功
	//--------------------------------------------------
}
//----------------------------------wc统计操作--------------------------------------
void WC::Basecount()
{
	
	string line;  
	for (int l = 0; l < linen; l++)
	{
		line = text[l];
		unsigned int e = 0;                   //读指针当前位置
		unsigned int b = 0;                  //读指针上次位置
		for (e = 0, b=0; e < line.length(); e++)
		{
			//----------------单词统计-------------------
			if ((line[e] == ' ' || line[e] == '.' || line[e] == '!' || line[e] == '?') && line[b] != ' ')
			{
				wordn++;
			}
			//----------------句子统计--------------------
			if (line[e] == '.' || line[e] == '!' || line[e] == '?')
			{
				Sentn++;
			}
			//---------------注释行统计-------------------
			if ((line[e] == '/' )&& (line[e+1] == '/' || line[e+1] == '*'))
			{
				Dlinen++;
			}
			//-------------------待扩展----------------------
			//--------------------------------------------------
			b = e;//记录该次读指针
		}
	}
}
//-----------------------------wc输出操作----------------------------------------
void WC::Output()
{
	for (int i = 0; i < ordern; i++)
	{
		//----------------输出字符数-----------------
		if (order[i] == "-c" || order[i] == "-C")
			cout << "Character number : " << charn << endl;
		//----------------输出字数--------------------
		else if (order[i] == "-w" || order[i] == "-W")
			cout << "Word number : " << wordn << endl;
		//----------------输出行数-------------------
		else if (order[i] == "-l" || order[i] == "-L")
			cout << "Line number : " << linen << endl;
		//-----------------输出句子数-------------------
		else if (order[i] == "-s" || order[i] == "-S")
			cout << "Sentence number : " << Sentn << endl;
		//-----------------输出空行数-------------------------
		else if (order[i] == "-e" || order[i] == "-E")
			cout << "Empty line number : " << Elinen << endl;
		//----------------输出注释行数-----------------------
		else if (order[i] == "-d" || order[i] == "-D")
			cout << "Definition line number : " << Dlinen << endl;
		//----------------------待扩展------------------------

		//-----------------未定义命令告知-------------
		else
			cout << order[i] << " is not defined in this program." << endl;

	}
}
//----------------------------------------------------------------------------------
void Splitmessage(vector<string>&,string);//命令分割 

int main()
{
	cout << "WORD COUNTER v1.3"<< endl;   //标题
	vector <string> orderlist;
	string message="Begin";
	while (1)                          
	{
		WC file;             //生成WC类实体
		orderlist.clear();//命令流清零
		getline(cin, message);
		if (message.length() == 0) continue;                            //排除空命令
		if (message == "exit" || message == "quit") break;    // 输入exit或quit退出程序
		Splitmessage(orderlist,message);
		if (!file.Init(orderlist))
			continue;
		file.Basecount();
		file.Output();
	}
    return 0;
}

void Splitmessage(vector <string>&orderlist, string message)
{
	int b=0;                   //命令长度
	int e=0;                   //开始字符
	int lenth = message.length();
	for (e = 0; e< lenth; e++)
	{
		if (message[e] != ' ')                    //遍历string寻找命令
		{
			while (message[e+b] != ' ')
			{
				b++;
				if (e+b>= lenth) break;
			}
			string x;
			x.assign(message, e, b);
			orderlist.push_back(x);
			e = e + b;                                   //开始字符跳过已录入命令
			b =0;								          //命令长度置零
		}	
	}
}