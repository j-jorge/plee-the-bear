#version 120

uniform sampler2D texture;

void main(void)
{
  vec4 color = texture2D(texture, gl_TexCoord[0].st);
  const int r = 2;

  if ( mod( floor(gl_FragCoord.x), r ) != mod( floor(gl_FragCoord.y), r ) )
    color.a = 0;

  gl_FragColor = color;
}
