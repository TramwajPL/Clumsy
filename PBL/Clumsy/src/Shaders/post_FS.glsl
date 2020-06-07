 #version 330 core
    in  vec2  TexCoords;
    out vec4  color;

    uniform sampler2D scene;
    uniform vec2      offsets[9];
    uniform int       edge_kernel[9];
    uniform float     blur_kernel[9];

    uniform bool reverse;
    uniform bool shake;
    uniform bool blur;

    void main()
    {
        color =  texture(scene, TexCoords);
        
        // gamma correction
        float gamma = 2.2;
        color.rgb = pow(color.rgb, vec3(1.0/2.2));
        color = vec4(color.rgb, 1.0);

        if(reverse)
        {
            color = vec4(1.0 - texture(scene, TexCoords).rgb, 1.0);
        }
    }