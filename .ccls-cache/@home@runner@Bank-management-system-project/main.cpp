#include <iostream>
#include<fstream>
#include<cctype>
using namespace std;
class account{      //  base class created to create a bank account for customer
  public:
  char cust_name[20],acc_type[20];
  int acc_no,bal;
  void get(){      //function to  create  account  
    cout<<"enter your name:\n";
    cin>>cust_name;
    cout<<"enter your type of account:\n";
    cin>>acc_type;
    cout<<"enter your account number:\n";
    cin>>acc_no;
    cout<<"\nenter your opening balance:\n";
    cin>>bal;
  }
  void display(){   //function to display account holder details
    cout<<"Account created successfully:\n";
    cout<<"\n your name is:\n"<<cust_name;
    cout<<"\n your acount type is:\n"<<acc_type;
    cout<<"\n your account number is:\n"<<acc_no;
    cout<<"\nyour opening balance is:\n"<<bal;
  }
};
class curr_acct:public account{  // An inherited class from base class 
  public:
  int p;
  
void deposit( ){   //function created to deposit amount by the user to their bank account
  int d=0;
    cout<<"\nenter your deposit:\n";
    cin>>p;
    d=bal+=p;
    cout<<"\nCurrent balance in your account is:\n"<<d<<" Rs";
}


void modify(){  //function created  for the user to modify their account details
  cout<<"enter the account holder name:\n";
  cin>>cust_name;
  cout<<"enter the new type of account type:\n";
  cin>>acc_type;
  
}

};
class  sav_accnt:public curr_acct{ 
  public:
  void withdrawal( ){//function created for the user to withdraw a amount from theirbankaccount
  int k,w;
    
    cout<<"\nenter the amount to  withdraw:\n";
    cin>>w;
    k=bal-w;
    if(k<500){
      cout<<"sorry! amount cannot be withdrawn";

    }
 else{
       cout<<"\nyour outstanding balance after withdrawal is:\n"<<k;
     
     }}
    
 inline  void delete_account(int); 
 inline void modify_account(int); 
 inline void create_account();   
 inline void display_account(int); 
 inline void withdrawal_amount(int); 
 inline void deposit_amount(int); 
 };


void sav_accnt::create_account(){ // functions to save account                                       details to  a file
sav_accnt acc;
ofstream fout;
fout.open("bank account.dat",ios::binary);
acc.get();
fout.write(reinterpret_cast<char *>(&acc),sizeof(sav_accnt));
fout.close();
}

void sav_accnt::display_account( int num){ //functions to                                                                       display account details from file 
sav_accnt acc;
bool flag=false;
ifstream fin;
fin.open("bank account.dat",ios::binary);
if(!fin){
  cout<<"sorry!  file  doesn't exist ";
}
cout<<"\n*********Your bank details***********\n";
while(fin.read(reinterpret_cast<char *>(&acc),sizeof(sav_accnt))){
if(acc.acc_no==num){
  acc.account::display();
 
  flag=true;
}
}
fin.close();
if(flag==false){
  cout<<"Account number doesn't exist";

}
}

void sav_accnt::modify_account( int num){ //function to modify account details and                                             save it to the file
bool found=false;
sav_accnt acc;
fstream file;
file.open("bank account.dat",ios::binary|ios::in|ios::out);
if(!file){
  cout<<"sorry! File doesn't exist";
}

while(!file.eof()&&found==false){
file.read(reinterpret_cast<char *>(&acc),sizeof(sav_accnt));

if(acc.acc_no==num){
  acc.account::display();
 
  cout<<"\n*******Modify your account******\n";
  acc.modify();
  int po=(-1)*static_cast<int> (sizeof(sav_accnt));
  file.seekp(po,ios::cur);
  file.write(reinterpret_cast<char*>(&acc),sizeof(sav_accnt));
  cout<<"\n*********Records updated*********\n";
  found=true;
}
}
file.close();
if(found==false){
  cout<<"\nRecords not found\n";
}
}

