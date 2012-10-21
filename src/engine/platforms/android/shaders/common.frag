uniform sampler2D tex;
uniform vec3 color;
uniform float opacity;
uniform bool withTexture;

void main() {
    if (opacity <= 0.0)
        discard;

    /*vec4 pixelColor;
    if (withTexture)
    {
        pixelColor = texture2D(tex, gl_TexCoord[0].st);
        if (pixelColor.a > 0.01)
            pixelColor.a = opacity;
    }
    else
    {
        pixelColor = vec4(color, opacity);
    }

    gl_FragColor = pixelColor;*/
}
