#include <iostream>
#include <cstring>
#include <cstdlib>

#include "LargeIntegers.h"

using namespace std;

// make sure the programs does not take too long to run!
int main()
{
    InfInt test;
    bool test2;
    InfInt n0("437929383622209275558318339279713251203803143557");
    InfInt n1("36884318120138657842986912");
    InfInt n2("56674143271069242969345343133314729658413823143");
    InfInt n3("9490218825906006136206299732608259673607608545886918056242582196031749781050");
    InfInt n4("8691792580194248637129985392154304282744427830821469056466733804477176");
    int s0 = 1587;
    int s1 = 1825;
    test = n1 + n3;
    cout<<"test 0 ";
    cout << (test == InfInt("9490218825906006136206299732608259673607608545886954940560702334689592767962") ? "passed" : "failed") << endl;
    test = n4 - n2;
    cout<<"test 1 ";
    cout << (test == InfInt("8691792580194248637129928718011033213501458485478335741737075390654033") ? "passed" : "failed") << endl;
    test = n0 / n0;
    cout<<"test 2 ";
    cout << (test == InfInt("1") ? "passed" : "failed") << endl;
    test = n1 % n0;
    cout<<"test 3 ";
    cout << (test == InfInt("36884318120138657842986912") ? "passed" : "failed") << endl;
    test = n3 ^ n1;
    cout<<"test 4 ";
    cout << (test == InfInt("9490218825906006136206299732608259673607608545886935597438021967036803156378") ? "passed" : "failed") << endl;
    test = n2 & n4;
    cout<<"test 5 ";
    cout << (test == InfInt("53612472409662059117615453795469053147486097568") ? "passed" : "failed") << endl;
    test = n0 | n1;
    cout<<"test 6 ";
    cout << (test == InfInt("437929383622209275558335264400581541284603232165") ? "passed" : "failed") << endl;
    test2 = n1 < n3;
    cout<<"test 7 ";
    cout << (test2 == true ? "passed" : "failed") << endl;
    test2 = n4 == n1;
    cout<<"test 8 ";
    cout << (test2 == false ? "passed" : "failed") << endl;
    test2 = n4 > n1;
    cout<<"test 9 ";
    cout << (test2 == true ? "passed" : "failed") << endl;
    test2 = n2 <= n4;
    cout<<"test 10 ";
    cout << (test2 == true ? "passed" : "failed") << endl;
    test2 = n1 >= n4;
    cout<<"test 11 ";
    cout << (test2 == false ? "passed" : "failed") << endl;
    test2 = n3 != n2;
    cout<<"test 12 ";
    cout << (test2 == true ? "passed" : "failed") << endl;
    test = n4 << s1;
    cout<<"test 13 ";
    cout << (test == InfInt("20837779618233990261821268343668142125953371230098570611299038042376418185723608124802937308822519271266863472855230811289795523101171165379593696893675193720241500478424807890015769014273156672545696744655097700533245004212987072385094349310100522910944988172040296502339261018535681547881824298728453595493864183591803074428024070752260060951470947170286347609774104296789553119719190321039094132460133444004845039729726646421671368361385414061856543204327863809097210882477627924056342172306112139608716736533829809949984807993235827148691232705979053476459665561366746865599720150215030438498864094015043000736940032") ? "passed" : "failed") << endl;
    test = n3 >> s1;
    cout<<"test 14 ";
    cout << (test == InfInt("0") ? "passed" : "failed") << endl;


    system("pause");
    return 0;
}