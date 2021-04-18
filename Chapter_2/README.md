# 第二章介绍

* ProcessDemo
  * CreateProcess 创建进程

* NtProcessDemo
  * 获取 PCB（Process Control Block）数据
  * 加载库，获取库的函数地址：LoadLibrary/GetProcAddress
  * 调用函数 QueryInformationProces 获取 PCB 数据

* IPCDemo / IPCWorker
  * 创建两个进程，两个进程通过一个mutex访问一个文件映射对象
  * CreateMutex 创建 mutex
  * CreateFileMapping 创建文件映射, MapViewOfFile, UnmapViewOfFile 读取内容
  * CloseHandle 删除 mutex 和 filemapping
  * OpenMutex 获得 mutex, OpenFileMapping 获得文件映射
  * 通过文件映射在进程之间传递数据

* PhilosophersDinner / Philosopher --- 哲学家问题
  * 通过信号同步多个进程
  * CreateSemaphore 创建信号， 这里使用两个信号， 最多有两个哲学家可以吃饭
  * WaitForMultipleObjects 可以等待其他进程或其它对象结束
  * CloseHandle 关闭进程或信号等其他对象句柄
  * WM_SETFONT 可设置一个控件的字体
  * CreateSolidBrush 创建笔刷，Ellipse 绘制椭圆
  * GetConsoleWindow 获取控制台窗口，ShowWindow 可用于隐藏控制台窗口
  * OpenSemaphore 打开信号, ReleaseSemaphore 释放信号

* MultithreadedArraySort --- 通过多线程排序数组
  * CreateThread 创建线程

* ConcurrentFileCopy --- 多线程拷贝文件
  * CreateWindow 创建控件 BS_PUSHBUTTON， PROGRESS_CLASS 进度条
  * OPENFILENAMEW，GetOpenFileName 打开文件对话框，GetSaveFileName 保存文件对话框
  * CreateFile 打开文件, 包括读写文件
  * PBM_SETRANGE 控制进度条进度消息
  * 主要实现逐块读取文件并逐块写入文件, 通过两个线程控制,一个读取线程一个写入线程.
  * LocalAlloc / LocalFree 分配和释放
  * ReadFile / WriteFile 读写文件