#version 120

uniform sampler2D texture;
uniform float intensity;

void main(void)
{
  vec4 color = texture2D(texture, gl_TexCoord[0].st);
  float grey = intensity * (color.r + color.g + color.b) / 3;

  float old_frac = max( 0, 1 - intensity );

  gl_FragColor =
    vec4( color.r * old_frac + grey,
          color.g * old_frac + grey,
          color.b * old_frac + grey,
          color.a );
}
