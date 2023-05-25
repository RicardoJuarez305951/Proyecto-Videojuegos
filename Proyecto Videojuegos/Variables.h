
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

int expan[] = {
    0
};

//Camera
float deltaTime = 0.0f, lastFrame = 0.0f;

Camera camera(vec3(0.0f, 0.0f, 3.0f));
float lastX = w / 2.0f;
float lastY = h / 2.0f;
bool firstMouse = true;

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
