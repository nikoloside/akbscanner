namespace ImageConnections
{
    partial class FormImageConnections
    {
        /// <summary>
        /// 必要なデザイナ変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナで生成されたコード

        /// <summary>
        /// デザイナ サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディタで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.button_Scan = new System.Windows.Forms.Button();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.button_Open = new System.Windows.Forms.Button();
            this.button_Close = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // button_Scan
            // 
            this.button_Scan.Location = new System.Drawing.Point(13, 21);
            this.button_Scan.Name = "button_Scan";
            this.button_Scan.Size = new System.Drawing.Size(106, 23);
            this.button_Scan.TabIndex = 0;
            this.button_Scan.Text = "Scan";
            this.button_Scan.UseVisualStyleBackColor = true;
            this.button_Scan.Click += new System.EventHandler(this.button_Scan_Click);
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.HorizontalScrollbar = true;
            this.listBox1.ItemHeight = 12;
            this.listBox1.Location = new System.Drawing.Point(13, 78);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(302, 220);
            this.listBox1.TabIndex = 1;
            this.listBox1.DoubleClick += new System.EventHandler(this.listBox1_DoubleClick);
            // 
            // button_Open
            // 
            this.button_Open.Location = new System.Drawing.Point(331, 164);
            this.button_Open.Name = "button_Open";
            this.button_Open.Size = new System.Drawing.Size(83, 23);
            this.button_Open.TabIndex = 2;
            this.button_Open.Text = "Open";
            this.button_Open.UseVisualStyleBackColor = true;
            this.button_Open.Click += new System.EventHandler(this.button_Open_Click);
            // 
            // button_Close
            // 
            this.button_Close.Location = new System.Drawing.Point(331, 302);
            this.button_Close.Name = "button_Close";
            this.button_Close.Size = new System.Drawing.Size(83, 23);
            this.button_Close.TabIndex = 3;
            this.button_Close.Text = "Close";
            this.button_Close.UseVisualStyleBackColor = true;
            this.button_Close.Click += new System.EventHandler(this.button_Close_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 61);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(26, 12);
            this.label1.TabIndex = 4;
            this.label1.Text = "List:";
            // 
            // FormImageConnections
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(426, 328);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button_Close);
            this.Controls.Add(this.button_Open);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.button_Scan);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(442, 366);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(442, 366);
            this.Name = "FormImageConnections";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Image Connections";
            this.Load += new System.EventHandler(this.FormImageConnections_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_Scan;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Button button_Open;
        private System.Windows.Forms.Button button_Close;
        private System.Windows.Forms.Label label1;
    }
}

