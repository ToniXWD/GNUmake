# 2 Hello World开始
## 2.1 makefile基本格式
makefile file 选项：
makefile [-f file] [option] [target]
- -f 指定makefilefile文件名
- -v 显示版本号
- -n 只输出命令，不执行
- -s 只执行命令，不显示命令，可以使用@抑制命令输出
- -w 显示执行前后的路径
- -C dir 指定makefilefile所在目录

没有指定目标时默认使用第一个目标
## 2.2 案例
```makefile
a:
	gcc helloworld.c

clean:
	rm -rf *.out
	@echo "Remove success!"
```

```bash
# 执行makefile
(base) toni@DESKTOP-LJK8IAI:~/CSLearn/makefile/myProject/002$ makefile
gcc helloworld.c
# 执行makefile clean
(base) toni@DESKTOP-LJK8IAI:~/CSLearn/makefile/myProject/002$ makefile clean
rm -rf *.out
Remove success!
```


# 3 编译流程
## 3.1 简单的依赖关系的makefilefile格式：
- 目标1:依赖
- 		命令1
- 目标2:依赖
- 		命令2
- ……

```makefile
calc:add.o sub.o multi.o
	gcc add.o sub.o multi.o calc.c -o calc
add.o:add.c
	gcc -c add.c -o add.o
sub.o:sub.c
	gcc -c sub.c -o sub.o
multi.o:multi.c
	gcc -c multi.c -o multi.o
```
## 3.2 gcc简单回顾
gcc选项
- -lstdc++：编译cpp文件
- -E：预处理
- -S：编译，得到汇编代码文件，默认文件后缀为.s
- -c：汇编，得到二进制文件，默认文件后缀为.o，此时尚未进行链接

gcc编译单文件的步骤


# 4 变量
## 4.1 系统变量
- $* 不包括扩展名的目标文件名称
- $+ 所有的依赖文件，以空格分隔
- $< 表示规则中的第一个条件
- $? 所有时间戳比目标文件晚的依赖文件，以空格分隔
- $@ 目标文件的完整名称
- $^ 所有不重复的依赖文件，以空格分隔
- $% 如果目标是归档成员，则该变量表示目标的归档成员名称
## 4.2 系统常量（可用 makefile -p 查看）
- AS - 汇编程序的名称，默认为as
- CC C编译器名称，默认cc
- CPP C预编译器名称,默认cc-E
- CXX C++编译器名称，默认g++
- RM 文件删除程序别名，默认rm -f
## 4.3 自定义变量
### 4.3.1 用法
1. 定义：变量名=变量值
2. 使用$(变量名)/${变量名}

### 4.3.2 案例1
```makefile
OBJ=add.o sub.o multi.o calc.c
TARGET=calc

$(TARGET):$(OBJ)
	gcc $(OBJ) -o $(TARGET)
add.o:add.c
	gcc -c add.c -o add.o
sub.o:sub.c
	gcc -c sub.c -o sub.o
multi.o:multi.c
	gcc -c multi.c -o multi.o
clean:
	rm -rf *.o
	@echo "Remove success!"
```
### 4.3.3 案例2-改进1
利用系统变量 $^、$@ 简化
```makefile
OBJ=add.o sub.o multi.o calc.c
TARGET=calc

$(TARGET):$(OBJ)
	gcc $^ -o $@
add.o:add.c
	gcc -c $^ -o $@
sub.o:sub.c
	gcc -c $^ -o $@
multi.o:multi.c
	gcc -c $^ -o $@
clean:
	rm -rf *.o
	@echo "Remove success!"
```
### 4.3.4 案例3-改进2
利用系统常量简化,目的：跨平台
```makefile
OBJ=add.o sub.o multi.o calc.c
TARGET=calc

$(TARGET):$(OBJ)
	$(CC) $^ -o $@
add.o:add.c
	$(CC) -c $^ -o $@
sub.o:sub.c
	$(CC) -c $^ -o $@
multi.o:multi.c
	$(CC) -c $^ -o $@
clean:
	$(RM) *.o $(TARGET)
	@echo "Remove success!"
```


# 5 伪目标和模式匹配
## 5.1 伪目标
.PHONY:clean
- 声明目标为伪目标之后，makefilefile将不会判新目标是否存在或该目标是否需要更新

