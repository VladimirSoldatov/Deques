#include<iostream>
#include<string>
#include<regex>
#include"windows.h"

using namespace std;
//в строке были только латинские буквы от a до e, цифры 0 до 4ж
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
	regex r(R"([А-ЯЁ][a-zа-яё]+\s[A-ZА-ЯЁ]\.[A-ZА-ЯЁ]\.)");
	text = regex_replace(text.data(), r, "Ф.И.О.");
}
void DeAnonimus(string& text, string name)
{
	regex a("[А-ЯЁа-яё]+(?:ова|ина|ева|ына)\\s[А-Я]\\.[А-Я]\\.");
	regex vn("[А-ЯЁа-яё]+(?:ов|ин|ев|ын)\\s[А-Я]\\.[А-Я]\\.");
	regex ss("[А-ЯЁа-яё]+[ь]\\s[А-Я]\\.[А-Я]\\.");
	regex x("[А-ЯЁа-яё]+[а]\\s[А-Я]\\.[А-Я]\\.");
	string old_name = name;
	if (regex_match(name.c_str(), a))
		name = name.replace(name.length() - 6, 1, "ой");
	else if (regex_match(name.c_str(), vn))
		name = name.replace(name.length() - 5,1, "а ");
	else if (regex_match(name.c_str(), ss))
		name = name.replace(name.length() - 6, 1, "я");
	else if (regex_match(name.c_str(), x))
		name = name.replace(name.length() - 6, 1, "ы");
	
	regex r(R"([F][I][O][r][p])");
	text = regex_replace(text.data(), r, name);
	regex r_old(R"([F][I][O])");
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
	date.replace(position, _date.length(), user_date.c_str());
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
		
		cout <<"any встречается в позиции № " << position << endl;
		stroka.replace(position, strlen("any"), "no");
		position = stroka.find("any");
		cout << stroka << endl;
	}
	stroka = NoToAny(stroka);
	cout << stroka << endl;
	string FIO = "Солдатов В.В. вышел на улице и сказал...\n";
	anonimus(FIO);
	cout << FIO;
	string otstup = "\t\t\t\t\t\t\t";
	string otstup2 = "\t\t\t\t";
	string shapka = otstup + string("Директору ООО \"Рога и копыта\"\n")
		+ otstup + string("Иванову И.И.\n")
		+ otstup + string("от FIOrp\n")
		+ otstup2 + string("Заявление\n\n")
		+ string("Прошу предоставить мне отпуск с {begin_date} по {end_date}.\n\n")
		+ string("{cur_date}") + string(otstup) + string{ "FIO\n" };
	cout << shapka;
	string fio = "{F.I.O.}";
	string name;
	string date;
	cout << "Введите имя: ";
	getline(cin,name);
	DeAnonimus(shapka, name);
	//cout << fio << "\n";
	cout << "Введите дату начала отпуска ";
	getline(cin, date);
	set_date(shapka, "{begin_date}", date);
	cout << "Введите дату окончания отпуска ";
	getline(cin, date);
	set_date(shapka, "{end_date}", date);
	cout << "Введите текущую дату (дату заявления)";
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
	return 0;
}
