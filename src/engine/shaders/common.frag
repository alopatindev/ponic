uniform sampler2D tex;
uniform float opacity;

void main() {
    if (opacity <= 0.0)
        discard;

    vec4 color = texture2D(tex, gl_TexCoord[0].st);
    if (color.a > 0.01)
        color.a = opacity;
    gl_FragColor = color;
}
