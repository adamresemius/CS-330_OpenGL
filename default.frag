#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D tex0;
uniform vec3 lightPos1; // Position of the key light
uniform vec3 lightPos2; // Position of the fill light
uniform vec3 lightColor1; // Color of the key light (e.g., greenish color)
uniform float lightIntensity1; // Intensity of the key light (e.g., 100%)
uniform float lightIntensity2; // Intensity of the fill light (e.g., 10%)

void main()
{
    // Calculate the lighting
    vec3 ambient = vec3(0.2f); // Ambient light color
    vec3 lightDir1 = normalize(lightPos1 - FragPos);
    vec3 lightDir2 = normalize(lightPos2 - FragPos);
    float diff1 = max(dot(Normal, lightDir1), 0.0);
    float diff2 = max(dot(Normal, lightDir2), 0.0);
    vec3 diffuse = lightIntensity1 * lightColor1 * diff1 + lightIntensity2 * vec3(1.0, 1.0, 1.0) * diff2;

    // Calculate final color by combining ambient and diffuse lighting with the texture
    vec4 texColor = texture(tex0, TexCoord);
    vec3 result = (ambient + diffuse) * texColor.rgb;

    FragColor = vec4(result, texColor.a);
}
