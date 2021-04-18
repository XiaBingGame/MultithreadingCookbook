# 第是三章介绍

* basic_MPI
  * WM_SETFONT 设置一个窗口的字体
  * SetWindowText 设置窗口文本
  * CreateWindow 里面可以设置按钮ID, 有 "BUTTON", "STATIC" 控件
  * WM_MOUSEMOVE 消息
  * 预定义宏 GET_X_LPARAM, GET_Y_LPARAM

* queue_MPI
  * PostMessage
  * 关键代码段 EnterCriticalSection / LeaveCriticalSection

* threadMPI
  * 在线程里面处理消息
  * peekMessage 为线程创建消息队列
  * PostThreadMessage 给线程发送消息

* pipe_server/pipe_client
  * CreateNamedPipe 创建管道, 格式 "\\.\pipe\管道名"
  * 服务器连接 ConnectNamedPipe
  * ReadFile / WriteFile 读写管道.
  * 客户端打开管道 CreateFile / CallNamedPipe
  * WaitNamedPipe 等待服务端准备好

