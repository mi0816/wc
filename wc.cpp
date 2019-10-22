//#include"stdafx.h"
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class WC
{
private:
	string filename;             //�ļ���
	vector <string> text;    //ȫ�Ĵ洢��
	vector <string> order; //������
	int ordern;                     //������ 
	long charn;                   //�ַ���
	int linen;                      //����
	int wordn;                    //������
	int Sentn;                   //������
 	int Elinen;                  //������
	int Dlinen;                  //ע������
public:
	bool Init(vector<string>& messagelist);  //wc��ʼ������ �����Ƿ��ʼ���ɹ�
	void Basecount();                                    //wcͳ�Ʋ���
	void Output();                                          //wc�������
};
//---------------------------------wc��ʼ������-----------------------------------
bool WC::Init(vector<string>& messagelist)//nΪmessagelist�ĳ�Ա��
{
	//---------------��������------------------
	if (messagelist[0] != "wc.exe")
	{
		cout << "Please enter wc.exe first if you want to use the Word_Count." << endl;
		return false;//��ʼ��ʧ��
	}
	//------------------------------------------------
	int n = messagelist.size();
	this->filename = messagelist[n - 1];//��ʼ���ļ���
	for (int i = 1 ; i < n - 1; i++)
		this->order.push_back( messagelist[i]) ;    //��ʼ��������
	ordern = order.size();                                         //��ʼ��������
	//--------------��ʼ������--------------------
	charn = 0;
	wordn = 0;
	linen = 0;
	Sentn = 0;
	Elinen = 0;
	Dlinen = 0;
	//--------------���ļ�-----------------------
	ifstream infile(filename, ios::ate);
	if (!infile)
	{
		cerr << "Open error! Please check the filename." << endl;
		return false;//��ʼ��ʧ��
	}
	//--------------------------------------------------
	charn = infile.tellg();     //�ļ��ַ���ͳ��
	//-------------------��¼ȫ��-------------------
	infile.seekg(0);   //�Ѷ�ָ�붨���ļ���ͷ
	string line; 
	while (getline(infile, line))
	{
		text.push_back(line);
		linen++;//ͬʱ���������ͳ��
		if (line.length() == 0) Elinen++;//����ͳ��
	}
	//-------------------�ر��ļ�--------------------
	infile.close();
	return true;//��ʼ���ɹ�
	//--------------------------------------------------
}
//----------------------------------wcͳ�Ʋ���--------------------------------------
void WC::Basecount()
{
	
	string line;  
	for (int l = 0; l < linen; l++)
	{
		line = text[l];
		unsigned int e = 0;                   //��ָ�뵱ǰλ��
		unsigned int b = 0;                  //��ָ���ϴ�λ��
		for (e = 0, b=0; e < line.length(); e++)
		{
			//----------------����ͳ��-------------------
			if ((line[e] == ' ' || line[e] == '.' || line[e] == '!' || line[e] == '?') && line[b] != ' ')
			{
				wordn++;
			}
			//----------------����ͳ��--------------------
			if (line[e] == '.' || line[e] == '!' || line[e] == '?')
			{
				Sentn++;
			}
			//---------------ע����ͳ��-------------------
			if ((line[e] == '/' )&& (line[e+1] == '/' || line[e+1] == '*'))
			{
				Dlinen++;
			}
			//-------------------����չ----------------------
			//--------------------------------------------------
			b = e;//��¼�ôζ�ָ��
		}
	}
}
//-----------------------------wc�������----------------------------------------
void WC::Output()
{
	for (int i = 0; i < ordern; i++)
	{
		//----------------����ַ���-----------------
		if (order[i] == "-c" || order[i] == "-C")
			cout << "Character number : " << charn << endl;
		//----------------�������--------------------
		else if (order[i] == "-w" || order[i] == "-W")
			cout << "Word number : " << wordn << endl;
		//----------------�������-------------------
		else if (order[i] == "-l" || order[i] == "-L")
			cout << "Line number : " << linen << endl;
		//-----------------���������-------------------
		else if (order[i] == "-s" || order[i] == "-S")
			cout << "Sentence number : " << Sentn << endl;
		//-----------------���������-------------------------
		else if (order[i] == "-e" || order[i] == "-E")
			cout << "Empty line number : " << Elinen << endl;
		//----------------���ע������-----------------------
		else if (order[i] == "-d" || order[i] == "-D")
			cout << "Definition line number : " << Dlinen << endl;
		//----------------------����չ------------------------

		//-----------------δ���������֪-------------
		else
			cout << order[i] << " is not defined in this program." << endl;

	}
}
//----------------------------------------------------------------------------------
void Splitmessage(vector<string>&,string);//����ָ� 

int main()
{
	cout << "WORD COUNTER v1.3"<< endl;   //����
	vector <string> orderlist;
	string message="Begin";
	while (1)                          
	{
		WC file;             //����WC��ʵ��
		orderlist.clear();//����������
		getline(cin, message);
		if (message.length() == 0) continue;                            //�ų�������
		if (message == "exit" || message == "quit") break;    // ����exit��quit�˳�����
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
	int b=0;                   //�����
	int e=0;                   //��ʼ�ַ�
	int lenth = message.length();
	for (e = 0; e< lenth; e++)
	{
		if (message[e] != ' ')                    //����stringѰ������
		{
			while (message[e+b] != ' ')
			{
				b++;
				if (e+b>= lenth) break;
			}
			string x;
			x.assign(message, e, b);
			orderlist.push_back(x);
			e = e + b;                                   //��ʼ�ַ�������¼������
			b =0;								          //���������
		}	
	}
}