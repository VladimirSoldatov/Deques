#include<iostream>
#include<string>
#include<regex>
#include"windows.h"
#include<fstream>
#include<filesystem>

using namespace std;
namespace fs = filesystem;
//? ?????? ???? ?????? ????????? ????? ?? a ?? e, ????? 0 ?? 4?
bool is_valid_email_id(string str)
{
	regex r(R"(\w+@\w+\.(?:com|ru))");
	return regex_match(str.data(), r);
	
}
bool is_ae(string str)
{
	regex r("[a-e0-4]+");
	return regex_match(str.data(), r);

}
string trim(string text) {
	regex r(R"(\s+)");
	return regex_replace(text.data(), r, "");
}
string NoToAny(string text) {
	regex r(R"([n][o])");
	return regex_replace(text.data(), r, "any");
}
void anonimus(string &text) 
{
	regex r(R"([?-ߨ][a-z?-??]+\s[A-Z?-ߨ]\.[A-Z?-ߨ]\.)");
	text = regex_replace(text.data(), r, "?.?.?.");
}
void DeAnonimus(string& text, string name)
{
	regex a("[?-ߨ?-??]+(?:???|???|???|???)\\s[?-?]\\.[?-?]\\.");
	regex vn("[?-ߨ?-??]+(?:??|??|??|??)\\s[?-?]\\.[?-?]\\.");
	regex ss("[?-ߨ?-??]+[?]\\s[?-?]\\.[?-?]\\.");
	regex x("[?-ߨ?-??]+[?]\\s[?-?]\\.[?-?]\\.");
	string old_name = name;
	if (regex_match(name.c_str(), a))
		name = name.replace(name.length() - 6, 1, "??");
	else if (regex_match(name.c_str(), vn))
		name = name.replace(name.length() - 5,1, "? ");
	else if (regex_match(name.c_str(), ss))
		name = name.replace(name.length() - 6, 1, "?");
	else if (regex_match(name.c_str(), x))
		name = name.replace(name.length() - 6, 1, "?");
	
	regex r(R"(\{(FIOrp)\})");
	text = regex_replace(text.data(), r, name);
	regex r_old(R"(\{(FIO)\})");
	text = regex_replace(text.data(), r_old, old_name);
}
bool isBirth(string str)
{
	regex r("[0-3][0-9]\\.[0-1][0-9]\\.[0-2][0-9][0-9][0-9]");
	return regex_match(str.data(), r);
}
bool isLabel(string str)
{
	regex r("[B-Z][a-z]{3,7}[0-9]{1,4}");
	return regex_match(str.c_str(), r);
}
bool isBig(string text)
{
	regex r("[A-Z][a-z]+[0-9]{3}" );
	return regex_match(text.data(), r);
}
void set_date(string& date, string _date, string user_date)
{

	int position;
	position = date.find(_date);
	if(!user_date.empty())
	date.replace(position, _date.length(), user_date.c_str());
}
void read_temlate(vector<string> &nouns, string &shapka, string path)
{
	fstream file;
	string buff;
	
	file.open(path);
	while (!file.eof())
	{
		getline(file, buff);
		if (buff == "" || buff.at(0) == '$')
			continue;
		if (buff.at(0)=='{')
			nouns.push_back(buff);
		else
		{
			shapka.append(buff);
			shapka.append("\r\n");
		}
	}

}
void get_name_of_template()
{
	fs::path current_path = fs::current_path();
	vector<string> paths;
	for (auto item : fs::directory_iterator(current_path))
	{
		if (item.is_regular_file() && item.path().extension().string() == ".txt")
			paths.push_back(item.path().string());
	}
	string template_name;
	fstream get_name(paths[0].c_str());
	getline(get_name, template_name);
	if (template_name.at(0) == '$')
		template_name = template_name.substr(1, template_name.length() - 1);
	else
		cout << "?? ?????? ??????\n";
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string stroka = "any good any more";
	cout << stroka << endl;
	int position = stroka.find("any");
	while (position > -1)
	{
		
		cout <<"any ??????????? ? ??????? ? " << position << endl;
		stroka.replace(position, strlen("any"), "no");
		position = stroka.find("any");
		cout << stroka << endl;
	}
	stroka = NoToAny(stroka);
	cout << stroka << endl;
	string FIO = "???????? ?.?. ????? ?? ????? ? ??????...\n";
	anonimus(FIO);
	cout << FIO;

	/*
	string otstup = "\t\t\t\t\t\t\t";
	string otstup2 = "\t\t\t\t";
	string shapka = otstup + string("????????? ??? \"???? ? ??????\"\n")
		+ otstup + string("??????? ?.?.\n")
		+ otstup + string("?? {FIOrp}\n")
		+ otstup2 + string("?????????\n\n")
		+ string("????? ???????????? ??? ?????? ? {begin_date} ?? {end_date}.\n\n")
		+ string("{cur_date}") + string(otstup) + string{ "{FIO}\n" };
	*/
	get_name_of_template();
	string shapka;
	vector<string> nouns;
	string path = "template_holiday.txt";
	read_temlate(nouns, shapka,path );
	cout << shapka;
	/*fstream infile;
	infile.open("template_holiday.txt",ios::app);
	if (infile.is_open())
		cout << "???? ??????\n";
	infile.write(shapka.c_str(), shapka.length());
	infile.close();*/
	string name;
	string date;
	cout << "??????? ???: ";
	getline(cin,name);
	DeAnonimus(shapka, name);
	cout << "??????? ???? ?????? ??????? ";
	getline(cin, date);
	set_date(shapka, "{begin_date}", date);
	cout << "??????? ???? ????????? ??????? ";
	getline(cin, date);
	set_date(shapka, "{end_date}", date);
	cout << "??????? ??????? ???? (???? ?????????)";
	getline(cin, date);
	set_date(shapka, "{cur_date}", date);
	cout << shapka;

	/*string note = "  sakd kdsksa ds    s\n";
	string plus = trim(note);
	cout << plus;
	*/
	/*deque<int>simple{1,2,3,4,5};
	int q[7];
	int start = 0, ends = 0;
	cout << "User, please enter 7 numbers\n";
	for (int h = 0; h < 7; h++)
	{
		int a;
		cin >> a;
		q[ends++] = a;
	}
	cout << "First element in a deque  ";
	start++;
	cout << q[start]<<"\n";
	cout << "Last element in deque "<<q[ends-1]<<"\n";
	if (start != ends)
		cout << "Deque is full\n";

	if (isLabel("Bok123"))
		cout << "OK\n";
	else
		cout << "No Good\n";
	*/

	const auto input_f = "please split,this,csv, ,line,\\,\n"s;
	const regex re{ "((?:[^\\\\,]|\\\\.)+)(?:,|$)" };
	const vector<string> m_vecFields{ sregex_token_iterator(cbegin(input_f), cend(input_f), re, 1), sregex_token_iterator() };

	cout << input_f << endl;

	copy(cbegin(m_vecFields), cend(m_vecFields), ostream_iterator<string>(cout, "\n"));

	const string input = "ABC:1->   PQR:2;;;   XYZ:3<<<";
	const regex r(R"((\w+):(\d))");
	// Note: vector<string> here, unlike vector<smatch> as in std::regex_iterator
	const vector<string> full_match{
		sregex_token_iterator{input.begin(), input.end(), r, 0}, // Mark `0` here i.e. whole regex match
		sregex_token_iterator{}
	};
	

	const vector<string> cptr_grp_1st{
		sregex_token_iterator{input.begin(), input.end(), r, 1}, // Mark `1` here i.e. 1st capture group
		sregex_token_iterator{}
	};
	

	const vector<string> cptr_grp_2nd{
		sregex_token_iterator{input.begin(), input.end(), r, 2}, // Mark `2` here i.e. 2nd capture group
		sregex_token_iterator{}
	};
	

	return 0;
}
