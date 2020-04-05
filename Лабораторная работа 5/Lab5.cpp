#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "cstdlib"
using namespace std;

struct pass {
   // PassengerId, Survived, Pclass, Name, Sex, Age, SibSp, Parch, Ticket, Fare, Cabin, Embarked;
    int id=0;
    bool surv=false;
    int Pclass=0;
    string name=" ";
    string sex=" ";
    int age=0;
    int sib=0;
    int par=0;
    string ticket = " ";
    double fare=0.0;
    string cabin = " ";
    string  emb="0";
};

pass help(string str) {
    pass p;
    string temp[13];
    int i = 0;

    for (int j = 0; j < 13; j++) {
        while (str[i] != ',' && str[i] != '\0') {
            temp[j] += str[i];
            i++;
        }
        i++;
    }
    p.id= atoi(temp[0].c_str());
    p.surv= atoi(temp[1].c_str());
    p.Pclass= atoi(temp[2].c_str());
    p.name = temp[3]+" "+temp[4];
    p.sex= temp[5];
    p.age= atoi(temp[6].c_str());
    p.sib= atoi(temp[7].c_str());
    p.par= atoi(temp[8].c_str());
    p.ticket = temp[9];
    p.fare = atof(temp[10].c_str());
    p.cabin = temp[11];
    p.emb = temp[12];
    return p;
}

int main()
{
    ifstream fin("train.csv");
    vector <string> temp;
    string str;
    while (getline(fin, str, '\r'))
    {
        if (str.size() > 0)
            temp.push_back(str);
    }
    fin.close();
   
    int all_surv = 0, surv1 = 0, surv2 = 0, surv3 = 0, surv_w = 0, surv_m = 0, C = 0, Q = 0, S = 0, all_w=0, all_m=0;
    vector<int> minor;
    double count_w = 0.0, count_m = 0.0, all_age = 0;
    for (int i = 1; i < temp.size(); i++) {
        pass a=help(temp[i]);
        if (a.surv == 1) {
            all_surv++;
            if (a.sex == "male") {
                surv_m++;
            }
            else surv_w++;

            switch (a.Pclass) {
            case 1:
                surv1++;
                break;
            case 2:
                surv2++;
                break;
            case 3:
                surv3++;
                break;
            }
        }

        if (a.age < 18) {
            minor.push_back(a.id);
        }
        if (a.emb == "C") {
            C++;
        }
        if (a.emb == "S") {
            S++;
        }
        if (a.emb == "Q") {
            Q++;
        }


        if (a.sex == "male") {
           all_m++;
           count_m += a.age;
        }
        else {
            all_w++;
            count_w += a.age;
        }
        all_age+=a.age;
    }

   string em;
    if (C > S) {
        if (C > Q) {
          em= "Cherbourg";
        }
        else em = "Queenstown";
    }
    else
    {
        if (S > Q) {
            em = "Southampton";
        }
        else em = "Queenstown";
    }
    ofstream fout("Rezult.txt");
        fout << "Общее число выживших:" << all_surv<< endl;
        fout << "Число выживших из 1 класса:" << surv1<< endl;
        fout << "Число выживших из 2 класса:" << surv2<< endl;
        fout << "Число выживших из 3 класса:" << surv3<< endl;
        fout << "Количество выживших женщин:" << surv_w<< endl;
        fout << "Количество выживших мужчин:" << surv_m<< endl;
        fout << "Средний возраст пассажира:" << all_age/ temp.size()<< endl;
        fout << "Средний женский возраст:" << count_w/all_w<< endl;
        fout << "Средний мужской возраст:" << count_m / all_m << endl;
        fout << "Штат, в котором село больше всего пассажиров:" <<em<< endl;
        fout << "Cписок идентификаторов несовершеннолетних (младше 18) пассажиров:";
        for (int i = 0; i < minor.size(); i++) {
            if (i == minor.size()-1) {
                fout << minor[i] << ".";
                fout.close();
                return 0;
            }
            fout << minor[i] << ", ";
        }
}
