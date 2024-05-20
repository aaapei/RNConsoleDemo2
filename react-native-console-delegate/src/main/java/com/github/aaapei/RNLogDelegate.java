package com.github.aaapei;

public interface RNLogDelegate {
     void d(String tag, String msg);
     void w(String tag, String msg);
     void i(String tag, String msg);
     void e(String tag, String msg);
     void v(String tag, String msg);
}
