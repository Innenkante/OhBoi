using ScintillaNET;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;

namespace LoaderUi
{
    class Editor
    {
        private ScintillaNET.Scintilla _codeArea;
        private AutocompleteMenuNS.AutocompleteMenu _autocompleteMenu;


        private string _keywordFile = "langDef.json";
        private KeywordCollection _autocompleteItems;

        public Editor(ScintillaNET.Scintilla editor, AutocompleteMenuNS.AutocompleteMenu autocomplete)
        {
            _codeArea = editor;

            _codeArea.CharAdded += (sender, e) =>
            {
                var currentPos = _codeArea.CurrentPosition;
                InsertMatchedChars(e);

                _autocompleteItems.RefreshWords();
                if(e.Char == 32)
                {
                    var lastWord = _codeArea.GetWordFromPosition(currentPos - 1);
                    _autocompleteItems.AddWord(lastWord);
                }
                if(e.Char == 13)
                {
                    var lastWord = _codeArea.GetWordFromPosition(currentPos - 3);
                    _autocompleteItems.AddWord(lastWord);
                }
            };

            _autocompleteMenu = autocomplete;
        }

        //stolen from https://github.com/jacobslusser/ScintillaNET/wiki/Character-Autocompletion#finishing-touch
        private void InsertMatchedChars(CharAddedEventArgs e)
        {
            var caretPos = _codeArea.CurrentPosition;
            var docStart = caretPos == 1;
            var docEnd = caretPos == _codeArea.Text.Length;

            var charPrev = docStart ? _codeArea.GetCharAt(caretPos) : _codeArea.GetCharAt(caretPos - 2);
            var charNext = _codeArea.GetCharAt(caretPos);

            var isCharPrevBlank = charPrev == ' ' || charPrev == '\t' ||
                                  charPrev == '\n' || charPrev == '\r';

            var isCharNextBlank = charNext == ' ' || charNext == '\t' ||
                                  charNext == '\n' || charNext == '\r' ||
                                  docEnd;

            var isEnclosed = (charPrev == '(' && charNext == ')') ||
                                  (charPrev == '{' && charNext == '}') ||
                                  (charPrev == '[' && charNext == ']');

            var isSpaceEnclosed = (charPrev == '(' && isCharNextBlank) || (isCharPrevBlank && charNext == ')') ||
                                  (charPrev == '{' && isCharNextBlank) || (isCharPrevBlank && charNext == '}') ||
                                  (charPrev == '[' && isCharNextBlank) || (isCharPrevBlank && charNext == ']');

            var isCharOrString = (isCharPrevBlank && isCharNextBlank) || isEnclosed || isSpaceEnclosed;

            var charNextIsCharOrString = charNext == '"' || charNext == '\'';

            switch (e.Char)
            {
                case '(':
                    if (charNextIsCharOrString) return;
                    _codeArea.InsertText(caretPos, ")");
                    break;
                case '{':
                    if (charNextIsCharOrString) return;
                    _codeArea.InsertText(caretPos, "}");
                    break;
                case '[':
                    if (charNextIsCharOrString) return;
                    _codeArea.InsertText(caretPos, "]");
                    break;
                case '"':
                    // 0x22 = "
                    if (charPrev == 0x22 && charNext == 0x22)
                    {
                        _codeArea.DeleteRange(caretPos, 1);
                        _codeArea.GotoPosition(caretPos);
                        return;
                    }

                    if (isCharOrString)
                        _codeArea.InsertText(caretPos, "\"");
                    break;
                case '\'':
                    // 0x27 = '
                    if (charPrev == 0x27 && charNext == 0x27)
                    {
                        _codeArea.DeleteRange(caretPos, 1);
                        _codeArea.GotoPosition(caretPos);
                        return;
                    }

                    if (isCharOrString)
                        _codeArea.InsertText(caretPos, "'");
                    break;
            }
        }

