#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<string>
#include<cstdint>

using namespace std;

static int employees_num;
static int accounts_num;
static int employee_id = 0;				// 0 states employee not logged in
static int64_t mobile_array[100];
static int customer_id = 0;				// 0 states user not logged in

class employee
{
private:
	int id;
	int64_t mobile;
	string name;
	string password;
public:
	void create()
	{
		system("cls");
		cout << "Employee Registeration Portal" << endl;
		cout << "Fill in the information correctly." << endl << endl;
		cout << "Name: ";
		cin >> name;
		cout << endl << "Mobile Number: ";
		cin >> mobile;
		cout << endl << "Password: ";
		cin >> password;
		::employees_num++;
		id = employees_num;
		system("cls");
		cout << "Employee registered successfully" << endl << endl;
		cout << "Name: " << name << endl;
		cout << "ID: " << id << endl;
		cout << "Mobile Number: " << mobile << endl << endl;
		cout << "Password is not revealed due to security purposes." << endl;
		cout << "Be sure to keep your password safe!" << endl;
		cout << "Press any key and you will be logged in." << endl;
		_getch();
		system("cls");
	}
	string getPassword()
	{
		return password;
	}
	int getId()
	{
		return id;
	}
	string getName()
	{
		return name;
	}
	void changePassword()
	{
		string prevpass, newpass;
		system("cls");
		cout << "Change Employee Account Password" << endl << endl;
		cout << "Account ID: " << id << endl << endl;
		cout << "Previous Password: ";
		cin >> prevpass;
		cout << endl << "New Password: ";
		cin >> newpass;
		if (prevpass == password)
		{
			password = newpass;
			system("cls");
			cout << "Password changed successfully";
			_getch();
			system("cls");
		}
		else
		{
			system("cls");
			cout << "You entered incorrect current password!";
			_getch();
			system("cls");
		}
	}
};

employee emp[100];

