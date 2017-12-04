
// select2 匹配时支持空格? 自定义 matcher 函数.
// 注意：select2 的最新版本V4和旧版本V3 matcher 逻辑不一样，这里只是针对最新版本的。
function matchWords(term, text) {
  var m = term.term;
  if (m === undefined) {
    return text;
  }
  var full = text.text.toLowerCase();
  var words = m.split(' ');
  for (var i in words) {
    if (full.indexOf(words[i].toLowerCase()) < 0) {
      return null;
    }
  }
  return text;
}

// 使用
$().select2({
  matcher: base.matchWords
});
