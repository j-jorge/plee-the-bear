#version 120

uniform sampler2D texture;

float curve_outside( float v )
{
  return sin( v * 3.14159 / 2 );
  //  return v * v * v;
}

float curve_inside( float v )
{
  return sin( v * 3.14159 / 2 );
}

void main(void)
{
  vec4 color = texture2D(texture, gl_TexCoord[0].st);
  const float center_x = 640;
  const float center_y = 360;
  const float tunnel_radius = 300;

  float dx = gl_FragCoord.x - center_x;
  float dy = gl_FragCoord.y - center_y;
  float distance = sqrt( dx * dx + dy * dy );

  if ( abs( distance - tunnel_radius ) < 1 )
    color.rgb = vec3( 0.9, 0.95, 0.99 );
  else if ( abs( distance - tunnel_radius ) < 2 )
    color.rgb = vec3( 1, 1, 1 );
  else if ( distance < tunnel_radius )
    {
      const float inside_gradient = 50;

      if ( tunnel_radius - distance < inside_gradient )
        color.rgb =
          mix
          ( vec3( 1, 1, 1 ), color.rgb,
            curve_inside
            ( (tunnel_radius - distance) / inside_gradient ) );
    }
  else
    {
      float light = 0.71516 * color.r + 0.212671 * color.g + 0.072169 * color.b;

      if ( light > 0.2 )
        color.rgb = vec3( 0, 0, 0 );
      else
        color.rgb = vec3( 1, 1, 1 );
    
      const float outside_gradient = 30;

      if ( distance - tunnel_radius < outside_gradient )
        {
          float frac =
            curve_outside( (distance - tunnel_radius) / outside_gradient );
          color.rgb = mix( vec3( 0.9, 0.95, 0.99 ), color.rgb, frac );
        }
    }

  gl_FragColor = color;
}
