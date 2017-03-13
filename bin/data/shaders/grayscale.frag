#define R_SCALE 0.298912
#define G_SCALE 0.586611
#define B_SCALE 0.114478

uniform sampler2DRect u_tex;

void main() {
    vec2 pos = gl_FragCoord.xy;
    vec3 scale = vec3(R_SCALE, G_SCALE, B_SCALE);
    
    vec4 texColor = texture2DRect(u_tex, pos);
    float gray = texColor.r * scale.r + texColor.g * scale.g + texColor.b * scale.b;
    
    vec4 color = vec4(vec3(gray), 1.0);
    
    gl_FragColor = color;
}
