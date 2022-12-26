#include<iostream>
#include<deque>
#include<regex>

using namespace std;

bool is_valid_email_id(string str)
{
	static const regex r(R"(\w+@\w+\.(?:com|in))");
	return regex_match(str.data(), r);
}
string trim(string text) {
	static const auto r = regex(R"(\s+)");
	return regex_replace(text.data(), r, "");
}
int main()
{
	string note = "  sakd kdsksa ds    s";
	string plus = trim(note);
	cout << plus;
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
*/
	if (is_valid_email_id("cbb@rambler.com"))
		cout << "OK\n";
	else
		cout << "No Good\n";
	
	return 0;
}
