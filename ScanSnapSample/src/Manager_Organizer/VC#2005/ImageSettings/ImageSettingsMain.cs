//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

using System;
using System.IO;
using System.Windows.Forms;

namespace ImageSettings
{
    static class ImageSettingsMain
    {
        public static string iniFilePath;           // for save

        /// <summary>
        /// Entry point
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            // Get args
            if (args.Length < 2 || File.Exists(args[1]) == false)
            {
                iniFilePath = null;
            }
            else
            {
                iniFilePath = args[1];
            }

            Application.Run(new FormImageSettings());
        }
    }
}