class account
{
private:
	int accno;
	string name;
	int amount;
	int openedBy;
	int64_t mobile;
	string password;
	string state = "active";
	string logs[500];
	int log_num = 0;

public:
	void openAccount()
	{
		int64_t temp_mobile;
		string temp_name;
		cout << "Account Opening Section" << endl;
		cout << "Please fill the following details" << endl;
		cout << "Name: ";
		cin >> temp_name;
		cout << endl << "Mobile Number: ";
		cin >> temp_mobile;
		system("cls");
		if (openAccountProcess(temp_name, temp_mobile))
		{
			cout << "Account Opened Successfully!" << endl;
			cout << "Account Details" << endl;
			cout << "Account Number: " << accno << endl;
			cout << "Customer Name: " << name << endl;
			cout << "Mobile Number: " << mobile << endl << endl;
			cout << "Press any key to return to Employee Dashboard....";
			_getch();
		}
		else
		{
			cout << "Customer with mobile number " << temp_mobile << " already exists";
			cout << "Press 1 to go back to Open Account Section or else press any other key to return to Employee Dashboard....";
			int choice = _getch();
			system("cls");
			if (choice == 1)	
				openAccount();
		}
	}
	void depositMoney()
	{
		int amount_temp = 0;
		system("cls");
		cout << "Deposit Money Section" << endl << endl;
		cout << "Account Number: " << accno << endl;
		cout << "Customer Name" << name << endl << endl;
		cout << "Enter Amount to be deposited (Enter 0 to cancel): ";
		cin >> amount_temp;
		system("cls");
		if (addAmount(amount_temp))
		{
			log_num++;
			logs[log_num] = "Amount Added: " + to_string(amount_temp);
			cout << "Amount added successfully!" << endl;
			cout << "The updated balance is " << amount << endl << endl;
			cout << "Press any key to return to the Employee Dashboard.....";
			_getch();
			system("cls");
		}
		else
		{
			cout << "Error depositing amount. The account is dormant." << endl;
			cout << "Press any key to return to the Employee Dashboard.....";
			_getch();
			system("cls");
		}
	}
	void withdrawMoney()
	{
		int amount_temp = 0;
		system("cls");
		cout << "Withdraw Money Section" << endl << endl;
		cout << "Account Number: " << accno << endl;
		cout << "Customer Name" << name << endl << endl;
		cout << "Enter Amount to be withdrawn (Enter 0 to cancel): ";
		cin >> amount_temp;
		system("cls");
		int code = deductAmount(amount_temp);
		if (code == 1)
		{
			log_num++;
			logs[log_num] = "Amount Withdrawn: " + to_string(amount_temp);
			cout << "Amount withdrawn successfully!" << endl;
			cout << "The updated balance is " << amount << endl << endl;
			cout << "Press any key to return to the Employee Dashboard.....";
			_getch();
			system("cls");
		}
		else
		{
			if (code == 3)
			{
				cout << "Amount to bw withdrawn should not be more than amount in account";
			}
			else
			{
				cout << "Error withdrawing amount. The account is dormant." << endl;
			}
			cout << "Press any key to return to the Employee Dashboard.....";
			_getch();
			system("cls");
		}
	}
	int openAccountProcess(string customer_name, int64_t mobile_no)
	{
		int flag;
		for (int i = 0; i < 100; i++)
		{
			if (::mobile_array[i] == mobile_no)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0)
			return 0;
		else
		{
			accno = ::accounts_num + 1;
			::accounts_num++;
			mobile_array[accounts_num] = mobile_no;
			mobile = mobile_no;
			::mobile_array[accounts_num] = mobile_no;
			openedBy = ::employee_id;
			name = customer_name;
			amount = 500;
			password = to_string(accno) + name + "123";
			return 1;
		}
	}
	int addAmount(int temp)
	{
		if (state == "dormant")
			return 0;
		else
		{
			amount += temp;
			return 1;
		}
	}
	int deductAmount(int temp)
	{
		if (state == "dormant")
			return 0;
		else
		{
			if (temp > amount)
				return 3;
			else
			{
				amount -= temp;
				return 1;
			}
		}
	}
	void changeState()
	{
		if (getState() == "active")
			state = "dormant";
		else
			state = "active";
	}
	string getState()
	{
		return state;
	}
	string getPassword()
	{
		return password;
	}
	int getAmount()
	{
		return amount;
	}
	void writeLogs(string log)
	{
		log_num++;
		logs[log_num] = log;
	}
	string getName()
	{
		return name;
	}
	void changePassword()
	{
		string prevpass, newpass;
		system("cls");
		cout << "Change your Password" << endl << endl;
		cout << "Previous Password: ";
		cin >> prevpass;
		cout << endl << "Enter New Password: ";
		cin >> newpass;
		system("cls");
		if (prevpass == password)
		{
			password = newpass;
			cout << "Password of your account has been changed!";
			_getch();
			system("cls");
		}
		else
		{
			cout << "You entered incorrect current password.";
			_getch();
			system("cls");
		}
	}
	
	void printInfo()
	{
		cout << "Account Number: " << accno << endl;
		cout << "Customer Name: " << name << endl;
		cout << "Mobile Number: " << mobile << endl;
		cout << "Opened By: " << ::emp[openedBy].getName() << endl;
		cout << "Balance: " << amount << endl << endl;
		cout << "Customer Logs" << endl << endl;
		for (int i = 1; i <= log_num; i++)
		{
			cout << logs[i] << endl;
		}
	}
	int64_t getMobile()
	{
		return mobile;
	}
	int getId()
	{
		return accno;
	}
};


account acc[500];


