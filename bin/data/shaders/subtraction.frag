uniform sampler2DRect u_texBaseGray;
uniform sampler2DRect u_texVideoGray;

void main() {
    vec2 pos = gl_FragCoord.xy;
    
    vec4 texBaseGray = texture2DRect(u_texBaseGray, pos);
    vec4 texVideoGray = texture2DRect(u_texVideoGray, pos);
    
//    vec4 color = texBaseGray - texVideoGray + 0.5;

    vec4 subt = texBaseGray - texVideoGray;
    vec4 color = vec4(0.5);
    
    if (subt.r * subt.r > 0.3 * 0.3) {
        color = color + subt;
    }
    
    color = vec4(color.rgb, 1.0);
    
    gl_FragColor = color;
}
