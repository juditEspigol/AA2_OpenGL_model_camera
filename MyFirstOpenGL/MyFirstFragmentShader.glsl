#version 440 core

uniform vec2 windowSize;
uniform sampler2D textureSampler;

in vec2 uvsFragmentShader;
in vec4 normalsFragmentShader;

in vec4 primitivePosition;

uniform vec4 ambientColor; 
uniform int hasTexture;

vec4 color;

out vec4 fragColor;

void main() {
        
        if(hasTexture == 1)
        {
            vec2 adjustedTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);
            vec4 baseColor = texture(textureSampler, adjustedTexCoord);  

            vec3 sourceLight = vec3(0, 0, 1); 

            vec3 lineToLight = normalize(sourceLight - primitivePosition.xyz); 
            float sourceLightAngle = dot(lineToLight, normalsFragmentShader.xyz); 

            color =  vec4(baseColor.rgb, 1.0) * ambientColor; 
        }
        else if(hasTexture == 0)
        {
            color = ambientColor;
        }

        fragColor = color;

}
