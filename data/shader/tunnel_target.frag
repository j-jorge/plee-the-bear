#version 120

uniform sampler2D texture;

void main(void)
{
  vec4 color = texture2D(texture, gl_TexCoord[0].st);
  const float center_x = 640;
  const float center_y = 360;
  const float tunnel_radius = 300;

  float dx = gl_FragCoord.x - center_x;
  float dy = gl_FragCoord.y - center_y;
  
  if ( sqrt( dx * dx + dy * dy ) > tunnel_radius )
    color.a = 0;
  else
    {
      const int r = 2;
      
      if ( mod( floor(gl_FragCoord.x), r ) != mod( floor(gl_FragCoord.y), r ) )
        color.a = 0;
      else
        {
          float light =
            0.71516 * color.r + 0.212671 * color.g + 0.072169 * color.b;
          const float p = 1.25;

          color.r = clamp( p * color.r, 0, 1 );
          color.g = clamp( p * color.g, 0, 1 );
          color.b = clamp( p * color.b, 0, 1 );
        }
    }

  gl_FragColor = color;
}
