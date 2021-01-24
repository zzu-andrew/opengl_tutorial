//
// Created by andrew on 2021/1/19.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image/stb_image.h"
#include "filesystem/filesystem.h"
#include "shader/shader_s.h"
#include <iostream>
using namespace std;

// 每次窗口变动会调用，并将窗口的变动值传递给glViewport函数，实现实时渲染不同窗口的大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 处理键盘输入
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    // 打印出glfw的版本信息
    //    int* major, int* minor, int* rev
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    cout << "major = " << major << " minor = " << minor << " rev = " << rev << endl;
    // 版本命中
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // 创建一个窗口,指定宽高，窗口的title, 使用多显示屏时可以按照喜好指定窗口显示的显示屏，这里默认NULL使用主显示屏
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "opengl_tutorial", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 为当前window设置上下文，每个线程只能设置一个，并且线程之间共用时，需要将当前线程设置为 non-current
    glfwMakeContextCurrent(window);
    // 设置窗口大小改变时的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // 调用一切opengl函数之前，先使用glad加载器把opengl函数加载进来
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // 指定动态编译的GPU小程序源码
    Shader ourShader("/work/opengl_tutorial/src/shader_src/texture_vs1.vs",
                     "/work/opengl_tutorial/src/shader_src/texture_fs1.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // 要绘制区域和对应纹理图的区域向对应
    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    1.0f, 1.0f, // top right
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3,  // second triangle
           // 0, 2, 3,  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 每行数据说明清楚取的方式就行了
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute  //纹理加载颜色没有使用
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture
    // 创建纹理
    unsigned int texture;
    // 生成纹理的数量
    glGenTextures(1, &texture);
    // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // glBindTexture 调用之后，所有对GL_TEXTURE_2D操作都将作用于 texture
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    //    GL_REPEAT 重复复制形式
    //    GL_MIRRORED_REPEAT 进行放置
    //  GL_CLAMP_TO_EDGE 边缘拉伸效果
    //  GL_CLAMP_TO_BORDER 用于指定的效果
    //  GL_REPEAT 垂直轴
    //  GL_TEXTURE_WRAP_T 水平轴
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // 配合 GL_CLAMP_TO_BORDER 指定边缘颜色
    float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);*/
    // set texture filtering parameters
    //    GL_NEAREST 临近值s
    // GL_LINEAR 线性插值方式
    /*当进行放大(Magnify)和缩小(Minify)操作的时候可以设置纹理过滤的选项，比如你可以在纹理被缩小的时候使用邻近过滤，
     * 被放大时使用线性过滤。我们需要使用`glTexParameter*`函数为放大和缩小指定过滤方式。这段代码看起来会和纹理环绕方式的设置很相似：*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    cout << FileSystem::getPath("resources/textures/container.jpg").c_str() << endl;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(),
                                    &width, &height, &nrChannels, 0);
    if (data)
    {
        /*
         * - 第一个参数指定了纹理目标(Target)。设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响）。
        - 第二个参数为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
        - 第三个参数告诉OpenGL我们希望把纹理储存为何种格式。我们的图像只有`RGB`值，因此我们也把纹理储存为`RGB`值。
        - 第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
        - 下个参数应该总是被设为`0`（历史遗留的问题）。
        - 第七第八个参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存为`char`(byte)数组，我们将会传入对应值。
        - 最后一个参数是真正的图像数据。
         * */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        // 生成多级渐远纹理，自动生成多级渐远纹理
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    //    生成了纹理和相应的多级渐远纹理后，释放图像的内存是一个很好的习惯。
    stbi_image_free(data);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // 设置背景的颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
//    cout << width << height << endl;
    glViewport(0, 0, width, height);
}
