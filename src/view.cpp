#include <GL/glew.h>
#include "view.h"
#include <QApplication>
#include <QKeyEvent>
#include "camera.h"
#include "scene.h"
#include "drawcontext.h"

using namespace std;

View::View(QWidget *parent) : QGLWidget(parent)
{   
    // View needs all mouse move events, not just mouse drag events
    setMouseTracking(true);

    // Hide the cursor since this is a fullscreen app
    setCursor(Qt::BlankCursor);

    // View needs keyboard focus
    setFocusPolicy(Qt::StrongFocus);

    // The game loop is implemented using a timer
    connect(&timer_, SIGNAL(timeout()), this, SLOT(tick()));
}

View::~View()
{
    delete scene_;
    delete camera_;
}

void View::initializeGL()
{       
    time_.start();
    timer_.start(1000 / 60);

    glewExperimental = GL_TRUE; 
    GLenum err = glewInit();
    
    if( GLEW_OK != err )
    {
        fprintf(stderr, "Error initializing GLEW: %s\n",
                        glewGetErrorString(err) );
    }
    
    DEBUG_LOG(glGetString(GL_VERSION));
    
    glClearColor(1, 0.7, 0, 1.0);
    glClearDepth(1.0);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // TAs said this call does some magic
    QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
    
    camera_ = new Camera();
    scene_ = new Scene();
}

void View::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    float seconds = time_.restart() * 0.001f;
    
    DrawContext context;
    context.deltaTime = seconds;
    context.camera = camera_;
    
    scene_->render(context);
}

void View::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    float aspectRatio = (float)w / h;
    camera_->setAspectRatio(aspectRatio);
}

void View::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    
    printf("%d %d\n", x, y);
    fflush(stdout);
}

void View::mouseMoveEvent(QMouseEvent *event)
{

}

void View::mouseReleaseEvent(QMouseEvent *event)
{
}

void View::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) QApplication::quit();
}

void View::keyReleaseEvent(QKeyEvent *event)
{
    
}

void View::tick()
{
    // Flag this view for repainting (Qt will call paintGL() soon after)
    update();
}
