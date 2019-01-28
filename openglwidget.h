#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>

#include <memory>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT

    GLuint vboVertices = 0;
    GLuint vboIndices = 0;

    GLuint vao = 0;

    std::unique_ptr<QVector4D []> vertices = nullptr;
    std::unique_ptr<unsigned int[]> indices = nullptr;

    GLuint shaderProgram;

    float playerPosY; // Current player Y position
    float playerPosX;

    float busPos[12];
    float busPosY[12];
    float busSpe[12];
    float moveFactor = 0;

    int score = 0;
    float maxRow = -0.5f;
    QTimer timer;
    QTime time;

public:
    explicit OpenGLWidget (QWidget *parent = 0);

    void createVBOs();
    void createShaders();

    void destroyVBOs();
    void destroyShaders();

protected:
    void initializeGL();
    void resizeGL (int width, int height);
    void paintGL();

    void keyPressEvent(QKeyEvent *event);
private:
    void startup();
signals:
    void updateHitsLabel(QString);

public slots:
    void animate();
};
#endif
