#version 330 core
out vec4 fragColor;

in vec4 color;
in vec2 uvs;
in vec3 normal;
in vec3 vertexPos;

uniform vec4 lightColor = {1.0f,1.0f,1.0f,1.0f};
uniform vec3 lightPos = {10.0, 5.0, 10.0};
uniform vec3 viewPos;
uniform sampler2D baseColorTexture;

void main()
{
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

	fragColor = (ambient + diffuse + specular) * texture(baseColorTexture,uvs);
}