/*
首先解决问题一：最简单的形式，3个商人(m)与3个随从(f)过河
拥有可行的状态，拥有状态转移的方式
从初始状态转移至最终状态
m指河左边的商人数，f是随从数，b=0代表船在左边，1在右边
*/
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::string;
using std::vector;
const int maxn = 1000 + 7;
int found[maxn][maxn][2];
int able[maxn][maxn][2];
struct State
{
   int m;
   int f;
   int b; // 0代表运向左边，1代表运向右边
   vector<int> sons;
};
vector<State> trackTree;
vector<int> trackStack;
int mNum, fNum, bCap;
//注意：在状态转移时不能转移回去，否则可能无限递归
//给经过的状态设置标记
// DFS返回0代表没有可行路径，返回正数代表结点在trackTree里的下标
int DFS(int m, int f, int b)
{
   if (m == 1 && f == 1 && b == 0)
   {
      int asdfa = 1;
      asdfa = 111;
   }
   found[m][f][b] = 1;
   trackTree.push_back(State{m, f, b, vector<int>()});
   int index = trackTree.size() - 1;
   if (m == 0 && f == 0 && b == 1)
   {
      found[m][f][b] = 0;
      return index;
   }
   int flag = 0;
   for (int d1 = 0; d1 <= bCap; d1++)
   {
      for (int d2 = 0; d2 <= bCap; d2++)
      {
         if (d1 + d2 <= bCap && d1 + d2 > 0)
         {
            int m1, f1, b1;
            if (b == 1)
            {
               m1 = m + d1, f1 = f + d2, b1 = 0;
               if (!(m1 <= mNum && f1 <= fNum && able[m1][f1][b1] && !found[m1][f1][b1]))
                  continue;
            }
            else
            {
               m1 = m - d1, f1 = f - d2, b1 = 1;
               if (!(m1 >= 0 && f1 >= 0 && able[m1][f1][b1] && !found[m1][f1][b1]))
                  continue;
            }
            int ret = 0;
            if (ret = DFS(m1, f1, b1))
            {
               trackTree[index].sons.push_back(ret);
               flag = 1;
            }
         }
      }
   }
   found[m][f][b] = 0;
   return flag == 1 ? index : 0;
}
void setEnableState()
{
   for (int m = 0; m <= mNum; m++)
   {
      for (int f = 0; f <= fNum; f++)
      {
         int m1 = mNum - m, f1 = fNum - f;
         //任何一边，商人比随从多或者商人为0为可行状态
         if ((m >= f || m == 0) && (m1 >= f1 || m1 == 0))
            able[m][f][0] = able[m][f][1] = 1;
      }
   }
}
void Print(int index)
{
   trackStack.push_back(index);
   if (trackTree[index].sons.size() == 0)
   {
      //此时栈里已经是一条完整的track
      for (auto i : trackStack)
      {
         auto t = trackTree[i];
         printf("(%d,%d,%d) ", t.m, t.f, t.b);
      }
      putchar('\n');
      trackStack.pop_back();
      return;
   }
   for (auto son : trackTree[index].sons)
   {
      Print(son);
   }
   trackStack.pop_back();
   return;
}
int main()
{
   cout << "请分别输入商人数、随从数、船只容量:\n";
   cin >> mNum >> fNum >> bCap;
   setEnableState();
   trackTree.push_back(State()); //添加一条空数据
   if (DFS(mNum, fNum, 0))
      Print(1);
   else
      cout << "无解！\n";
   return 0;
}