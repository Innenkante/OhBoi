namespace LoaderUi
{
    partial class Ui
    {
        /// <summary>
        /// Erforderliche Designervariable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Verwendete Ressourcen bereinigen.
        /// </summary>
        /// <param name="disposing">True, wenn verwaltete Ressourcen gelöscht werden sollen; andernfalls False.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Vom Windows Form-Designer generierter Code

        /// <summary>
        /// Erforderliche Methode für die Designerunterstützung.
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Ui));
            this.CodeArea = new ScintillaNET.Scintilla();
            this.AutoComplete = new AutocompleteMenuNS.AutocompleteMenu();
            this.LogTextbox = new MetroFramework.Controls.MetroTextBox();
            this.SaveFileButton = new MetroFramework.Controls.MetroButton();
            this.LoadButton = new MetroFramework.Controls.MetroButton();
            this.SelectExecutableButton = new MetroFramework.Controls.MetroButton();
            this.ExecutablePathTextbox = new MetroFramework.Controls.MetroTextBox();
            this.LoadOnEntryPointCheckbox = new MetroFramework.Controls.MetroCheckBox();
            this.ReloadFile = new MetroFramework.Controls.MetroButton();
            this.RunExecutable = new MetroFramework.Controls.MetroButton();
            this.SuspendLayout();
            // 
            // CodeArea
            // 
            this.CodeArea.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.CodeArea.CaretForeColor = System.Drawing.Color.White;
            this.CodeArea.CaretLineBackColor = System.Drawing.Color.DimGray;
            this.CodeArea.CaretLineVisible = true;
            this.CodeArea.Lexer = ScintillaNET.Lexer.Cpp;
            this.CodeArea.Location = new System.Drawing.Point(23, 146);
            this.CodeArea.Name = "CodeArea";
            this.CodeArea.Size = new System.Drawing.Size(1246, 573);
            this.CodeArea.TabIndex = 10;
            this.CodeArea.Text = "//your code here";
            this.CodeArea.UseTabs = true;
            // 
            // AutoComplete
            // 
            this.AutoComplete.Colors = ((AutocompleteMenuNS.Colors)(resources.GetObject("AutoComplete.Colors")));
            this.AutoComplete.Font = new System.Drawing.Font("Lucida Console", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.AutoComplete.ImageList = null;
            this.AutoComplete.Items = new string[0];
            this.AutoComplete.MinFragmentLength = 1;
            this.AutoComplete.TargetControlWrapper = null;
            this.AutoComplete.ToolTipDuration = 0;
            // 
            // LogTextbox
            // 
            this.LogTextbox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            // 
            // 
            // 
            this.LogTextbox.CustomButton.Image = null;
            this.LogTextbox.CustomButton.Location = new System.Drawing.Point(1057, 2);
            this.LogTextbox.CustomButton.Name = "";
            this.LogTextbox.CustomButton.Size = new System.Drawing.Size(73, 73);
            this.LogTextbox.CustomButton.Style = MetroFramework.MetroColorStyle.Blue;
            this.LogTextbox.CustomButton.TabIndex = 1;
            this.LogTextbox.CustomButton.Theme = MetroFramework.MetroThemeStyle.Light;
            this.LogTextbox.CustomButton.UseSelectable = true;
            this.LogTextbox.CustomButton.Visible = false;
            this.LogTextbox.Lines = new string[0];
            this.LogTextbox.Location = new System.Drawing.Point(23, 725);
            this.LogTextbox.MaxLength = 32767;
            this.LogTextbox.Multiline = true;
            this.LogTextbox.Name = "LogTextbox";
            this.LogTextbox.PasswordChar = '\0';
            this.LogTextbox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.LogTextbox.SelectedText = "";
            this.LogTextbox.SelectionLength = 0;
            this.LogTextbox.SelectionStart = 0;
            this.LogTextbox.ShortcutsEnabled = true;
            this.LogTextbox.Size = new System.Drawing.Size(1246, 78);
            this.LogTextbox.TabIndex = 11;
            this.LogTextbox.UseCustomBackColor = true;
            this.LogTextbox.UseCustomForeColor = true;
            this.LogTextbox.UseSelectable = true;
            this.LogTextbox.WaterMarkColor = System.Drawing.Color.FromArgb(((int)(((byte)(109)))), ((int)(((byte)(109)))), ((int)(((byte)(109)))));
            this.LogTextbox.WaterMarkFont = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Pixel);
            // 
            // SaveFileButton
            // 
            this.SaveFileButton.Location = new System.Drawing.Point(266, 78);
            this.SaveFileButton.Name = "SaveFileButton";
            this.SaveFileButton.Size = new System.Drawing.Size(237, 28);
            this.SaveFileButton.TabIndex = 17;
            this.SaveFileButton.Text = "Save file";
            this.SaveFileButton.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.SaveFileButton.UseSelectable = true;
            this.SaveFileButton.Click += new System.EventHandler(this.SaveFileButton_Click);
            // 
            // LoadButton
            // 
            this.LoadButton.Location = new System.Drawing.Point(509, 111);
            this.LoadButton.Name = "LoadButton";
            this.LoadButton.Size = new System.Drawing.Size(224, 28);
            this.LoadButton.TabIndex = 15;
            this.LoadButton.Text = "Load";
            this.LoadButton.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.LoadButton.UseSelectable = true;
            this.LoadButton.Click += new System.EventHandler(this.LoadButton_Click);
            // 
            // SelectExecutableButton
            // 
            this.SelectExecutableButton.Location = new System.Drawing.Point(23, 77);
            this.SelectExecutableButton.Name = "SelectExecutableButton";
            this.SelectExecutableButton.Size = new System.Drawing.Size(237, 28);
            this.SelectExecutableButton.TabIndex = 13;
            this.SelectExecutableButton.Text = "Select an executable";
            this.SelectExecutableButton.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.SelectExecutableButton.UseSelectable = true;
            this.SelectExecutableButton.Click += new System.EventHandler(this.SelectExecutableButton_Click);
            // 
            // ExecutablePathTextbox
            // 
            // 
            // 
            // 
            this.ExecutablePathTextbox.CustomButton.Image = null;
            this.ExecutablePathTextbox.CustomButton.Location = new System.Drawing.Point(211, 2);
            this.ExecutablePathTextbox.CustomButton.Name = "";
            this.ExecutablePathTextbox.CustomButton.Size = new System.Drawing.Size(23, 23);
            this.ExecutablePathTextbox.CustomButton.Style = MetroFramework.MetroColorStyle.Blue;
            this.ExecutablePathTextbox.CustomButton.TabIndex = 1;
            this.ExecutablePathTextbox.CustomButton.Theme = MetroFramework.MetroThemeStyle.Light;
            this.ExecutablePathTextbox.CustomButton.UseSelectable = true;
            this.ExecutablePathTextbox.CustomButton.Visible = false;
            this.ExecutablePathTextbox.Enabled = false;
            this.ExecutablePathTextbox.FontSize = MetroFramework.MetroTextBoxSize.Medium;
            this.ExecutablePathTextbox.Lines = new string[] {
        "Executable"};
            this.ExecutablePathTextbox.Location = new System.Drawing.Point(23, 111);
            this.ExecutablePathTextbox.MaxLength = 32767;
            this.ExecutablePathTextbox.Multiline = true;
            this.ExecutablePathTextbox.Name = "ExecutablePathTextbox";
            this.ExecutablePathTextbox.PasswordChar = '\0';
            this.ExecutablePathTextbox.ScrollBars = System.Windows.Forms.ScrollBars.None;
            this.ExecutablePathTextbox.SelectedText = "";
            this.ExecutablePathTextbox.SelectionLength = 0;
            this.ExecutablePathTextbox.SelectionStart = 0;
            this.ExecutablePathTextbox.ShortcutsEnabled = true;
            this.ExecutablePathTextbox.Size = new System.Drawing.Size(237, 28);
            this.ExecutablePathTextbox.TabIndex = 20;
            this.ExecutablePathTextbox.Text = "Executable";
            this.ExecutablePathTextbox.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.ExecutablePathTextbox.UseSelectable = true;
            this.ExecutablePathTextbox.WaterMarkColor = System.Drawing.Color.FromArgb(((int)(((byte)(109)))), ((int)(((byte)(109)))), ((int)(((byte)(109)))));
            this.ExecutablePathTextbox.WaterMarkFont = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Pixel);
            // 
            // LoadOnEntryPointCheckbox
            // 
            this.LoadOnEntryPointCheckbox.AutoSize = true;
            this.LoadOnEntryPointCheckbox.FontSize = MetroFramework.MetroCheckBoxSize.Medium;
            this.LoadOnEntryPointCheckbox.Location = new System.Drawing.Point(739, 78);
            this.LoadOnEntryPointCheckbox.Name = "LoadOnEntryPointCheckbox";
            this.LoadOnEntryPointCheckbox.Size = new System.Drawing.Size(143, 19);
            this.LoadOnEntryPointCheckbox.TabIndex = 21;
            this.LoadOnEntryPointCheckbox.Text = "Load on entrypoint";
            this.LoadOnEntryPointCheckbox.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.LoadOnEntryPointCheckbox.UseSelectable = true;
            // 
            // ReloadFile
            // 
            this.ReloadFile.Location = new System.Drawing.Point(266, 111);
            this.ReloadFile.Name = "ReloadFile";
            this.ReloadFile.Size = new System.Drawing.Size(237, 28);
            this.ReloadFile.TabIndex = 24;
            this.ReloadFile.Text = "Reload file";
            this.ReloadFile.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.ReloadFile.UseSelectable = true;
            this.ReloadFile.Click += new System.EventHandler(this.ReloadFile_Click);
            // 
            // RunExecutable
            // 
            this.RunExecutable.Location = new System.Drawing.Point(509, 78);
            this.RunExecutable.Name = "RunExecutable";
            this.RunExecutable.Size = new System.Drawing.Size(224, 28);
            this.RunExecutable.TabIndex = 25;
            this.RunExecutable.Text = "Run executable";
            this.RunExecutable.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.RunExecutable.UseSelectable = true;
            this.RunExecutable.Click += new System.EventHandler(this.RunExecutable_Click);
            // 
            // Ui
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1292, 826);
            this.Controls.Add(this.RunExecutable);
            this.Controls.Add(this.ReloadFile);
            this.Controls.Add(this.LoadOnEntryPointCheckbox);
            this.Controls.Add(this.ExecutablePathTextbox);
            this.Controls.Add(this.SaveFileButton);
            this.Controls.Add(this.SelectExecutableButton);
            this.Controls.Add(this.LoadButton);
            this.Controls.Add(this.LogTextbox);
            this.Controls.Add(this.CodeArea);
            this.ForeColor = System.Drawing.SystemColors.ControlText;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Ui";
            this.Style = MetroFramework.MetroColorStyle.Silver;
            this.Text = "OhBoi";
            this.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.Load += new System.EventHandler(this.Ui_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private ScintillaNET.Scintilla CodeArea;
        private AutocompleteMenuNS.AutocompleteMenu AutoComplete;
        private MetroFramework.Controls.MetroTextBox LogTextbox;
        private MetroFramework.Controls.MetroButton SaveFileButton;
        private MetroFramework.Controls.MetroButton LoadButton;
        private MetroFramework.Controls.MetroButton SelectExecutableButton;
        private MetroFramework.Controls.MetroTextBox ExecutablePathTextbox;
        private MetroFramework.Controls.MetroCheckBox LoadOnEntryPointCheckbox;
        private MetroFramework.Controls.MetroButton ReloadFile;
        private MetroFramework.Controls.MetroButton RunExecutable;
    }
}

