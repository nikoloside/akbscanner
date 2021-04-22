//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

using System;
using System.IO;
using System.Text;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Windows.Forms;

namespace CardConnections
{
    public partial class FormCardConnections : Form
    {
        [DllImport("User32.dll", EntryPoint = "SendMessage")]
        public static extern Int32 SendMessage(
                                            IntPtr hWnd,
                                            UInt32 Msg,
                                            UInt32 wParam,
                                            ref COPYDATASTRUCT lParam);

        [DllImport("kernel32.dll", EntryPoint = "GetPrivateProfileString")]
        public static extern Int32 GetPrivateProfileString(
                                            string lpAppName,
                                            string lpKeyName,
                                            string lpDefault,
                                            StringBuilder lpReturnedString,
                                            UInt32 nSize,
                                            string lpFileName);

        [DllImport("kernel32.dll", EntryPoint = "GetPrivateProfileInt")]
        public static extern UInt32 GetPrivateProfileInt(
                                            string lpAppName,
                                            string lpKeyName,
                                            Int32 nDefault,
                                            string lpFileName);

        /// <summary>
        /// COPYDATASTRUCT
        /// </summary>
        public struct COPYDATASTRUCT
        {
            public Int32 dwData;
            public Int32 cbData;
            public IntPtr lpData;
        }

        /// <summary>
        /// constructor
        /// </summary>
        public FormCardConnections()
        {
            InitializeComponent();

        }

        /// <summary>
        /// override
        /// </summary>
        /// <param name="winMessage">Windows message</param>
        protected override void WndProc(ref Message winMessage)
        {
            switch (winMessage.Msg)
            {
                // sendmessage
                case CardConnectionsMain.WM_COPYDATA:
                    string filePath;
                    int result = 1;         // success
                    try
                    {
                        CardConnectionsMain.COPYDATASTRUCT cds = new CardConnectionsMain.COPYDATASTRUCT();
                        Type cdsType = cds.GetType();
                        cds = (CardConnectionsMain.COPYDATASTRUCT)winMessage.GetLParam(cdsType);
                        filePath = cds.lpData;

                        // DeleteDataFolder
                        Directory.Delete(Path.GetDirectoryName(CardConnectionsMain.ResultFilePath), true);
                        CardConnectionsMain.ResultFilePath = filePath;

                        // DeleteTmpFolder
                        Directory.Delete(CardConnectionsMain.TempDirectory, true);
                        // create
                        Directory.CreateDirectory(CardConnectionsMain.TempDirectory);

                        // clear file list
                        listBox1.Items.Clear();

                        // copy file
                        CopyFile(filePath);
                    }
                    catch
                    {
                        // Please describe processing when the error occurs.
                        result = 0;         // failed
                    }
                    winMessage.Result = (IntPtr)result;
                    break;
                default:
                    break;
            }
            base.WndProc(ref winMessage);
        }

        /// <summary>
        /// Load
        /// </summary>
        private void FormCardConnections_Load(object sender, EventArgs e)
        {
            if (String.IsNullOrEmpty(CardConnectionsMain.ResultFilePath) == false)
            {
                try
                {
                    // copy file
                    CopyFile(CardConnectionsMain.ResultFilePath);
                }
                catch
                {
                    // Please describe processing when the error occurs.
                }
            }
        }

        /// <summary>
        /// Click button_Open
        /// </summary>
        private void button_Open_Click(object sender, EventArgs e)
        {
            string selectedFile;        // selected file name

            if (listBox1.SelectedItem != null)
            {
                selectedFile = CardConnectionsMain.TempDirectory.ToString() + @"\" + listBox1.SelectedItem.ToString();
                try
                {
                    Process.Start(selectedFile);
                }
                catch
                {
                    // No relation of the extension. 
                }
            }
        }

        /// <summary>
        /// Click button_Close
        /// </summary>
        private void button_Close_Click(object sender, EventArgs e)
        {
            Close();
        }

        /// <summary>
        /// analyze, and copy file
        /// </summary>
        /// <param name="resultFilePath">result file path</param>
        /// <returns>TRUE:SUCCESS,FALSE:ERROR</returns>
        private bool CopyFile(string resultFilePath)
        {
            int maxPath = 260;                  // MAXPATH
            StringBuilder returnedString = new StringBuilder(maxPath);

            UInt32 dataFileNum = GetPrivateProfileInt("FILES", "FileCount", 0, resultFilePath);     // Win32API
            if (dataFileNum == 0)
            {
                return false;
            }

            for (int i = 1; i <= dataFileNum; i++)
            {
                string keyName = "File" + i;
                string dataFilePath;
                string dataFileName;
                string destFileName;

                returnedString.Remove(0, returnedString.Length);
                GetPrivateProfileString("FILES", keyName, "", returnedString,
                                        (UInt32)(returnedString.Capacity), resultFilePath);         // Win32API
                dataFilePath = returnedString.ToString();
                dataFileName = Path.GetFileName(dataFilePath);
                destFileName = CardConnectionsMain.TempDirectory + @"\" + dataFileName;

                // Add to listBox
                listBox1.Items.Add(dataFileName);

                // copy data
                File.Copy(dataFilePath, destFileName);
            }
            return true;
        }

        /// <summary>
        /// DoubleClick
        /// </summary>
        private void listBox1_DoubleClick(object sender, EventArgs e)
        {
            button_Open_Click(sender, e);
        }
    }
}