

function enableLoading() {
  $('.loading').show();
  $('body').addClass('body-loading');
}

function disableLoading() {
  $('.loading').hide();
  $('body').removeClass('body-loading');
}

/**
* 带 Loading 界面的异步请求
* @param url: 请求API
* @param dic: 字典类型的参数，如果无填为 `{}`
* @param success_func: 成功时的回调函数, 参数为 API 返回值(字典)
* @param loading: 是否需要 loading 框，建议速度快的请求，不带 loading ，这样效果更好
 */
function ajaxPost(url, dic, success_func, loading) {
  loading = (typeof loading == 'undefined') ? true : false;
  $.ajax(url, {
    type: 'POST',
    data: dic,
    beforeSend: function() {
      if (loading) {
        enableLoading();
      }
    },
    complete: function() {
    },
    error: function(data) {
      if (loading) {
        disableLoading();
      }
      alert('服务器内部错误!');
    },
    success: function(data) {
      if (loading) {
        disableLoading();
      }
      success_func(data);
    }
  });
}

/**
* ajax上传文件
* @param url: 请求url
* @param form_data: FormData数据
* @param success_func: 成功时的回调 函数，参数为API返回值（字典）
* @param loading: 是否需要loading框
 */
function ajaxPostFile(url, form_data, success_func, loading) {
  loading = (typeof loading == 'undefined') ? true : false;
  $.ajax(url, {
    type: 'POST',
    data: form_data,
    beforeSend: function() {
      if (loading) {
        enableLoading();
      }
    },
    complete: function() {
    },
    error: function(data) {
      if (loading) {
        disableLoading();
      }
      alert('服务器内部错误!');
    },
    success: function(data) {
      if (loading) {
        disableLoading();
      }
      success_func(data);
    },
    contentType: false,
    processData: false,
    cache: false
  });
}