例如将clean设置为伪目标
```makefile
.PHONY:clean
```
## 5.2 模式匹配
格式：
- 模式匹配%目标:%依赖
- 目标和依赖相同部份,r可用%来通配

案例
```makefile
%.o:%.c
	$(CC) -c $^ -o $@
```
匹配所有以.o为后缀的目标，其依赖以.c为后缀

## 5.3 其他通配符
| 命令     |         用法案例          |                          作用 |
| :------- | :-----------------------: | ----------------------------: |
| wildcard |     $(wildcard ./*.c)     |    获取当前目录下所有的.c文件 |
| patsubst | $(patsubst %.c,%.o,./*.c) | 将对应的c文件名替换成.o文件名 |

用法案例：
```makefile
OBJ=$(patsubst %.c,%.o,$(wildcard ./*.c))
TARGET=calc

.PHONY:clean show

$(TARGET):$(OBJ)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) -c $^ -o $@
clean:
	$(RM) *.o $(TARGET)
	@echo "Remove success!"
```


# 5 Makefile运行流程
- 保证目标是用最新的依赖生成的
- 第一次全完编译，后面只编译最新的代码(部份编译)


# 6 Makefile 中编译动态链接库
## 6.1 动态链接库基本概念
- 动态链接库:不会把代码编译到二进制文件中，而是在运行时才去加载，所以只需要维护一个地址
- -fPIC 产生位置无关的代码
- -shared 共享
- -l(小写L) 指定动态库
- -I(大写I) 指定头文件目录，默认当前目录
- -L 手动指定库文件搜索目录，默认只链接共享目录

**动态链接库，好处是程序可以和库文件分离，可以分别发版，然后库文件可以被多处共享**

| 定义 |                                                       含义 |
| :--- | ---------------------------------------------------------: |
| 动态 |                                    运行时才去加载﹐动态加载 |
| 链接 | 指库文件和二进制程序分离，用某种特殊手段维护两者之间的关系 |
| 库   |                                              库文件.dll.so |

## 6.2 编译动态链接库
**g++/gcc编译动态链接库的指令:**
```bash
g++ -shared -fPIC SoTest.cpp -o libSoTest.so
g++ test.cpp -L . -l SoTest -o test

# 只发布testSoOutside.cpp和SoTest.h，编译时连接动态链接库
g++ testSoOutside.cpp -L ./SO -lSoTest -o test
```

## 6.3 运行时链接动态链接库
***按照上述流程，编译时指定了要依赖的动态库，但是运行时，找不到.so文件***
```shell
./test: error while loading shared libraries: libSoTest.so: cannot open shared object file: No such file or directory
```
**原因:系统搜索的动态库路径找不到对应动态链接库**
***Linux默认动态链接库路径***
- /usr/lib
- /usr/local/lib

***Linux默认动态链接库配置文件***
- /etc/ld.so.conf
- /etc/ld.so.conf.d/*.conf

**解决方案**
1. 复制.so文件到默认搜索路径
2. 运行时手动指定
   在LD_LIBRARY_PATH环境变量中加上库所在路径
   ```bash
   export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/toni/CSLearn/Make/myProject/SO
   ```

## 6.4 将编译动态链接库写入Makefile
```makefile
test:libSoTest.so
	$(CXX) test.cpp -o $@ -L . -l SoTest
libSoTest.so:SoTest.cpp
	$(CXX) -fPIC -shared $^ -o $@

.PHONY:clean

clean:
	$(RM) *.so test
```

# 7 makefile编译静态库
## 7.1 静态库的概念
- 静态链接库:会把库中的代码编译到二进制文件中，当程序编译完成后，该库文件可以删除而动态链接库不行，动态链接库必须与程序同时部署，还要保证程序能加载得到库文件
- 与动态库相比，静态库可以不用部署(己经被加载到程序里面了)，而且运行时速度更快(因为不用去加载)但是会导致程序体积更大，并且库中的内容如果有更新，则需要重新编译生成程序
- windows:.lib, linux:.a

## 7.2 命令行编译
```Cpp
// aTest.h
#ifndef INC_A_ATEST_H
#define INC_A_ATEST_H
class aTest{
    void func1();
};
#endif

// aTest.cpp
#include <iostream>
#include "aTest.h"
void aTest::func1(){
    printf("func1\n");
}
```
命令行输入如下命令编译静态库
```shell
(base) toni@DESKTOP-LJK8IAI:~/CSLearn/Make/myProject/A$ g++ -c aTest.cpp -o aTest.o
(base) toni@DESKTOP-LJK8IAI:~/CSLearn/Make/myProject/A$ ar -r libaTest.a aTest.o
ar: creating libaTest.a
```
在父级路径下新建文件夹，复制aTest.h与生成的libaTest.a，并新建main.cpp如下
```cpp
#include <iostream>
#include"aTest.h"
int main(){
    aTest a;
    a.func1();
}
```
**命令行输入如下命令在编译时使用静态库**
```shell
g++ main.cpp -o main -laTest -L ../A
```
删除libaTest.a后，main任然能运行

## 7.3 Makefile编译静态库
```makefile
TARGET=main
LDFLAGS=-L ../A
LIBS=-laTest

$(TARGET):main.cpp
	$(CXX) $^ -o $@ $(LIBS) $(LDFLAGS)

.PHONY:clean

clean:
	$(RM) $(TARGET)
```

# 8 Makefile中通用部份做公共头文件
## 8.1 语法
直接用include包含公用makefile
```makefile
include public_makefile_path
```
## 8.2 案例
新建myProject/public_Head文件夹，新建公共makefile文件如下
```makefile
# myProject/public_Head/makefile
SOURCE=$(wildcard ./*.cpp ./*.c)
OBJ=$(patsubst %.cpp, %.o, $(SOURCE))
OBJ:=$(patsubst %.c, %.o, $(OBJ))

.PHONY: clean

$(TARGET):$(OBJ)
	$(CXX) $^ -o $@

# %.o:%.cpp
#	gcc -c $^ -o $@
# 以上内容可以不写，makefile运行时会自动推导

clean:
	$(RM)  $(TARGET) $(OBJ)
```
新建myProject/public_Head_Reuse文件夹，新建公共x.cpp, y.cpp, z.cpp, makefile文件如下
```cpp
// x.cpp
#include<iostream>
void func1(){
    printf("func1-cpp\n");
}
// y.cpp
#include<iostream>
void func2(){
    printf("func2-cpp\n");
}
// z.cpp
extern void func1();
extern void func2();

#include<iostream>
int main(){
    func1();
    func2();
    return 0;
}
```
```makefile
# makefile
TARGET=c
include ../public_Head/makefile
```

新建myProject/public_Head_Reuse2文件夹，新建公共a.c, b.c, c.c, makefile文件如下
```c
// a.c
#include<stdio.h>
void func1(){
    printf("func1-cpp\n");
}
// b.c
#include<stdio.h>
void func2(){
    printf("func2-cpp\n");
}
// c.c
extern void func1();
extern void func2();

#include<stdio.h>
int main(){
    func1();
    func2();
    return 0;
}
```
```makefile
TARGET=c
include ../public_Head/makefile
```

- **public_Head_Reuse和public_Head_Reuse2两个项目共用了public_Head中的makefile**
- **该共用makefile可自动进行推导**

# 9 Makfile中为变量赋值
## 9.1 Makefile赋值逻辑
Makefile 中，都是先展开所有变量，再调用指令
|运算符|说明|
|:---|---|
|=|赋值，但是用终值，就是不管变量调用写在赋值前还是赋值后，调用时都是取终值|
|:=|也是赋值，但是只受当前行及之前的代码影响，而不会受后面的赋值影响|
## 9.2 用ifndef控制变量赋值
对于公共的makefile头文件，可以如下设置TARGET
```makefile
ifndef TARGET
TARGET:=test
endif

ifndef LDLIBS
LDLIBS:=
endif
```
引用公共头文件的makefile如下
```makefile
LDLIBS:=-lstdc++
include ../public_Head/makefile
$(TARGET):$(OBJ)
	$(CC) $(LDLIBS) $^ -o $@
```
将设置TARGET为test，且会根据当前makefile的指定是否添加gcc中c++的编译选项-lstdc++

