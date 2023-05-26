
const unsigned int w = 500;
const unsigned int h = 300;
const bool poly = false;

//Buffer
unsigned int VBO, VAO, EBO;
unsigned int VBOSKY, VAOSKY, EBOSKY;

//Texture
unsigned int texture[1];
unsigned int textureSky;
int limite;

string nombre[] = {
    "Imagenes/caja.jpg"
};

string modeloNombre[] = {
    "Obstaculos/obstaculoCilindro.obj",
    "Obstaculos/obstaculoCilindro2A.obj",
    "Obstaculos/obstaculoCilindro2B.obj",
    "Obstaculos/obstaculoCilindro2C.obj",
    "Obstaculos/obstaculoCilindro2D.obj",
    "Obstaculos/obstaculoCilindro3.obj",
    "Obstaculos/obstaculoMuro1.obj",
    "Obstaculos/obstaculoMuro2.obj"
};

string escenario[] = {
    "Obstaculos/escenario.obj"
};

int expan[] = {
    0
};

//Camera
mat4 projection, view, model;

float deltaTime = 0.0f, lastFrame = 0.0f;
Camera camera(vec3(0.0f, 0.0f, 6.0f));
float lastX = w / 2.0f;
float lastY = h / 2.0f;
bool firstMouse = true;

// Luz
int totalP = 1;
vec3 droppedPos = camera.Position;
vec3 droppedDir = camera.Front;
vec3 lightPos(0.5f, 0.2f, 1.0f);
vec3 lightDirect(-0.2f, -1.0f, -0.3f);

float constantV = 1.0f;
float linearV = 0.09f;
float quadraticV = 0.032f;

float cutOffValue = 12.5f;
float outerCutOffValue = 17.5f;

bool attached = true;

vec3 pointLightPositions[] = {
        vec3(0.7f,  0.2f,  2.0f),
        vec3(2.3f, -3.3f, -4.0f),
        vec3(-4.0f,  2.0f, -12.0f),
        vec3(0.0f,  0.0f, -3.0f)
};


//SKY
vector<string> faces
{
    /*
    right
    left
    top
    bottom
    front
    back

    o

    ft
    bk
    up
    dn
    rt
    lf

    */

    "Imagenes/Sky/elyvisions/rainbow_ft.png",
    "Imagenes/Sky/elyvisions/rainbow_bk.png",
    "Imagenes/Sky/elyvisions/rainbow_up.png",
    "Imagenes/Sky/elyvisions/rainbow_dn.png",
    "Imagenes/Sky/elyvisions/rainbow_rt.png",
    "Imagenes/Sky/elyvisions/rainbow_lf.png"
};
