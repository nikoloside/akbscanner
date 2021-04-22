//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

using System;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace ImageSettings
{
    public partial class FormImageSettings : Form
    {
        // DllImport
        [DllImport("kernel32.dll", EntryPoint = "GetPrivateProfileInt")]
        public static extern UInt32 GetPrivateProfileInt(
                                            string lpAppName,
                                            string lpKeyName,
                                            Int32 nDefault,
                                            string lpFileName);

        [DllImport("kernel32.dll", EntryPoint = "WritePrivateProfileString")]
        public static extern bool WritePrivateProfileString(
                                            string lpAppName,
                                            string lpKeyName,
                                            string lpString,
                                            string lpFileName);

        /// <summary>
        /// constructor
        /// </summary>
        public FormImageSettings()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Load
        /// </summary>
        private void FormImageSettings_Load(object sender, EventArgs e)
        {
            int buttonIndex;

            if (String.IsNullOrEmpty(ImageSettingsMain.iniFilePath) == true)
            {
                // for ScanSnap Organizer
                // read the configuration file
                buttonIndex = Properties.Settings.Default.RadioButtonIndex;
            }
            else
            {
                // for ScanSnap Manager
                // read the ini file
                buttonIndex = readFile(ImageSettingsMain.iniFilePath);
            }

            switch (buttonIndex)
            {
                case 0:
                default:
                    radioButton1.Checked = true;
                    break;
                case 1:
                    radioButton2.Checked = true;
                    break;
            }
        }

        /// <summary>
        /// Click button_OK
        /// </summary>
        private void button_OK_Click(object sender, EventArgs e)
        {
            // save
            int buttonIndex;

            if (radioButton2.Checked == true)
            {
                // 1
                buttonIndex = 1;
            }
            else
            {
                buttonIndex = 0;
            }

            if (String.IsNullOrEmpty(ImageSettingsMain.iniFilePath) == true)
            {
                // for ScanSnap Organizer
                // write the configuration file
                Properties.Settings.Default.RadioButtonIndex = buttonIndex;
                Properties.Settings.Default.Save();
            }
            else
            {
                // for ScanSnap Manager
                // write the ini file
                writeFile(ImageSettingsMain.iniFilePath, buttonIndex);
            }

            Close();
        }

        /// <summary>
        /// Click button_Cancel
        /// </summary>
        private void button_Cancel_Click(object sender, EventArgs e)
        {
            Close();
        }
        
        /// <summary>
        /// read the ini file
        /// </summary>
        /// <param name="filepath">ini file path</param>
        /// <returns>Result of GetPrivateProfileInt</returns>
        private int readFile(string filepath)
        {
            return (int)GetPrivateProfileInt("COMMON", "RADIOBUTTON", 0, filepath);             // Win32API
        }

        /// <summary>
        /// write the ini file
        /// </summary>
        /// <param name="filepath">ini file path</param>
        /// <param name="value">value</param>
        /// <returns>Result of WritePrivateProfileString</returns>
        private bool writeFile(string filepath, int value)
        {
            return WritePrivateProfileString("COMMON", "RADIOBUTTON", value.ToString(), filepath);   // Win32API
        }
    }
}