class customer
{
private:
	int id;
public:
	customer()
	{
		id = ::customer_id;
	}
	void sendMoney()
	{
		int account_num;
		int send_amount;
		system("cls");
		id = ::customer_id;
		cout << "Send money to other account holders at the same bank" << endl;
		cout << "Maximum amount you can send at once is 10000" << endl << endl;
		cout << "Your Account Number: " << id << endl;
		cout << "Amount you have: " << ::acc[id].getAmount() << endl << endl;
		cout << "Enter the recepient\'s account number (enter 0 to abort): ";
		cin >> account_num;
		system("cls");
		if (account_num > ::accounts_num || account_num < 1)
		{
			cout << "Invalid account number entered, to try again, press t";
			if (_getch() == 'e')
				sendMoney();
		}
		else
		{
			cout << "Recipient Account Number: " << account_num << endl;
			cout << "Recipient Name: " << ::acc[account_num].getName() << endl << endl;
			cout << "Your Balance: " << ::acc[id].getAmount() << endl << endl;
			cout << "Enter the amount that is to be sent: ";
			cin >> send_amount;
			if (send_amount < 0 || send_amount > 10000)
			{
				cout << "Illegal Amount!";
				_getch();
				sendMoney();
			}
			else
			{
				::acc[id].deductAmount(send_amount);
				::acc[account_num].addAmount(send_amount);
				::acc[id].writeLogs(to_string(send_amount) + " sent to " + to_string(::acc[account_num].getId()) + " (" + ::acc[account_num].getName() + ")");
				::acc[account_num].writeLogs(to_string(send_amount) + " recieved from " + to_string(::acc[id].getId()) + " (" + ::acc[id].getName() + ")");
				system("cls");
				cout << "Amount successfully sent! Now your balance is " << ::acc[id].getAmount();
				_getch();
			}

		}

	}
};

