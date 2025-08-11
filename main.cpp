#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

char board[3][3] = { {' ',' ',' '}, {' ',' ',' '}, {' ',' ',' '}};
char currentPlayer = 'X';

bool gameEnded = false;

bool checkWinner()
{
    for (int row{0};row < 3;++row)
    {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != ' ')
        {
            return true;
        }
    }
    
    for (int col{0};col < 3;++col)
    {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != ' ')
        {
            return true;
        }
    }
    
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == ' ')
    {
        return true;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == ' ')
    {
        return true;
    }
    
    return false;
}

int main() {
    if (!glfwInit())
        return 1;

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Create window with graphics context
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
    GLFWwindow* window = glfwCreateWindow((int)(590 * main_scale), (int)(630 * main_scale), "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
    style.FontScaleDpi = main_scale;

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    std::string labels[2][2] = {};

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(590, 630));

            if (ImGui::Begin("Tik Tac Toe!", nullptr, flags))
            {
                for (int row{0};row < 3;++row)
                {
                    for (int col{0};col < 3;++col)
                    {
                        float xPos = 10.0f + col * (100.0f + 10.0f);
                        float oPos = 30.0f + row * (100.0f + 10.0f);

                        ImGui::SetCursorPos(ImVec2(xPos,oPos));
                        std::string btnlbl = std::string(1,board[row][col]) + "##" + std::to_string(row) + "," + std::to_string(col);
                        if (ImGui::Button(btnlbl.c_str(), ImVec2(100.0f, 100.0f)))
                        {
                            if (board[row][col] == ' ')
                            {
                                board[row][col] = currentPlayer;
                                if (checkWinner())
                                {
                                    gameEnded = true;
                                }
                                else
                                {
                                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                                }
                            }
                        }
                    }
                }
            }    
            if (gameEnded)
            {
                ImGui::SetNextWindowSize(ImVec2(150, 200));
                ImGui::OpenPopup("Game over!");
            }
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
