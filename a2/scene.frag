uniform vec3 CameraPos;

uniform vec3 Ambient;
uniform vec3 Diffuse;
uniform vec3 Specular;
uniform float Shininess;

uniform int HasDiffuseMap;
uniform sampler2D DiffuseMap;

in vec2 fTexCoord;
in vec3 fragment_color;
out vec4 FragColor;
out vec3 normal;

in vec3 normalInterp;
in vec3 vertPos;

in vec4 shadowMapCoord;
uniform sampler2DShadow ShadowMap;

void main()
{
    // TODO: Replace with Phong shading
    //adapt from whikepidia
    float visibility = textureProj(ShadowMap, shadowMapCoord);

    vec3 normal = normalize(normalInterp);
    vec3 lightDir = normalize(CameraPos - vertPos);
    float lambertian = max(dot(lightDir,normal), 0.0);
    float specular = 0.0;
    vec3 viewDir = normalize(-vertPos);

    // this is blinn phong
    vec3 halfDir = normalize(lightDir + viewDir);
    float specAngle = max(dot(halfDir, normal), 0.0);
    specular = pow(specAngle, Shininess);

    vec3 diffuseMap = Diffuse;
   // vec3 Diffuse = texture(DiffuseMap, fTexCoord).rgb;
    if (HasDiffuseMap != 0)
        diffuseMap = Diffuse * texture(DiffuseMap, fTexCoord).rgb;

    vec3 color = vec3(0.0f) +lambertian * diffuseMap +specular * Specular;

    FragColor = vec4(color * visibility, 1.0);

    //FragColor = vec4(color, 1);

}


