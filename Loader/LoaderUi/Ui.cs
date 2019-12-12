using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;
using MemoryUtilities;
using ScintillaNET;
using System.Threading;

namespace LoaderUi
{
    public partial class Ui : MetroFramework.Forms.MetroForm
    {
        public string SelectedExecutable { get; set; }

        Loader _loader; 

        public void Log(string message)
        {
            LogTextbox.AppendText("[" + DateTime.Now.ToLongTimeString() + "]::" + message + Environment.NewLine);
        }

        public Ui()
        {
            InitializeComponent();
            Log("Initialized the Ui...");

            new Editor(CodeArea, AutoComplete).Initialize();


            Paint += (s, e) =>
            {
                e.Graphics.FillRectangle(new System.Drawing.Drawing2D.HatchBrush(System.Drawing.Drawing2D.HatchStyle.Percent50, TransparencyKey), DisplayRectangle);
            };
        }

        private void Ui_Load(object sender, EventArgs e)
        {
            AutoComplete.TargetControlWrapper = new ScintillaWrapper(CodeArea);
            LogTextbox.BackColor = Color.FromArgb(32, 32, 32);
            LogTextbox.ForeColor = Color.FromArgb(255, 255, 255);
        }

        private void LoadButton_Click(object sender, EventArgs e)
        {
            if (_loader == null)
            {
                MessageBox.Show("Run the process first...", "OhBoi");
                return;
            }


            if(LoadOnEntryPointCheckbox.Checked)
            {
                _loader.ResumeProcess();

                Log("Resumed " + SelectedExecutable + "...");
            }
            else
            {
                if (_loader.LoadJavascriptRuntimeUnsuspended())
                {
                    Log("Loaded the javascript runtime successfully...");

                    Thread.Sleep(1000);

                    if (_loader.LoadJavascriptFileUnsuspended())
                        Log("Loaded the javascript file successfully");
                }
                else
                    Log("Failed to load the javascript runtime or file, please retry with administrator rights!");
            }

        }

        private void SelectExecutableButton_Click(object sender, EventArgs e)
        {
            Log("Choosing an executable...");
            OpenFileDialog openFileDialog = new OpenFileDialog
            {
                InitialDirectory = "C:\\",
                Filter = "Executable files (*.exe)|*.exe",
                RestoreDirectory = true,
                CheckFileExists = true,
                CheckPathExists = true
            };

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                SelectedExecutable = openFileDialog.FileName;
            }

            if (SelectedExecutable != null)
            {
                ExecutablePathTextbox.Text = Path.GetFileName(SelectedExecutable);

                if (File.Exists(Path.GetDirectoryName(SelectedExecutable) + "\\OhBoi.js"))
                {
                    CodeArea.Text = File.ReadAllText(Path.GetDirectoryName(SelectedExecutable) + "\\OhBoi.js");
                }
                else
                {
                    File.WriteAllText(Path.GetDirectoryName(SelectedExecutable) + "\\OhBoi.js", @"//yourcode");
                    CodeArea.Text = File.ReadAllText(Path.GetDirectoryName(SelectedExecutable) + "\\OhBoi.js");
                }
            }

        }

        private void SaveFileButton_Click(object sender, EventArgs e)
        {
            if(SelectedExecutable == null)
            {
                MessageBox.Show("Select an executable first...", "OhBoi");
                return;
            }

            File.WriteAllText(Path.GetDirectoryName(SelectedExecutable) + "\\OhBoi.js", CodeArea.Text);

            Log("File saved...");
        }

        private void RunExecutable_Click(object sender, EventArgs e)
        {
            if (SelectedExecutable != null)
            {
                _loader = new Loader(SelectedExecutable);

                if (LoadOnEntryPointCheckbox.Checked)
                {
                    _loader.RunProcessSuspended();
                    _loader.RedirectThread();
                }
                else
                {
                    _loader.RunProcessUnsuspended();
                }

                Log("Run " + SelectedExecutable + "...");
            }
            else
                MessageBox.Show("Select an executable first...");
        }

        private void HelpButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show("To be done....");
        }
    }
}
