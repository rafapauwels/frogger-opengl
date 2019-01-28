#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    playerPosX = 0;
    playerPosY = -0.8f;
}

void OpenGLWidget::startup()
{
    busPos[0] = 0;
    busPos[1] = 1;
    busPos[2] = -1;

    busPos[3] = -0.5f;
    busPos[4] = 0.8f;
    busPos[5] = 0.2f;

    busPos[6] = -0.6f;
    busPos[7] = 0;
    busPos[8] = 0.6f;

    busPos[9] = 0.1f;
    busPos[10] = 0.9f;
    busPos[11] = -1.1f;

    busPosY[0] = -0.5f;
    busPosY[1] = -0.5f;
    busPosY[2] = -0.5f;

    busPosY[3] = -0.4f;
    busPosY[4] = -0.4f;
    busPosY[5] = -0.4f;

    busPosY[6] = -0.3f;
    busPosY[7] = -0.3f;
    busPosY[8] = -0.3f;

    busPosY[9] = -0.2f;
    busPosY[10] = -0.2f;
    busPosY[11] = -0.2f;

    busSpe[0] = 1.0f;
    busSpe[1] = 1.0f;
    busSpe[2] = 1.0f;

    busSpe[3] = -0.8f;
    busSpe[4] = -0.8f;
    busSpe[5] = -0.8f;

    busSpe[6] = 1.2f;
    busSpe[7] = 1.2f;
    busSpe[8] = 1.2f;

    busSpe[9] = -1.5f;
    busSpe[10] = -1.5f;
    busSpe[11] = -1.5f;

}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

    qDebug("OpenGL version: %s", glGetString(GL_VERSION));
    qDebug("GLSL %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

    createShaders();
    createVBOs();

    connect(&timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer.start(0);

    startup();

    time.start();
}

void OpenGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    GLint locScaling = glGetUniformLocation(shaderProgram, "scaling");
    GLint locLength = glGetUniformLocation(shaderProgram, "length");
    GLint locTranslation = glGetUniformLocation(shaderProgram, "translation");
    GLint locColor = glGetUniformLocation(shaderProgram, "color");

    glUseProgram(shaderProgram);

    glBindVertexArray(vao);           

    // SIDEROAD YELLOW
    glUniform4f(locColor, 1.0, 0.84, 0.0, 0);
    glUniform1f(locScaling, 0.1f);
    glUniform1f(locLength, 20);
    glUniform4f(locTranslation, 0, -0.6f, 0, 0);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);
    glUniform4f(locTranslation, 0, -0.1f, 0, 0);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    // END ZONE
    glUniform4f(locColor, 0.65f, 0.65f, 0.60f, 0);
    glUniform1f(locScaling, 0.3f);
    glUniform4f(locTranslation, 0, 0.1f, 0, 0);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    // == Bus's ==
    glUniform1f(locScaling, 0.1f);
    glUniform1f(locLength, 3);

    // First Row
    glUniform4f(locColor, 1.0, 1.0, 1.0, 0);

    glUniform4f(locTranslation, busPos[0], -0.5, 0, 0);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    glUniform4f(locTranslation, busPos[1], -0.5, 0, 0);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    glUniform4f(locTranslation, busPos[2], -0.5, 0, 0);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    // Second Row
    glUniform4f(locColor, 1.0, 0.0, 0.0, 0);

    glUniform4f(locTranslation, busPos[3], -0.4f, 0, 0);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    glUniform4f(locTranslation, busPos[4], -0.4f, 0, 0);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    glUniform4f(locTranslation, busPos[5], -0.4f, 0, 0);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    // Third Row
    glUniform4f(locColor, 0.0, 0.0, 1.0, 0);

    glUniform4f(locTranslation, busPos[6], -0.3f, 0, 0);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    glUniform4f(locTranslation, busPos[7], -0.3f, 0, 0);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    glUniform4f(locTranslation, busPos[8], -0.3f, 0, 0);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    // Forth Row
    glUniform4f(locColor, 0.0, 1.0, 1.0, 0);

    glUniform4f(locTranslation, busPos[9], -0.2f, 0, 0);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    glUniform4f(locTranslation, busPos[10], -0.2f, 0, 0);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    glUniform4f(locTranslation, busPos[11], -0.2f, 0, 0);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

    // Player
    glUniform4f(locColor, 0.0, 0.6f, 0.3f, 0);
    glUniform4f(locTranslation, playerPosX, playerPosY, 0, 0);
    glUniform1f(locScaling, 0.1f);
    glUniform1f(locLength, 1);
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

}

