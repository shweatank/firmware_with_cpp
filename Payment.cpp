#include<bits/stdc++.h>
using namespace std;

class PaymentMethod{
    public:
        virtual void pay(){
            cout<<"Unknown Payment"<<endl;
        }
};

class CreditCard : public PaymentMethod{
    public:
        long long creditcardnumber;
    
    CreditCard(long long credit){
        creditcardnumber = credit;
    }

    void pay(){
        cout<<"Credit card payment : "<<creditcardnumber<<endl;
    }
    
};

class PayPal : public PaymentMethod{
    public:
        string email;
    
    PayPal(string email){
        this->email = email;
    }

    void pay(){
        cout<<"Paypal  payment with email : "<<email<<endl;
    }
};

class BankTransfer : public PaymentMethod{
    public:
        string accountnumber;
    
    BankTransfer(string acc){
        accountnumber = acc;
    }

    void pay(){
        cout<<"Bank Transfer with acc number "<<accountnumber<<endl;
    }
};

void processPayment(PaymentMethod *pm){
    if(pm){
        pm->pay();
    }
    else{
        cout<<"Unknown payment"<<endl;
    }
}
   

int main(){
     CreditCard cc(123456789012);
    PayPal pp("honour@gmail.com");
    BankTransfer bt("SBIN123456");

    PaymentMethod *pm;
    
    pm = &cc;
    processPayment(pm);
    
    pm = &pp;
    processPayment(pm);

    pm = &bt;
    processPayment(pm);

    pm = nullptr;
    processPayment(pm);

    return 0;
}
