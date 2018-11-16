#include<iostream>
#include<stack>
#include<vector>

using namespace std;

//返回操作符优先级
int prior(char optr)
{
	if (optr == '+' || optr == '-')
	{
		return 1;
	}
	else if (optr == '*' || optr == '/')
	{
		return 2;
	}
	else
	{
		return -1;
	}
}

//计算后缀表达式
void calculate(char a[], int a_len)
{
	stack<float> opnd;
	float opnd_temp;
	for (int i = 0; i < a_len; i++)
	{
		int begin = i;
		int end = i;
		
		if (a[i] == '!')
		{
			continue;
		}
		//当第i+1位不为‘!’时，索引+1
		while (a[++end] != '!')
		{
			if (end >= a_len)
			{
				break;
			}
		}
		//cout << "end-begin:" << end-begin << endl;
		//如果第i位是数字且为一位数，直接入栈opnd
		if (a[i] > 47 && a[i] < 58 && (end - begin == 1))
		{
			char s[2];
			s[0] = a[i];
			opnd_temp = atof(s);
			opnd.push(opnd_temp);
			cout << "yaru1 " << opnd.top()<<endl;
		}
		//如果第i位是数字且长度不止一位（可能是多位数或小数），转换成float型后再入栈opnd
		else if (a[i] > 47 && a[i] < 58 && (end - begin > 1))
		{
			char s[20];
			memset(s, NULL, 20 * sizeof(s[0]));
			int forlen = end - begin;
			for (int i = 0; i < forlen; i++)
			{
				s[i] = a[begin];
				begin++;
			}
			float stemp = atof(s);
			opnd.push(stemp);
			cout << "yaru2 " << opnd.top() << endl;
		}
		//如果第i位是操作符，则将两个操作数退栈，先退的在右侧，后退的在左侧，进行运算后重新入栈
		else if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/')
		{
			float right = opnd.top();
			opnd.pop();
			float left = opnd.top();
			opnd.pop();

			switch (a[i])
			{
			case '+':
				opnd.push(left + right);
				break;
			case '-':
				opnd.push(left - right);
				break;
			case '*':
				opnd.push(left * right);
				break;
			case '/':
				opnd.push(left / right);
				break;
			default:
				opnd.push(0);
				break;
			}
		}
		//如果第i位是’#‘，则处理方法与多位数时相同
		else if (a[i] == '#')
		{
			char s[20];
			int forlen = end - begin;
			for (int i = 0; i < forlen-1; i++)
			{
				begin++;
				s[i] = a[begin];
			}
			float stemp = -1.0 * atof(s);
			opnd.push(stemp);
		}
		i = end;
	}
	cout << "结果为" << opnd.top() << endl;
	opnd.pop();
}