void OpenGLWidget::createShaders()
{
    // makeCurrent();
    destroyShaders();

    QFile vs(":/shaders/vshader1.glsl");
    QFile fs(":/shaders/fshader1.glsl");

    vs.open(QFile::ReadOnly | QFile::Text);
    fs.open(QFile::ReadOnly | QFile::Text);

    QTextStream streamVs(&vs), streamFs(&fs);

    QString qtStringVs = streamVs.readAll();
    QString qtStringFs = streamFs.readAll();

    std::string stdStringVs = qtStringVs.toStdString();
    std::string stdStringFs = qtStringFs.toStdString();

    // Create an empty vertex shader handle
    GLuint vertexShader = 0;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Send the vertex shader source code to GL
    const GLchar *source = stdStringVs.c_str();

    glShaderSource(vertexShader, 1, &source, 0);

    // Compile the vertex shader
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        qDebug("%s", &infoLog[0]);

        glDeleteShader(vertexShader);
        return;
    }

    // Create an empty fragment shader handle
    GLuint fragmentShader = 0;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Send the fragment shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    source = stdStringFs.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);

    // Compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
        qDebug("%s", &infoLog[0]);

        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
        return;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    shaderProgram = glCreateProgram();

    // Attach our shaders to our program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Link our program
    glLinkProgram(shaderProgram);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);
        qDebug("%s", &infoLog[0]);

        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    vs.close();
    fs.close();
}

void OpenGLWidget::destroyShaders()
{
    makeCurrent();
    glDeleteProgram(shaderProgram);
}

void OpenGLWidget::createVBOs()
{
    makeCurrent();
    destroyVBOs();

    vertices = std::make_unique<QVector4D[]>(4);
    indices = std::make_unique<unsigned int[]>(2 * 3);

    vertices[0] = QVector4D(-0.5, -0.5, 0, 1);
    vertices[1] = QVector4D( 0.5, -0.5, 0, 1);
    vertices[2] = QVector4D( 0.5,  0.5, 0, 1);
    vertices[3] = QVector4D(-0.5,  0.5, 0, 1);

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(QVector4D), vertices.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &vboIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(unsigned int), indices.get(), GL_DYNAMIC_DRAW);
}

void OpenGLWidget::destroyVBOs()
{
    glDeleteBuffers(1, &vboVertices);
    glDeleteBuffers(1, &vboIndices);
    glDeleteVertexArrays(1, &vao);

    vboVertices = 0;
    vboIndices = 0;
    vao = 0;
}

void OpenGLWidget::animate()
{
    float elapsedTime = time.restart() / 1000.0f;
    // Animate
    float speed = 0.5f;

    moveFactor = speed * elapsedTime;

    // Check player colision
    for (int i = 0; i < 12; i++)
    {
        if (std::fabs(busPos[i] - playerPosX) < 0.15f)
        {
            if (std::fabs(busPosY[i] - playerPosY) < 0.025f)
            {
                qDebug("HIT!");
                score = 0;
                emit updateHitsLabel(QString("Score: %1").arg(score));
                maxRow = -0.8f;
                playerPosX = 0;
                playerPosY = -0.8f;
            }
        }
    }

    // Bus animation
    for (int i = 0; i < 12; i++)
    {
        busPos[i] += moveFactor * busSpe[i];
        if (busPos[i] > 1.5f)
        {
            busPos[i] = -1.5f;
        }
        if (busPos[i] < -1.5f)
        {
            busPos[i] = 1.5f;
        }
    }

    // Check player bounds
    if (playerPosY < -0.8f)
        playerPosY = -0.8f;
    if (playerPosY > 0.8f)
        playerPosY = 0.8f;
    if (playerPosX < -0.8f)
        playerPosX = -0.8f;
    if (playerPosX > 0.8f)
        playerPosX = 0.8f;    

    if (maxRow < playerPosY)
    {
        maxRow += 0.1f;
        score += 1;
        if (maxRow > 0)
        {
            score += 9;
            maxRow = -0.5f;
            playerPosX = 0;
            playerPosY = -0.8f;
        }
        emit updateHitsLabel(QString("Score: %1").arg(score));
    }

    update();
}

// Strong focus is required
void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up ||
        event->key() == Qt::Key_W)
        playerPosY += 0.1f;

    if (event->key() == Qt::Key_Down ||
        event->key() == Qt::Key_S)
        playerPosY -= 0.1f;

    if (event->key() == Qt::Key_Left ||
        event->key() == Qt::Key_A)
        playerPosX -= 0.1f;

    if (event->key() == Qt::Key_Right ||
        event->key() == Qt::Key_D)
        playerPosX += 0.1f;

    if (event->key() == Qt::Key_Escape)
    {
        QApplication::quit();
    }
}

