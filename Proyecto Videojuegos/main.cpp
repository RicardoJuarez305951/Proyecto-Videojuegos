#include "libraries.h"

#include "Camera.h"
#include "Variables.h"
#include "Cubo.h"
#include "SkyBoxVertex.h"
#include "Model.h"

#include "Shader.h"
#include "Textura.h"

void initGLFWVersion();
bool gladLoad();
void updateWindow(GLFWwindow* window, Shader ourShader, Textura ourTexture, Shader ourShaderSky, Textura ourTextureSky);
void updateWindow2(GLFWwindow* window, Shader ourShader, Model ourModel, Shader ourShaderSky, Textura ourTextureSky);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

void GeneracionBuffer();
void GeneracionBufferSky();
void VertexAttribute(int layout, int data, int total, int start);

void TransformacionObjeto(Shader ourShader);
void TransformacionObjeto(Shader ourShader, Model ourModel, vec3 poseModel);
void CameraTransform(Shader ourShader, bool isSky);
void illumination(Shader ourShader);

int main()
{
    initGLFWVersion();

    GLFWwindow* window = glfwCreateWindow(w, h, "Texturas", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoad())
    {
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    limite = (sizeof(texture) / sizeof(texture[0]));

    Shader ourShader("vertexShader.vs", "fragmenShader.fs");
    Shader ourShaderSky("vertexShaderSky.vs", "fragmenShaderSky.fs");

    //Model ourModel(modeloNombre[0]);
    Model ourModel(escenario[0]);

    Textura ourTexture(texture, limite);
    Textura ourTextureSky(textureSky);

    GeneracionBuffer();
    

    //Model
    for (int i = 0; i < limite; i++)
    {
        ourTexture.GeneraTextura(texture[i], nombre[i], expan[i]);
        //ourTexture.GeneraTextura(texture[i], modeloNombre[i], expan[i]);
    }

    if (limite > 1)
    {
        ourShader.use();
        for (int i = 0; i < limite; i++)
        {
           ourShader.setInt(ourTexture.UniformTextura(), i);
        }
    }

    //Sky
    GeneracionBufferSky();
    ourTextureSky.GeneraTexturaSky(faces);
    ourShaderSky.use();
    ourShaderSky.setInt(ourTextureSky.UniformTexturaSky(), 0);

    
    
    //updateWindow(window, ourShader, ourTexture, ourShaderSky, ourTextureSky);
    updateWindow2(window, ourShader, ourModel, ourShaderSky, ourTextureSky);

    //Model
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    //SKY
    glDeleteVertexArrays(1, &VAOSKY);
    glDeleteBuffers(1, &VBOSKY);
    glDeleteBuffers(1, &EBOSKY);

    glfwTerminate();
    return 0;
}

void initGLFWVersion()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

}
bool gladLoad()
{
    bool active = true;
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    return active;
}
void updateWindow(GLFWwindow* window, Shader ourShader, Textura ourTexture, Shader ourShaderSky, Textura ourTextureSky)
{
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Model
        ourShader.use();
        CameraTransform(ourShader, false);
        glBindVertexArray(VAO);
        ourTexture.ViewTextura();
        TransformacionObjeto(ourShader);

        //SKY
        glDepthFunc(GL_LEQUAL);
        ourShaderSky.use();
        CameraTransform(ourShaderSky, true);
        glBindVertexArray(VAOSKY);
        ourTextureSky.ViewTexturaSKY();
        glDepthFunc(GL_LESS);
       
        
        if (poly)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void updateWindow2(GLFWwindow* window, Shader ourShader, Model ourModel, Shader ourShaderSky, Textura ourTextureSky)
{
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        

        //Model
        ourShader.use();
        illumination(ourShader);
        CameraTransform(ourShader, false);
        glBindVertexArray(VAO);
        //ourModel.ViewTextura();
        TransformacionObjeto(ourShader, ourModel, vec3(0.0f,0.0f,0.0f));

        //SKY
        glDepthFunc(GL_LEQUAL);
        ourShaderSky.use();
        CameraTransform(ourShaderSky, true);
        glBindVertexArray(VAOSKY);
        ourTextureSky.ViewTexturaSKY();
        glDepthFunc(GL_LESS);


        if (poly)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    //Camara move
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
        
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

void GeneracionBuffer()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    VertexAttribute(0, 3, 5, 0);
    VertexAttribute(1, 2, 5, 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GeneracionBufferSky()
{
    glGenVertexArrays(1, &VAOSKY);
    glGenBuffers(1, &VBOSKY);
    glGenBuffers(1, &EBOSKY);
    glBindVertexArray(VAOSKY);

    glBindBuffer(GL_ARRAY_BUFFER, VBOSKY);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOSKY);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesSky), indicesSky, GL_STATIC_DRAW);

    VertexAttribute(0, 3, 3, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VertexAttribute(int layout, int data, int total, int start)
{
    glVertexAttribPointer(layout, data, GL_FLOAT, GL_FALSE, total * sizeof(float), (void*)(start * sizeof(float)));
    glEnableVertexAttribArray(layout);
}

void CameraTransform(Shader ourShader, bool isSky)
{
    mat4 projection = perspective(radians(camera.Zoom),(float)w/(float)h,0.1f,100.0f);
    ourShader.setMat4("projection", projection);

    mat4 view;
    if (isSky)
    {
        view = mat4(mat3(camera.GetViewMatrix()));
    }
    else
    {
        view = camera.GetViewMatrix();
    }
    
    ourShader.setMat4("view", view);
}

void TransformacionObjeto(Shader ourShader, Model ourModel, vec3 poseModel)
{
    mat4 model = mat4(1.0f);
    model = translate(model, poseModel);
    model = scale(model, vec3(1.0f, 1.0f, 1.0f));
    ourShader.setMat4("model", model);
    ourModel.Draw(ourShader);
}

void TransformacionObjeto(Shader ourShader)
{
    bool one = false;
    int n = 10;

    if (one)
    {
        mat4 model = mat4(1.0f);
        //model = rotate(model, (float)glfwGetTime() * radians(50.0f), vec3(0.5f, 1.0f, 0.0f));
        ourShader.setMat4("model", model);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
    else
    {
        for (unsigned int i = 0; i < n; i++)
        {
            mat4 model = mat4(1.0f);
            model = translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = rotate(model, radians(angle), vec3(0.5f, 1.0f, 0.0f));
            ourShader.setMat4("model", model);

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
    }
}

void illumination(Shader ourShader)
{

    ourShader.setVec3("viewPos", camera.Position);

    //Directional
    ourShader.setVec3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
    ourShader.setVec3("dirLight.diffuse", 0.8f, 0.8f, 0.8f);
    ourShader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);
    ourShader.setVec3("dirLight.direction", lightDirect);

    //Point
    for (int i = 0; i < totalP; ++i) {
        string i_str = to_string(i);
        ourShader.setVec3("pointLights[" + i_str + "].ambient", 0.05f, 0.05f, 0.05f);
        ourShader.setVec3("pointLights[" + i_str + "].diffuse", 0.8f, 0.8f, 0.8f);
        ourShader.setVec3("pointLights[" + i_str + "].specular", 1.0f, 1.0f, 1.0f);
        ourShader.setVec3("pointLights[" + i_str + "].pose", pointLightPositions[i]);
        ourShader.setFloat("pointLights[" + i_str + "].constant", constantV);
        ourShader.setFloat("pointLights[" + i_str + "].linear", linearV);
        ourShader.setFloat("pointLights[" + i_str + "].quadratic", quadraticV);
    }

    //Spot
    if (attached)
    {
        ourShader.setVec3("spotLight.pose", camera.Position);
        ourShader.setVec3("spotLight.direction", camera.Front);
    }
    else
    {
        ourShader.setVec3("spotLight.pose", droppedPos);
        ourShader.setVec3("spotLight.direction", droppedDir);
    }
    ourShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    ourShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    ourShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    ourShader.setFloat("spotLight.constant", constantV);
    ourShader.setFloat("spotLight.linear", linearV);
    ourShader.setFloat("spotLight.quadratic", quadraticV);
    ourShader.setFloat("spotLight.cutOff", cos(radians(cutOffValue)));
    ourShader.setFloat("spotLight.outerCutOff", cos(radians(outerCutOffValue)));
}