class Authenticator
{
private:
	int id;
	string password;
public:
	int loginCustomer(int id_temp, string pass_temp)
	{
		if (id_temp > accounts_num || id_temp < 1)
		{
			return 0;
		}
		else
		{
			if (pass_temp == ::acc[id_temp].getPassword())
			{
				::customer_id = id_temp;
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	// login employee to do (DONE)
	int loginEmployee(int id_temp, string pass_temp)
	{
		if (id_temp > employees_num || id_temp < 1)
		{
			return 0;
		}
		else
		{
			if (pass_temp == ::emp[id_temp].getPassword())
			{
				::employee_id = id_temp;
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	int logout()
	{
		::employee_id = 0;
		::customer_id = 0;
		return 1;
	}
	int checkLoginCustomer()
	{
		if (::customer_id == 0)
			return 0;
		else
			return 1;
	}
	int checkLoginEmployee()
	{
		if (::employee_id == 0)
			return 0;
		else
			return 1;
	}
};

Authenticator emp_auth;
Authenticator cust_auth;

customer c;

void employee_panelCheckCustomer()
{
	int acc;
	system("cls");
	cout << "Customer Check Portal" << endl << endl;
	cout << "Enter account number to check: ";
	cin >> acc;
	system("cls");
	if (acc > ::accounts_num || acc < 1)
	{
		cout << "Account does not exists!";
		_getch();
		system("cls");
	}
	else
	{
		::acc[acc].printInfo();
		_getch();
	}
}

void employee_panelDepositMoney()
{
	int acc_no;
	system("cls");
	cout << "Deposit Section" << endl << endl;
	cout << "Enter account no: ";
	cin >> acc_no;
	if (acc_no > ::accounts_num || acc_no < 1)
	{
		cout << "Invalid Account Number!";
		_getch();
		system("cls");
	}
	else
	{
		::acc[acc_no].depositMoney();
		_getch();
		system("cls");
	}
}

void employee_panelWithdrawMoney()
{
	int acc_no;
	system("cls");
	cout << "Withdraw Section" << endl << endl;
	cout << "Enter account no: ";
	cin >> acc_no;
	if (acc_no > ::accounts_num || acc_no < 1)
	{
		cout << "Invalid Account Number!";
		_getch();
		system("cls");
	}
	else
	{
		::acc[acc_no].withdrawMoney();
		_getch();
		system("cls");
	}
}

void employee_panelChangePassword()
{
	::emp[::employee_id].changePassword();
	_getch();
	system("cls");
}

void employee_panelOpenCustomerAcc()
{
	::acc[::accounts_num + 1].openAccount();
	_getch();
	system("cls");
}

void employee_panelInvalidChoice()
{
	cout << endl << "Invalid Choice!";
	_getch();
}

// customer panel functions start here

void customer_panelStatement()
{
	system("cls");
	::acc[::customer_id].printInfo();
	_getch();
	system("cls");
}

void customer_panelSendMoney()
{
	::c.sendMoney();
	system("cls");
}

void customer_panelChangePassword()
{
	::acc[::customer_id].changePassword();
}

void customer_panelInvalidChoice()
{
	system("cls");
	cout << "Invalid Choice!";
	_getch();
	system("cls");
}

void employee_panel()
{
	int id_temp;
	string pass_temp;
	int choice;
	system("cls");
	if (::employee_id == 0)
	{
		cout << "EMPLOYEE LOGIN FORM" << endl << endl;
		cout << "ID: ";
		cin >> id_temp;
		cout << endl << "Password: ";
		cin >> pass_temp;
		int result = ::emp_auth.loginEmployee(id_temp, pass_temp);
		if (result)
			employee_panel();
		else
		{
			system("cls");
			cout << "Invalid Login Credentials!";
			_getch();
		}
	}
	else
	{
		while (1)
		{
			system("cls");
			cout << "Employee Panel" << endl << endl;
			cout << "Your ID: " << ::employee_id << endl;
			cout << "Your Name: " << ::emp[::employee_id].getName() << endl << endl;
			cout << "1. Check Customer Details" << endl;
			cout << "2. Deposit Money to Customer" << endl;
			cout << "3. Customer Withdraw Money" << endl;
			cout << "4. Change Password" << endl;
			cout << "5. Open Customer Account" << endl;
			cout << "6. Logout" << endl << endl;
			cout << "Your choice: ";
			cin >> choice;
			system("cls");
			switch (choice)
			{
			case 1:
				employee_panelCheckCustomer();
				break;
			case 2:
				employee_panelDepositMoney();
				break;
			case 3:
				employee_panelWithdrawMoney();
				break;
			case 4:
				employee_panelChangePassword();
				break;
			case 5:
				employee_panelOpenCustomerAcc();
				break;
			case 6:
				break;
			default:
				employee_panelInvalidChoice();
				break;
			}
			if(choice == 6)
			{
				::emp_auth.logout();
				break;
			}
		}
	}
}

void customer_panel()
{
	int id_temp;
	string pass_temp;
	int choice;
	if (::customer_id == 0)
	{
		system("cls");
		cout << "Customer Login" << endl << endl;
		cout << "Make sure you dont tell your passwords to anyone!" << endl << endl;
		cout << "Account Number: ";
		cin >> id_temp;
		cout << endl << "Password:";
		cin >> pass_temp;
		system("cls");
		int result = ::cust_auth.loginCustomer(id_temp, pass_temp);
		if (result)
		{
			customer_panel();
		}
		else
		{
			cout << "Invalid login credentials!";
			_getch();
			system("cls");
		}
	}
	else
	{
		while (1)
		{
			system("cls");
			cout << "Customer Panel" << endl << endl;
			cout << "Account Number: " << ::customer_id << endl;
			cout << "Mobile Number: " << ::acc[::employee_id].getMobile() << endl << endl;
			cout << "1. Account Statement" << endl;
			cout << "2. Send Money" << endl;
			cout << "3. Change Password" << endl;
			cout << "4. Logout" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				customer_panelStatement();
				break;
			case 2:
				customer_panelSendMoney();
				break;
			case 3:
				customer_panelChangePassword();
				break;
			case 4:
				break;
			default:
				customer_panelInvalidChoice();
			}
			if (choice == 4)
			{
				::cust_auth.logout();
				break;
			}
		}
	}
}



void main()
{
	cout << "Welcome to Banking System!" << endl << endl;
	cout << "This program is written by Atharva Deosthale. Please support on GitHub!" << endl;
	cout << "http://github.com/atharvadeosthale" << endl << endl;
	cout << "Press any key to continue";
	_getch();
	system("cls");
	cout << "First of all, we need to create an employee account to start things up." << endl;
	_getch();
	cout << "Now the program will guide you from here, press any key to continue." << endl;
	_getch();
	system("cls");
	::emp[1].create();
	::Authenticator auth;
	auth.loginCustomer(1, ::emp[1].getPassword());
	employee_panel();
	int choice = 0;
	while (1)
	{
		system("cls");
		cout << "Welcome to Banking System" << endl << endl;
		cout << "1. Customer Login" << endl;
		cout << "2. Employee Login" << endl << endl;
		cout << "Your choice: ";
		cin >> choice;
		if (choice == 1)
			customer_panel();
		else
			employee_panel();
	}
}

