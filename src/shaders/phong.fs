#version 330

in vec3 normalW;
in vec3 positionW;
in vec2 uv;

uniform vec3 lightDir;
uniform vec3 lightColor;

uniform vec3 eyePositionW;

uniform vec3 diffuse;
uniform vec3 ambient;
uniform vec3 specular;
uniform float shiness;

uniform bool useDiffuseMap;
uniform sampler2D diffuseMap;

out vec4 fragColor;

void main()
{
    vec3 n = normalize(normalW);
    vec3 l = normalize(-lightDir);
    vec3 v = normalize(eyePositionW - positionW);
    
    vec3 h = normalize(v + l);

    vec3 brdf_diffuse = useDiffuseMap ? texture(diffuseMap, uv).xyz : diffuse;
    vec3 brdf_phong = brdf_diffuse + specular * pow(max(0, dot(n, h)), shiness);

    float cos_factor = max(0, dot(l, n));
    vec3 Li = lightColor * cos_factor;

    vec3 color = Li * brdf_phong;
    color += ambient * brdf_diffuse;

    fragColor = vec4(color, 1);
}
