namespace sudogui
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.button_start = new System.Windows.Forms.Button();
            this.button_tishi = new System.Windows.Forms.Button();
            this.button_check = new System.Windows.Forms.Button();
            this.button_easy = new System.Windows.Forms.Button();
            this.button_middle = new System.Windows.Forms.Button();
            this.button_hard = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button_start
            // 
            this.button_start.Location = new System.Drawing.Point(123, 550);
            this.button_start.Name = "button_start";
            this.button_start.Size = new System.Drawing.Size(124, 70);
            this.button_start.TabIndex = 0;
            this.button_start.Text = "开始游戏";
            this.button_start.UseVisualStyleBackColor = true;
            this.button_start.Click += new System.EventHandler(this.button_start_Click);
            // 
            // button_tishi
            // 
            this.button_tishi.Location = new System.Drawing.Point(347, 550);
            this.button_tishi.Name = "button_tishi";
            this.button_tishi.Size = new System.Drawing.Size(124, 70);
            this.button_tishi.TabIndex = 1;
            this.button_tishi.Text = "提示";
            this.button_tishi.UseVisualStyleBackColor = true;
            this.button_tishi.Click += new System.EventHandler(this.button_tishi_Click);
            // 
            // button_check
            // 
            this.button_check.Location = new System.Drawing.Point(571, 550);
            this.button_check.Name = "button_check";
            this.button_check.Size = new System.Drawing.Size(124, 70);
            this.button_check.TabIndex = 2;
            this.button_check.Text = "检查";
            this.button_check.UseVisualStyleBackColor = true;
            this.button_check.Click += new System.EventHandler(this.button_check_Click);
            // 
            // button_easy
            // 
            this.button_easy.Location = new System.Drawing.Point(347, 156);
            this.button_easy.Name = "button_easy";
            this.button_easy.Size = new System.Drawing.Size(124, 70);
            this.button_easy.TabIndex = 3;
            this.button_easy.Text = "简单";
            this.button_easy.UseVisualStyleBackColor = true;
            this.button_easy.Click += new System.EventHandler(this.button_easy_Click);
            // 
            // button_middle
            // 
            this.button_middle.Location = new System.Drawing.Point(347, 313);
            this.button_middle.Name = "button_middle";
            this.button_middle.Size = new System.Drawing.Size(124, 70);
            this.button_middle.TabIndex = 4;
            this.button_middle.Text = "中等";
            this.button_middle.UseVisualStyleBackColor = true;
            this.button_middle.Click += new System.EventHandler(this.button_middle_Click);
            // 
            // button_hard
            // 
            this.button_hard.Location = new System.Drawing.Point(347, 470);
            this.button_hard.Name = "button_hard";
            this.button_hard.Size = new System.Drawing.Size(124, 70);
            this.button_hard.TabIndex = 5;
            this.button_hard.Text = "难";
            this.button_hard.UseVisualStyleBackColor = true;
            this.button_hard.Click += new System.EventHandler(this.button_hard_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 650);
            this.Controls.Add(this.button_hard);
            this.Controls.Add(this.button_middle);
            this.Controls.Add(this.button_easy);
            this.Controls.Add(this.button_check);
            this.Controls.Add(this.button_tishi);
            this.Controls.Add(this.button_start);
            this.Name = "Form1";
            this.Text = "数独游戏";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button_start;
        private System.Windows.Forms.Button button_tishi;
        private System.Windows.Forms.Button button_check;
        private System.Windows.Forms.Button button_easy;
        private System.Windows.Forms.Button button_middle;
        private System.Windows.Forms.Button button_hard;
    }
}

