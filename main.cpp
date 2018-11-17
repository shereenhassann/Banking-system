#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

class acc
{
    int ano;
    char name[100];
    int dep;
    char type;
    char address[100];
    int phone;

public:
    void create_acc();    //function to create a new account
    void show_acc() const;    //function to show account details
    void adep(int);    //function to accept deposit amount
    void draw(int);    //function to subtract withdrawal amount
    void report() const;    //function to show data in tabular format
    int retano() const;    //For returning account number
    int retbal() const;    //For returning balance amount
    char qtype() const;    //For returning type of account
};



void acc::create_acc()
{
    cout<<"\nEnter The Account Number :";
    cin>>ano;
    cout<<"\n\nEnter client name : ";
    cin.ignore();
    cin.getline(name,100);
    cout<<"\nEnter client address: ";
    cin.ignore();
    cin.getline(address,100);
    cout<<"\nEnter your phone number: ";
    cin>>phone;
    cout<<"\nEnter Type of Account(Current/Savings) : ";
    cin>>type;
    cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
    cin>>dep;     //We have set the minimum initial amount for savings be 500 & for current be 1000
    cout<<"\n\nYour account has been created..";
}

void acc::show_acc() const
{
    cout<<"\nAccount Number : "<<ano;
    cout<<"\nAccount Holder Name : ";
    cout<<name;
    cout<<"\nType of Account : "<<type;
    cout<<"\nBalance amount : "<<dep;
}



void acc::adep(int x)
{
    dep+=x;
}

void acc::draw(int x)
{
    dep-=x;
}

void acc::report() const
{
    cout<<ano<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<dep<<endl;
}

int acc::retano() const
{
    return ano;
}

int acc::retbal() const
{
    return dep;
}

char acc::qtype() const
{
    return type;
}

void write_acc();    //function to write record in binary file
void display_all();        //function to display all account details
void dep_withdraw(int, int); // function to desposit/withdraw amount for given account


int main()
{
    char ch;
    int num;

    do
    {

        cout<<"\nWelcom to FCI Banking System";
        cout<<"\n1.Create a New Account";
        cout<<"\n2.Deposit";
        cout<<"\n3.Withdraw";
        cout<<"\n4.List Clients and Accounts";
        cout<<"\n5.EXIT";
        cout<<"\n\nPlease enter Choice: ";
        cin>>ch;

        switch(ch)
        {
        case '1':
            write_acc();
            break;
        case '2':
            cout<<"\n\n\tEnter The Account Number : "; cin>>num;
            dep_withdraw(num, 1);
            break;
        case '3':
            cout<<"\n\n\tEnter The Account Number : "; cin>>num;
            dep_withdraw(num, 2);
            break;
     /*   case '4':
            cout<<"\n\n\tEnter The Account Number : "; cin>>num;
            display_sp(num);
          */  break;
        case '4':
            display_all();
            break;
       /* case '6':
            cout<<"\n\n\tEnter The Account Number : "; cin>>num;
            delete_acc(num);
            break;
         case '7':
            cout<<"\n\n\tEnter The Account Number : "; cin>>num;
            modify_acc(num);
            break; */
         case '5':
            cout<<"\n\nThanks For Your Visiting!";
            break;
        // default :cout<<"\a";
        }
        cin.ignore();
        cin.get();
    }while(ch!='5');
    return 0;
}// Function To write the account data to .dat file
void write_acc()
{
    acc ac;
    ofstream x;
    x.open("info.dat",ios::binary|ios::app);
    ac.create_acc();
    x.write(reinterpret_cast<char *> (&ac), sizeof(acc));
    x.close();
}


// function to display account details from the stored file*/
void display_all()
{
    acc ac;
    ifstream x;
    x.open("info.dat",ios::binary);
    if(!x)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout<<"====================================================\n";
    cout<<"A/c no.      NAME           Type  Balance\n";
    cout<<"====================================================\n";
    while(x.read(reinterpret_cast<char *> (&ac), sizeof(acc)))
    {
        ac.report();
    }
    x.close();
}// function to withdraw amout from the account
void dep_withdraw(int n, int option)
{
    int amt;
    bool found=false;
    acc ac;
    fstream x;
    x.open("info.dat", ios::binary|ios::in|ios::out);
    if(!x)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!x.eof() && found==false)
    {
        x.read(reinterpret_cast<char *> (&ac), sizeof(acc));
        if(ac.retano()==n)
        {
            ac.show_acc();
            if(option==1)
            {
                cout<<"\n\n\tTO DEPOSITE AMOUNT ";
                cout<<"\n\nEnter The amount to be deposited: ";
                cin>>amt;
                ac.adep(amt);
            }
            if(option==2)
            {
                cout<<"\n\n\tTO WITHDRAW AMOUNT ";
                cout<<"\n\nEnter The amount to be withdraw: ";
                cin>>amt;
                int bal=ac.retbal()-amt;
                if((bal<500 && ac.qtype()=='S') || (bal<1000 && ac.qtype()=='C'))
                    cout<<"Insufficience balance";
                else
                    ac.draw(amt);
            }


            x.write(reinterpret_cast<char *> (&ac), sizeof(acc));
            cout<<"\n\n\t Record Updated";
            found=true;
           }
         }
    x.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
}
