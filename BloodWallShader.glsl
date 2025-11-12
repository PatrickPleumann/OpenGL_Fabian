#version 330 core

out vec4 fragColor;

in vec4 color;
in vec2 uvs;
in vec3 vertexPos;
in mat3 TBN;

vec3 normal;
float metallic = 0.36;
float smoothness = 0.44;
float powFloat = 0.34;
float speed = 6;
float pulseMin = -0.25;
float pulseMax = 0.25;
float pulseStrengthMin = 1 / 3;
float pulseStrengthMax = 1 / 7;


uniform vec4 lightColor = {1.0f,1.0f,1.0f,1.0f};
uniform vec3 lightPos = {10.0, 5.0, 10.0};
uniform vec3 viewPos;

uniform sampler2D cracksTexture;
uniform sampler2D normalTexture;

uniform float time;
uniform float pulsatingSpeed = 5.0;

const vec2 size = vec2(2.0,0.0);
const ivec3 off = ivec3(-1,0,1) ;
vec4 baseWallColor = vec4(0.372549, 0.345098, 0.3058823, 1.0);

vec4 getheightFromCracks(vec4 _wave, float _sinTime)
{
    float s11 = _wave.x;
    float s01 = textureOffset(cracksTexture, uvs, off.xy).x * mix(pulseMin, pulseMax, _sinTime);
    float s21 = textureOffset(cracksTexture, uvs, off.zy).x * mix(pulseMin, pulseMax, _sinTime);
    float s10 = textureOffset(cracksTexture, uvs, off.yx).x * mix(pulseMin, pulseMax, _sinTime);
    float s12 = textureOffset(cracksTexture, uvs, off.yz).x * mix(pulseMin, pulseMax, _sinTime);
	
    vec3 va = normalize(vec3(size.xy,s21-s01));
    vec3 vb = normalize(vec3(size.yx,s12-s10));
    vec4 bump = vec4(cross(va,vb), s11 );
	return bump;
}


void main()
{
	vec2 texScale = uvs * 10;
	vec4 cracksColor = texture(cracksTexture, texScale);
	float pulseTime = ((sin(time * pulsatingSpeed) * 0.5) + 0.5);
	vec4 heightFromCracks = getheightFromCracks(cracksColor, pulseTime) * mix(pulseStrengthMin, pulseStrengthMax, pulseTime);
	vec4 addedTextures = texture(normalTexture, texScale) + heightFromCracks;
	vec4 baseColor = pow(cracksColor, vec4(0.0,2.0,2.0,2.0));

	vec4 wallColor = baseColor * baseWallColor;

	vec4 smoothPulse = smoothstep(0.0, min(pulseTime, 0.8), cracksColor);
	vec4 pulseNormal = mix(heightFromCracks, addedTextures, smoothPulse);

	normal = pulseNormal.rgb;
	normal = normal * 2.0 - 1.0;   
	normal = normalize(TBN * normal);

	float ambientStrength = 0.3f;
	vec4 ambient = ambientStrength * lightColor;

	float diffuseStrength = 0.5;
	vec3 lightDir = normalize(lightPos - vertexPos);

	float diff = max(dot(lightDir, normal),0.0);
	vec4 diffuse = diffuseStrength * diff * lightColor;

	float specularStrength = 0.5;
	vec3 reflectDir = normalize(reflect(-lightDir, normal));
	vec3 viewDir = normalize(viewPos - vertexPos);

	float spec = pow(max(dot(viewDir, reflectDir),0.0f),64);

	vec4 specular = specularStrength * spec * lightColor;

	fragColor = (ambient + diffuse + specular) * wallColor;
}