using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace sudogui
{
    public class Sudoku
    {
        public int[] shift = new int[8] { 3, 6, 1, 4, 7, 2, 5, 8 };    //除去第一行，其余都是通过左移变换得到，左移列数如右图所示
        public int[ ,] sudo = new int[9, 9];   //存储数独
        public int[] c1 = new int[3];       //存储中间三行经过变换的顺序
        public int[] c2 = new int[3];       //存储最后三行经过变换的顺序
        public int[,] answer = new int[9, 9];   //存储数独题目和答案
        public int[] p = new int[8];       //存储经过全排列的第一行后8个顺序
        public int snum1 = 1;
        public int snum2 = 2;

        public Sudoku()                             //生成第一个数独
        {
            for (int i = 0; i < 9; i++)
                sudo[0, i] = i+1;                     //第一行为123456789
            produce();
        }

        public void produce()
        {
            for (int i = 1; i < 9; i++)
                for (int j = 0; j < 9; j++)         //由shift函数生成
                    sudo[i, j] = sudo[0, (j + shift[i - 1]) % 9];
        }

        public void swap(int a, int b) //交换函数，交换a和b
        {
            int temp = a;
            a = b;
            b = temp;
        }

        public bool nextPermutation(int[] p, int n) //全排列函数
        {
            int last = n - 1;
            int i, j, k;
            //从后向前查找，看有没有后面的数大于前面的数的情况，若有则停在后一个数的位置。   
            i = last;
            while (i > 0 && p[i] < p[i - 1])
                i--;
            //若没有后面的数大于前面的数的情况，说明已经到了最后一个排列，返回false。   
            if (i == 0)
                return false;
            //从后查到i，查找大于p[i - 1]的最小的数，记入k   
            k = i;
            for (j = last; j >= i; j--)
                if (p[j] > p[i - 1] && p[j] < p[k])
                    k = j;
            //交换p[k]和p[i - 1]   
            swap(p[k], p[i - 1]);
            //倒置p[last]到p[i]   
            for (j = last, k = i; j > k; j--, k++)
                swap(p[j], p[k]);

            return true;
        }

        void jiaohan_1(int s1)     //中间4，5，6行的变换
        {
            if (s1 == 1) { c1[0] = 3; c1[1] = 4; c1[2] = 5; }
            if (s1 == 2) { c1[0] = 3; c1[1] = 5; c1[2] = 4; }
            if (s1 == 3) { c1[0] = 4; c1[1] = 3; c1[2] = 5; }
            if (s1 == 4) { c1[0] = 4; c1[1] = 5; c1[2] = 3; }
            if (s1 == 5) { c1[0] = 5; c1[1] = 3; c1[2] = 4; }
            if (s1 == 6) { c1[0] = 5; c1[1] = 4; c1[2] = 3; }
        }

        void jiaohan_2(int s2)     //中间7，8，9行的变换
        {
            if (s2 == 1) { c2[0] = 6; c2[1] = 7; c2[2] = 8; }
            if (s2 == 2) { c2[0] = 6; c2[1] = 8; c2[2] = 7; }
            if (s2 == 3) { c2[0] = 7; c2[1] = 6; c2[2] = 8; }
            if (s2 == 4) { c2[0] = 7; c2[1] = 8; c2[2] = 6; }
            if (s2 == 5) { c2[0] = 8; c2[1] = 6; c2[2] = 7; }
            if (s2 == 6) { c2[0] = 8; c2[1] = 7; c2[2] = 6; }
        }

        public void create_sudo()           //下一个数独题目生成
        {
            if(snum1 == 1 && snum2 == 1)        //当前第一行经过行变换所产生的36种数独已经完成
            {
                nextPermutation(p, 8);          //全排列，产生新的一个第一行
                for (int i = 1; i < 9; i++)
                    sudo[0, i] = p[i - 1];        
                produce();                      //生成整个数独终局
            }
            if (snum2 == 6)                     //当最后三行的6种行变换全部完成时，进行中间三行的行变化
            {                                   //如果中间三行的行变换也完成了，就重新计数
                snum2 = 1;
                if (snum1 == 6) snum1 = 1;
                else snum1++;
            }
            else snum2++;
        }

        public void create_quzi(int flag)        //随机生成题目
        {
            create_sudo();
            Random rdm = new Random();  //一个随机数
            int blank;
            if (flag == 1) blank = rdm.Next(30, 40);  //简单，30 - 40 个空
            else if (flag == 2) blank = rdm.Next(40, 50); //中的，40 - 50 个空
            else blank = rdm.Next(50, 60);  //难，50 - 60 个空

            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                    answer[i, j] = sudo[i, j];   //先赋值

            for (int i = 0; i < 9 && blank > 0; i++)   //9个九宫格
            {
                for (int j = 0; j < 2 && blank > 0; j++)  //每个九宫格选两个空
                {
                    int position = rdm.Next(9);   //随机生成一个数，来选九宫格里的位置
                    int x = i / 3 * 3 + position / 3;
                    int y = i % 3 * 3 + position % 3;
                    if (answer[x, y] != 0)   //这个位置没被挖空
                    {
                        answer[x, y] = 0;
                        blank--;
                    }
                    else   //这个位置已经是空了
                    {
                        j--;
                        continue;
                    }
                }
            }
            while (blank > 0)  //当还有空时
            {
                int block = rdm.Next(9);  //选择哪个九宫格
                int position = rdm.Next(9);  //九宫格里的哪个位置
                int x = block / 3 * 3 + position / 3;
                int y = block % 3 * 3 + position % 3;
                if (answer[x, y] != 0)  //没有被挖空
                {
                    answer[x, y] = 0;
                    blank--;
                }
                else continue;
            }
        }

    }
}
