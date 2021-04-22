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
using System.Threading;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace ImageConnections
{
    static class ImageConnectionsMain
    {
        public static string ResultFilePath;           // Full path of result file
        public static string TempDirectory;             // Temporary directory
        public const Int32 WM_COPYDATA = 0x4A;          // Value of WM_COPYDATA

        private static Mutex mutex;                     // Mutex

        // DllImport
        [DllImport("USER32.dll", EntryPoint = "FindWindow")]
        public static extern IntPtr FindWindow(
                                            string lpClassName,
                                            string lpWindowName);         

        [DllImport("User32.dll", EntryPoint = "SendMessage")]
        public static extern Int32 SendMessage(
                                            IntPtr hWnd,
                                            UInt32 Msg,
                                            UInt32 wParam,
                                            ref COPYDATASTRUCT lParam);

        //COPYDATASTRUCT
        public struct COPYDATASTRUCT
        {
            public Int32 dwData;
            public Int32 cbData;
            public string lpData;
        }


        /// <summary>
        /// Entry point
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            // Get args
            if (args.Length == 0)
            {
                // no args
                ResultFilePath = null;
            }
            else
            {
                ResultFilePath = args[0];
            }

            // Create  temporary directory
            string tempPath = Path.GetTempPath();
            TempDirectory = tempPath + "ScanSnapSample";
            if (Directory.Exists(TempDirectory) == false)
            {
                try
                {
                    // create
                    Directory.CreateDirectory(TempDirectory);
                }
                catch
                {
                    return;
                }
            }
            
            mutex = new Mutex(false, "ImageConnections");

            // Demand Mutex
            if (mutex.WaitOne(0, false) == false)
            {
                // Process exist

                if (args.Length == 0)
                {
                    return;
                }

                string windowName = "Image Connections";                        // todo: Please update Window Title
                IntPtr hwnd = FindWindow(null, windowName);                     // Win32API    
                if (hwnd != IntPtr.Zero)
                {
                    // SendMessage COPYDATA
                    Int32 len = Encoding.Default.GetByteCount(ResultFilePath);
                    COPYDATASTRUCT cds;
                    cds.dwData = 0;
                    cds.lpData = ResultFilePath;
                    cds.cbData = len + 1;

                    SendMessage(hwnd, WM_COPYDATA, 0, ref cds);                 // Win32API
                }

                // Close Mutex
                mutex.Close();

                return;
            }


            // Show form
            Application.Run(new FormImageConnections());

            try
            {
                // DeleteTmpFolder
                Directory.Delete(TempDirectory, true);    // all delete
            }
            catch
            {
                // Please describe processing when the error occurs.
            }

            // Close Mutex
            mutex.Close();
        }
    }
}