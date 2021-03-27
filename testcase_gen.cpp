#include<bits/stdc++.h>

using namespace std;

int main()
{
    string s = "./testcase/input/input";
    string t = ".txt";
    int ss = 0;             // starting number of testcase
    int tt = 40;            // ending number of testcase
    int intinf = 1e4;

    std::mt19937_64 rng(time(0));
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,intinf);
    std::uniform_int_distribution<std::mt19937::result_type> dist2(6,10);


    for(int i1 = ss;i1<tt;i1++)
    {
        string nam;
        nam += s;
        nam += (char)(i1/10 + '0');
        nam += (char)(i1%10 + '0');
        nam += t;

        fstream fin;
        fin.open(nam,fstream::out);

        int n = (1 << dist2(rng));
        fin << n << '\n';

        for(int i = 0;i<n;i++)
        {
            for(int j = 0;j<n;j++)
                fin << dist(rng) << " ";
            fin << '\n';
        }

        fin.close();
    } 


    return 0;
}