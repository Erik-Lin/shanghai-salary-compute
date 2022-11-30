#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;

class man{
private:
    string name;        //姓名
    double salary;
    double monSalary;    //税后底薪
    double yearEnd;     //年终奖
    double rate;        //调薪幅度
    double yanglao;
    double yiliao;
    double shiye;
    double gongjijin;
    double gerensuodeshui;
    double salaryRate;
    double susuankouchushu;
    int yearEndMonth;   //平均年终奖月份
    vector<double> saving = vector<double>(20);
public:
    man(string name){
        this->name = name;
    }
    void computeYearEnd(int years){
        this->yearEndMonth = years;
        this->yearEnd = this->yearEndMonth*this->monSalary;
    }
    void computeRate(double temp){
        if(temp > 80000){
            this->salaryRate = 0.45;
            this->susuankouchushu = 15160;
        }else if(temp > 55000){
            this->salaryRate = 0.35;
            this->susuankouchushu = 7160;
        }else if(temp > 35000){
            this->salaryRate = 0.30;
            this->susuankouchushu = 4410;
        }else if(temp > 25000){
            this->salaryRate = 0.25;
            this->susuankouchushu = 2660;
        }else if(temp > 12000){
            this->salaryRate = 0.20;
            this->susuankouchushu = 1410;
        }else if(temp > 3000){
            this->salaryRate = 0.10;
            this->susuankouchushu = 210;
        }else{
            this->salaryRate = 0.03;
            this->susuankouchushu = 0;
        }
    }
    void setMonSalary(double salary){
        //三险一金计算
        this->salary = salary;
        this->yanglao = salary * 0.08;
        this->yiliao = salary * 0.02;
        this->shiye = salary * 0.005;
        this->gongjijin = salary * 0.07;
        //应缴税额计算
        double yingjiaoshuie = this->salary - this->yanglao - this->yiliao - this->shiye - this->gongjijin - 5000;//5000为个税免征额
        //计算个税缴费税率和速算扣除数
        computeRate(yingjiaoshuie);
        //计算个人所得税
        this->gerensuodeshui = yingjiaoshuie*this->salaryRate - this->susuankouchushu;
        this->monSalary = this->salary - this->yanglao - this->yiliao - this->shiye - this->gongjijin - this->gerensuodeshui;
    }
    void setrate(double rate){
        this->rate = rate;
    }
    void computeSavings(double salary,double months,double rate){
        setMonSalary(salary);
        setrate(rate);
        computeYearEnd(months);
        this->saving[0] = this->monSalary*12 + yearEnd;
        vector<double> salarys = vector<double>(20);
        salarys[0]=this->saving[0];
        for(int i=1;i<salarys.size();i++){
            salarys[i] = salarys[i-1]*(1+this->rate);
        }
        for(int i=1;i<saving.size();i++){
            this->saving[i] = this->saving[i-1] + salarys[i];
        }
    }
    void printData(){
        cout<<"姓名：\t"<< this->name <<endl;
        cout<<"税前月薪：\t"<< this->salary <<"元"<<endl;
        cout<<"税后月薪：\t"<< this->monSalary <<"元"<<endl;
        cout<<"税后年终奖：\t"<< this->yearEnd <<"元"<<endl;
        cout<<"医疗保险：\t"<< this->yiliao <<"元"<<endl;
        cout<<"养老保险：\t"<< this->yanglao <<"元"<<endl;
        cout<<"公积金：\t"<< this->gongjijin <<"元"<<endl;
        cout<<"失业保险：\t"<< this->shiye <<"元"<<endl;
        cout<<"个人所得税：\t"<< this->gerensuodeshui <<"元"<<endl;
        cout<<"个税缴纳税率：\t"<< this->salaryRate*100 <<"%" <<endl;
        cout<<"速算扣除数：\t"<< this->susuankouchushu <<"元"<<endl;
        cout<<"平均调薪比率：\t"<< this->rate*100 <<"%"<<endl;

        for(int i=0;i<this->saving.size();i++){
            cout<<"第"<<i+1<<"\t年，不吃不喝不消费，到手积蓄预计为：\t"<< fixed <<setprecision(2)<<this->saving[i]/10000<<"万元"<<endl;
        }
    }
};



int main(){
    man lin("peter");
    double mon=23650,yearend=2,rate=0.08;
    cin>>mon>>yearend>>rate;
    lin.computeSavings(mon,yearend,rate);
    lin.printData();
    cout<<endl;cout<<endl;cout<<endl;

    return 0;
}
