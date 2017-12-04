
// 基于 sessionStorage 实现的浏览器 key-value 存储接口

function getString(key) {
  return sessionStorage.getItem(key);
}

function setString(key, value) {
  sessionStorage.setItem(key, value);
}

function getObject(key) {
  var value = getString(key);
  if (value) {
    return JSON.parse(value);
  } else {
    return null;
  }
}

function setObject(key, value) {
  if (value) {
    sessionStorage.setItem(key, JSON.stringify(value));
  }
}

// 删除 key 对应的存储数据
function removeItem(key) {
  sessionStorage.removeItem(key);
}

// 删除所有存储数据
function clear() {
  sessionStorage.clear();
}
