#version 120

uniform sampler2D texture;

void main(void)
{
  vec4 color = texture2D(texture, gl_TexCoord[0].st);
  float light = 0.71516 * color.r + 0.212671 * color.g + 0.072169 * color.b;

  const float black_threshold = 0.3;
  const float medium_threshold = 0.4;

  if ( light < black_threshold )
    color = vec4( 0, 0, 0, color.a );
  else if ( light < medium_threshold )
    color = vec4( 0.7, 0.7, 0.7, color.a );
  else
    color = vec4( 1, 1, 1, color.a );

  gl_FragColor = color;
}
