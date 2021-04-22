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

namespace CardSettings
{
    static class CardSettingsMain
    {
        /// <summary>
        /// Entry point
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new FormCardSettings());
        }
    }
}