//判断中缀表达式是否合理
bool isValid(char input[], int len)
{
	stack<char> match;//括号匹配栈
	int pos = 0;//判断运算符位置是否合理的变量
	int cur;//记录搜索浮点数、多位数时的索引信息的变量

	for (int i = 0; i < len + 1; i++)
	{
		pos++;
		//判断第i位是否为不合理字符
		if (input[i] != '#' && input[i] != '.' && input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' &&
			input[i] != '(' && input[i] != ')' && !(input[i] > 47 && input[i] < 58))
		{
			cout << "输入中有不合理字符" << endl;
			return false;
		}
		//判断第i位是否为括号
		else if (input[i] == '(' || input[i] == ')')
		{
			//判断是否碰到左括号，如果是，压入match栈中
			if (input[i] == '(') 
			{
				match.push(input[i]);
				
				if ((input[i + 1] > 47 && input[i + 1] < 58) || input[i + 1] == '#' || input[i + 1] == '(')
				{
					pos--;
					continue;
				}
				else if (input[i + 1] == '.')
				{
					cout << "小数点位置不合理" << endl;
					return false;
				}
				else if(input[i+1]==')')
				{
					cout << "括号中无内容" << endl;
					return false;
				}
				else
				{
					cout << "操作符位置不合理" << endl;
					return false;
				}
			}
			//判断是否碰到右括号，如果是，检查栈顶是否为对应的左括号，若是则弹出左括号，否则打印错误信息
			else if (input[i] == ')')
			{
				if (match.empty())
				{
					cout << "括号不匹配" << endl;
					return false;
				}

				if (!(input[i - 1] > 47 && input[i - 1] < 58) && 
					input[i + 1] != '+'&& input[i + 1] != '-'&& input[i + 1] != '*'&& input[i + 1] != '/'&& input[i + 1] != ')')
				{
					cout << "符号错误" << endl;
					return false;
				}

				if (match.top() == '(')
				{
					match.pop();
					pos--;
					//i++;
					continue;
				}
				else
				{
					cout << "括号不匹配" << endl;
					return false;
				}
			}
			else
			{			
				pos--;
				continue;
			}
		}
		//判断第i位是否为单目负’#‘
		else if (input[i] == '#')
		{
			//如果’#‘在第一位，则继续
			if (i == 0)
			{
				if (!(input[1] > 47 && input[1] < 58))
				{
					cout << "#位置不合理" << endl;
					return false;
				}
				pos--;
				continue;
			}
			//如果’#‘左边不是括号或运算符，或者’#‘右边不是数字，则打印错误信息，否则继续
			else if (input[i - 1] != '+' && input[i - 1] != '-' && input[i - 1] != '*' && input[i] != '/' && input[i - 1] != '('
				|| !(input[i + 1] > 47 && input[i + 1] < 58))
			{
				cout << "#位置不合理" << endl;
				return false;
			}
			else
			{
				pos--;
				continue;
			}
		}
		//判断第i位是否为数字
		else if (input[i] > 47 && input[i] < 58)
		{
			int dotNum = 0; 
			//判断第i位是否为最后一位
 			if (i != len)
			{
				cur = i + 1;
				while (input[cur] != '+' && input[cur] != '-' && input[cur] != '*' && input[cur] != '/' && cur < len)
				{
					if (input[cur] == '.')
					{
						dotNum++;
						
						if ((input[cur - 1] > 47 && input[cur - 1] < 58) && (input[cur + 1] > 47 && input[cur + 1] < 58))
						{
							cur++;
							continue;
						}
						else
						{
							cout << "小数点位置不合理" << endl;
							return false;
						}
						cur++;
					}
					else if (input[cur] > 47 && input[cur] < 58)
					{
						cur++;
					}
					else
					{
						break;
					}
				}

				if (i != 0)
				{
					if (input[i] == '0' && input[i - 1] == '/' && 
						(input[i + 1] == '+' || input[i + 1] == '-'|| input[i + 1] == '*'|| input[i + 1] == '/' || input[i + 1] == ')'))
					{
						cout << "除0错误" << endl;
						return false;
					}
				}

				if (dotNum > 1)
				{
					cout << "小数点位置不合理" << endl;
					return false;
				}

				i = cur - 1;
			}
			else
			{
				if (input[i] == '0' && input[i - 1] == '/')
				{
					cout << "除0错误" << endl;
					return false;
				}
			}
		}
		//判断第i位是否为操作符
		else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
		{
			if (pos % 2 != 0)
			{
				cout << "操作符位置不合理" << endl; 
				return false;
			}
		}
		else if (input[i] == '.')
		{
			cout << "小数点位置不合理" << endl;
			return false;
		}
	}

	if (!match.empty())
	{
		cout << "括号不匹配" << endl;
		return false;
	}
	
	return true;
	
}

