#version 330

uniform float time;
uniform vec2 resolution;

in vec2 fragTextCoord;
in vec4 fragColor;

out vec4 finalColor;

vec3 palette(float t)
{
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263, 0.416, 0.557);

    return a + b * cos(6.28318 * (c * t + d));
}

void main()
{
    vec2 uv = (gl_FragCoord.xy * 2.0 - resolution.xy) / resolution.y;
    vec2 uv0 = uv;
    vec3 color = vec3(0.0);

    for (float i = 0.0; i < 4.0; i++) {
        uv = fract(uv * 1.5) - 0.5;
        
        float d = length(uv) * exp(-length(uv0));

        vec3 col = palette(length(uv0) + i * 0.4 + time * 0.4);

        d = sin(d * 8.0 + time) / 8.0;
        d = abs(d);

        d = pow(0.01 / d, 1.2);

        color += col * d;
    }
    finalColor = vec4(color, 1.0);
}