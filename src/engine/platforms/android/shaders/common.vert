attribute vec4 vPosition;

uniform bool ortho;
uniform float angle;
uniform float scale;
uniform vec4 position;

uniform mat4 perspProjMat;

void main() {
    vec4 pos = vPosition;

    if (angle != 0.0)
    {
        float a = radians(-angle);
        mat4 rotationMatrixZ = mat4(cos(a), -sin(a), 0.0,     0.0,
                                    sin(a),  cos(a), 0.0,     0.0,
                                    0.0,     0.0,    1.0,     0.0,
                                    0.0,     0.0,    0.0,     1.0);
        pos *= rotationMatrixZ;
    }

    pos *= vec4(scale, scale, 1.0, 1.0);
    pos += position;

    if (!ortho)
        pos = perspProjMat * pos;

    gl_Position = pos;
    //gl_TexCoord[0] = gl_MultiTexCoord0;
}
