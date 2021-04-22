//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

using System;
using System.Text;
using System.Windows.Forms;

namespace CardSettings
{
    public partial class FormCardSettings : Form
    {

        /// <summary>
        /// constructor
        /// </summary>
        public FormCardSettings()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Load
        /// </summary>
        private void FormCardSettings_Load(object sender, EventArgs e)
        {
            // read the configuration file
            checkBox1.Checked = Properties.Settings.Default.CheckBox1;
            checkBox2.Checked = Properties.Settings.Default.CheckBox2;
        }

        /// <summary>
        /// Click button_OK
        /// </summary>
        private void button_OK_Click(object sender, EventArgs e)
        {
            // save
            Properties.Settings.Default.CheckBox1 = checkBox1.Checked;
            Properties.Settings.Default.CheckBox2 = checkBox2.Checked;
            // write the configuration file
            Properties.Settings.Default.Save();

            Close();
        }

        /// <summary>
        /// Click button_Cancel
        /// </summary>
        private void button_Cancel_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}