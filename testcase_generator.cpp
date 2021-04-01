#include<bits/stdc++.h>

using namespace std;

int main()
{
    int size = 64;
    int num = 7;
    for(;size <= 4096;size *= 2)
    {
        string s = "./testcase/";
        int x = size;
        string mp;
        while(x > 0)
        {
            mp += (char)(x%10 + '0');
            x = x/10;
        }
        reverse(mp.begin(),mp.end());
        s += mp;
        s += "/input";
        string t = ".txt";
        for(int yy = 0;yy < num;yy++)
        {
            cout << yy << '\n';
            int intinf = 1e4;

            mt19937 rng(yy);

            std::uniform_int_distribution<std::mt19937::result_type> dist(1,intinf);
            std::uniform_int_distribution<std::mt19937::result_type> dist2(6,10);

            string nam;
            nam += s;
            nam += (char)(yy/10 + '0');
            nam += (char)(yy%10 + '0');
            nam += t;

            fstream fin;
            cout << nam << endl;
            fin.open(nam,fstream::out);

            fin << size << '\n';

            for(int i = 0;i<size;i++)
            {
                for(int j = 0;j<size;j++)
                {
                    fin << dist(rng) << " ";
                }
                fin << '\n';
            }

            fin.close();
        } 
    }

    return 0;
}