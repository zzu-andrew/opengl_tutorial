## `Hello opengl`

![OpenGL Logo](image/opengl.jpg)

### 往期文章链接汇总

[github源码仓库](https://github.com/zzu-andrew/opengl_tutorial)

[opengl环境准备](https://wangyazhou.blog.csdn.net/article/details/112717440)

[opengl编程从入门到精通-hello,window](https://wangyazhou.blog.csdn.net/article/details/112723441)





### 前置知识

1. 全文使用`C++`实现，要有一定的`C++`基础，但你并不非得是一个`C++`专家
2. 线性代数
3. 几何
4. 三角学

在开始这段旅程之前我们先了解一下`OpenGL`到底是什么。一般它被认为是一个`API`(`Application Programming Interface,` 应用程序编程接口)，包含了一系列可以操作图形、图像的函数。然而，`OpenGL`本身并不是一个`API`，它仅仅是一个由`[Khronos`组织](http://www.khronos.org/)制定并维护的规范(`Specification`)。

### 安装`OpenGL`

网上教程有很多，这个自行百度，我这里是在`Linux`上进行的，只需要使用

```bash
sudo apt-get install build-essential libgl1-mesa-dev
sudo apt-get install freeglut3-dev
sudo apt-get install libglew-dev libsdl2-dev libsdl2-image-dev libglm-dev libfreetype6-dev
```

### 构建`GLFW`

地址：

[GLDW]: https://www.glfw.org/download.html	"opengl-glfw"



### 用`GLAD`简化`OpenGL`



使用`GLAD`简化`OpenGL`，这里我已经构建好了，要是想省事就直接下载就行了

链接: https://pan.baidu.com/s/1TmtM7O8J4aTnfP6elIgs7g  密码: g5go



### 窗口

>  请确认是在包含`GLFW`的头文件之前包含了`GLAD`的头文件。`GLAD`的头文件包含了正确的`OpenGL`头文件（例如`GL/gl.h`），所以需要在其它依赖于`OpenGL`的头文件之前包含GLAD。

1. 进行任何事之前先初始化`glfw`

初始化函数`glfwInit`

```cpp
// 对glfw进行初始化
glfwInit();
```

2. 版本的命中和版本信息的获取(非必须)

```cpp
// 打印出glfw的版本信息
//    int* major, int* minor, int* rev
int major, minor, rev;
glfwGetVersion(&major, &minor, &rev);
cout << "major = " << major << " minor = " << minor << " rev = " << rev << endl;
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```

3. 创建窗口

```cpp
// glfw window creation
// glfw创建窗口
GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
if (window == nullptr)
{
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
}
// 为当前window设置上下文，每个线程只能设置一个，并且线程之间共用时，需要将当前线程设置为 non-current
glfwMakeContextCurrent(window);
```

`window`将在整个程序运行期间，用于维护窗口的上下文和状态，其实整个`glfw`就是一个大的状态机。

4. 窗口信息设置

```cpp
// 设置窗口大小的回调函数，当窗口大小改变时，会调用该函数调整串口的大小
// 注册窗口大小改变回调函数
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
```

5. 调用任何`opengl`函数之前，先使用`gladLoadGLLoader`加载`opengl`的函数指针

```cpp
// glad: load all OpenGL function pointers
// glad 会加载所有openGL函数指针，在调用任何opengl函数之前需要先初始化glad
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
    cout << "Failed to initialize GLAD" << std::endl;
    return -1;
}
```

6. 窗口渲染

```cpp
// render loop
// 循环绘图，防止窗口关闭
while (!glfwWindowShouldClose(window))
{
    // input
    // -----
    processInput(window);

    // Render color
    // 设置青清空屏幕需要使用的颜色， 更准确的来说，就是一个状态设置函数
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // 清空屏幕的颜色 -- 状态使用函数
    glClear(GL_COLOR_BUFFER_BIT);
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // 交换颜色缓冲区
    /*
         * 双缓冲(Double Buffer)
         * 应用程序使用单缓冲绘图时可能会存在图像闪烁的问题。
         * 这是因为生成的图像不是一下子被绘制出来的，而是按照从左到右，
         * 由上而下逐像素地绘制而成的。最终图像不是在瞬间显示给用户，
         * 而是通过一步一步生成的，这会导致渲染的结果很不真实。
         * 为了规避这些问题，我们应用双缓冲渲染窗口应用程序。
         * 前缓冲保存着最终输出的图像，它会在屏幕上显示；
         * 而所有的的渲染指令都会在后缓冲上绘制。
         * 当所有的渲染指令执行完毕后，我们交换(Swap)前缓冲和后缓冲，
         * 这样图像就立即呈显出来，之前提到的不真实感就消除了。
         * */
    glfwSwapBuffers(window);
    // 检查有没有欻发手动事件，比如键盘输入，鼠标移动等
    glfwPollEvents();
}
```



两个函数的定义

```cpp
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    // 用户按下 esc键，就设置退出串口为真
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // opengl渲染串口大小，每次调整窗口
    cout << "view port call back" << endl;
    //
    glViewport(0, 0, width, height);
}

```

**完整代码实现**

```cpp
//
// Created by andrew on 2021/1/17.
//
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings C++ style
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // 对glfw进行初始化
    glfwInit();
    // 打印出glfw的版本信息
    //    int* major, int* minor, int* rev
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    cout << "major = " << major << " minor = " << minor << " rev = " << rev << endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // glfw创建窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 为当前window设置上下文，每个线程只能设置一个，并且线程之间共用时，需要将当前线程设置为 non-current
    glfwMakeContextCurrent(window);

    // 设置窗口大小的回调函数，当窗口大小改变时，会调用该函数调整串口的大小
    // 注册窗口大小改变回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // glad 会加载所有openGL函数指针，在调用任何opengl函数之前需要先初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // render loop
    // 循环绘图，防止窗口关闭
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // Render color
        // 设置青清空屏幕需要使用的颜色， 更准确的来说，就是一个状态设置函数
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清空屏幕的颜色 -- 状态使用函数
        glClear(GL_COLOR_BUFFER_BIT);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // 交换颜色缓冲区
        /*
         * 双缓冲(Double Buffer)
         * 应用程序使用单缓冲绘图时可能会存在图像闪烁的问题。
         * 这是因为生成的图像不是一下子被绘制出来的，而是按照从左到右，
         * 由上而下逐像素地绘制而成的。最终图像不是在瞬间显示给用户，
         * 而是通过一步一步生成的，这会导致渲染的结果很不真实。
         * 为了规避这些问题，我们应用双缓冲渲染窗口应用程序。
         * 前缓冲保存着最终输出的图像，它会在屏幕上显示；
         * 而所有的的渲染指令都会在后缓冲上绘制。
         * 当所有的渲染指令执行完毕后，我们交换(Swap)前缓冲和后缓冲，
         * 这样图像就立即呈显出来，之前提到的不真实感就消除了。
         * */
        glfwSwapBuffers(window);
        // 检查有没有欻发手动事件，比如键盘输入，鼠标移动等
        glfwPollEvents();
    }

    // 正确的释放之前分配的所有资源
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    // 用户按下 esc键，就设置退出串口为真
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // opengl渲染串口大小，每次调整窗口
    cout << "view port call back" << endl;
    //
    glViewport(0, 0, width, height);
}
```

### 三角形

绘图中需要牢记下面这几个单词

- 顶点数组对象：`Vertex Array Object, VAO`
- 顶点缓冲对象：`Vertex Buffer Object, VBO`
- 索引缓冲区：`Element Buffer Object, EBO或Index Buffer Object, IBO`

> 在`OpenGL`中，任何事物都在`3D`空间中，而屏幕和窗口却是`2D`像素数组，这导致`OpenGL`的大部分工作都是关于把`3D`坐标转变为适应你屏幕的`2D`像素。`3D`坐标转为`2D`坐标的处理过程是由`OpenGL`的图形渲染管线（Graphics Pipeline，大多译为管线，实际上指的是一堆原始图形数据途经一个输送管道，期间经过各种变化处理最终出现在屏幕的过程）管理的。图形渲染管线可以被划分为两个主要部分：第一部分把你的`3D`坐标转换为`2D`坐标，第二部分是把`2D`坐标转变为实际的有颜色的像素。这个教程里，我们会简单地讨论一下图形渲染管线，以及如何利用它创建一些漂亮的像素。

> 图形渲染管线接受一组`3D`坐标，然后把它们转变为你屏幕上的有色`2D`像素输出。图形渲染管线可以被划分为几个阶段，每个阶段将会把前一个阶段的输出作为输入。所有这些阶段都是高度专门化的（它们都有一个特定的函数），并且很容易并行执行。正是由于它们具有并行执行的特性，当今大多数显卡都有成千上万的小处理核心，它们在`GPU`上为每一个（渲染管线）阶段运行各自的小程序，从而在图形渲染管线中快速处理你的数据。这些小程序叫做着色器(Shader)。

> `OpenGL`着色器是用`OpenGL`着色器语言(`OpenGL` Shading Language, `GLSL`)写成的，在下一节中我们再花更多时间研究它。

#### 顶点的输入

想绘制一个图形，肯定得给出图像的坐标点，这里我们直接给出的坐标点就是标准化之后的坐标点，所以在设置向量属性的时候，设置的也是`GL_FALSE`不需要再进一步的进行标准化。

**<u>顶点信息</u>**

```c
float vertices[] = {
    -0.5f, -0.5f, 0.0f, // left
    0.5f, -0.5f, 0.0f, // right
    0.0f,  0.5f, 0.0f  // top
};
```

设置顶点属性也选择`GL_FALSE`

```c
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
```

因为`OpenGL`想要快速的绘制一张图形，一般都是走的`GPU`因此这里绘制图形也是要用到`GPU`关于`GPU`着色器的介绍可以参考：

[OpenGL-你好三角形](https://learnopengl-cn.github.io/01%20Getting%20started/04%20Hello%20Triangle/#_1)

<u>下面要做的就是把顶点信息放到缓存中去</u>

```c
unsigned int VBO, VAO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
/* 要想使用VAO，要做的只是使用glBindVertexArray绑定VAO。从绑定之后起，我们应该绑定和配置对应的VBO和属性指针，之后解绑VAO供之后使用 */
/* // ..:: 初始化代码（只运行一次 (除非你的物体频繁改变)） :: ..
    // 1. 绑定VAO */
glBindVertexArray(VAO);
// 2. 把顶点数组复制到缓冲中供OpenGL使用
glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 把之前定义的顶点，复制到缓冲的内存中去
/*
    GL_STATIC_DRAW ：数据不会或几乎不会改变。
    GL_DYNAMIC_DRAW：数据会被改变很多。
    GL_STREAM_DRAW ：数据每次绘制时都会改变。 */
/*
    三角形的位置数据不会改变，每次渲染调用时都保持原样，所以它的使用类型最好是GL_STATIC_DRAW。
    如果，比如说一个缓冲中的数据将频繁被改变，那么使用的类型就是GL_DYNAMIC_DRAW或GL_STREAM_DRAW，
    这样就能确保显卡把数据放在能够高速写入的内存部分。 */
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

/*
    位置数据被储存为32位（4字节）浮点值。
    每个位置包含3个这样的值。
    在这3个值之间没有空隙（或其他值）。这几个值在数组中紧密排列(Tightly Packed)。
    数据中第一个值在缓冲开始的位置 */
//  告诉GPU数据怎样取
/*
    第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)
       定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。
       因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
    第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
    第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
    下个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，
       所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。
       我们把它设置为GL_FALSE。
    第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。
      由于下个组位置数据在3个float之后，我们把步长设置为3 * sizeof(float)。
      要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）
      我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。
      一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，
      我们在后面会看到更多的例子（译注: 这个参数的意思简单说
      就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节）。
    最后一个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。
      它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，
      所以这里是0。我们会在后面详细解释这个参数。 */
//   设置顶点属性指针
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
/*
    现在我们已经定义了OpenGL该如何解释顶点数据，
    我们现在应该使用glEnableVertexAttribArray，
    以顶点属性位置值作为参数，启用顶点属性；顶点属性默认是禁用的。 */
glEnableVertexAttribArray(0);

// note that this is allowed, the call to glVertexAttribPointer registered 
//VBO as the vertex attribute's bound   vertex buffer object so afterwards we can safely unbind
glBindBuffer(GL_ARRAY_BUFFER, 0);

// You can unbind the VAO afterwards so other VAO calls 
//won't accidentally modify this VAO, but this rarely happens. Modifying other
// VAOs requires a call to glBindVertexArray anyways 
//so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
glBindVertexArray(0);
```

#### 着色器

着色器创建需要创建顶点着色器和片段着色器，然后使用链接程序把两个着色器链接，需要注意的是链接程序链接的着色器前一个程序的输出，必须要和后面一个程序的输入对应，否则就会报错。

1. 创建着色器

```cpp
// build and compile our shader program
// ------------------------------------
// vertex shader
// 创建一个着色器对象， 返回出着色器的ID
//  顶点着色器
int vertexShader = glCreateShader(GL_VERTEX_SHADER);
```

因为着色器是运行在`GPU`上的一个个小程序，因此需要动态编译，需要时将编译好的程序交给`GPU`运行，使用的语言是`GLSL`需要了解的可以看

[着色器](https://learnopengl-cn.github.io/01%20Getting%20started/05%20Shaders/)

```cpp
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
// 将着色器源码附加到着色器对象上，然后使用glCompileShader进行编译
// param1 着色器ID, param2 源码字符串数量
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
```

因为传入的是程序片段，我们需要知道程序是运行时出错还是根本就编译不过，可以使用`glGetShaderiv`函数获取上述程序编译的状态

```c
// check for shader compile errors
int success; // 获取程序编译的状态，0成功非0失败
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if (!success)
{
    // 程序编译失败的信息
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}
```

用同样的方法处理片段着色器

```c
// fragment shader
// 片段着色器
int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);
// check for shader compile errors
glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
if (!success)
{
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
}
```

使用连接器链接两个着色器

```c
 // link shaders
 /*
 当链接着色器至一个程序的时候，它会把每个着色器的输出链接到下个着色器的输入。
 当输出和输入不匹配的时候，你会得到一个连接错误。
 */
 int shaderProgram = glCreateProgram();
 glAttachShader(shaderProgram, vertexShader);
 glAttachShader(shaderProgram, fragmentShader);
 glLinkProgram(shaderProgram);
 // check for linking errors
 glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
 if (!success) {
 glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
 std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
 }
```

在`Render`里面渲染三角形

```c
// draw our first triangle
// 2. 当我们渲染一个物体时要使用着色器程序
glUseProgram(shaderProgram);
glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
// 3. 绘制物体 GL_TRIANGLES 绘制三角形，从0起点开始绘制，绘制3个点
glDrawArrays(GL_TRIANGLES, 0, 3);
```



**<u>完整代码实现</u>**

```cpp
//
// Created by andrew on 2021/1/17.
//
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";


int main()
{
    // 对glfw进行初始化
    glfwInit();
    // 打印出glfw的版本信息
    //    int* major, int* minor, int* rev
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    cout << "major = " << major << " minor = " << minor << " rev = " << rev << endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // glfw创建窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 为当前window设置上下文，每个线程只能设置一个，并且线程之间共用时，需要将当前线程设置为 non-current
    glfwMakeContextCurrent(window);

    // 设置窗口大小的回调函数，当窗口大小改变时，会调用该函数调整串口的大小
    // 注册窗口大小改变回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // glad 会加载所有openGL函数指针，在调用任何opengl函数之前需要先初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    // 创建一个着色器对象， 返回出着色器的ID
    //  顶点着色器
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 将着色器源码附加到着色器对象上，然后使用glCompileShader进行编译
    // param1 着色器ID, param2 源码字符串数量
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader
    // 片段着色器
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    /*
    当链接着色器至一个程序的时候，它会把每个着色器的输出链接到下个着色器的输入。
    当输出和输入不匹配的时候，你会得到一个连接错误。
     */
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
            0.5f, -0.5f, 0.0f, // right
            0.0f,  0.5f, 0.0f  // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    /* 要想使用VAO，要做的只是使用glBindVertexArray绑定VAO。从绑定之后起，我们应该绑定和配置对应的VBO和属性指针，之后解绑VAO供之后使用 */
    /* // ..:: 初始化代码（只运行一次 (除非你的物体频繁改变)） :: ..
    // 1. 绑定VAO */
    glBindVertexArray(VAO);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 把之前定义的顶点，复制到缓冲的内存中去
    /*
    GL_STATIC_DRAW ：数据不会或几乎不会改变。
    GL_DYNAMIC_DRAW：数据会被改变很多。
    GL_STREAM_DRAW ：数据每次绘制时都会改变。 */
    /*
    三角形的位置数据不会改变，每次渲染调用时都保持原样，所以它的使用类型最好是GL_STATIC_DRAW。
    如果，比如说一个缓冲中的数据将频繁被改变，那么使用的类型就是GL_DYNAMIC_DRAW或GL_STREAM_DRAW，
    这样就能确保显卡把数据放在能够高速写入的内存部分。 */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /*
    位置数据被储存为32位（4字节）浮点值。
    每个位置包含3个这样的值。
    在这3个值之间没有空隙（或其他值）。这几个值在数组中紧密排列(Tightly Packed)。
    数据中第一个值在缓冲开始的位置 */
    //  告诉GPU数据怎样取
    /*
    第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)
       定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。
       因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
    第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
    第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
    下个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，
       所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。
       我们把它设置为GL_FALSE。
    第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。
      由于下个组位置数据在3个float之后，我们把步长设置为3 * sizeof(float)。
      要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）
      我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。
      一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，
      我们在后面会看到更多的例子（译注: 这个参数的意思简单说
      就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节）。
    最后一个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。
      它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，
      所以这里是0。我们会在后面详细解释这个参数。 */
    //   设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    /*
    现在我们已经定义了OpenGL该如何解释顶点数据，
    我们现在应该使用glEnableVertexAttribArray，
    以顶点属性位置值作为参数，启用顶点属性；顶点属性默认是禁用的。 */
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer 
    //registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other 
    // VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways 
    // so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /*
    就这么多了！前面做的一切都是等待这一刻，一个储存了我们顶点属性配置和应使用的VBO的顶点数组对象。
    一般当你打算绘制多个物体时，你首先要生成/配置所有的VAO（和必须的VBO及属性指针)，然后储存它们供后面使用。
    当我们打算绘制物体的时候就拿出相应的VAO，绑定它，绘制完物体后，再解绑VAO。
     */
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        //  北背景
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        // 2. 当我们渲染一个物体时要使用着色器程序
        glUseProgram(shaderProgram);
         // seeing as we only have a single 
        // VAO there's no need to bind it every time, 
        // but we'll do so to keep things a bit more organized
        glBindVertexArray(VAO);
        // 3. 绘制物体
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        // glBindVertexArray(0); // no need to unbind it every time
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 正确的释放之前分配的所有资源
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    // 用户按下 esc键，就设置退出串口为真
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // opengl渲染串口大小，每次调整窗口
    cout << "view port call back" << endl;
    //
    glViewport(0, 0, width, height);
}
```

[github源码仓库](https://github.com/zzu-andrew/opengl_tutorial)

[opengl环境准备](https://wangyazhou.blog.csdn.net/article/details/112717440)

[opengl编程从入门到精通-hello,window](https://wangyazhou.blog.csdn.net/article/details/112723441)













