using ScintillaNET;
using System;
using System.Collections.Generic;
using System.Linq;

namespace LoaderUi
{
    class Keyword
    {
        public int Category { get; set; }
        public string Word { get; set; }
        public bool IsMember { get; set; }
    }


    class KeywordCollection : IEnumerable<AutocompleteMenuNS.AutocompleteItem>
    {
        private ScintillaNET.Scintilla _tb;
        private List<Keyword> _keywords;
        private List<string> _words = new List<string>();

        private bool IsWordRelevant(string word)
        {
            _tb.TargetStart = 0;
            _tb.TargetEnd = _tb.TextLength;
            _tb.SearchFlags = SearchFlags.WholeWord;

            if (_tb.SearchInTarget(word) != -1)
                return true;
            else
                return false;
        }

        public void RefreshWords()
        {
            _words.RemoveAll(s => !IsWordRelevant(s));
        }

        public void AddWord(string word)
        {
            if (_keywords.Find(k => k.Word == word) == null && !_words.Contains(word))
                _words.Add(word);
        }

        public KeywordCollection(Scintilla tb, List<Keyword> source)
        {
            _tb = tb;
            _keywords = source;

            _tb.WordChars = _tb.WordChars + ".";
        }

        public IEnumerator<AutocompleteMenuNS.AutocompleteItem> GetEnumerator()
        {
            return BuildList().GetEnumerator();
        }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        private IEnumerable<AutocompleteMenuNS.AutocompleteItem> BuildList()
        {
            var startPosition = _tb.WordStartPosition(_tb.CurrentPosition, false);

            var currentWord = _tb.GetWordFromPosition(startPosition);

            if (currentWord.Contains("."))
            {
                foreach (var word in _keywords.Where(k => k.Word.StartsWith(currentWord)))// || k.Word.StartsWith("any.")))
                    yield return new AutocompleteMenuNS.MethodAutocompleteItem(word.Word.Split('.')[1]);

                if (_words.Contains(currentWord.Trim('.')))
                    foreach (var word in _keywords.Where(k => k.Word.StartsWith("any.")))
                        yield return new AutocompleteMenuNS.MethodAutocompleteItem(word.Word.Split('.')[1]);

            }
            else
            {
                foreach (var word in _keywords.Where(k => k.Word.StartsWith(currentWord) && !k.Word.Contains(".")))
                {
                    yield return new AutocompleteMenuNS.AutocompleteItem(word.Word);
                }

                foreach (var word in _words.Where(w => w.StartsWith(currentWord)))
                {
                    yield return new AutocompleteMenuNS.AutocompleteItem(word);
                }
            }
        }
    }
}