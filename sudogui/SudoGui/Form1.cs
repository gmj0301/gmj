using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace sudogui
{
    public partial class Form1 : Form
    {
        TextBox[ , ] textbox = new TextBox[9, 9];
        Sudoku sudoku = new Sudoku();
        bool temp = true;
        int flag = 0;
        public Form1()
        {
            InitializeComponent();
            button_tishi.Enabled = false;  //禁止使用“下一轮游戏”按键
            button_check.Enabled = false; //禁止使用“检查答案”按键
            //“简单”“中等”“难”三个按键不可见
            button_easy.Visible = false;   
            button_middle.Visible = false;
            button_hard.Visible = false;
        }
       
        private void Initial()
        {
            int x = 80, y = 8, w = 40, d = 45;
            for(int i = 0; i < 9; i++)
                for(int j = 0; j < 9; j++)
                {
                    TextBox txt = new TextBox
                    {
                        //输入长度，上，左，宽，高，是否可见，标签
                        MaxLength = 1,  Top = y + i * d, Left = x + j * d, 
                        Width = w, Height = w, Visible = true, Tag = i * 9 + j
                    };
                    
                    txt.Font = new Font("宋体", 25);
                    txt.Text = "";

                    txt.KeyPress += Txt_KeyPress; //建立按键事件
                    textbox[i, j] = txt;
                    this.Controls.Add(txt);
                }
        }

        private void Txt_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != '\b')
            {
                if ((e.KeyChar < '1') || (e.KeyChar > '9'))
                {
                    e.Handled = true;
                }
            }
        }

        private bool Check_fill()     //检查是否每个空都填了
        {
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                    if (textbox[i, j].Text  == "")
                        return false;
            return true;
        }

        private bool Check_correct()   //检查是否每个空都填对了
        {
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                {
                    int num = int.Parse(textbox[i, j].Text);
                    if (num != sudoku.sudo[i, j])
                        return false;

                }
            return true;
        }

        public void write()
        {
            for (int i = 0; i < 9; i++)
                for(int j = 0; j < 9; j++)
                {
                    if (sudoku.answer[i, j] > 0)   //数字
                    {
                        textbox[i, j].Text = sudoku.answer[i, j].ToString();
                        textbox[i, j].Font = new Font("黑体", 25);
                        textbox[i, j].ReadOnly = true;
                    }
                    else                           //空
                    {
                        textbox[i, j].Font = new Font("宋体", 25);
                        textbox[i, j].Text = "";
                    }

                    textbox[i, j].KeyPress += Txt_KeyPress;
                    this.Controls.Add(textbox[i, j]);
                }
        }

        private void button_start_Click(object sender, EventArgs e)
        {
            //第二次点击“开始游戏”按键，需提前是文本框不可见。
            if (temp == false)  //temp表示是否可见，temp为true表示第一次点击
            {
                for (int i = 0; i < 9; i++)
                    for (int j = 0; j < 9; j++)
                        textbox[i, j].Visible = false;
            }
            //“简单”“中等”“难”三个按键可见
            button_easy.Visible = true;
            button_hard.Visible = true;
            button_middle.Visible = true;
            //“开始游戏”“提示”“检查”三个按键不可见
            button_tishi.Visible = false;
            button_start.Visible = false;
            button_check.Visible = false;
        }

        public void click_dif()
        {
            //“开始游戏”“提示”“检查”三个按键可见
            button_tishi.Visible = true;
            button_start.Visible = true;
            button_check.Visible = true;
            //“提示”“检查”三个按键可以使用
            button_tishi.Enabled = true;
            button_check.Enabled = true;
            //“简单”“中等”“难”三个按键不可见
            button_easy.Visible = false;
            button_hard.Visible = false;
            button_middle.Visible = false;
            if (flag == 1 || flag == 2 || flag == 3) //判断到底点的“简单”“中等”“难”三个按键中的哪个
            {                                        //方便生成数独题目使用
                if (temp == false)                   //如果是不是第一次点“开始游戏”，此时文本框不可见
                {
                    for (int i = 0; i < 9; i++)
                        for (int j = 0; j < 9; j++)
                            textbox[i, j].Visible = true;  //重新设置使其可见
                }
                if (temp == true)        //如果是第一次点“开始游戏”
                {
                    Initial();          //初始化文本框
                    temp = false;        //修改判断标识符
                }
                sudoku.create_quzi(flag);   //用flag把题目的难以程度传递，生成符合要求的数独题目
                write();                    //把数独题目写进文本框
            }
        }

        private void button_tishi_Click(object sender, EventArgs e)
        {
            int i, j, temp = 0, h = 0, l = 0;
            for (i = 0; i < 9; i++)
            {
                for (j = 0; j < 9; j++)   //遍历文本框
                {
                    if (textbox[i, j].Text == "" && temp == 0) //第一个是空白的文本框
                    {
                        temp = 1; h = i; l = j;                //改变标志temp，记录下标
                    }
                    else if(textbox[i, j].Text != "")
                    {
                        int num = int.Parse(textbox[i, j].Text);
                        if (num != sudoku.sudo[i, j])              //如果文本框里的内容与答案不符，出错
                        {
                            textbox[i, j].BackColor = Color.Red;   //文本背景标红
                            MessageBox.Show("标红地方出错，请修改！", "提示");   //窗口提示
                            textbox[i, j].BackColor = Color.White;    //背景恢复
                            break;
                        }
                    }
                }
                if (j < 9) break;  //说明出现错误，跳出循环，文本框没遍历完成
            }
            if (i > 8) //整个文本框遍历完成，说明没找到错误
            {
                if (temp == 1) textbox[h, l].Text = sudoku.sudo[h, l].ToString(); //有空白，写入
                else MessageBox.Show("您已经完成数独，恭喜！", "提示");     //玩成数独了
            }
        }
        private void button_check_Click(object sender, EventArgs e)
        {
            if (Check_fill())  //检查是否填满
            {
                if (Check_correct())  //检查填入是否正确
                    MessageBox.Show("祝贺你，完成数独！");
                else
                    MessageBox.Show("很遗憾，有错误！");
            }
            else
                MessageBox.Show("还有空没有填入数字！");
        }

        private void button_easy_Click(object sender, EventArgs e)
        {
            flag = 1;
            click_dif();
        }

        private void button_middle_Click(object sender, EventArgs e)
        {
            flag = 2;
            click_dif();
        }

        private void button_hard_Click(object sender, EventArgs e)
        {
            flag = 3;
            click_dif();
        }
    }
}
