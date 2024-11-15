varying vec3 Normal;

void main(void)
{
    Normal = normalize(gl_NormalMatrix * gl_Normal);
    #ifdef __GLSL_CG_DATA_TYPES // Fix clipping for Nvidia and ATI
    gl_ClipVertex = gl_ModelViewMatrix * gl_Vertex;
    #endif
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}