        private void InitializeSurface()
        {
            _codeArea.StyleResetDefault();

            _codeArea.Styles[ScintillaNET.Style.Default].Font = "Lucida Console";
            _codeArea.Styles[ScintillaNET.Style.Default].Size = 12;
            _codeArea.Styles[ScintillaNET.Style.Default].BackColor = Color.FromArgb(32, 32, 32);
            _codeArea.Styles[ScintillaNET.Style.Default].ForeColor = Color.FromArgb(255, 255, 255);

            _codeArea.StyleClearAll();

            _codeArea.Styles[ScintillaNET.Style.LineNumber].BackColor = Color.FromArgb(64, 64, 64);
            _codeArea.Styles[ScintillaNET.Style.LineNumber].ForeColor = Color.FromArgb(172, 176, 176);
            _codeArea.Styles[ScintillaNET.Style.IndentGuide].BackColor = Color.FromArgb(64, 64, 64);
            _codeArea.Styles[ScintillaNET.Style.IndentGuide].ForeColor = Color.FromArgb(0, 0, 204);

            var nums = _codeArea.Margins[1];
            nums.BackColor = Color.FromArgb(64, 64, 64);
            nums.Width = 30;
            nums.Type = MarginType.Number;
            nums.Sensitive = true;
            nums.Mask = 1;

            _codeArea.CaretForeColor = Color.White;
            _codeArea.CaretLineBackColor = Color.FromArgb(64, 64, 64);
        }

        private void InitializeLexer()
        {
            _codeArea.Lexer = ScintillaNET.Lexer.Cpp;

            _codeArea.Styles[ScintillaNET.Style.Cpp.Default].ForeColor = Color.DarkGray;
            _codeArea.Styles[ScintillaNET.Style.Cpp.Comment].ForeColor = Color.OliveDrab;
            _codeArea.Styles[ScintillaNET.Style.Cpp.CommentLine].ForeColor = Color.OliveDrab;
            _codeArea.Styles[ScintillaNET.Style.Cpp.CommentDoc].ForeColor = Color.OliveDrab;
            _codeArea.Styles[ScintillaNET.Style.Cpp.Word].ForeColor = Color.Aqua;
            _codeArea.Styles[ScintillaNET.Style.Cpp.String].ForeColor = Color.Yellow;
            _codeArea.Styles[ScintillaNET.Style.Cpp.Character].ForeColor = Color.Gold;
            _codeArea.Styles[ScintillaNET.Style.Cpp.Operator].ForeColor = Color.White;
            _codeArea.Styles[ScintillaNET.Style.Cpp.StringEol].ForeColor = Color.Yellow;
            _codeArea.Styles[ScintillaNET.Style.Cpp.Word2].ForeColor = Color.Orange;
            _codeArea.Styles[ScintillaNET.Style.Cpp.GlobalClass].ForeColor = Color.Crimson;
            _codeArea.Styles[ScintillaNET.Style.Cpp.StringRaw].ForeColor = Color.Yellow;
            _codeArea.Styles[ScintillaNET.Style.Cpp.HashQuotedString].ForeColor = Color.Yellow;
            _codeArea.Styles[ScintillaNET.Style.Cpp.Number].ForeColor = Color.SteelBlue;
        }

        private void InitializeKeywords()
        {
            var keywords = Newtonsoft.Json.JsonConvert.DeserializeObject<List<Keyword>>(System.IO.File.ReadAllText(_keywordFile));

            _codeArea.SetKeywords(0, String.Join(" ", keywords.Where(k => k.Category == 0).Select(k => k.Word)));
            _codeArea.SetKeywords(1, String.Join(" ", keywords.Where(k => k.Category == 1).Select(k => k.Word.Split('.')[1])));
            _codeArea.SetKeywords(3, String.Join(" ", keywords.Where(k => k.Category == 3).Select(k => k.IsMember ? k.Word.Split('.')[1] : k.Word)));

            _autocompleteItems = new KeywordCollection(_codeArea, keywords);

            _autocompleteMenu.SetAutocompleteItems(_autocompleteItems);
        }


        public void Initialize()
        {
            InitializeSurface();
            InitializeLexer();
            InitializeKeywords();
        }




    }
}
