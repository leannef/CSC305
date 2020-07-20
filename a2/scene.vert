layout(location = SCENE_POSITION_ATTRIB_LOCATION)
in vec4 Position;

layout(location = SCENE_TEXCOORD_ATTRIB_LOCATION)
in vec2 TexCoord;

layout(location = SCENE_NORMAL_ATTRIB_LOCATION)
in vec3 Normal;

out vec3 fragment_color;
out vec2 fTexCoord;
out vec3 normalInterp;
out vec3 vertPos;

uniform mat4 ModelWorld;
uniform mat4 ModelViewProjection;
uniform mat3 Normal_ModelWorld;

uniform mat4 lightMatrix;
out vec4 shadowMapCoord;

void main()
{

    // TODO: Set to MVP * P
    //gl_Position = vec4(0,0,0,1);
    gl_Position = ModelViewProjection * Position;
    //fragment_color = vec3(1,1,1);

    // TODO: Pass vertex attributes to fragment shader
    //fragment_color = vec3(1,1,1);
    fTexCoord = TexCoord;

    vec4 position = ModelWorld * Position;
    vertPos = vec3(position)/ position.w;
    normalInterp = Normal_ModelWorld * Normal;

    shadowMapCoord = lightMatrix * Position;

}
