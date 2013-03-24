#version 120

uniform sampler2D texture;
uniform int textureSize;

void main(void)
{
  vec4 color = texture2D(texture, gl_TexCoord[0].st);
  
  if ( mod( floor(gl_FragCoord.y), 2 ) == 0 )
    color =
      vec4
      ( min(1, 1.5 * color.r), min(1, 1.5 * color.g), min(1, 1.5 * color.b),
        color.a );

  gl_FragColor = color;
}
