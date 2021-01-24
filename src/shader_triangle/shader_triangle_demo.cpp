//
// Created by andrew on 2021/1/17.
//
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "shader/shader_s.h"

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
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

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("/work/opengl_tutorial/src/shader_src/shader_vs1.vs",
                     "/work/opengl_tutorial/src/shader_src/shader_fs1.fs"); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            // positions         // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    /*
    现在我们已经定义了OpenGL该如何解释顶点数据，
    我们现在应该使用glEnableVertexAttribArray，
    以顶点属性位置值作为参数，启用顶点属性；顶点属性默认是禁用的。 */
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // 启用对应顶点的属性，顶点定义在vs完成
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  //  glBindVertexArray(0);

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
        ourShader.use();
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
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
