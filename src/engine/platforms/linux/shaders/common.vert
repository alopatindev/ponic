uniform bool ortho;
uniform float angle;
uniform float scale;
uniform vec4 position;

uniform mat4 perspProjMat;

void main() {
    vec4 pos = gl_Vertex;

    if (angle != 0.0)
    {
        float a = radians(-angle);
        /*mat4 rotationMatrixX = mat4(1.0,     0.0,    0.0,     0.0,
                                    0.0,     cos(a), -sin(a), 0.0,
                                    0.0,     sin(a), cos(a),  0.0,
                                    0.0,     0.0,    0.0,     1.0);

        mat4 rotationMatrixY = mat4(cos(a),  0.0,    sin(a),  0.0,
                                    0.0,     1.0,    0.0,     0.0,
                                    -sin(a), 0.0,    cos(a),  0.0,
                                    0.0,     0.0,    0.0,     1.0);*/

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
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