void sav_accnt::delete_account(int num){ // function to delete the account                                                      permanently from the file 
  ifstream fin;
  ofstream fout;
  sav_accnt acc;
  fin.open("bank account.dat",ios::binary);
  if(!fin){
    cout<<"sorry! File doesn't exist";
  }
  fout.open("account data.dat",ios::binary);
  fin.seekg(0,ios::beg);
  while(fin.read(reinterpret_cast<char *>(&acc),sizeof(sav_accnt))){
    if(acc.acc_no!=num){
      fout.write(reinterpret_cast<char *>(&acc),sizeof(sav_accnt));
     
     }
    }
    fout.close();
    fin.close();
    remove("bank account.dat");
    rename("account data.dat","bank account.dat");
    cout<<"\n*********Records removed********\n";
}

void sav_accnt::deposit_amount( int num){ //function to deposit amount and update                                                in the same changes in the file
sav_accnt acc;
bool got=false;
fstream file;
file.open("bank account.dat",ios::binary|ios::in|ios::out);

if(!file){
  cout<<"sorry! file doesn't exists";
}

while(!file.eof()&&got==false){
  file.read(reinterpret_cast<char *>(&acc),sizeof(sav_accnt));
if(acc.acc_no==num){
  acc.account::display();
  cout<<"\n";
  acc.sav_accnt::deposit();
  }

int po=(-1)*static_cast<int> (sizeof(sav_accnt));
file.seekp(po,ios::cur);
file.write(reinterpret_cast<char *>(&acc),sizeof(sav_accnt));
cout<<"\n*************Records updated***********\n";
got=true;

}
file.close();
if(got==false){
  cout<<"\n*******Records not fount********\n";
}
}

void sav_accnt::withdrawal_amount(int num){ //function to withdraw amount from the account after checking the balance in your account and updating the same in the file
  bool got= false;
  fstream file;
  sav_accnt acc;
  file.open("bank account.dat",ios::binary|ios::in|ios::out);

  if(!file){
    cout<<"Sorry!file doesn't exist";
  }

  while(!file.eof()&&got==false){
    file.read(reinterpret_cast<char *>(&acc),sizeof(sav_accnt));

    if(acc.acc_no==num){
      acc.display();
      acc.sav_accnt::withdrawal();
}
int po=(-1)*static_cast<int>(sizeof(sav_accnt));
file.seekp(po,ios::cur);
file.write(reinterpret_cast<char *>(&acc),sizeof(sav_accnt));
cout<<"\n********Records updated*******\n";
got=true;
  }
file.close();

if(got==false){
  cout<<"\n********Records not found*********\n";
}
}
int main() {
int n,i,f,num;
sav_accnt a1;
//Welcome message
cout<<"            Welcome to Bank Management System\n\n\n ";
// option displayed for the users to perform according to their requirement
cout<<"Choice 1:Create Account\n";
cout<<"Choice 2:Show account\n";
cout<<"Choice 3:Deposit amount\n";
cout<<"Choice 4:withdraw amount\n";
cout<<"Choice 5:Close account\n";
cout<<"Choice 6:Modify account\n";

label:
 cout<<"\nenter your option here:\n";
 cin>>n;

 switch(n){
   case 1:{
a1.sav_accnt:: create_account();

break;
   }
  case 2:{
    cout<<"enter your account number:\n";
    cin>>num;
    a1.sav_accnt::display_account( num);

break;
   }
   case 3:{
     cout<<"enter your account number:\n";
    cin>>num;
a1.sav_accnt::deposit_amount(num);

   }
  case 4:{
cout<<"enter your account number:\n";
cin>>num;
a1.sav_accnt::withdrawal_amount(num);
break;
  } 
  
  case 5:{
cout<<"enter the account number:\n";
cin>>num;
a1.sav_accnt::delete_account(num);
break;
  }
  case 6:{
    cout<<"enter the account number:\n";
    cin>>num;
a1.sav_accnt::modify_account(num);
break;
  }
  
default:{
    cout<<"please check our preference";
    break;
  }
 }
cout<<"\nWant to make choice again"<<
"\n"<<"Either choose '1' for yes"<<
"\n"<<
"or"<<"\n '0'to exit the page:\n";
cin>>f;
if(f==1){
  goto label;
}
else{
  cout<<"\nThank you for using bank managment system\n";
}
                 //Project details
cout<<"\n********* Project ************\n";
cout<<"\n*****  Bank Management system  *****\n";
cout<<"Name-Priya yadav\n";
cout<<"UID-20BCS6126\n";
cout<<"Class/Section-20AIML-B1\n";
return 0;
}
