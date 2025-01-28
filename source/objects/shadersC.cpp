
#include "shadersC.hpp"

/* ------------------------------------------------------------------------------------- */
/* normal shaders */

const char* vertexSS = R"( 
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 P;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    P = vec3(model * vec4(aPos, 1.0));
	//normal = vec4(aNormal, 0.0f).xyz;
    normal = normalize(model * vec4(aNormal, 0.0f)).xyz;
} 
)";

const char* fragmentSSCombined = R"(
#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct LightDirectional {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct LightPoint {
	vec3 pos;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct LightSpotlight {
    vec3 pos;
    vec3 direction;
    float cutoff;
    float outerCutoff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 normal;
in vec3 P;

uniform Material material;

uniform LightDirectional lightD[4];
uniform LightSpotlight lightS[4];
uniform LightPoint lightP[4];

uniform int lightDCount;
uniform int lightSCount;
uniform int lightPCount;

uniform vec3 viewPos;

uniform vec3 fogColor;
uniform float fogDensity;

out vec4 FragColor;

vec3 lightdirectionalCalculate(LightDirectional light, vec3 N, vec3 V) {
    vec3 L = light.direction;
    vec3 R = reflect(-L, N);

    vec3 ambient = light.ambient * material.ambient; 
    vec3 diffuse = light.diffuse * max(dot(N, L), 0.0) * material.diffuse;
    vec3 specular = light.specular * pow(max(dot(V, R), 0.0), material.shininess) * material.specular;

    return ambient + diffuse + specular;
}

vec3 pointlightCalculate(LightPoint light, vec3 N, vec3 V) {
	vec3 L = normalize(light.pos - P);
	vec3 R = reflect(-L, N);
	
	vec3 d = light.pos - P;
    float dist = length(d);

	vec3 ambient = light.ambient * material.ambient; 
    vec3 diffuse = light.diffuse * max(dot(N, L), 0.0) * material.diffuse;
    vec3 specular = light.specular * pow(max(dot(V, R), 0.0), material.shininess) * material.specular;
    
    float attenuation = 1.0 / (light.constant + light.linear * dist + 
    		    light.quadratic * (dist * dist)); 
    ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation; 

    return ambient + diffuse + specular;
}

vec3 spotlightCalculate(LightSpotlight light, vec3 N, vec3 V) {
	vec3 L = normalize(light.pos - P);
	vec3 R = reflect(-L, N);
	
	float theta = dot(L, light.direction);
    float epsilon = light.cutoff - light.outerCutoff;
    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
	
	vec3 ambient = light.ambient * material.ambient; 
    vec3 diffuse = light.diffuse * max(dot(N, L), 0.0) * material.diffuse;
    vec3 specular = light.specular * pow(max(dot(V, R), 0.0), material.shininess) * material.specular;
	
	diffuse  *= intensity;
    specular *= intensity;
	
	return ambient + diffuse + specular;
}

void main()
{
    vec3 N = normalize(normal);
    vec3 V = normalize(viewPos - P);


	vec3 res = vec3(0.0f, 0.0f, 0.0f);
	for(int i = 0; i < lightDCount; ++i)
	{
		res += lightdirectionalCalculate(lightD[i], N, V);
	}
	for(int i = 0; i < lightSCount; ++i)
	{
		res += spotlightCalculate(lightS[i], N, V);
	}
	for(int i = 0; i < lightPCount; ++i)
	{
		res += pointlightCalculate(lightP[i], N, V);
	}
    res = min(res, 1.0f);    

	// calculate fog
	float fogFactor = 1.0f - exp(-fogDensity * length(viewPos - P));
    fogFactor = clamp(fogFactor, 0.0, 1.0);

	res = mix(res, fogColor, fogFactor);
    FragColor = vec4(res, 1.0);
}


)";


/* ------------------------------------------------------------------------------------- */
/* shaders for bezier sufrace */

/* BSS = Bezier Surface Source */

const char* vertexSBSS = R"(
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float u;
layout (location = 2) in float v;

uniform float time;

