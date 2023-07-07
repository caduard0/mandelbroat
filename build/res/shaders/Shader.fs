// Called for every rasterized "pixel"
#version 400 core

#define DISTANCE 2
#define ZOOM_OUT 5
#define ITERATIONS 50
#define PRECISION 500
#define EXPOSURE 4

uniform float accuracy;
uniform vec4 screenSize;

out vec4 FragColor;

vec4 GetValue(in float x,in float y) {
    vec2 c = vec2((x-screenSize.x)/accuracy + 0.25, (y-screenSize.y)/accuracy + 0);
    vec2 z = vec2(0.0, 0.0);

    float i = 0.0;

    for (i = 0; i < ITERATIONS; i++) {
        z = vec2(pow(z.x, 2) - pow(z.y, 2), 2*z.x*z.y) + c;

        if (sqrt(pow(z.x, 2) + pow(z.y, 2)) > 2){
            break;
        }
    }

    return vec4(i, i, i, 0)/(ITERATIONS+EXPOSURE);
}

void main() {
    FragColor = GetValue(gl_FragCoord.x, gl_FragCoord.y);
}