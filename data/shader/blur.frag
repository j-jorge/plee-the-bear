#version 120

uniform sampler2D texture;
uniform int textureSize;

void main(void)
{
  vec4 color = texture2D(texture, gl_TexCoord[0].st);
  const float x_offset = 1.0 / 256;
  const float y_offset = 1.0 / 256;

  vec3 result = color.rgb;
  int count = 1;

  for ( int x = -2; x <= 2; ++x )
    for ( int y = -2; y <= 2; ++y )
      if ( (x != 0) || (y != 0) )
        {
          vec2 texture_coord =
            vec2( gl_TexCoord[0].s + x_offset * x,
              gl_TexCoord[0].t + y_offset * y );

          if ( ( 0 <= texture_coord.x ) && ( texture_coord.x < 256 )
               && ( 0 <= texture_coord.y ) && ( texture_coord.y < 256 ) )
            {
              vec4 neighbor_color = texture2D( texture, texture_coord );
              result += neighbor_color.rgb * neighbor_color.a;
              ++count;
            }
        }

  result /= count;
  
  gl_FragColor = vec4( result.rgb, color.a );
}