//将中缀表达式转换成后缀表达式
void tranverse()
{
	stack<char> optr;
	char suffix[100];
	int suffix_index = 0;
	memset(suffix, NULL, 100 * sizeof(suffix[0]));
	char input[100];
	memset(input, NULL, 100 * sizeof(input[0]));
	cout << "请输入要转换的表达式" << endl;
	cin >> input;
	getchar();
	int len = strlen(input) - 1;
	
	//判断输入的中缀表达式是否合理
	if (!isValid(input, len))
	{
		return;
	}
	else
	{
		for (int i = 0; i < len + 1; i++)
		{
			//如果第i位为运算符
			if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
			{
				//如果此时optr栈为空，直接压入，否则比较栈顶操作符，
				if (optr.empty())
				{
					optr.push(input[i]);
				}
				else 
				{
					int optr_now = prior(input[i]);
					int optr_stacktop = prior(optr.top());
					do
					{
						if (optr_stacktop < optr_now)
						{
							optr.push(input[i]);
							break;
						}
						else
						{
							suffix[suffix_index] = optr.top();
							suffix_index++;
							suffix[suffix_index] = '!';
							suffix_index++;
							cout << optr.top() << " ";
							optr.pop();
							if (!optr.empty())
							{
								optr_stacktop = prior(optr.top());
							}
							else
							{
								optr.push(input[i]);
								break;
							}
							
						}
					} while (!optr.empty());
				}
			}
			//如果第i位为单目负‘#’
			else if (input[i] == '#')
			{
				int cur = i;
				int cur_temp = i + 1;
				int float_pos = 0;
				char float_temp[20];
				float real_num;
				
				//如果第cur位不是运算符或括号，进入下一位
				while (input[cur] != '+' && input[cur] != '-' && input[cur] != '*' 
					&& input[cur] != '/' && input[cur] != ')' && cur <= len)
				{
					cur++;
				}

				//记录终点索引
				i = cur - 1;
				suffix[suffix_index] = '#';
				suffix_index++;
				for (int j = cur_temp; j < cur; j++)
				{
					float_temp[float_pos] = input[j];
					suffix[suffix_index] = input[j];
					suffix_index++;
					float_pos++;
				}
				suffix[suffix_index] = '!';
				suffix_index++;
				real_num = atof(float_temp) * -1.0;
				cout << real_num << " ";
			}
			//如果第i位为数字
			else if (input[i] > 47 && input[i] < 58)
			{
				int cur = i;
				//如果第i位为最后一位，直接打印并退出
				if (i == len)
				{
					suffix[suffix_index] = input[i];
					suffix_index++;
					suffix[suffix_index] = '!';
					suffix_index++;
					cout << input[i] << " ";
					break;
				}
				//如果不是最后一位的数字
				else
				{
					//当cur位不是运算符或括号时，直接打印
					while (input[cur] != '+' && input[cur] != '-' && input[cur] != '*' && input[cur] != '/' && input[cur] != ')')
					{
						suffix[suffix_index] = input[cur];
						suffix_index++;
						cout << input[cur];
						cur++;
						if (cur > len)
						{
							break;
						}
					}
					suffix[suffix_index] = '!';
					suffix_index++;
					i = cur - 1;
					cout << " ";
				}
			}
			//如果第i位为左括号
			else if (input[i] == '(')
			{
				optr.push(input[i]);
			}
			//如果第i位为右括号
			else if (input[i] == ')')
			{
				if (input[i] == ')')
				{
					while (optr.top() != '(')
					{
						suffix[suffix_index] = optr.top();
						suffix_index++;
						suffix[suffix_index] = '!';
						suffix_index++;
						cout << optr.top() << " ";
						optr.pop();
					}
					optr.pop();
				}
			}
		}
		while (!optr.empty())
		{
			suffix[suffix_index] = optr.top();
			suffix_index++;
			suffix[suffix_index] = '!';
			suffix_index++;
			cout << optr.top() << " ";
			optr.pop();	
		}
	}
	
	cout << endl;
	//cout << suffix << endl;
	calculate(suffix, suffix_index);
}

int main()
{
	char choice = 'a';

	cout << "Welcome to the calculator X." << endl;

	do {
		choice = 'a';
		cout << "What would you like to do?" << endl;
		cout << "\t1. calculate" << endl;
		cout << "\t0. exit" << endl;
		cout << "your choice ---" << endl;

		cin >> choice;
		int ch; 
		while ((ch = getchar()) != '\n' && ch != EOF);//清空缓存区

		switch (choice)
		{
		case '1':
			tranverse();
			fflush(stdin);
			break;
		default:
			system("CLS");
			fflush(stdin);
			break;
		}
	} while (choice != '0');
	system("pause");
	return 0;
}