void main()
{
    vec3 point = aPos;
    float waveAmplitudeY = 0.2;
    float waveFrequencyY = 4.0;
    float waveSpeedY = 1.0;
    float displacementY = v * waveAmplitudeY * sin(waveFrequencyY * u + time * waveSpeedY);

    float waveAmplitudeZ = 0.45;
    float waveFrequencyZ = 6.0;
    float waveSpeedZ = 4.6;
    float displacementZ = u * waveAmplitudeZ * sin(waveFrequencyZ * u + time * waveSpeedZ)
        + 0.2 * u * cos(1.0 * v + time * 3.0);

    //point.x += displacementY;
    point.z += displacementZ;

    gl_Position = vec4(point, 1.0);
}
)";

const char* tesselacionControlSBSS = R"(
#version 460 core

// specify number of control points per patch output
// this value controls the size of the input and output arrays
layout (vertices = 16) out;

void main()
{
    // ----------------------------------------------------------------------
    // pass attributes through
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

    // ----------------------------------------------------------------------
    // invocation zero controls tessellation levels for the entire patch
    if (gl_InvocationID == 0)
    {
        gl_TessLevelOuter[0] = 16.0;
        gl_TessLevelOuter[1] = 16.0;
        gl_TessLevelOuter[2] = 16.0;
        gl_TessLevelOuter[3] = 16.0;

        gl_TessLevelInner[0] = 16.0;
        gl_TessLevelInner[1] = 16.0;
    }
}
)";

const char* tesselationEvaluationSBSS = R"(
#version 460 core

layout (quads, fractional_odd_spacing, ccw) in;

uniform mat4 model;           // the model matrix
uniform mat4 view;            // the view matrix
uniform mat4 projection;      // the projection matrix

out vec3 P;
out vec3 normal;

void main()
{
    // get patch coordinate
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

	// get bezier surface point location

    float Bu[4] = float[4](
        (1.0 - u) * (1.0 - u) * (1.0 - u), // B0(u)
        3.0 * u * (1.0 - u) * (1.0 - u),  // B1(u)
        3.0 * u * u * (1.0 - u),          // B2(u)
        u * u * u                         // B3(u)
    );

    float Bv[4] = float[4](
        (1.0 - v) * (1.0 - v) * (1.0 - v), // B0(v)
        3.0 * v * (1.0 - v) * (1.0 - v),  // B1(v)
        3.0 * v * v * (1.0 - v),          // B2(v)
        v * v * v                         // B3(v)
    );

    vec3 point = vec3(0.0);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            float weight = Bu[i] * Bv[j];
            point += weight * gl_in[i * 4 + j].gl_Position.xyz;
        }
    }

	// normal vector calculation

    float dBu[4] = float[4](
        -3.0 * (1.0 - u) * (1.0 - u),
        3.0 * (1.0 - u) * (1.0 - u) - 6.0 * u * (1.0 - u),
        6.0 * u * (1.0 - u) - 3.0 * u * u,
        3.0 * u * u
    );

    float dBv[4] = float[4](
        -3.0 * (1.0 - v) * (1.0 - v),
        3.0 * (1.0 - v) * (1.0 - v) - 6.0 * v * (1.0 - v),
        6.0 * v * (1.0 - v) - 3.0 * v * v,
        3.0 * v * v
    );

    vec3 dPdu = vec3(0.0);
    vec3 dPdv = vec3(0.0);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            float weightU = dBu[i] * Bv[j];
            float weightV = Bu[i] * dBv[j];
            vec3 controlPoint = gl_in[i * 4 + j].gl_Position.xyz;

            dPdu += weightU * controlPoint;
            dPdv += weightV * controlPoint;
        }
    }

    normal = normalize(cross(dPdu, dPdv));
	P = (model * vec4(point, 1.0f)).xyz;
    gl_Position = projection * view * model * vec4(point, 1.0f);
}
)";

const char* fragmentSBSS = R"(
#version 460 core

out vec4 FragColor;
in vec3 P;

void main()
{
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
)";


