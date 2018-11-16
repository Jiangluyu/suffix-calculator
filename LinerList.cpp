#include<iostream>
#include<stack>
#include<vector>

using namespace std;

//���ز��������ȼ�
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

//�����׺���ʽ
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
		//����i+1λ��Ϊ��!��ʱ������+1
		while (a[++end] != '!')
		{
			if (end >= a_len)
			{
				break;
			}
		}
		//cout << "end-begin:" << end-begin << endl;
		//�����iλ��������Ϊһλ����ֱ����ջopnd
		if (a[i] > 47 && a[i] < 58 && (end - begin == 1))
		{
			char s[2];
			s[0] = a[i];
			opnd_temp = atof(s);
			opnd.push(opnd_temp);
			cout << "yaru1 " << opnd.top()<<endl;
		}
		//�����iλ�������ҳ��Ȳ�ֹһλ�������Ƕ�λ����С������ת����float�ͺ�����ջopnd
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
		//�����iλ�ǲ���������������������ջ�����˵����Ҳ࣬���˵�����࣬���������������ջ
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
		//�����iλ�ǡ�#�������������λ��ʱ��ͬ
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
	cout << "���Ϊ" << opnd.top() << endl;
	opnd.pop();
}

//�ж���׺���ʽ�Ƿ����
bool isValid(char input[], int len)
{
	stack<char> match;//����ƥ��ջ
	int pos = 0;//�ж������λ���Ƿ����ı���
	int cur;//��¼��������������λ��ʱ��������Ϣ�ı���

	for (int i = 0; i < len + 1; i++)
	{
		pos++;
		//�жϵ�iλ�Ƿ�Ϊ�������ַ�
		if (input[i] != '#' && input[i] != '.' && input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' &&
			input[i] != '(' && input[i] != ')' && !(input[i] > 47 && input[i] < 58))
		{
			cout << "�������в������ַ�" << endl;
			return false;
		}
		//�жϵ�iλ�Ƿ�Ϊ����
		else if (input[i] == '(' || input[i] == ')')
		{
			//�ж��Ƿ����������ţ�����ǣ�ѹ��matchջ��
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
					cout << "С����λ�ò�����" << endl;
					return false;
				}
				else if(input[i+1]==')')
				{
					cout << "������������" << endl;
					return false;
				}
				else
				{
					cout << "������λ�ò�����" << endl;
					return false;
				}
			}
			//�ж��Ƿ����������ţ�����ǣ����ջ���Ƿ�Ϊ��Ӧ�������ţ������򵯳������ţ������ӡ������Ϣ
			else if (input[i] == ')')
			{
				if (match.empty())
				{
					cout << "���Ų�ƥ��" << endl;
					return false;
				}

				if (!(input[i - 1] > 47 && input[i - 1] < 58) && 
					input[i + 1] != '+'&& input[i + 1] != '-'&& input[i + 1] != '*'&& input[i + 1] != '/'&& input[i + 1] != ')')
				{
					cout << "���Ŵ���" << endl;
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
					cout << "���Ų�ƥ��" << endl;
					return false;
				}
			}
			else
			{			
				pos--;
				continue;
			}
		}
		//�жϵ�iλ�Ƿ�Ϊ��Ŀ����#��
		else if (input[i] == '#')
		{
			//�����#���ڵ�һλ�������
			if (i == 0)
			{
				if (!(input[1] > 47 && input[1] < 58))
				{
					cout << "#λ�ò�����" << endl;
					return false;
				}
				pos--;
				continue;
			}
			//�����#����߲������Ż�����������ߡ�#���ұ߲������֣����ӡ������Ϣ���������
			else if (input[i - 1] != '+' && input[i - 1] != '-' && input[i - 1] != '*' && input[i] != '/' && input[i - 1] != '('
				|| !(input[i + 1] > 47 && input[i + 1] < 58))
			{
				cout << "#λ�ò�����" << endl;
				return false;
			}
			else
			{
				pos--;
				continue;
			}
		}
		//�жϵ�iλ�Ƿ�Ϊ����
		else if (input[i] > 47 && input[i] < 58)
		{
			int dotNum = 0; 
			//�жϵ�iλ�Ƿ�Ϊ���һλ
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
							cout << "С����λ�ò�����" << endl;
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
						cout << "��0����" << endl;
						return false;
					}
				}

				if (dotNum > 1)
				{
					cout << "С����λ�ò�����" << endl;
					return false;
				}

				i = cur - 1;
			}
			else
			{
				if (input[i] == '0' && input[i - 1] == '/')
				{
					cout << "��0����" << endl;
					return false;
				}
			}
		}
		//�жϵ�iλ�Ƿ�Ϊ������
		else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
		{
			if (pos % 2 != 0)
			{
				cout << "������λ�ò�����" << endl; 
				return false;
			}
		}
		else if (input[i] == '.')
		{
			cout << "С����λ�ò�����" << endl;
			return false;
		}
	}

	if (!match.empty())
	{
		cout << "���Ų�ƥ��" << endl;
		return false;
	}
	
	return true;
	
}

//����׺���ʽת���ɺ�׺���ʽ
void tranverse()
{
	stack<char> optr;
	char suffix[100];
	int suffix_index = 0;
	memset(suffix, NULL, 100 * sizeof(suffix[0]));
	char input[100];
	memset(input, NULL, 100 * sizeof(input[0]));
	cout << "������Ҫת���ı��ʽ" << endl;
	cin >> input;
	getchar();
	int len = strlen(input) - 1;
	
	//�ж��������׺���ʽ�Ƿ����
	if (!isValid(input, len))
	{
		return;
	}
	else
	{
		for (int i = 0; i < len + 1; i++)
		{
			//�����iλΪ�����
			if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
			{
				//�����ʱoptrջΪ�գ�ֱ��ѹ�룬����Ƚ�ջ����������
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
			//�����iλΪ��Ŀ����#��
			else if (input[i] == '#')
			{
				int cur = i;
				int cur_temp = i + 1;
				int float_pos = 0;
				char float_temp[20];
				float real_num;
				
				//�����curλ��������������ţ�������һλ
				while (input[cur] != '+' && input[cur] != '-' && input[cur] != '*' 
					&& input[cur] != '/' && input[cur] != ')' && cur <= len)
				{
					cur++;
				}

				//��¼�յ�����
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
			//�����iλΪ����
			else if (input[i] > 47 && input[i] < 58)
			{
				int cur = i;
				//�����iλΪ���һλ��ֱ�Ӵ�ӡ���˳�
				if (i == len)
				{
					suffix[suffix_index] = input[i];
					suffix_index++;
					suffix[suffix_index] = '!';
					suffix_index++;
					cout << input[i] << " ";
					break;
				}
				//����������һλ������
				else
				{
					//��curλ���������������ʱ��ֱ�Ӵ�ӡ
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
			//�����iλΪ������
			else if (input[i] == '(')
			{
				optr.push(input[i]);
			}
			//�����iλΪ������
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
		while ((ch = getchar()) != '\n' && ch != EOF);//��ջ�����

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
